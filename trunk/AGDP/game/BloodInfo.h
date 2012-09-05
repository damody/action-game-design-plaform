#pragma once
#include "math/Vector2.h"
namespace boost {namespace serialization {class access;}}
struct BloodInfo
{

	//������Y��j�p
	float	m_Scale;
	//����ܪ���m
	Vector2	m_Position;
	//��C��X%�|���
	float	m_EnableValue;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& 	m_Scale;
		ar& 	m_Position;
		ar& 	m_EnableValue;
	}
};
typedef std::vector<BloodInfo> BloodInfos;
