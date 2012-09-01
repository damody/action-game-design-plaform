#pragma once
#include "math/Polygon2D.h"
#include <vector>
namespace boost{namespace serialization{class access;}}
struct Body
{
	//®≠≈ÈΩd≥Ú
	Polygon2D	m_Area;
	float		m_ZWidth;
	int		m_Kind;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar &	m_Area;
		ar &	m_ZWidth;
		ar &	m_Kind;
	}
};
typedef std::vector<Body> Bodys;
