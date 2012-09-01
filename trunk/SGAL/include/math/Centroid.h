#pragma once
#include "math\Vector2.h"
#include "math\Polygon2D.h"

class Centroid 
{
public:
	Centroid(){}
	Centroid(const Polygon2D& poly)
	{
		m_centroid = Vector2::ZERO;
		int psize = (int)poly.const_Points().size();
		for (int i = 0; i < psize; i++) 
			m_centroid += poly.const_Points()[i];
		m_centroid /= (float)psize;
		m_radius = 0;
		for (int i = 0; i < psize; i++) 
		{		
			float tmp = m_centroid.dotProduct(poly.const_Points()[i]);
			if (tmp>m_radius)
				m_radius = tmp;
		}
	}
	Vector2 m_centroid;
	float	m_radius;
};

