#pragma once
#include "math/Vector2.h"

struct BloodInfo
{
	//������Y��j�p
	float	m_Scale;
	//����ܪ���m
	Vector2	m_Position;
	//��C��X%�|���
	float	m_EnableValue;
};
typedef std::vector<BloodInfo> BloodInfos;
