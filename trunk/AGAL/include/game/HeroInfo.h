#pragma once
#include <string>
#include <vector>

#include "PictureData.h"
#include "Lua/LuaCell.h"
#include "FrameInfo.h"
#include "CrouchData.h"
#include "common/shared_ptr.h"
namespace boost {namespace serialization {class access;}}



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
	//crouch inforamtion ���a������T
	CrouchMap	m_CrouchMap;
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

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& 	m_Name;
		ar& 	m_Headpic;
		ar& 	m_Smallpic;
		ar& 	m_PictureDatas;
		ar& 	m_FramesMap;
		ar& 		m_WalkingSpeed;
		ar& 		m_WalkingSpeedZ;
		ar& 		m_RunningSpeed;
		ar& 		m_RunningSpeedZ;
		ar& 		m_HeavyWalkingSpeed;
		ar& 		m_HeavyWalkingSpeedZ;
		ar& 		m_HeavyRunningSpeed;
		ar& 		m_HeavyRunningSpeedZ;
		ar& 		m_JumpHeight;
		ar& 		m_JumpDistance;
		ar& 		m_JumpDistanceZ;
		ar& 		m_DashHeight;
		ar& 		m_DashDistance;
		ar& 		m_DashDistanceZ;
		ar& 		m_RowingHeight;
		ar& 		m_RowingDistance;
		ar& 		m_MaxMP;
		ar& 		m_MaxHP;
		ar& 		m_MaxFall;
		ar& 		m_MaxDefend;
		ar& 		m_PhysicsDefense;
		ar& 		m_MagicDefense;
		ar& 		m_AntiPhysics;
		ar& 		m_AntiPhysicsPercent;
		ar& 		m_AntiMagic;
		ar& 		m_AntiMagicPercent;
	}
public:
	HeroInfo();
	static bool CheckHeroDataVaild( LuaCell_Sptr luadata );
	static void WriteLua( HeroInfo* hero , std::wstring filePath );
	void	LoadHeroData( LuaCell_Sptr luadata );
	LuaCell_Sptr	m_LuaCell;
};
SHARE_PTR( HeroInfo )

typedef std::map<std::string, HeroInfo_Sptr> HeroInfoMap;
