#include "AABB2D.h"

void AABB2D::AddPoint( const Vec2& p )
{
	if (p.x > mMax.x)
		mMax.x = p.x;
	else if (p.x < mMin.x)
		mMin.x = p.x;
	if (p.y > mMax.y)
		mMax.y = p.y;
	else if (p.y < mMin.y)
		mMin.y = p.y;
}

void AABB2D::Larger( float val )
{
	mMin.x -= val;
	mMin.y -= val;
	mMax.x += val;
	mMax.y += val;
}

void AABB2D::SetBounding( float left, float right, float top, float down )
{
	mMin.x = left;
	mMin.y = top;
	mMax.x = right;
	mMax.y = down;
}

bool AABB2D::IsContain( const AABB2D& rhs )
{
	if (mMin.x <= rhs.mMin.x &&
		mMin.y <= rhs.mMin.y &&
		mMax.x >= rhs.mMax.x &&
		mMax.y >= rhs.mMax.y)
	{
		return true;
	}
	return false;
}

bool Collision( const AABB2D& lhs, const AABB2D& rhs )
{
	if (lhs.mMin.x < rhs.mMin.x && lhs.mMax.x > rhs.mMin.x)
	{
		if (lhs.mMin.y < rhs.mMin.y && lhs.mMax.y > rhs.mMin.y)
			return true;
		if (lhs.mMin.y < rhs.mMax.y && lhs.mMax.y > rhs.mMax.y)
			return true;
	}
	if (lhs.mMin.x < rhs.mMax.x && lhs.mMax.x > rhs.mMax.x)
	{
		if (lhs.mMin.y < rhs.mMin.y && lhs.mMax.y > rhs.mMin.y)
			return true;
		if (lhs.mMin.y < rhs.mMax.y && lhs.mMax.y > rhs.mMax.y)
			return true;
	}
}

bool AABB2D::IsCollision( const AABB2D& rhs )
{
	if (Collision(*this, rhs) || Collision(rhs, *this))
		return true;
}
