#pragma once
#include <vector>
#include <string>
#include <map>
namespace boost {namespace serialization {class access;}}
struct HitData
{
	//ex. d>a
	std::string	m_KeyQueue;
	//ex. super_punch
	std::wstring	m_FrameName;
	//ex. 1
	int		m_FrameOffset;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& 	m_KeyQueue;
		ar& 	m_FrameName;
		ar& 	m_FrameOffset;
	}
};
typedef std::vector<HitData> HitDatas;
typedef std::map<int, HitDatas> ActionKeyMap;
