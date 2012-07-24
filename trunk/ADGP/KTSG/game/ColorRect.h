#pragma once

#include <vector>
#include "math/Vector3.h"

struct ColorRect
{
	// min:0.0 ~ max:1.0, RGBA
	Vector4		m_Color;
	Vector3		m_Position;
	float		m_Width;
	float		m_Height;
	bool		m_IsGround;
};
typedef std::vector<ColorRect> ColorRects;