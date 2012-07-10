#pragma once
#include "common/SGA_config.h"
#include "common/shared_ptr.h"
#include "algo/Trajectory.h"
#include "math/Polygon2D.h"
#include "ball/Axis_bind.h"

// for sort
typedef bool (*CompareBall)(const Ball* lhs, const Ball* rhs);

class BallptrManager
{
public:
	BallptrVector	mDeleteVector;
private:
	BallptrVector	mBallptrVector;
	int		mNumThreads;
	bool		mKdtreeBuild;
	boost::thread_group mThreadgroup;
	struct work
	{
		BallptrVector* bv;
		size_t	begin;
		size_t	end;
	};
	struct work_info
	{
		work_info():work_done(true)
		{}
		MUTEX	m;
		std::vector<work> works;
		float	time;
		bool	work_done;
	};
	SHARE_PTR(work_info);
	work_info* mThreadsWork[SGA_MAX_THREADS];
	bool mOver;
	Axis_binds mXbinds, mYbinds;
public:
	BallptrManager( int _mNumThreads = 1 );
	~BallptrManager();
	bool Empty();
	const BallptrVector& Ballptrs();
	void MutiThreadUpdate( int i );
	void Update( float time );
	void SetNumThreads( int i );
	void Sort(CompareBall fun_cb);
	BallptrVector GetCollision( Polygon2D& poly, int collisionMask = 0xffffffff);
	void SortCollision();
	void AddBallptr( Ball* b )
	{
		assert(!b->mPolygon2D.Points().empty());
		mBallptrVector.push_back(b);
		mXbinds.push_back(Axis_bind(mBallptrVector.back()));
	}
	void AddBallptrs( const BallptrVector& bv )
	{
		for (BallptrVector::const_iterator it = bv.begin();
			it != bv.end(); ++it)
		{
			assert(!(*it)->mPolygon2D.Points().empty());
			mBallptrVector.push_back(*it);
			mXbinds.push_back(Axis_bind(mBallptrVector.back()));
		}
	}
};
