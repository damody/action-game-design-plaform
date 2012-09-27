#pragma once
#include <vector>
#include "math\Polygon2D.h"

namespace boost {namespace serialization {class access;}}
//每一個攻擊判定所含的資訊
struct Attack
{

	//範圍
	Polygon2D m_Area;
	//傷害
	int	m_Injury;
	//判定強度
	int	m_Strength;
	//傷害種類
	int	m_Kind;
	//傷害效果
	int	m_Effect;
	//擊中後 x 方向左右的移動
	float	m_DVX;
	//擊中後 y 方向上下的移動
	float	m_DVY;
	//擊中後 z 方向上下的移動
	float	m_DVZ;
	//Z方向的寬度
	float	m_ZWidth;
	//擊倒值
	int	m_Fall;
	//破防值
	int	m_BreakDefend;
	//擊中停頓圈數
	int	m_AttackRest;
	//再攻擊圈數
	int	m_ReAttackRest;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& m_Area;
		ar& m_Injury;
		ar& m_Strength;
		ar& m_Kind;
		ar& m_Effect;
		ar& m_DVX;
		ar& m_DVY;
		ar& m_DVZ;
		ar& m_ZWidth;
		ar& m_Fall;
		ar& m_BreakDefend;
		ar& m_AttackRest;
		ar& m_ReAttackRest;
	}
};
typedef std::vector<Attack> Attacks;

const std::string effectTable[] =
{
	"Fire",
	"BlackFire",
	"PurpleFire",
	"Freeze",
	"IceSlow",
	"Punch",
	"Knife",
	"Thunder",
	"Palsy",
	"Faint",
	"End"
};