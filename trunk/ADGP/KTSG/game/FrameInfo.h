#pragma once
#include <vector>
#include <map>
#include "HeroAction.h"
#include "Consume.h"
#include "math\Polygon2D.h"
#include "Attack.h"
#include "HitData.h"
#include "CatchInfo.h"
#include "BeCatch.h"
#include "BloodInfo.h"
#include "Body.h"

//每一個動作 Frame 所含的資訊
struct FrameInfo
{
	//動作狀態
	HeroAction::e	m_HeroAction;
	//Frame Name
	std::string	m_FrameName;
	//Frame index of action
	int		m_FrameIndex;
	//Next Frame Name
	std::string	m_NextFrameName;
	//Next Frame index of action
	int		m_NextFrameIndex;
	//表示讀入圖片的id
	int	m_PictureID;
	//表示圖片的 x 位置
	int	m_PictureX;
	//表示圖片的 y 位置
	int	m_PictureY;
	//人物X方向偏移修正量
	float	m_CenterX;
	//人物Y方向偏移修正量
	float	m_CenterY;
	//消耗資訊
	Consume	m_Consume;
	//x方向左右的移動可能
	float	m_DVX;
	//y方向上下的移動可能
	float	m_DVY;
	//Z方向上下的移動可能
	float	m_DVZ;
	//這個 Frame 執行圈數，一圈1/60秒
	int	m_Wait;
	//是否要清掉 KeyQueue 的資料
	bool	m_ClearKeyQueue;
	//身體
	Bodys		m_Bodys;
	//攻擊判定
	Attacks		m_Attacks;
	//絕招判定
	HitDatas	m_HitDatas;
	//抓人判定
	CatchInfos	m_Catchs;
	//被抓判定
	BeCatch		m_BeCatch;
	//流血資訊
	BloodInfos	m_BloodInfos;
};
typedef std::vector<FrameInfo> FrameInfos;
typedef std::map<std::string, FrameInfos> FramesMap;
