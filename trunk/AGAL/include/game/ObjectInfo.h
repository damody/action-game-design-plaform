#pragma once
#include <string>
#include <vector>
#include "PictureData.h"
#include "Lua/LuaCell.h"
#include "FrameInfo.h"
#include "common\shared_ptr.h"
#include "game\ObjectType.h"
#include "game\FlyingPath.h"

namespace boost {namespace serialization {class access;}}


//�C�@�Ӫ���ݭn�Ψ쪺��T
struct ObjectInfo
{
	//�W��
	std::string	m_Name;
	//action picture
	PictureDatas	m_PictureDatas;
	//frame inforamtion
	FramesMap	m_FramesMap;
	//��q
	float		m_Mess;
	//�u��
	float		m_Elasticity;
	//�̤j��q
	int		m_MaxHP;
	//�������O
	ObjectType::e	m_Type;
	//����Φ�
	FlyingType::e   m_FlyingType;

public:
	bool	CheckObjectDataVaild( LuaCell_Sptr luadata );
	void	LoadObjectData( LuaCell_Sptr luadata );
	LuaCell_Sptr	m_LuaCell;
};
SHARE_PTR( ObjectInfo );
typedef std::map<std::string, ObjectInfo_Sptr> ObjectInfoMap;
