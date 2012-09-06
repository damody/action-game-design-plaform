#pragma once
#include <vector>
#include <string>
namespace boost {namespace serialization {class access;}}
struct HitData
{
	//ex. d>a
	std::string	m_KeyQueue;
	//ex. super_punch
	std::string	m_FrameName;
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
