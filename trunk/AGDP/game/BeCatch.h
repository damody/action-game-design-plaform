#pragma once
#include <vector>
#include "math/Vector2.h"
namespace boost{namespace serialization{class access;}}
struct BeCatch
{
	
	//�Q�쪺�I ��l
	Vector2 m_Neck;
	//�Q�쪺�I �}
	Vector2 m_Leg;
	//�Q�쪺�I �y
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
