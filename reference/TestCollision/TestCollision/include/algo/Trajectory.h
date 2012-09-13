#pragma once
#include "math\Vector3.h"
#include "math\Quaternion.h"
#include "ball/ball.h"
#include "ball/behavior.h"
#include "common/shared_ptr.h"

class Trajectory
{
public:
	int		mNumTrajectory;
	float		mInitializeTime;
	Behavior*	mBehavior;
	NewBallFunction mNewBallFunction;
	Polygon2D	mPolygon;
	int& NumTrajectory()
	{
		mNeedUpdate = true;
		return mNumTrajectory;
	}
	Vector3&	Position()
	{
		mNeedUpdate = true;
		return mPosition;
	}
	void SetAngle( float a )
	{
		mNeedUpdate = true;
		mDirection = Quaternion::GetRotation( Vector3::ZERO, a );
	}
	Vector3&	Direction()
	{
		mNeedUpdate = true;
		return mDirection;
	}
	Vector3&	Up()
	{
		mNeedUpdate = true;
		return mUp;
	}
protected:
	Vector3	mPosition;
	Vector3	mDirection;
	float		mAngle;
	Vector3	mUp;
public:
	Trajectory( int _mNumTrajectory, Vector3 _mPosition, Vector3 _mDirection, NewBallFunction _mNewBallFunction = NULL )
		: mNumTrajectory( _mNumTrajectory ), mPosition( _mPosition ), mDirection( _mDirection ),
		  mInitializeTime( 0 ), mUp( Vector3::NEGATIVE_UNIT_Z ), mBehavior( 0 ), mNeedUpdate( false ), mNewBallFunction( _mNewBallFunction )
	{}
	virtual ~Trajectory()
	{}
	virtual void OutputBall( BallptrVector& out, NewBallFunction bf = NULL )
	{
		CheckModify();

		if ( bf ) // test not NULL
		{
			bf;        // nothing
		}
		else if ( mNewBallFunction ) // test not NULL
		{
			bf = mNewBallFunction;
		}
		else // or retuen
		{
			assert( bf );
			return ;
		}

		for ( BallVector::iterator it = mBall_PreComptue.begin();
		                it != mBall_PreComptue.end(); it++ )
		{
			Ball* b = bf();
			*b = *it;
			out.push_back( b );
		}
	}
	virtual void OutputBall( BallList& out )
	{
		CheckModify();
		std::copy( mBall_PreComptue.begin(), mBall_PreComptue.end(), out.end() );
	}
	virtual void OutputBall( BallVector& out )
	{
		CheckModify();
		std::copy( mBall_PreComptue.begin(), mBall_PreComptue.end(), out.end() );
	}
	virtual BallptrVector NewBallptrVector( NewBallFunction bf = NULL )
	{
		CheckModify();
		BallptrVector bv;

		if ( bf ) // test not NULL
		{
			bf;        // nothing
		}
		else if ( mNewBallFunction ) // test not NULL
		{
			bf = mNewBallFunction;
		}
		else // or retuen
		{
			assert( bf );
			return bv;
		}

		for ( BallVector::iterator it = mBall_PreComptue.begin();
		                it != mBall_PreComptue.end(); it++ )
		{
			Ball* b = bf();
			*b = *it;
			bv.push_back( b );
		}

		return bv;
	}
	virtual BallList NewBallList()
	{
		CheckModify();
		return BallList( mBall_PreComptue.begin(), mBall_PreComptue.end() );
	}
	virtual BallVector NewBallVector()
	{
		CheckModify();
		return mBall_PreComptue;
	}
	virtual BallVector& GetBallVector()
	{
		CheckModify();
		return mBall_PreComptue;
	}
	virtual void SetBehavior( Behavior* b )
	{
		mBehavior = b;
		mNeedUpdate = true;
		CheckModify();
	}
protected:
	BallVector	mBall_PreComptue;
	bool		mNeedUpdate;
	virtual void CheckModify()
	{
		if ( mNeedUpdate )
		{
			mDirection.normalise();
			mAngle = Radian( mDirection.x, mDirection.y ).valueDegrees();
			Modifyed();
			mNeedUpdate = false;
		}
	}
	virtual void Modifyed() = 0;
};
SHARE_PTR( Trajectory )
