#pragma warning(disable:4819)
#pragma once

#ifndef _POLYGON2D_H_
#define _POLYGON2D_H_
#include "Vector2.h"
#include "Vector3.h"
#include "BasicMath.h"
#include "AABB2D.h"
#include <vector>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometry.hpp>

typedef boost::geometry::model::d2::point_xy<float> point2;
typedef boost::geometry::model::polygon<point2> polygon;

class Polygon2D 
{
public:
	Polygon2D():m_angle(0), m_zPoint(0), m_zRange(0.01){}
	~Polygon2D();
	Vec2s& Points()
	{
		m_needBuildAABB = true;
		m_needBuildPolygon = true;
		return m_points;
	}
	const Vec2s& const_Points() const
	{
		return m_points;
	}
	AABB2D& AABB()
	{
		return m_aabb;
	}
	void AddPoint(float x, float y);
	void AddPoint(const Vec2& p);
	void Offset(float x, float y);
	void Offset(const Vec2& v);
	void Offset(float x, float y, float z);
	void Offset(const Vec3& v);
	void SetAngle(float angle);
	void SetZRange(float scale){m_zRange = scale;}
	void SetZPoint(float rz){m_zPoint = rz;}
	float GetAngle(){return m_angle;}
	float GetZRange(){return m_zRange;}
	float GetZPoint(){return m_zPoint;}
	void Rotation(float angle, const Vec2& middle = Vec2::ZERO);
	bool IsCollision(const Polygon2D& rhs);
	bool zIsCollision(const Polygon2D& rhs);
	void CheckBuildAABB();
	void CheckBuildPolygon();
	void CheckBuildEdges(){} // do nothing
	void Clear();
private:
	void BuildAABB();
	void BuildPolygon();
	void BuildEdges(){} // do nothing
	// Calculate the distance between [minA, maxA] and [minB, maxB]
	// The distance will be negative if the intervals overlap
	inline float IntervalDistance(float minA, float maxA, float minB, float maxB)
	{
		if (minA < minB) {
			return minB - maxA;
		} else {
			return minA - maxB;
		}
	}
	// Calculate the projection of a polygon on an axis and returns it as a [min, max] interval
	void ProjectPolygon(const Vec2& axis, const Polygon2D& polygon, float* min, float* max);
private:
	float	m_angle;
	Vec2s	m_points, m_edges;
	bool	m_needBuildAABB;
	bool	m_needBuildPolygon;
	polygon m_polygon;
	float   m_zRange; // ª½®|
	float   m_zPoint;
	AABB2D  m_aabb;
};
typedef std::vector<Polygon2D> Polygons;
typedef std::vector<Polygon2D> Polygon2Ds;
#endif // _POLYGON2D_H_