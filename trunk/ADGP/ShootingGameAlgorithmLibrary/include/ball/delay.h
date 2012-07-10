#pragma once
#include "ball.h"
#include "behavior.h"
#include "math\Vector3.h"

class Delay : public Behavior
{
public:
	float mElapsedTime;
	float mLaunchTime;
	float mVelocity;
	GET_CLASS_SIZE(Delay)
	inline Delay()
	{m_typehash = strhasher("Delay");}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Delay()
	{}
};
