#pragma once
#include <vector>
#include "DX11/Vertex.h"
#include "math/Vector3.h"

struct Point
{
	float x, y;
	float r, g, b, a;
	Point( float x, float y, float r, float g, float b, float a ): x( x ), y( y ), r( r ), g( g ), b( b ), a( a ) {}
};
typedef std::vector<Point> Points;

class PointManager
{
private:
	Points		 m_Point;
	Vector3		 m_LineColor;
	const float      m_Size;
public:
	PointManager( void );
	~PointManager( void );

	void Add( float x, float y, float r = 0, float g = 0, float b = 0, float a = 1 );
	void SetLineColor( float r, float g, float b );

	Points& GetPoints() {return m_Point;}

	int Size();
	void Clear();
	bool Empty();
	Points::iterator End();
	void Transale( float x, float y );

	Points::iterator Select_GetIterator( float x, float y );
	int Select_GetIndex( float x, float y );
	void Erase( Points::iterator it_point );
	void Erase( int index );
	void Modify( Points::iterator it_point, float x, float y );
	void Modify( int index, float x, float y );
	void Transale( Points::iterator it_point, float x, float y );
	void Transale( int index, float x, float y );
	void ChangeColor( Points::iterator it_point, float r, float g, float b, float a = 1.0f );
	void ChangeColor( int index, float r, float g, float b, float a = 1.0f );
	void ChangeColor( float r, float g, float b, float a = 1.0f );
	PointVertices BuildPoint( float scale, float offsetX, float offsetY );
	LineVertices  BuildLine( float scale, float offsetX, float offsetY, float loop = true );
	LineVertices  BuildLineP2P( float scale, float offsetX, float offsetY );

	void operator =( PointManager index )
	{
		this->m_Point = index.m_Point;
	};

};
typedef std::vector<PointManager> Bounds;

