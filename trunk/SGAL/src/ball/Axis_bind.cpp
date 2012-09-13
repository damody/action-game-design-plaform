#include "ball/Axis_bind.h"


bool operator<( const Axis_bind<Ball*>& lhs, float rhs )
{
	return *lhs.x < rhs;
}

bool operator<( float lhs, const Axis_bind<Ball*>& rhs )
{
	return lhs < *rhs.x;
}

