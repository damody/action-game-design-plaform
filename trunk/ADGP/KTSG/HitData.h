#pragma once
#include <vector>
#include <string>
struct HitData
{
	//ex. d>a
	std::string	m_KeyQueue;
	//ex. super_punch
	std::string	m_FrameName;
	//ex. 1
	int		m_FrameOffset;
};
typedef std::vector<HitData> HitDatas;
