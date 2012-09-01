#include "AABB2D.h"

void AABB2D::AddPoint( const Vector2& p )
{
	if (p.x > m_Max.x)
		m_Max.x = p.x;
	else if (p.x < m_Min.x)
		m_Min.x = p.x;
	if (p.y > m_Max.y)
		m_Max.y = p.y;
	else if (p.y < m_Min.y)
		m_Min.y = p.y;
}

void AABB2D::Larger( float val )
{
	m_Min.x -= val;
	m_Min.y -= val;
	m_Max.x += val;
	m_Max.y += val;
}

void AABB2D::SetBounding( float left, float right, float top, float down )
{
	m_Min.x = left;
	m_Min.y = top;
	m_Max.x = right;
	m_Max.y = down;
}

bool AABB2D::IsContain( const AABB2D& rhs )
{
	if (m_Min.x <= rhs.m_Min.x &&
		m_Min.y <= rhs.m_Min.y &&
		m_Max.x >= rhs.m_Max.x &&
		m_Max.y >= rhs.m_Max.y)
	{
		return true;
	}
	return false;
}

bool Collision( const AABB2D& lhs, const AABB2D& rhs )
{
	if (lhs.m_Min.x < rhs.m_Min.x && lhs.m_Max.x > rhs.m_Min.x)
	{
		if (lhs.m_Min.y < rhs.m_Min.y && lhs.m_Max.y > rhs.m_Min.y)
			return true;
		if (lhs.m_Min.y < rhs.m_Max.y && lhs.m_Max.y > rhs.m_Max.y)
			return true;
	}
	if (lhs.m_Min.x < rhs.m_Max.x && lhs.m_Max.x > rhs.m_Max.x)
	{
		if (lhs.m_Min.y < rhs.m_Min.y && lhs.m_Max.y > rhs.m_Min.y)
			return true;
		if (lhs.m_Min.y < rhs.m_Max.y && lhs.m_Max.y > rhs.m_Max.y)
			return true;
	}
}

bool AABB2D::IsCollision( const AABB2D& rhs )
{
	if (Collision(*this, rhs) || Collision(rhs, *this))
		return true;
}
