#include "BallptrManager.h"
#include "math/AABB2D.h"

BallptrManager::BallptrManager( int _mNumThreads /*= 1 */ ) :mNumThreads(_mNumThreads), mOver(false)
{
	memset(mThreadsWork, 0, sizeof(mThreadsWork));
	if (mNumThreads>1)
	{
		for (int i=0;i<mNumThreads;i++)
		{
			mThreadsWork[i] = new work_info;
			mThreadgroup.create_thread(
				boost::bind(&BallptrManager::MutiThreadUpdate, boost::ref(*this), i));
		}
	}
}

BallptrManager::~BallptrManager()
{
	mOver = true;
	mThreadgroup.join_all();
	for (int i=0;i<SGA_MAX_THREADS;i++)
	{
		if (mThreadsWork[i])
			delete mThreadsWork[i];
	}
}

void BallptrManager::SetNumThreads( int i )
{
	if (i<=0) i=1;
	if (i>SGA_MAX_THREADS) i=SGA_MAX_THREADS;
	mNumThreads = i;
	mOver = true;
	mThreadgroup.join_all();
	memset(mThreadsWork, 0, sizeof(mThreadsWork));
	if (mNumThreads>1)
	{
		for (int i=0;i<mNumThreads;i++)
		{
			mThreadsWork[i] = new work_info;
			mThreadgroup.create_thread(
				boost::bind(&BallptrManager::MutiThreadUpdate, boost::ref(*this), i));
		}
	}
}

void BallptrManager::MutiThreadUpdate( int i )
{
	for (;!mOver;) // 程式還沒結束
	{
		work_info& info = *mThreadsWork[i];
		if (!info.work_done) // 要工作了
		{
			LOCK l(info.m); //鎖
			size_t numwork = info.works.size();
			for (size_t nw=0;nw<numwork;nw++)
			{
				BallptrVector& bv = *(info.works[nw].bv);
				size_t bsize = bv.size();
				for (size_t i=info.works[nw].begin;i < info.works[nw].end;i++)
				{
					if (i < bv.size())
					{
						bv[i]->Update(info.time);
						if (bv[i]->mBallStatus == Ball::DESTORY)
						{
							mDeleteVector.push_back(bv[i]);
							mBallptrVector.erase(mBallptrVector.begin()+i);
							i--;
						}
					}
				}
			}
			info.work_done = true;
		}
	}
}

void BallptrManager::Update( float time )
{
	mKdtreeBuild = false;
	if (mNumThreads>1)
	{
		for (int i=0;i<mNumThreads;i++)
		{
			LOCK l(mThreadsWork[i]->m); // 鎖住並清除工作
			mThreadsWork[i]->works.clear();
		}
		double step = mBallptrVector.size()/(double)mNumThreads;
		double now_step = 0;
		for (int i=0;i<mNumThreads;i++)
		{
			LOCK l(mThreadsWork[i]->m); //鎖住並更新
			if (mThreadsWork[i]->work_done)
			{
				if ((int)now_step == mBallptrVector.size())
					break;
				mThreadsWork[i]->work_done = false;
				mThreadsWork[i]->time = time;
				work w;
				w.bv = &mBallptrVector;
				w.begin = (int)now_step;
				now_step += step;
				if ((size_t)now_step >= mBallptrVector.size())
					now_step = (double)mBallptrVector.size();
				w.end = (int)now_step;
				mThreadsWork[i]->works.push_back(w);
			}
		}
	}
	else
	{
		size_t bsize = mBallptrVector.size();
		for (size_t i=0;i < bsize;i++)
		{
			if (mBallptrVector[i]->mBallStatus == Ball::FLY)
				mBallptrVector[i]->Update(time);
			if (mBallptrVector[i]->mBallStatus == Ball::DESTORY)
			{
				mDeleteVector.push_back(mBallptrVector[i]);
				mBallptrVector.erase(mBallptrVector.begin()+i);
				i--;
				bsize--;
			}
		}
		// TODO: it's can faster
		bsize = mDeleteVector.size();
		for (int ix = 0;ix < (int)mXbinds.size();++ix)
		{
			for (size_t i=0;i < bsize;i++)
			{
				if (mXbinds[ix] == mDeleteVector[i])
				{
					mXbinds.erase(mXbinds.begin()+ix);
					if (ix-1>=0) ix--;
				}
			}
		}
		for (int iy = 0;iy < (int)mYbinds.size();++iy)
		{
			for (size_t i=0;i < bsize;i++)
			{
				if (mYbinds[iy] == mDeleteVector[i])
				{
					mYbinds.erase(mYbinds.begin()+iy);
					if (iy-1>=0) iy--;
				}
			}
		}
	}
}

void BallptrManager::Sort( CompareBall fun_cb )
{
	std::sort(mBallptrVector.begin(), mBallptrVector.end(), fun_cb);
}

bool BallptrManager::Empty()
{
	return mBallptrVector.empty();
}

const BallptrVector& BallptrManager::Ballptrs()
{
	return mBallptrVector;
}

void BallptrManager::SortCollision()
{
	std::sort(mXbinds.begin(), mXbinds.end(), Compare_axis_x);
}

template<class _Ty>
struct axis_y_greater
	: public std::binary_function<_Ty, _Ty, bool>
{	// functor for operator>
	bool operator()(const _Ty& _Left, const _Ty& _Right) const
	{	// apply operator> to operands
		return *_Left.y > *_Right.y;
	}
};

template<class _Ty>
struct axis_y_less
	: public std::binary_function<_Ty, _Ty, bool>
{	// functor for operator>
	bool operator()(const _Ty& _Left, const _Ty& _Right) const
	{	// apply operator> to operands
		return *_Left.y < *_Right.y;
	}
};

BallptrVector BallptrManager::GetCollision( Polygon2D& poly, int collisionMask )
{
 	BallptrVector res;
	if (mBallptrVector.empty())
		return res;
	poly.CheckBuildEdges(); // important
	
	AABB2D aabb(poly);
	aabb.Larger(50);
	Axis_binds::iterator x_index_max, x_index_min, tmp;
 	x_index_max = std::upper_bound(mXbinds.begin(), mXbinds.end(), Axis_bind(&aabb.m_Max.x), Compare_axis_x);
	x_index_min = std::lower_bound(mXbinds.begin(), mXbinds.end(), Axis_bind(&aabb.m_Min.x), Compare_axis_x);
	if (x_index_max-x_index_min > 0)
	{
		mYbinds.clear();
		std::copy(x_index_min, x_index_max, std::back_inserter(mYbinds));
		tmp = std::partition(mYbinds.begin(), mYbinds.end(),         // range
			std::bind2nd(axis_y_greater<Axis_bind>(), Axis_bind(&aabb.m_Min.y)));   // criterion
		tmp = std::partition(mYbinds.begin(), tmp,       // range
			std::bind2nd(axis_y_less<Axis_bind>(), Axis_bind(&aabb.m_Max.y)));
		if (tmp - mYbinds.begin()>0)
		for (Axis_binds::iterator it = mYbinds.begin();it != tmp;it++)
		{
			if (it->ball->mCollisionMask & collisionMask)
				if (it->ball->mPolygon2D.IsCollision(poly))
					res.push_back(it->ball);
		}
	}
	/*
	size_t bsize = mBallptrVector.size();
	for (size_t i=0;i < bsize;i++)
	{
		if (mBallptrVector[i]->mCollisionMask & collisionMask)
			if (mBallptrVector[i]->mPolygon2D.IsCollision(poly))
				res.push_back(mBallptrVector[i]);
	}
	*/
	return res;
}
