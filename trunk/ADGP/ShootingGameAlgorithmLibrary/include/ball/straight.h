#pragma once
#include "ball.h"
#include "behavior.h"
#include "math\Vector3.h"

class Straight : public Behavior
{
public:
	float	mVelocity;
	GET_CLASS_SIZE(Straight)
	inline Straight()
	{m_typehash = strhasher("Straight");}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Straight()
	{}
};


