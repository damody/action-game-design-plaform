#pragma once
#include <map>

struct CrouchData
{
	//ex. super_punch
	std::wstring	m_FrameName;
	//ex. 1
	int		m_FrameOffset;
};
typedef std::map<int, CrouchData> CrouchMap;
