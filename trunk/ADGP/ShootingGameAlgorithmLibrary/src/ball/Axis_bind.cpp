#include "ball/Axis_bind.h"

bool operator<( const Axis_bind& lhs, float rhs )
{
	return *lhs.x < rhs;
}

bool operator<( float lhs, const Axis_bind& rhs )
{
	return lhs < *rhs.x;
}

bool Compare_axis_x( const Axis_bind& lhs, const Axis_bind& rhs )
{
	return *lhs.x < *rhs.x;
}

bool Compare_axis_y( const Axis_bind& lhs, const Axis_bind& rhs )
{
	return *lhs.y < *rhs.y;
}
