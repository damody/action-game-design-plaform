#pragma once
#include "ball.h"
#include "behavior.h"
#include "math\Vector3.h"

class Split : public Behavior
{
public:
	float	mVelocity;
	float	mAngle;
	float	mMaxAngle;
	float	mOAngle;
	GET_CLASS_SIZE(Split)
	inline Split()
	{m_typehash = strhasher("Split");}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Split()
	{}
};