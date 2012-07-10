#pragma once
#include "ball/ball.h"

struct Axis_bind
{
	float* x, *y;
	Ball* ball;

	Axis_bind(Ball* b)
		:x(&(b->mPosition.x)), y(&(b->mPosition.y)), ball(b){}
	Axis_bind(float *val)
		:x(val), y(val), ball(0)
	{}
	bool operator == (Ball* b) const
	{
		return ball == b;
	}
	
};
bool Compare_axis_x (const Axis_bind& lhs, const Axis_bind& rhs);
bool Compare_axis_y (const Axis_bind& lhs, const Axis_bind& rhs);
typedef std::vector<Axis_bind> Axis_binds;
