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
	//�����d��
	Polygon2D m_Area;
	//�쪺z�d��
	float	m_ZWidth;
	//�ˮ`
	int	m_Injury;
	//�T�ت��p�G��H���B���n��H
	int	m_Kind;
	//�H�Q�줧��A���ӳQ�쪺�H�|���@�ӳQ�쪺�I�A�Ө����I�n����쪺�H�� m_CatchPosition �Ӧ�m
	Vector2	m_CatchPosition;
	//�n�����m
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
