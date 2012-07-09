#pragma once
#include <string>
#include <vector>
#include "PictureData.h"
#include "Lua/LuaCell.h"
#include "FrameInfo.h"
#include "common\shared_ptr.h"

//�C�@�ӭ^���ݭn�Ψ쪺��T
struct HeroInfo
{
	//�H���W��
	std::string	m_Name;
	//head picture
	std::string	m_Headpic;
	//small picture
	std::string	m_Smallpic;
	//action picture
	PictureDatas	m_PictureDatas;
	//frame inforamtion
	FramesMap	m_FramesMap;
	//�����t��
	float		m_WalkingSpeed;
	//������z(��������)�t��
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
	//�̤j�]�q
	int		m_MaxMP;
	//�̤j��q
	int		m_MaxHP;
	//�̤j���˭�
	int		m_MaxFall;
	//�̤j���m��
	int		m_MaxDefend;
	//���z���m�O
	int		m_PhysicsDefense;
	//�]�k���m�O
	int		m_MagicDefense;
	//���z���
	float		m_AntiPhysics;
	//���z���%��
	float		m_AntiPhysicsPercent;
	//�]�k���
	float		m_AntiMagic;
	//�]�k���%��
	float		m_AntiMagicPercent;
public:
	bool	CheckHeroDataVaild(LuaCell_Sptr luadata);
	void	LoadHeroData(LuaCell_Sptr luadata);
	LuaCell_Sptr	m_LuaCell;
};
SHARE_PTR(HeroInfo)

typedef std::map<std::string, HeroInfo_Sptr> HeroInfoMap; 
