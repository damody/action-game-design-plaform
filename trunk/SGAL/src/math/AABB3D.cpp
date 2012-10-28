#include "AABB3D.h"
#include "Polygon2D.h"

void AABB3D::AddPoint( const Vector2& p )
{
	if ( p.x > m_Max.x )
	{
		m_Max.x = p.x;
	}
	else if ( p.x < m_Min.x )
	{
		m_Min.x = p.x;
	}

	if ( p.y > m_Max.y )
	{
		m_Max.y = p.y;
	}
	else if ( p.y < m_Min.y )
	{
		m_Min.y = p.y;
	}

	m_Len.x = std::abs(m_Max.x - m_Min.x);
	m_Len.y = std::abs(m_Max.y - m_Min.y);
}

void AABB3D::Larger( float val )
{
	m_Min.x -= val;
	m_Min.y -= val;
	m_Min.z -= val;
	m_Max.x += val;
	m_Max.y += val;
	m_Max.z += val;

	m_Len.x = std::abs(m_Max.x - m_Min.x);
	m_Len.y = std::abs(m_Max.y - m_Min.y);
	m_Len.z = std::abs(m_Max.z - m_Min.z);
}

void AABB3D::Larger( float x, float y, float z )
{
	m_Min.x -= x;
	m_Min.y -= y;
	m_Min.z -= z;
	m_Max.x += x;
	m_Max.y += y;
	m_Max.z += z;

	m_Len.x = std::abs(m_Max.x - m_Min.x);
	m_Len.y = std::abs(m_Max.y - m_Min.y);
	m_Len.z = std::abs(m_Max.z - m_Min.z);
}

void AABB3D::SetBounding( float left, float right, float top, float down, float front, float back )
{
	m_Min.x = left;
	m_Min.y = top;
	m_Min.z = front;
	m_Max.x = right;
	m_Max.y = down;
	m_Max.z = back;

	m_Len.x = std::abs(m_Max.x - m_Min.x);
	m_Len.y = std::abs(m_Max.y - m_Min.y);
	m_Len.z = std::abs(m_Max.z - m_Min.z);
}

void AABB3D::SetBounding( float value )
{
	m_Min.x = value;
	m_Min.y = value;
	m_Min.z = value;
	m_Max.x = value;
	m_Max.y = value;
	m_Max.z = value;

	m_Len.x = std::abs(m_Max.x - m_Min.x);
	m_Len.y = std::abs(m_Max.y - m_Min.y);
	m_Len.z = std::abs(m_Max.z - m_Min.z);
}

bool AABB3D::IsContain( const AABB3D& rhs )
{
	if ( m_Min.x <= rhs.m_Min.x &&
		m_Min.y <= rhs.m_Min.y &&
		m_Min.z <= rhs.m_Min.z &&
		m_Max.x >= rhs.m_Max.x &&
		m_Max.y >= rhs.m_Max.y &&
		m_Max.z >= rhs.m_Max.z )
	{
		return true;
	}

	return false;
}

bool Collision( const AABB3D& lhs, const AABB3D& rhs )
{
	bool ret = false;

	if ( lhs.m_Min.x <= rhs.m_Min.x && lhs.m_Max.x >= rhs.m_Min.x )
	{
		ret = true;
	}
	else if ( lhs.m_Min.x <= rhs.m_Max.x && lhs.m_Max.x >= rhs.m_Max.x )
	{
		ret = true;
	}

	if(ret)
	{
		if ( lhs.m_Min.y <= rhs.m_Min.y && lhs.m_Max.y >= rhs.m_Min.y )
		{
			ret = true;
		}
		else if ( lhs.m_Min.y <= rhs.m_Max.y && lhs.m_Max.y >= rhs.m_Max.y )
		{
			ret = true;
		}
		else
		{
			ret = false;
		}
	}

	if(ret)
	{
		if ( lhs.m_Min.z <= rhs.m_Min.z && lhs.m_Max.z >= rhs.m_Min.z )
		{
			ret = true;
		}
		else if ( lhs.m_Min.z <= rhs.m_Max.z && lhs.m_Max.z >= rhs.m_Max.z )
		{
			ret = true;
		}
		else
		{
			ret = false;
		}
	}

	return ret;
}

bool AABB3D::IsCollision( const AABB3D& rhs )
{
	if ( Collision( *this, rhs ) || Collision( rhs, *this ) )
	{
		return true;
	}

	return false;
}

void AABB3D::ReBuild( const Polygon2D& poly )
{
	Vector2 ori = Point2toVec2( poly.CPoints()[0] );
	m_Max.x = ori.x;
	m_Max.y = ori.y;
	m_Min.x = ori.x;
	m_Min.y = ori.y;

	for ( auto it = poly.CPoints().begin(); it != poly.CPoints().end(); ++it )
	{
		AddPoint( *it );
	}
}

void AABB3D::ReBuild( const Polygon2Ds& polys )
{
	AddPolygon2D( *polys.begin() );

	for ( auto it = ++polys.begin(); it != polys.end(); ++it )
	{
		AddPolygon2D( *it );
	}
}

AABB3D::AABB3D( const Vector2& orgin )
{
	Vector3 ori;
	ori.x = orgin.x;
	ori.y = orgin.y;
	ori.z = 0.0f;
	m_Min = ori;
	m_Max = ori;

	m_Len.x = std::abs(m_Max.x - m_Min.x);
	m_Len.y = std::abs(m_Max.y - m_Min.y);
	m_Len.z = std::abs(m_Max.z - m_Min.z);
}

AABB3D::AABB3D( const Polygon2D& poly )
{
	ReBuild( poly );
}

AABB3D::AABB3D( const Vector3& orgin ) : m_Min( orgin ), m_Max( orgin )
{
	m_Len.x = std::abs(m_Max.x - m_Min.x);
	m_Len.y = std::abs(m_Max.y - m_Min.y);
	m_Len.z = std::abs(m_Max.z - m_Min.z);
}

AABB3D::AABB3D()
{

}



void AABB3D::AddPolygon2D( const Polygon2D& poly )
{
	for ( auto it = poly.CPoints().begin(); it != poly.CPoints().end(); ++it )
	{
		AddPoint( *it );
	}
}

void AABB3D::AddPoint( const point2& p )
{
	if ( p.x() > m_Max.x )
	{
		m_Max.x = p.x();
	}
	else if ( p.x() < m_Min.x )
	{
		m_Min.x = p.x();
	}

	if ( p.y() > m_Max.y )
	{
		m_Max.y = p.y();
	}
	else if ( p.y() < m_Min.y )
	{
		m_Min.y = p.y();
	}

	m_Len.x = std::abs(m_Max.x - m_Min.x);
	m_Len.y = std::abs(m_Max.y - m_Min.y);
}

void AABB3D::Move( float x, float y, float z )
{
	m_Min.x += x;
	m_Max.x += x;
	m_Min.y += y;
	m_Max.y += y;
	m_Min.z += z;
	m_Max.z += z;
}

void AABB3D::ChangeFace()
{
	Vec2 vmin(m_Min.x, m_Min.y), vmax(m_Max.x, m_Max.y);
	m_Min.x = -vmax.x;
	m_Max.x = -vmin.x;
}

void AABB3D::Scale( float v )
{
	m_Min *= v;
	m_Max *= v;

	m_Len.x = std::abs(m_Max.x - m_Min.x);
	m_Len.y = std::abs(m_Max.y - m_Min.y);
	m_Len.z = std::abs(m_Max.z - m_Min.z);
}

void AABB3D::Scale( float x, float y, float z )
{
	m_Min.x *= x;
	m_Max.x *= x;
	m_Min.y *= y;
	m_Max.y *= y;
	m_Min.z *= z;
	m_Max.z *= z;

	m_Len.x = std::abs(m_Max.x - m_Min.x);
	m_Len.y = std::abs(m_Max.y - m_Min.y);
	m_Len.z = std::abs(m_Max.z - m_Min.z);
}