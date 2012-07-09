#pragma once
#include <vector>
#include "math/Vector2.h"
struct BeCatch
{
	//被抓的點 脖子
	Vector2 m_Neck;
	//被抓的點 腳
	Vector2 m_Leg;
	//被抓的點 腰
	Vector2 m_Waist;
};
typedef std::vector<BeCatch> BeCatchs;
