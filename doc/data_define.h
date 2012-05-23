#pragma once
#include <string>
#include <vector>
#include "Vector3.h"
#include "Polygon.h"

//攻擊型態管理者
class AttackTypeManager
{
public:
	//註冊新攻擊型態
	bool RegisterAttackType(cosnt AttackType &);
	const AttackType& FindAttackType(size_t hash);
};

struct AttackType
{
	std::string m_Name;	//攻擊種類名
	size_t	m_TypeHash;	//名字的 Hash
	/*
	* Punsh 拳擊
	* Knife 刀
	* Fire  火
	* Freeze 冰
	* Burst  爆裂
	*/
	float	m_HealablePercent;	//可被冶癒的百分比
	std::string	m_ShaderName;	//使用的特效文件名
};

//每一個攻擊判定所含的資訊
struct Attack
{
	Polygon2D m_Area;	//範圍
	int	m_Damage,	//傷害
		m_FixDamage,	//絕對傷害
		m_Strength;	//判定強度
	size_t	m_TypeHash;	//傷害種類 Hash 由字串產生
};
typedef std::vector<Attack> Attacks;

//必要的基本動作定義
enum HeroAction
{
	STANDING,		//站立
	WALKING,		//走路
	RUNNING,		//跑步
	STOP_RUNNING,		//停止跑步
	HEAVY_WEAPON_WALK,	//負重行走
	HEAVY_WEAPON_RUN,	//負重跑步
	LIGHT_WEAPON_STAND_ATTACK,	//輕武器站攻
	LIGHT_WEAPON_JUMP_ATTACK,	//輕武器跳攻
	LIGHT_WEAPON_RUN_ATTACK,	//輕武器跑攻
	LIGHT_WEAPON_DASH_ATTACK,	//輕武器衝攻
	LIGHT_WEAPON_THROW,		//輕武器丟出
	HEAVY_WEAPON_THROW,		//重武器丟出
	LIGHT_WEAPON_JUMP_THROW,	//輕武器跳起時丟出
	HEAVY_WEAPON_JUMP_THROW,	//重武器跳起時丟出
	DRINK,			//喝飲料
	LIGHT_PUNCH,		//輕拳
	LIGHT_KICK,		//輕腳
	HEAVY_PUNCH,		//重拳
	HEAVY_KICK,		//重腳
	SUPER_PUNCH,		//終結拳
	SUPER_KICK,		//終結腳
	JUMP_PUNCH,		//跳拳
	JUMP_KICK,		//跳腳
	RUN_PUNCH,		//跑拳
	RUN_KICK,		//跑腳
	FORWARD_FLY_ROWING,	//前空翻
	BACKWARD_FLY_ROWING,	//後空翻
	FORWARD_ROWING,		//前滾
	BACKWARD_ROWING,	//後滾
	DEFEND,			//防禦
	DEFEND_PUNCH,		//反擊拳
	DEFEND_KICK,		//反擊腳
	CATCHING,		//抓人
	CAUGHT,			//被抓
	FALLING,		//跌倒
	JUMP,			//跳
	CROUCH,			//蹲
	INJURED,		//受傷
	FORWARD_LYING,		//趴在地上
	BACKWARD_LYING,		//躺在地上
	UNIQUE_SKILL,		//放絕招
	BASIC_ACTION_END	//基本動作結束值
};
	
//每一個動作 Frame 所含的資訊
struct FrameInfo
{
	HeroAction m_HeroAction; //動作狀態
	int	m_FrameIndex,	//Frame index of all
		m_OffsetX,	//人物X方向偏移修正量
		m_OffsetY,	//人物Y方向偏移修正量
		m_ConsumeMP,	//消耗MP
		m_ConsumeHP,	//消耗HP
		m_ZMoveable,	//上下的移動可能
		m_Defend;	//這個動作的防禦力
	float	m_FrameTime;	//這個 Frame 執行的時間
	Vector3	m_Acceleration,	//加速度
		m_FixMove;	//固定移動量
	Polygons	m_Bodys;	//身體
	Attacks		m_Attacks;	//攻擊判定
};

//每一位玩家所要記錄的資訊
struct PlayerRecord
{
	std::string	m_Name;	//玩家名稱
	int	m_KilledSum,	//殺人數
		m_AttackSum,	//總傷害
		m_HPLostSum,	//總失血量
		m_MPUsageSum,	//總MP使用量
		m_HealSum,	//總回血量
		m_Picking;	//總撿物品數
	bool	m_Win;		//有沒有贏
};

//每一個英雄需要用到的資訊
struct HeroInfo
{
	std::string	m_Name;		//人物名稱
	HeroAction	m_Status;	//目前動作狀態
	int		m_MP,		//目前魔量
			m_Visable,	//-1:invisible 0:flash 1:visible
			m_MaxMP,	//最大魔量
			m_HP,		//目前血量
			m_MaxHP,	//最大血量
			m_Shield,	//目前護盾值
			m_Fall,		//擊倒值，會影響可否授身
			m_MaxFall,	//最大擊倒值
			m_Defend,	//防禦值
			m_MaxDefend,	//最大防禦值
			m_Alive,	//角色是否還活著
			m_Life,		//目前剩下的幾條命
			m_PhysicsDefense,	//物理防禦力
			m_MagicDefense;		//魔法防禦力
	float		m_RemainTime,	//目前frame還剩下的時間
			m_FlashTime,	//閃爍時間
			m_InvincibleTime,	//無敵時間
			m_InvisibleTime,	//隱形時間
			m_AntiPhysicsPercent,	//物理減傷
			m_AntiPhysicsPercent,	//物理減傷%數
			m_AntiMagicPercent,	//魔法減傷
			m_AntiMagicPercent;	//魔法減傷%數
	bool		m_FaceSide;	// false:Right true:Left
};

class Controller
{
public:
	virtual void PutKey(Hero* hero) = 0;
	virtual ~Controller(){}
};

class AI : public Controller
{
public:
	virtual void PushKey(Hero* hero);
	virtual ~AI();
};

enum ActionKey
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	ATTACK4,
	JUMP,
	DEFINED,
	NONE
};

class Player : public Controller
{
public:
	virtual void PushKey(Hero* hero);
	virtual ~Player();
	void	SetKeyMapping(char key, ActionKey value);
	void	GetUserInput();
};

struct InputKey
{
	float m_Time;	//按下去的瞬間
	ActionKey	m_Key; //代表的動作
};
typedef std::deque<InputKey> InputKeys;

class Hero
{
protected:
	float	m_FrameTime;	//目前的 Frame 還剩下多少時間
	int	m_CurrentFrame;	//目前的 Frame index
	// 由於英雄資訊常常需要傳來傳去所以用指標
	HeroInfo	*m_HeroInfo;	//英雄的資訊
	InputKeys	m_InputKeys;
};
typedef std::list<Hero> Herolist;

class FighterSceneManager
{
	
};

