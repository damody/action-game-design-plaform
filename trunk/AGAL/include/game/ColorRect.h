#pragma once

#include <vector>
#include "math/Vector3.h"
namespace boost{namespace serialization{class access;}}
struct ColorRect
{
	// min:0.0 ~ max:1.0, RGBA
	Vector4		m_Color;
	Vector3		m_Position;
	float		m_Width;
	float		m_Height;
	bool		m_IsGround;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar &		m_Color;
		ar &		m_Position;
		ar &		m_Width;
		ar &		m_Height;
		ar &		m_IsGround;
	}
};
typedef std::vector<ColorRect> ColorRects;