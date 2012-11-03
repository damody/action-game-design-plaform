#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Polygon2D.h"

class AABB3D
{
public:
	AABB3D( const Polygon2D& poly );
	void AddPoint( const Vector2& p );
	AABB3D();
	AABB3D( const Vector2& orgin );
	AABB3D( const Vector3& orgin );
	void ReBuild( const Polygon2D& poly );
	void ReBuild( const Polygon2Ds& polys );
	void AddPolygon2D( const Polygon2D& poly );
	void AddPoint( const point2& p );
	void Larger( float val );
	void Larger( float x, float y, float z );
	void SetBounding( float left, float right, float top, float down, float front, float back );
	void SetBounding( float value );
	bool IsContain( const AABB3D& rhs );
	bool IsCollision( const AABB3D& rhs );
	void Move(float x, float y, float z);
	void Scale(float v);
	void Scale( float x, float y, float z );
	void ChangeFace();
	void SetZWidth(float z);
	Vector3 m_Min, m_Max, m_Len;
};
bool Collision( const AABB3D& lhs, const AABB3D& rhs );