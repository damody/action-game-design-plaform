#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include "math/Vector3.h"
#include "math/Polygon2D.h"
#include <deque>

class Hero;

//攻擊種類
struct AttackType
{
	//攻擊種類名稱
	//Punsh 拳擊
	//Knife 刀
	//Fire  火
	//Freeze 冰
	//Burst  爆裂
	std::string m_Name;
	//名字的 Hash
	size_t	m_TypeHash;
	//可被冶癒的百分比
	float	m_HealablePercent;
	//使用的特效文件名
	std::string	m_ShaderName;
};

//攻擊型態管理者
class AttackTypeManager
{
public:
	//註冊新攻擊型態，回傳產生的 hash 值
	size_t RegisterAttackType(const AttackType &);
	//用 hash 值，找到原來的攻擊型態
	const AttackType& FindAttackType(size_t hash);
};


//每一個攻擊判定所含的資訊
struct Attack
{
	//攻擊位置
	Vector3	m_Position;
	//範圍
	Polygon2D m_Area;
	//Z方向的寬度
	int	m_ZWidth;
	//傷害
	int	m_Damage;
	//絕對傷害
	int	m_FixDamage;
	//判定強度
	int	m_Strength;
	//傷害種類 Hash 由字串產生
	size_t	m_TypeHash;
};
typedef std::vector<Attack> Attacks;


//必要的基本動作定義
enum HeroAction
{
	//站立
	STANDING,
	//走路
	WALKING,
	//跑步
	RUNNING,
	//停止跑步
	STOP_RUNNING,
	//負重行走
	HEAVY_WEAPON_WALK,
	//負重跑步
	HEAVY_WEAPON_RUN,
	//輕武器站攻
	LIGHT_WEAPON_STAND_ATTACK,
	//輕武器跳攻
	LIGHT_WEAPON_JUMP_ATTACK,
	//輕武器跑攻
	LIGHT_WEAPON_RUN_ATTACK,
	//輕武器衝攻
	LIGHT_WEAPON_DASH_ATTACK,
	//輕武器丟出
	LIGHT_WEAPON_THROW,
	//重武器丟出
	HEAVY_WEAPON_THROW,
	//輕武器跳起時丟出
	LIGHT_WEAPON_JUMP_THROW,
	//重武器跳起時丟出
	HEAVY_WEAPON_JUMP_THROW,
	//喝飲料
	DRINK,
	//輕拳
	LIGHT_PUNCH,
	//輕腳
	LIGHT_KICK,
	//重拳
	HEAVY_PUNCH,
	//重腳
	HEAVY_KICK,
	//終結拳
	SUPER_PUNCH,
	//終結腳
	SUPER_KICK,
	//跳拳
	JUMP_PUNCH,
	//跳腳
	JUMP_KICK,
	//跑拳
	RUN_PUNCH,
	//跑腳
	RUN_KICK,
	//前空翻
	FORWARD_FLY_ROWING,
	//後空翻
	BACKWARD_FLY_ROWING,
	//前滾
	FORWARD_ROWING,
	//後滾
	BACKWARD_ROWING,
	//防禦
	DEFEND,
	//反擊拳
	DEFEND_PUNCH,
	//反擊腳
	DEFEND_KICK,
	//抓人
	CATCHING,
	//被抓
	CAUGHT,
	//跌倒
	FALLING,
	//跳
	JUMP,
	//蹲
	CROUCH,
	//受傷
	INJURED,
	//趴在地上
	FORWARD_LYING,
	//躺在地上
	BACKWARD_LYING,
	//放絕招
	UNIQUE_SKILL,
	//基本動作結束值
	BASIC_ACTION_END
};


//每一個動作 Frame 所含的資訊
struct FrameInfo
{
	//動作狀態
	HeroAction m_HeroAction;
	//Frame index of all
	int	m_FrameIndex;
	//人物X方向偏移修正量
	int	m_OffsetX;
	//人物Y方向偏移修正量
	int	m_OffsetY;
	//消耗MP
	int	m_ConsumeMP;
	//消耗HP
	int	m_ConsumeHP;
	//上下的移動可能
	int	m_ZMoveable;
	//這個動作的防禦力
	int	m_Defend;
	//這個 Frame 執行的時間
	float	m_FrameTime;
	//加速度
	Vector3	m_Acceleration;
	//固定移動量
	Vector3	m_FixMove;
	//身體
	Polygon2Ds	m_Bodys;
	//攻擊判定
	Attacks		m_Attacks;
};


//每一位玩家所要記錄的資訊
struct PlayerRecord
{
	//玩家名稱
	std::string	m_Name;
	//殺人數
	int	m_KilledSum;
	//總傷害
	int	m_AttackSum;
	//總失血量
	int	m_HPLostSum;
	//總MP使用量
	int	m_MPUsageSum;
	//總回血量
	int	m_HealSum;
	//總撿物品數
	int	m_Picking;
	//有沒有贏
	bool	m_Win;
};


//每一個英雄需要用到的資訊
struct HeroInfo
{
	//人物名稱
	std::string	m_Name;
	//目前動作狀態
	HeroAction	m_Status;
	//目前魔量
	int		m_MP;
	//-1:invisible 0:flash 1:visible
	int		m_Visable;
	//最大魔量
	int		m_MaxMP;
	//目前血量
	int		m_HP;
	//最大血量
	int		m_MaxHP;
	//目前護盾值
	int		m_Shield;
	//擊倒值，會影響可否授身
	int		m_Fall;
	//最大擊倒值
	int		m_MaxFall;
	//防禦值
	int		m_Defend;
	//最大防禦值
	int		m_MaxDefend;
	//角色是否還活著
	int		m_Alive;
	//目前剩下的幾條命
	int		m_Life;
	//物理防禦力
	int		m_PhysicsDefense;
	//魔法防禦力
	int		m_MagicDefense;
	//目前frame還剩下的時間
	float		m_RemainTime;
	//閃爍時間
	float		m_FlashTime;
	//無敵時間
	float		m_InvincibleTime;
	//隱形時間
	float		m_InvisibleTime;
	//物理減傷
	float		m_AntiPhysics;
	//物理減傷%數
	float		m_AntiPhysicsPercent;
	//魔法減傷
	float		m_AntiMagic;
	//魔法減傷%數
	float		m_AntiMagicPercent;
	// false:Right true:Left
	bool		m_FaceSide;
};


//控制者，是按下按鍵的介面
class Controller
{
public:
	// 控制者按下按鍵
	virtual void PutKey(Hero* hero) = 0;
	virtual ~Controller(){}
};


class AI : public Controller
{
public:
	// AI 按下按鍵
	virtual void PushKey(Hero* hero);
	virtual ~AI();
};


struct InputKey
{
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
	//按下去的瞬間
	float m_Time;
	//代表的動作
	ActionKey	m_Key;
};
typedef std::deque<InputKey> InputKeys;

class Player : public Controller
{
public:
	// 玩家按下按鍵
	virtual void PushKey(Hero* hero);
	virtual ~Player();
	void	SetKeyMapping(char key, InputKey::ActionKey value);
	void	GetUserInput();
};

class Hero
{
protected:
	//目前的 Frame 還剩下多少時間
	float	m_FrameTime;
	//目前的 Frame index
	int	m_CurrentFrame;
	//英雄的資訊，由於英雄資訊常常需要傳來傳去所以用指標
	HeroInfo	*m_HeroInfo;
	//輸入鍵佇列
	InputKeys	m_InputKeys;
};
typedef std::list<Hero> Herolist;

class FighterSceneManager
{
	
};

