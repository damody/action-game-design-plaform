#pragma once
#include <vector>

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
};
typedef std::vector<Attack> Attacks;
