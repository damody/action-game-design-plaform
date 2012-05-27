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

void Polygon2D::BuildEdges()
{
	Vec2* p1;
	Vec2* p2;
	m_edges.clear();
	
	for (size_t i = 0; i < m_points.size(); i++) 
	{
		p1 = &m_points[i];
		if (i + 1 >= m_points.size()) {
			p2 = &m_points[0];
		} else {
			p2 = &m_points[i + 1];
		}
		m_edges.push_back(*p2 - *p1);
	}
}

bool Polygon2D::IsCollision( const Polygon2D& rhs )
{
	CheckBuildEdges();
	size_t edgeCountA = m_edges.size();
	size_t edgeCountB = rhs.m_edges.size();
	float minIntervalDistance = (float)INT_MAX;
	Vec2 edge;

	// Loop through all the edges of both polygons
	for (size_t edgeIndex = 0; edgeIndex < edgeCountA + edgeCountB; edgeIndex++) {
		if (edgeIndex < edgeCountA) {
			edge = m_edges[edgeIndex];
		} else {
			edge = rhs.m_edges[edgeIndex - edgeCountA];
		}

		// ===== 1. Find if the polygons are currently intersecting =====

		// Find the axis perpendicular to the current edge
		Vec2 axis(-edge.y, edge.x);
		axis.normalise();

		// Find the projection of the polygon on the current axis
		float minA = 0; float minB = 0; float maxA = 0; float maxB = 0;
		ProjectPolygon(axis, *this, &minA, &maxA);
		ProjectPolygon(axis, rhs, &minB, &maxB);

		// Check if the polygon projections are currentlty intersecting
		if (IntervalDistance(minA, maxA, minB, maxB) > 0)
			return false;
	}
	return true;
}

void Polygon2D::ProjectPolygon( const Vec2& axis, const Polygon2D& polygon, float* min, float* max )
{
	// To project a point on an axis use the dot product
	float d = axis.dotProduct(polygon.m_points[0]);
	*min = d;
	*max = d;
	for (size_t i = 0; i < polygon.m_points.size(); i++) {
		d = polygon.m_points[i].dotProduct(axis);
		if (d < *min) {
			*min = d;
		} else {
			if (d > *max) {
				*max = d;
			}
		}
	}
}

void Polygon2D::CheckBuildEdges()
{
	if (m_needBuildEdges)
	{
		BuildEdges();
		m_needBuildEdges = false;
	}
}

void Polygon2D::AddPoint( float x, float y )
{
	m_needBuildEdges = true;
	m_points.push_back(Vec2(x, y));
}

void Polygon2D::AddPoint( const Vec2& p )
{
	m_needBuildEdges = true;
	m_points.push_back(p);
}

void Polygon2D::Offset( float x, float y )
{
	for (Vec2s::iterator it = m_points.begin();
		it != m_points.end();++it)
	{
		it->x += x;
		it->y += y;
	}
}

void Polygon2D::Offset( const Vec2& v )
{
	for (Vec2s::iterator it = m_points.begin();
		it != m_points.end();++it)
	{
		*it += v;
	}
}

void Polygon2D::Offset( const Vec3& v )
{
	for (Vec2s::iterator it = m_points.begin();
		it != m_points.end();++it)
	{
		it->x += v.x;
		it->y += v.y;
	}
}

void Polygon2D::SetAngle( float angle )
{
	for (Vec2s::iterator it = m_points.begin();
		it != m_points.end();++it)
	{
		*it = Quaternion::GetRotation(*it, angle-m_angle, Vec2::ZERO);
	}
	m_angle = angle;
}

void Polygon2D::Rotation( float angle, const Vec2& middle /*= Vec2::ZERO*/ )
{
	m_angle = angle;
	for (Vec2s::iterator it = m_points.begin();
		it != m_points.end();++it)
	{
		*it = Quaternion::GetRotation(*it, angle, middle);
	}
}

void Polygon2D::Clear()
{
	m_points.clear();
	m_edges.clear();
}


