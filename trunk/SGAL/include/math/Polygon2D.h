#pragma warning(disable:4819)
#pragma once

#ifndef _POLYGON2D_H_
#define _POLYGON2D_H_
#include "Vector2.h"
#include "Vector3.h"
#include "BasicMath.h"
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
	Vec2s& Points()
	{
		m_needBuildEdges = true;
		return m_points;
	}
	const Vec2s& const_Points() const
	{
		return m_points;
	}
	void AddPoint(float x, float y);
	void AddPoint(const Vec2& p);
	void Offset(float x, float y);
	void Offset(const Vec2& v);
	void Offset(float x, float y, float z);
	void Offset(const Vec3& v);
	void SetAngle(float angle);
	void SetZRange(float scale){m_zRange = scale;}
	float GetAngle(){return m_angle;}
	float GetZRange(){return m_zRange;}
	float GetZPoint(){return m_zPoint;}
	void Rotation(float angle, const Vec2& middle = Vec2::ZERO);
	bool IsCollision(const Polygon2D& rhs);
	bool zIsCollision(const Polygon2D& rhs);
	void CheckBuildEdges();
	void Clear();
private:
	void BuildEdges();
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
	bool	m_needBuildEdges;
	polygon m_polygon;
	float   m_zRange; // ª½®|
	float   m_zPoint;
};
typedef std::vector<Polygon2D> Polygons;
typedef std::vector<Polygon2D> Polygon2Ds;
#endif // _POLYGON2D_H_