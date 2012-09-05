#pragma once
#include "math/Vector2.h"
namespace boost {namespace serialization {class access;}}
struct BloodInfo
{

	//血塊的縮放大小
	float	m_Scale;
	//血顯示的位置
	Vector2	m_Position;
	//血低於幾%會顯示
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
