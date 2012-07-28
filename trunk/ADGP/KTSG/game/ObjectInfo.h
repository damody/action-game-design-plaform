#pragma once
#include <string>
#include <vector>
#include "PictureData.h"
#include "Lua/LuaCell.h"
#include "FrameInfo.h"
#include "common\shared_ptr.h"
#include "game\FlyingType.h"

namespace boost{namespace serialization{class access;}}
//�C�@�Ӫ���ݭn�Ψ쪺��T
struct ObjectInfo
{
	//�W��
	std::string	m_Name;
	//action picture
	PictureDatas	m_PictureDatas;
	//frame inforamtion
	FramesMap	m_FramesMap;
	//
	float		m_MaxHp;
	//�O�_��B�_
	bool		m_CanPick;
	//�������λ�����
	bool		m_IsHeavy;
	//����Φ�
	FlyingType::e   m_Flyingtype;
	
};
SHARE_PTR(ObjectInfo)

typedef std::map<std::string, ObjectInfo_Sptr> ObjectInfoMap; 
