#pragma once
#include "math/Polygon2D.h"
#include <vector>

struct Body
{
	//®≠≈ÈΩd≥Ú
	Polygon2D	m_Area;
	float		m_ZWidth;
	int		m_Kind;
};
typedef std::vector<Body> Bodys;
