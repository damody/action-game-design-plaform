#pragma once
#include <boost/bind.hpp>
#include <boost/dynamic_bitset.hpp>
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
#include "game\Record.h"
#include "Lua/LuaCell.h"
#include "game/Condition.h"
#include <string>
#include <cmath>
#include <cstdlib>
#include <bitset>

namespace boost {namespace serialization {class access;}}


class Hero
{
public:
	struct AttackRest{
		const Hero *d;		//�ĤH
		int t;				//time
	};
private:
	int				m_TimeTik;		//Count down TimeTik from Frame Wait
	ClipVertex		m_Pic;
	HeroInfo_Sptr   m_HeroInfo;
	int				m_Action;		//��U�ʧ@���A
	std::wstring    m_Frame;		//Current Frame
	int				m_FrameID;		//Current Frame ID

	int				m_Texture;		//Current Texture ID
	int				m_PicID;
	int				m_PicW;			//W�I������
	int				m_PicH;			//H�I������
	int				m_PicX;
	int				m_PicY;

	Vector3			m_Position;
	Vector3			m_Vel;
	float			m_CenterX;
	float			m_CenterY;
	FrameInfo*		m_FrameInfo;
	float			m_Angle;
	bool			m_FaceSide;		//true �k, false ��
	int			d_run;			//�P�w�]�B�ΡA�k�����t
	bool			d_Ground;		//�P�_�O�_�b�a���W
	int			m_Team;			//0������
	int			m_MaxRecoverHP;	//�̤j��_��q
	int			m_HP;
	int			m_MP;
	//EffectType::e   m_Effect;
	float			m_EffectScale;
	Record_Sptr		m_Record;
	AABB2D			m_BodyAABB;
	float			m_BodyMaxZ;
	float			m_BodyMinZ;
	AABB2D			m_AttackAABB;
	float			m_AttackMaxZ;
	float			m_AttackMinZ;
	AABB2D			m_CatchAABB;
	float			m_CatchMaxZ;
	float			m_CatchMinZ;

	int			m_FrontDefence;
	int			m_BackDefence;
	int			m_Fall;
	AttackRest		m_AtkRest;
	KeyQueue		m_KeyQue;
	Condition*	m_Condition;
	LuaCell_Sptr	m_HeroFunctionLua; //�s������HeroFunction��luastate

	//�P�_�D��V����@�λP�_�A1��ܤw�@�ΡA0�h�_�A0:atk1, 1:atk2, 2:j, 3:d
	boost::dynamic_bitset<byte> d_key;

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

	//ConditionUpdate
	inline void ConditionUpdate( float dt );
public:
	const std::wstring hero;

	Hero();
	Hero( std::wstring h );
	void			Update( float dt );
	void			UpdateDataToDraw();	//Data To m_Pic
	int				GetTextureID() const;
	int				Team() const;
	ClipVertex		GetPic() const;
	Texture_Sptr	GetTexture() const;
	const Vector3&	Position() const;
	const Vector3&	Velocity() const;
	bool			IsAlive() const;
	bool			GetFace() const;
	AABB2D&			GetBodyAABB();
	AABB2D&			GetAttackAABB();
	AABB2D&			GetCatchAABB();
	Bodys&			GetBodys( ) const;
	Attacks&		GetAttacks( ) const;
	CatchInfos&		GetCatches( ) const;
	Record_Sptr		GetRecord() const;
	void			SetRecord( Record_Sptr r );
	void			SetTeam( int team );
	void			SetPosition( const Vector3& pos );
	//void			SetEffect( EffectType::e effect );
	void			PushKey( KeyInfo& k );
	PolygonVerteices GetPolygonVerteices() const;
	PolygonVerteices GetPolygonLineVerteices() const;
	//���A
	static void	RegisterFunctionToLua( LuaCell_Sptr luadata );
	inline void	AddCondition( int effectIndex , int time );
	inline void	ModifyMaxHP( int delta );
	inline void	ModifyHP( int delta );
	inline void	ModifyMP( int delta );
	inline void	ModifyFall( int delta );
	inline void	ModifyFrontDefence( int delta );
	inline void	ModifyBackDefence( int delta );
	inline void	ChangeTeam( int newTeam );
	//�гy����
	friend bool			Creat( const Vector3& pos, const Creation& obj, bool face, const Record_Sptr owner );
	//�I���P�w��
	friend Polygon2Ds	GetHeroBodys( const Hero& r );
	friend Polygon2Ds	GetHeroAttacks( const Hero& r );
	friend Polygon2Ds	GetHeroCatches( const Hero& r );
	void beCaught( const CatchInfo& rCatch, const Vector3& hitPos, bool rFace );
	void beAttack( const Attack *rAtk, const Hero *rHero, const Vector3& hitPos, bool rFace );
	//void beHit(const )

protected:
	void		Init();
	void		NextFrame();
	void		SwitchFrame( std::wstring rFrame, int rFrameID );
	FrameInfo*	FindFrame( std::wstring rframe, int rframeID );
	bool		ScanKeyQue();	//false�L����ʧ@
	void		ClearKeyQue();
	void		Flicker();		//�{�{
	void		Recover();		//�^��B��B�}����.....
	void		CreateEffect();
	void		UpdateVel( int dx, int dz );

	bool		isKeyUsed( char ) const;
	void		keyUsed( char );
	void		newKey( char );
};
SHARE_PTR( Hero );
typedef std::vector <Hero_RawPtr> Heroes;

//bool Creat(Vector3 pos, Creation obj, const Hero *owner);
bool SortHero( Hero_RawPtr a, Hero_RawPtr b );

struct GetBodyAABB2D
{
	AABB2D& operator()(Hero* hero){return (hero->GetBodyAABB());}
};

struct GetAttackAABB2D
{
	AABB2D& operator()(Hero* hero){return (hero->GetAttackAABB());}
};

struct GetCatchAABB2D
{
	AABB2D& operator()(Hero* hero){return (hero->GetCatchAABB());}
};

struct GetPolygonsFromBody
{
	Polygon2Ds operator()(Hero* hero){return (GetHeroBodys(*hero));}
};

struct GetPolygonsFromAttack
{
	Polygon2Ds operator()(Hero* hero){return (GetHeroAttacks(*hero));}
};
