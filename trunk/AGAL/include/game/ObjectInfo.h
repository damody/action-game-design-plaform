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


//每一個物件需要用到的資訊
struct ObjectInfo
{
	//名稱
	std::string	m_Name;
	//action picture
	PictureDatas	m_PictureDatas;
	//frame inforamtion
	FramesMap	m_FramesMap;
	//質量
	float		m_Mess;
	//彈性
	float		m_Elasticity;
	//最大血量
	int		m_MaxHP;
	//物件類別
	ObjectType::e	m_Type;
	//飛行形式
	FlyingType::e   m_FlyingType;

public:
	bool	CheckObjectDataVaild( LuaCell_Sptr luadata );
	void	LoadObjectData( LuaCell_Sptr luadata );
	LuaCell_Sptr	m_LuaCell;
};
SHARE_PTR( ObjectInfo );
typedef std::map<std::string, ObjectInfo_Sptr> ObjectInfoMap;
