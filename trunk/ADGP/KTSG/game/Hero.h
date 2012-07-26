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
	int Kill;    //���ļ�
	int Attack;  //����
	int HPLost;  //�l��q
	int MPUsage; //���]�q
	int Picking; //�B�_���~�ƥ�
	bool Status; //true: win false: lose
};
SHARE_PTR(Record)

class Hero
{
private:
	int m_TimeTik;//Count down TimeTik from Frame Wait
	ClipVertex	m_Pic;
	HeroInfo_Sptr   m_HeroInfo;
	HeroAction::e	m_Action;//��U�ʧ@���A
	std::string     m_Frame;//Current Frame
	int		m_FrameID;//Current Frame ID

	int		m_Texture;//Current Texture ID
	int             m_PicID;
	int		m_PicW;//W�I������
	int		m_PicH;//H�I������
	int		m_PicX;
	int		m_PicY;
	
	Vector3		m_Position;
	Vector3		m_Vel;
	Bodys		m_Bodys;
	float		m_Angle;
	bool		m_FaceSide;//true �k, false ��

	int		m_Team;//0������
	int		m_MaxRecoverHP;//�̤j��_��q
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
	bool ScanKeyQue();//false�L����ʧ@
	void ClearKeyQue();
	void Flicker();//�{�{
	void Recover();//�^��B��B�}����.....
	void UpdateDataToDraw();//Data To m_Pic

};
SHARE_PTR(Hero)

bool SortHero( Hero_RawPtr a,Hero_RawPtr b);
