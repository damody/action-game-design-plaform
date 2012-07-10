#pragma once
#include <vector>
#include <list>
#include "math/Quaternion.h"
#include "math/Vector3.h"
#include "common/utility.h"
#include "behavior.h"
#include "math/Polygon2D.h"


class Ball
{
public:
	enum BallStatus
	{
		FLY,
		STOP,
		DESTORY // if on this status, system will delete this ball
	};
	Vector3	mPosition;
	Vector3	mDirection;
	// Vector3	mUp;  // no use
	Polygon2D	mPolygon2D;
	float		mTimeRate;
	Behavior*	mpBehavior;
	BallStatus	mBallStatus;
	int		mCollisionMask;
public:
	VIRTUAL_GET_CLASS_SIZE(Behavior)
	inline Ball():mTimeRate(1), mCollisionMask(1)
	{
	}
	inline Ball(const Vector3 pos, const Vector3 dir, Behavior* behavior = NULL)
		:mTimeRate(1), mPosition(pos), mDirection(dir), mCollisionMask(1),
		//mUp(Vector3::NEGATIVE_UNIT_Z), 
		mpBehavior(behavior), mBallStatus(FLY)
	{
	}
	inline Ball(const Vector3 pos, float angle, Behavior* behavior = NULL)
		:mTimeRate(1), mPosition(pos), mDirection(Quaternion::GetRotation(pos, angle)), 
		//mUp(Vector3::NEGATIVE_UNIT_Z), 
		mpBehavior(behavior), mBallStatus(FLY), mCollisionMask(1)
	{
	}
	virtual int Update(float elapsedtime);
	bool HasBehavior();
	virtual ~Ball()
	{}
	Ball(const Ball& b)
	{
		*this = b;
	}
};
// TODO: typedef Ball* (*NewBallFunction)(void*);
typedef Ball* (*NewBallFunction)();
typedef std::vector<Ball> BallVector;
typedef std::list<Ball> BallList;
typedef std::vector<Ball*> BallptrVector;

