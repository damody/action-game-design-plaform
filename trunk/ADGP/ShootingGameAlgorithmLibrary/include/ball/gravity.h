#pragma once
#include "ball.h"
#include "behavior.h"
#include "math\Vector3.h"

class Gravity : public Behavior
{
public:
	Vector3	mVelocity;
	Vector3	mForce;
	Vector3	mGravity;
	GET_CLASS_SIZE(Gravity)
	inline Gravity()
	{m_typehash = strhasher("Gravity");}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Gravity()
	{}
};