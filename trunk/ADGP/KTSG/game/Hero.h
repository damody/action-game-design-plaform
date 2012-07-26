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
#include <cmath>

#define KEYLIFE_AFTER_KEYUP 120
#define FRICTION 0.2f

struct Record
{
	int Kill;    //炳寄计
	int Attack;  //ю阑
	int HPLost;  //穕﹀秖
	int MPUsage; //臸秖
	int Picking; //珺癬珇计ヘ
	bool Status; //true: win false: lose
};
SHARE_PTR(Record)

class Hero
{
private:
	int m_TimeTik;//Count down TimeTik from Frame Wait
	ClipVertex	m_Pic;
	HeroInfo_Sptr   m_HeroInfo;
	HeroAction::e	m_Action;//讽笆篈
	std::string     m_Frame;//Current Frame
	int		m_FrameID;//Current Frame ID

	int		m_Texture;//Current Texture ID
	int             m_PicID;
	int		m_PicW;//W篒ちΩ计
	int		m_PicH;//H篒ちΩ计
	int		m_PicX;
	int		m_PicY;
	
	Vector3		m_Position;
	Vector3		m_Vel;
	Bodys		m_Bodys;
	float		m_Angle;
	bool		m_FaceSide;//true , false オ

	int		m_Team;//0ぃだ
	int		m_MaxRecoverHP;//程確﹀秖
	int		m_HP;
	int		m_MP;
	Record_Sptr     m_Record;

	KeyQueue	m_KeyQue;

public:
	const std::string hero;

	Hero();
	Hero(std::string h);
	void Update(float dt);
	
	Texture_Sptr GetTexture();
	int GetTextureID();
	ClipVertex GetPic();
	void SetRecord(Record_Sptr r);
	void SetTeam(int team);
	void PushKey(KeyInfo k);
	void Position(Vector3 pos);
protected:
	void Init();
	void NextFrame();
	bool ScanKeyQue();//false礚北笆
	void ClearKeyQue();
	void Flicker();//皗脅
	void Recover();//﹀瘆ň.....
	void UpdateDataToDraw();//Data To m_Pic

};
SHARE_PTR(Hero)

bool SortHero( Hero_RawPtr a,Hero_RawPtr b);
