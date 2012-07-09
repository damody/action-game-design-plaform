#pragma once
#include "math/Vector2.h"

struct BloodInfo
{
	//血塊的縮放大小
	float	m_Scale;
	//血顯示的位置
	Vector2	m_Position;
	//血低於幾%會顯示
	float	m_EnableValue;
};
typedef std::vector<BloodInfo> BloodInfos;
