#pragma once
#include <string>
#include <vector>
#include "PictureData.h"
#include "Lua/LuaCell.h"
#include "FrameInfo.h"
#include "common\shared_ptr.h"
#include "game\FlyingType.h"

namespace boost{namespace serialization{class access;}}
//每一個物件需要用到的資訊
struct ObjectInfo
{
	//名稱
	std::string	m_Name;
	//action picture
	PictureDatas	m_PictureDatas;
	//frame inforamtion
	FramesMap	m_FramesMap;
	//
	float		m_MaxHp;
	//是否能拾起
	bool		m_CanPick;
	//重物間或輕物件
	bool		m_IsHeavy;
	//飛行形式
	FlyingType::e   m_Flyingtype;
	
};
SHARE_PTR(ObjectInfo)

typedef std::map<std::string, ObjectInfo_Sptr> ObjectInfoMap; 
