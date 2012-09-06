//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Polygon.cpp
//  @ Date : 2011/9/4
//  @ Author :
//
//

#include "Polygon2D.h"
#include "Quaternion.h"

using namespace boost::geometry;

void Polygon2D::BuildEdges()
{
	m_polygon.clear();

	for ( unsigned int i = 0; i < m_points.size(); i++ )
	{
		m_polygon.outer().push_back( point2( m_points[i].x, m_points[i].y ) );
	}

	correct( m_polygon );
}

bool Polygon2D::IsCollision( const Polygon2D& rhs )
{
	CheckBuildEdges();

	if ( m_points.size() < 3 )
	{
		for ( unsigned int i = 0; i < m_points.size(); i++ )
		{
			point2 pt( m_points[0].x, m_points[0].y );

			if ( within( pt, rhs.m_polygon ) ) { return true; }
		}
	}
	else
	{
		return intersects<polygon, polygon>( m_polygon, rhs.m_polygon );
	}

	return false;
}

void Polygon2D::ProjectPolygon( const Vec2& axis, const Polygon2D& polygon, float* min, float* max )
{
	// To project a point on an axis use the dot product
	float d = axis.dotProduct( polygon.m_points[0] );
	*min = d;
	*max = d;

	for ( size_t i = 0; i < polygon.m_points.size(); i++ )
	{
		d = polygon.m_points[i].dotProduct( axis );

		if ( d < *min )
		{
			*min = d;
		}
		else
		{
			if ( d > *max )
			{
				*max = d;
			}
		}
	}
}

void Polygon2D::CheckBuildEdges()
{
	if ( m_needBuildEdges )
	{
		BuildEdges();
		m_needBuildEdges = false;
	}
}

void Polygon2D::AddPoint( float x, float y )
{
	m_needBuildEdges = true;
	m_points.push_back( Vec2( x, y ) );
}

void Polygon2D::AddPoint( const Vec2& p )
{
	m_needBuildEdges = true;
	m_points.push_back( p );
}

void Polygon2D::Offset( float x, float y )
{
	for ( Vec2s::iterator it = m_points.begin();
	                it != m_points.end(); ++it )
	{
		it->x += x;
		it->y += y;
	}
}

void Polygon2D::Offset( const Vec2& v )
{
	for ( Vec2s::iterator it = m_points.begin();
	                it != m_points.end(); ++it )
	{
		*it += v;
	}
}

void Polygon2D::Offset( const Vec3& v )
{
	for ( Vec2s::iterator it = m_points.begin();
	                it != m_points.end(); ++it )
	{
		it->x += v.x;
		it->y += v.y;
	}
}

void Polygon2D::SetAngle( float angle )
{
	for ( Vec2s::iterator it = m_points.begin();
	                it != m_points.end(); ++it )
	{
		*it = Quaternion::GetRotation( *it, angle - m_angle, Vec2::ZERO );
	}

	m_angle = angle;
}

void Polygon2D::Rotation( float angle, const Vec2& middle /*= Vec2::ZERO*/ )
{
	m_angle = angle;

	for ( Vec2s::iterator it = m_points.begin();
	                it != m_points.end(); ++it )
	{
		*it = Quaternion::GetRotation( *it, angle, middle );
	}
}

void Polygon2D::Clear()
{
	m_points.clear();
	m_edges.clear();
}


