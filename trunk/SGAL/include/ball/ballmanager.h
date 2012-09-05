#pragma once
#include "common/SGA_config.h"
#include "ball/ball.h"
#include "Trajectory.h"
#include "common/shared_ptr.h"

class BallManager
{
private:
	int		mNumThreads;
	Trajectory_RawPtrs mTrajectoryRawPtrs;
#if (SGA_USE_MUTITHREAD > 0)
	boost::thread_group mThreadgroup;
	struct work
	{
		BallVector* bv;
		size_t	begin;
		size_t	end;
	};
	struct work_info
	{
		work_info(): work_done( true )
		{}
		MUTEX	m;
		std::vector<work> works;
		float	time;
		bool	work_done;
	};
	SHARE_PTR( work_info )
	work_info* mThreadsWork[SGA_MAX_THREADS];
	bool mOver;
#endif
public:
#if (SGA_USE_MUTITHREAD > 0)
	BallManager( int _mNumThreads = 1 );
	~BallManager();
#else
	BallManager( int _mNumThreads = 1 )
		: mNumThreads( _mNumThreads )
	{
	}
#endif
	void SetNumThreads( int i );
	void AddTrajectory( Trajectory* t );
	void Update( float time );
#if (SGA_USE_MUTITHREAD > 0)
	void MutiThreadUpdate( int i );
#endif
};

