#pragma once
#include "math/Polygon2D.h"
#include "math/Vector2.h"
namespace boost{namespace serialization{class access;}}
struct CatchInfo
{
	enum	CatchPosition
	{
		NECK,
		LEG,
		WAIST
	};
	//攻擊範圍
	Polygon2D m_Area;
	//抓的z範圍
	float	m_ZWidth;
	//傷害
	int	m_Injury;
	//三種狀況：抓人中、正要抓人
	int	m_Kind;
	//人被抓之後，那個被抓的人會有一個被抓的點，而那個點要移到抓的人的 m_CatchPosition 個位置
	Vector2	m_CatchPosition;
	//要抓住的位置
	CatchPosition	m_CatchWhere;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar &	m_Area;
		ar &	m_ZWidth;
		ar &	m_Injury;
		ar &	m_Kind;
		ar &	m_CatchPosition;
		ar &	m_CatchWhere;
	}
};
typedef std::vector<CatchInfo> CatchInfos;
