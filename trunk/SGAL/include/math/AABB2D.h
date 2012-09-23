#pragma once
#include "Vector2.h"

class AABB2D
{
public:
	/*AABB2D( const Polygon2D& poly )
	{
		m_Min = m_Max = poly.const_Points().front();

		for ( size_t i = 1; i < poly.const_Points().size(); i++ )
		{
			AddPoint( poly.const_Points()[i] );
		}
	}*/
	void AddPoint( const Vector2& p );
	AABB2D() {}
	AABB2D( const Vector2& orgin )
		: m_Min( orgin ), m_Max( orgin )
	{}
	void ReBuild( const Vec2s& vec2s )
	{
		m_Min = m_Max = vec2s.front();

		for ( size_t i = 1; i < vec2s.size(); i++ )
		{
			AddPoint( vec2s[i] );
		}
	}
	void Larger( float val );
	void SetBounding( float left, float right, float top, float down );
	bool IsContain( const AABB2D& rhs );
	bool IsCollision( const AABB2D& rhs );
	Vector2 m_Min, m_Max;
};
bool Collision( const AABB2D& lhs, const AABB2D& rhs );