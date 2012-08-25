#pragma once
#include <boost/bind.hpp>
#include <deque>
#include "DX11\Vertex.h"
#include "DX11\TextureManager.h"
#include "math\Vector3.h"
#include "algo\nway.h"
#include "ball\straight.h"
#include "common\shared_ptr.h"
#include "game\EffectData.h"
#include "CtrlKey.h"
#include "HeroInfo.h"
#include "HeroAction.h"
#include <string>
#include <cmath>
#include <cstdlib>
#include <bitset>

#define KEYLIFE_AFTER_KEYUP 120
#define WAIT_FOR_KEY_RUN 30
#define FRICTION 0.5f
#define G_ACCE g_BGManager.CurrentBG()->Gravity()
#define SCALE 3.0f

namespace boost{namespace serialization{class access;}}
struct Record
{
	int Kill;    //殺敵數
	int Attack;  //攻擊
	int HPLost;  //損血量
	int MPUsage; //耗魔量
	int Picking; //拾起物品數目
	bool Status; //true: win false: lose

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & Kill;    
		ar & Attack;  
		ar & HPLost;  
		ar & MPUsage; 
		ar & Picking; 
		ar & Status; 
	}
};
SHARE_PTR(Record)

class Hero
{
private:
	int m_TimeTik;//Count down TimeTik from Frame Wait
	ClipVertex	m_Pic;
	HeroInfo_Sptr   m_HeroInfo;
	HeroAction::e	m_Action;//當下動作狀態
	std::string     m_Frame;//Current Frame
	int		m_FrameID;//Current Frame ID

	int		m_Texture;//Current Texture ID
	int		m_PicID;
	int		m_PicW;//W截切次數
	int		m_PicH;//H截切次數
	int		m_PicX;
	int		m_PicY;
	
	Vector3		m_Position;
	float		m_CenterX,m_CenterY;
	Vector3		m_Vel;
	Bodys		m_Bodys;
	float		m_Angle;
	bool		m_FaceSide; //true 右, false 左
	int		d_run;		//判定跑步用，右正左負
	std::bitset<4>	d_key;	//判斷非方向按鍵作用與否，1表示已作用，0則否，0:atk1, 1:atk2, 2:j, 3:d
	bool		d_Ground;  //判斷是否在地面上
	int		m_Team;//0為不分
	int		m_MaxRecoverHP;//最大恢復血量
	int		m_HP;
	int		m_MP;
	EffectType::e   m_Effect;
	float		m_EffectScale;
	Record_Sptr     m_Record;

	KeyQueue	m_KeyQue;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar &	m_TimeTik;
		ar &	m_Pic;
		ar &	m_HeroInfo;
		ar &	m_Action;
		ar &    m_Frame;
		ar &	m_FrameID;

		ar &	m_Texture;
		ar &    m_PicID;
		ar &	m_PicW;
		ar &	m_PicH;
		ar &	m_PicX;
		ar &	m_PicY;

		ar &	m_Position;
		ar &	m_Vel;
		ar &	m_Bodys;
		ar &	m_Angle;
		ar &	m_FaceSide;

		ar &	m_Team;
		ar &	m_MaxRecoverHP;
		ar &	m_HP;
		ar &	m_MP;
		ar &    m_Record;

		ar &	m_KeyQue; 
	}

public:
	const std::string hero;

	Hero();
	Hero(std::string h);
	void Update(float dt);
	void UpdateDataToDraw();//Data To m_Pic

	Texture_Sptr GetTexture();
	int GetTextureID();
	ClipVertex GetPic();
	int Team() const;
	const Vector3& Position();
	const Vector3& Velocity(); 

	void SetRecord(Record_Sptr r);
	void SetTeam(int team);
	void SetPosition(Vector3 pos);
	void SetEffect(EffectType::e effect);
	void PushKey(KeyInfo k);
	BodyVerteices GetBodyVerteices();
	BodyVerteices GetBodyLineVerteices();
	friend bool Creat(const Vector3 &pos, const Creation &obj, const Hero *owner);
protected:
	void Init();
	void NextFrame();
	bool ScanKeyQue();//false無控制動作
	void ClearKeyQue();
	void Flicker();//閃爍
	void Recover();//回血、氣、破防值.....
	void CreateEffect();

};
SHARE_PTR(Hero)
typedef std::vector <Hero_RawPtr> Heroes;

//bool Creat(Vector3 pos, Creation obj, const Hero *owner);
bool SortHero( Hero_RawPtr a,Hero_RawPtr b);
