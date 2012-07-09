#pragma once
#include <boost/bind.hpp>
#include <deque>
#include "DX11\Vertex.h"
#include "DX11\TextureManager.h"
#include "math\Vector3.h"
#include "algo\nway.h"
#include "ball\straight.h"
#include "path\LinearLine.h"
#include "path\BezierCurve.h"
#include "path\BsplineCurve.h"
#include "path\HSplineCurve.h"
#include "common\shared_ptr.h"

#include "CtrlKey.h"
#include "HeroInfo.h"
#include "HeroAction.h"
#include <string>

class Hero
{
private:
	int m_TimeTik;//Count down TimeTik from Frame Wait
	ClipVertex	m_Pic;
	HeroInfo_Sptr   m_HeroInfo;
	HeroAction	m_Action;//當下動作狀態
	std::string     m_Frame;//Current Frame
	int		m_FrameID;//Current Frame ID

	int		m_Texture;//Current Texture ID
	int             m_PicID;
	int		m_PicW;//W截切次數
	int		m_PicH;//H截切次數
	int		m_PicX;
	int		m_PicY;
	
	Vector3		m_Position;
	Bodys		m_Bodys;
	float		m_Angle;

	int		m_Team;//0為不分
	int		m_MaxRecoverHP;//最大恢復血量
	int		m_HP;
	int		m_MP;

	KeyQue		m_KeyQue;

public:
	const std::string hero;

	Hero();
	Hero(std::string h);
	void Update(float dt);
	
	Texture_Sptr GetTexture();
	int GetTextureID();
	ClipVertex GetPic();
	void Position(Vector3 pos);
protected:
	void Init();
	void NextFrame();
	bool ScanKeyQue();//false無控制動作
	void Flicker();//閃爍
	void Recover();//回血、氣、破防值.....
	void UpdateDataToDraw();//Data To m_Pic

};
SHARE_PTR(Hero)

bool SortHero( Hero_RawPtr a,Hero_RawPtr b);
