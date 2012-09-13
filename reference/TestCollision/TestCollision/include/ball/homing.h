#pragma once
#include "ball.h"
#include "behavior.h"
#include "math\Vector3.h"
#include <boost/function.hpp>

class Homing : public Behavior
{	
public:
	float	mVelocity;
	boost::function<Vector3()> GetEnemyPos;
	GET_CLASS_SIZE(Homing)
	inline Homing()
	{m_typehash = strhasher("Homing");}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Homing()
	{}
};