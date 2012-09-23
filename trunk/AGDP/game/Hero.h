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
#include "game\HeroInfo.h"
#include "game\HeroAction.h"
#include "game\Record.h"
#include <string>
#include <cmath>
#include <cstdlib>
#include <bitset>

#define KEYLIFE_AFTER_KEYUP 120
#define WAIT_FOR_KEY_RUN 30
#define FRICTION 0.5f
#define G_ACCE g_BackgroundManager.GetCurrentBackground()->Gravity()
#define SCALE 3.0f

namespace boost {namespace serialization {class access;}}

class Hero
{
private:
	int				m_TimeTik;		//Count down TimeTik from Frame Wait
	ClipVertex		m_Pic;
	HeroInfo_Sptr   m_HeroInfo;
	int				m_Action;		//��U�ʧ@���A
	std::string     m_Frame;		//Current Frame
	int				m_FrameID;		//Current Frame ID

	int				m_Texture;		//Current Texture ID
	int				m_PicID;
	int				m_PicW;			//W�I������
	int				m_PicH;			//H�I������
	int				m_PicX;
	int				m_PicY;

	Vector3			m_Position;
	float			m_CenterX, m_CenterY;
	Vector3			m_Vel;
	FrameInfo*		m_FrameInfo;
	float			m_Angle;
	bool			m_FaceSide;		//true �k, false ��
	int				d_run;			//�P�w�]�B�ΡA�k�����t
	std::bitset<4>	d_key;			//�P�_�D��V����@�λP�_�A1��ܤw�@�ΡA0�h�_�A0:atk1, 1:atk2, 2:j, 3:d
	bool			d_Ground;		//�P�_�O�_�b�a���W
	int				m_Team;			//0������
	int				m_MaxRecoverHP;	//�̤j��_��q
	int				m_HP;
	int				m_MP;
	EffectType::e   m_Effect;
	float			m_EffectScale;
	Record_Sptr     m_Record;

	int				m_FrontDefence;
	int				m_BackDefence;
	int				m_Fall;

	KeyQueue		m_KeyQue;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& 	m_TimeTik;
		ar& 	m_Pic;
		ar& 	m_HeroInfo;
		ar& 	m_Action;
		ar&     m_Frame;
		ar& 	m_FrameID;
		ar& 	m_Texture;
		ar&     m_PicID;
		ar& 	m_PicW;
		ar& 	m_PicH;
		ar& 	m_PicX;
		ar& 	m_PicY;
		ar& 	m_Position;
		ar& 	m_Vel;
		ar& 	m_FrameInfo;
		ar& 	m_Angle;
		ar& 	m_FaceSide;
		ar& 	m_Team;
		ar& 	m_MaxRecoverHP;
		ar& 	m_HP;
		ar& 	m_MP;
		ar&     m_Record;
		ar& 	m_KeyQue;
	}

public:
	const std::string hero;

	Hero();
	Hero( std::string h );
	void Update( float dt );
	void UpdateDataToDraw();	//Data To m_Pic
	Texture_Sptr GetTexture();
	int GetTextureID();
	ClipVertex GetPic();
	int Team() const;
	const Vector3& Position();
	const Vector3& Velocity();
	Bodys getBodys( );
	Attacks getAtks( );
	CatchInfos getCatches( );
	void SetRecord( Record_Sptr r );
	void SetTeam( int team );
	void SetPosition( Vector3 pos );
	void SetEffect( EffectType::e effect );
	void PushKey( KeyInfo k );
	PolygonVerteices GetPolygonVerteices();
	PolygonVerteices GetPolygonLineVerteices();
	//�гy����
	friend bool Creat( const Vector3& pos, const Creation& obj, bool face, const Record_Sptr owner );
	//�I���P�w��
	friend Polygon2Ds getHeroBodys( const Hero& r );
	friend Polygon2Ds getHeroAtks( const Hero& r );
	friend Polygon2Ds getHeroCatches( const Hero& r );
	void beCaught( const CatchInfo& rCatch, Vector3 hitPos, bool rFace );
	void beAttack( const Attack& rAtk, const Record_Sptr& rHero, Vector3 hitPos, bool rFace );
	//void beHit(const )

protected:
	void Init();
	void NextFrame();
	void SwitchFrame( std::string rFrame, int rFrameID );
	FrameInfo* FindFrame( std::string rframe, int rframeID );
	bool ScanKeyQue();	//false�L����ʧ@
	void ClearKeyQue();
	void Flicker();		//�{�{
	void Recover();		//�^��B��B�}����.....
	void CreateEffect();
	void UpdateVel( int dx, int dz );

	bool isKeyUsed( char );
	void keyUsed( char );
	void newKey( char );
};
SHARE_PTR( Hero );
typedef std::vector <Hero_RawPtr> Heroes;

//bool Creat(Vector3 pos, Creation obj, const Hero *owner);
bool SortHero( Hero_RawPtr a, Hero_RawPtr b );

struct GetPolygonsFromBody
{
	Polygon2Ds operator()(Hero* hero){return (getHeroBodys(*hero));}
};

struct GetPolygonsFromAttack
{
	Polygon2Ds operator()(Hero* hero){return (getHeroAtks(*hero));}
};
