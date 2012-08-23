#pragma once
#include <vector>
#include "DX11/Vertex.h"
#include "math/Vector3.h"

struct Point{
	float x,y;
	float r,g,b,a;
	Point(float x,float y,float r,float g, float b, float a):x(x),y(y),r(r),g(g),b(b),a(a){}
};
typedef std::vector<Point> Points;

class PointManager
{
private:
	Points		 m_Point;
	Vector3		 m_LineColor;
	const float      m_Size;
public:
	PointManager(void);
	~PointManager(void);

	void Add(float x, float y,float r=0,float g=0, float b=0, float a=1);
	void SetLineColor(float r,float g,float b);

	void Clear();
	bool Empty();
	Points::iterator End();
	void Transale(float x,float y);

	Points::iterator Select(float x, float y);
	void Erase(Points::iterator it_point);
	void Modify(Points::iterator it_point,float x,float y);
	void Transale(Points::iterator it_point,float x,float y);
	void ChangeColor(Points::iterator it_point,float r,float g, float b,float a=1.0f);

	PointVertices BuildPoint();
	LineVertices  BuildLine(float loop = true);

	void operator =(PointManager index){
					this->m_Point = index.m_Point;
	};

};
typedef std::vector<PointManager> Bounds;

