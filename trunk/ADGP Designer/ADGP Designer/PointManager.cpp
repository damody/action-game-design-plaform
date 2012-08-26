#include "stdafx.h"
#include "PointManager.h"
#include "global.h"

PointManager::PointManager(void):m_Size(5.0f),m_LineColor(Vector3(0,0,0))
{
}


PointManager::~PointManager(void)
{
}

void PointManager::Add( float x, float y,float r/*=0*/,float g/*=0*/, float b/*=0*/, float a/*=1*/ )
{
	m_Point.push_back(Point(x,y,r,g,b,a));
}

void PointManager::Clear()
{
	m_Point.clear();
}

void PointManager::Transale( float x,float y )
{
	for (Points::iterator it=m_Point.begin(); it != m_Point.end(); it++)
	{
		it->x += x;
		it->y += y;
	}
}

void PointManager::Transale( Points::iterator it_point,float x,float y )
{
	if(it_point == m_Point.end())return;
	it_point->x += x;
	it_point->y += y;
}

Points::iterator PointManager::Select( float x, float y )
{
	float error = 100;
	Points::iterator it_point = m_Point.end();
	for (Points::iterator it=m_Point.begin(); it != m_Point.end(); it++)
	{
		float length = (it->x-x)*(it->x-x) + (it->y-y)*(it->y-y);
		if (error > length)
		{
			error = length;
			it_point = it;
		}
	}
	return it_point;
}

void PointManager::Erase( Points::iterator it_point )
{
	m_Point.erase(it_point);
}

void PointManager::Modify( Points::iterator it_point,float x,float y )
{
	if(it_point == m_Point.end())return;
	it_point->x = x;
	it_point->y = y;
}

PointVertices PointManager::BuildPoint(float scale,float offsetX, float offsetY)
{
	PointVertices pvs;
	for (Points::iterator it=m_Point.begin(); it != m_Point.end(); it++)
	{
		PointVertex pv;
		pv.position.x	= it->x * scale + offsetX;
		pv.position.y	= it->y * scale + offsetY;
		pv.size.x	= m_Size ;
		pv.size.y	= m_Size ;
		pv.color.x	= it->r;
		pv.color.y	= it->g;
		pv.color.z	= it->b;
		pv.color.w	= it->a;

		pvs.push_back(pv);
	}
	return pvs;
}

LineVertices PointManager::BuildLine(float scale,float offsetX, float offsetY, float loop /*= true*/ )
{
	LineVertices lvs;
	for (unsigned int i=0; i+1<m_Point.size() ;i++)
	{
		LineVertex lv;
		
		lv.color.x	= m_LineColor.x;
		lv.color.y	= m_LineColor.y;
		lv.color.z	= m_LineColor.z;
		lv.color.w	= 1.0f;

		lv.position.x	= m_Point[i].x * scale + offsetX;
		lv.position.y	= m_Point[i].y * scale + offsetY;
		lvs.push_back(lv);
		lv.position.x	= m_Point[i+1].x * scale + offsetX;
		lv.position.y	= m_Point[i+1].y * scale + offsetY;
		lvs.push_back(lv);
	}

	if(loop && m_Point.size()>2){
		LineVertex lv;
		lv.color.x	= m_LineColor.x;
		lv.color.y	= m_LineColor.y;
		lv.color.z	= m_LineColor.z;
		lv.color.w	= 1.0f;

		lv.position.x	= m_Point.back().x * scale + offsetX;
		lv.position.y	= m_Point.back().y * scale + offsetY;
		lvs.push_back(lv);
		lv.position.x	= m_Point.front().x * scale + offsetX;
		lv.position.y	= m_Point.front().y * scale + offsetY;
		lvs.push_back(lv);
	}

	return lvs;
}

bool PointManager::Empty()
{
	return m_Point.empty();
}

Points::iterator PointManager::End()
{
	return m_Point.end();
}

void PointManager::ChangeColor( Points::iterator it_point,float r,float g, float b,float a/*=1.0f*/ )
{
	if(it_point == m_Point.end())return;
	it_point->r = r;
	it_point->g = g;
	it_point->b = b;
	it_point->a = a;
}

void PointManager::ChangeColor( float r,float g, float b,float a/*=1.0f*/ )
{
	for (Points::iterator it=m_Point.begin(); it != m_Point.end(); it++)
	{
		it->r = r;
		it->g = g;
		it->b = b;
		it->a = a;
	}
}

void PointManager::SetLineColor( float r,float g,float b )
{
	m_LineColor.x = r;
	m_LineColor.y = g;
	m_LineColor.z = b;
}

LineVertices PointManager::BuildLineP2P( float scale,float offsetX, float offsetY )
{
	LineVertices lvs;
	for (unsigned int i=0; i+1<m_Point.size() ;i+=2)
	{
		LineVertex lv;

		lv.color.x	= m_LineColor.x;
		lv.color.y	= m_LineColor.y;
		lv.color.z	= m_LineColor.z;
		lv.color.w	= 1.0f;

		lv.position.x	= m_Point[i].x * scale + offsetX;
		lv.position.y	= m_Point[i].y * scale + offsetY;
		lvs.push_back(lv);
		lv.position.x	= m_Point[i+1].x * scale + offsetX;
		lv.position.y	= m_Point[i+1].y * scale + offsetY;
		lvs.push_back(lv);
	}
	return lvs;
}
