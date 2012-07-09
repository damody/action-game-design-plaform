#pragma once
#include <string>
#include <vector>
#include "PictureData.h"
#include "Lua/LuaCell.h"
#include "FrameInfo.h"
#include "common\shared_ptr.h"

//每一個英雄需要用到的資訊
struct HeroInfo
{
	//人物名稱
	std::string	m_Name;
	//head picture
	std::string	m_Headpic;
	//small picture
	std::string	m_Smallpic;
	//action picture
	PictureDatas	m_PictureDatas;
	//frame inforamtion
	FramesMap	m_FramesMap;
	//走路速度
	float		m_WalkingSpeed;
	//走路的z(按↑↓時)速度
	float		m_WalkingSpeedZ;
	float		m_RunningSpeed;
	float		m_RunningSpeedZ;
	float		m_HeavyWalkingSpeed;
	float		m_HeavyWalkingSpeedZ;
	float		m_HeavyRunningSpeed;
	float		m_HeavyRunningSpeedZ;
	float		m_JumpHeight;
	float		m_JumpDistance;
	float		m_JumpDistanceZ;
	float		m_DashHeight;
	float		m_DashDistance;
	float		m_DashDistanceZ;
	float		m_RowingHeight;
	float		m_RowingDistance;
	//最大魔量
	int		m_MaxMP;
	//最大血量
	int		m_MaxHP;
	//最大擊倒值
	int		m_MaxFall;
	//最大防禦值
	int		m_MaxDefend;
	//物理防禦力
	int		m_PhysicsDefense;
	//魔法防禦力
	int		m_MagicDefense;
	//物理減傷
	float		m_AntiPhysics;
	//物理減傷%數
	float		m_AntiPhysicsPercent;
	//魔法減傷
	float		m_AntiMagic;
	//魔法減傷%數
	float		m_AntiMagicPercent;
public:
	bool	CheckHeroDataVaild(LuaCell_Sptr luadata);
	void	LoadHeroData(LuaCell_Sptr luadata);
	LuaCell_Sptr	m_LuaCell;
};
SHARE_PTR(HeroInfo)

typedef std::map<std::string, HeroInfo_Sptr> HeroInfoMap; 
