#include "BallManager.h"

void BallManager::SetNumThreads( int i )
{
	if (i<=0) i=1;
	if (i>SGA_MAX_THREADS) i=SGA_MAX_THREADS;
}

void BallManager::AddTrajectory( Trajectory* t )
{
	mTrajectoryRawPtrs.push_back(t);
}

#if (SGA_USE_MUTITHREAD > 0)

BallManager::BallManager( int _mNumThreads/*=1*/ ) :mNumThreads(_mNumThreads), mOver(false)
{
	memset(mThreadsWork, 0, sizeof(mThreadsWork));
	if (mNumThreads>1)
	{
		for (int i=0;i<mNumThreads;i++)
		{
			mThreadsWork[i] = new work_info;
			mThreadgroup.create_thread(
				boost::bind(&BallManager::MutiThreadUpdate, boost::ref(*this), i));
		}
	}
}

BallManager::~BallManager()
{
	mOver = true;
	mThreadgroup.join_all();
	for (int i=0;i<SGA_MAX_THREADS;i++)
	{
		if (mThreadsWork[i])
			delete mThreadsWork[i];
	}
}


void BallManager::MutiThreadUpdate( int i )
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
				BallVector& bv = *(info.works[nw].bv);
				size_t bsize = bv.size();
				for (size_t i=info.works[nw].begin;i < info.works[nw].end;i++)
				{
					bv[i].Update(info.time);
				}
			}
			info.work_done = true;
		}
	}
}

void BallManager::Update( float time )
{
	Trajectory_RawPtrs::iterator it = mTrajectoryRawPtrs.begin();
	if (mNumThreads>1)
	{
		for (int i=0;i<mNumThreads;i++)
		{
			LOCK l(mThreadsWork[i]->m); // 鎖住並清除工作
			mThreadsWork[i]->works.clear();
		}
		for (;it != mTrajectoryRawPtrs.end();it++)
		{
			BallVector& bv = (*it)->GetBallVector();
			double step = bv.size()/(double)mNumThreads;
			double now_step = 0;
			for (int i=0;i<mNumThreads;i++)
			{
				LOCK l(mThreadsWork[i]->m); //鎖住並更新
				if (mThreadsWork[i]->work_done)
				{
					if ((int)now_step == bv.size())
						break;
					mThreadsWork[i]->work_done = false;
					mThreadsWork[i]->time = time;
					work w;
					w.bv = &bv;
					w.begin = (int)now_step;
					now_step += step;
					if ((size_t)now_step >= bv.size())
						now_step = (double)bv.size();
					w.end = (int)now_step;
					mThreadsWork[i]->works.push_back(w);
				}
			}
		}
	}
	else
	{
		for (;it != mTrajectoryRawPtrs.end();it++)
		{
			BallVector& bv = (*it)->GetBallVector();
			size_t bsize = bv.size();
			for (size_t i=0;i < bsize;i++)
			{
				bv[i].Update(time);
			}
		}
	}
}

#else

void BallManager::Update( float time )
{
	TrajectoryRawPtrs::iterator it = mTrajectoryRawPtrs.begin();
	for (;it != mTrajectoryRawPtrs.end();it++)
	{
		BallVector& bv = (**it).GetBallVector();
		size_t bsize = bv.size();
		for (size_t i=0;i < bsize;i++)
		{
			bv[i].Update(time);
		}
	}
}


#endif
