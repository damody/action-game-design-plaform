#pragma once
#include <vector>
#include "math/Vector2.h"
namespace boost{namespace serialization{class access;}}
struct BeCatch
{
	
	//被抓的點 脖子
	Vector2 m_Neck;
	//被抓的點 腳
	Vector2 m_Leg;
	//被抓的點 腰
	Vector2 m_Waist;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & m_Neck;
		ar & m_Leg;
		ar & m_Waist;
	}
};
typedef std::vector<BeCatch> BeCatchs;
