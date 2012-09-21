#pragma once
#include <string>
#include <map>
#include "Lua/LuaCell.h"

class LuaMap : public std::map<std::string, int>
{
public:
	LuaMap(){}
	LuaMap(LuaCell_Sptr lsptr)
	{
		keys.clear();
		keys = lsptr->GetLuaTableKeys("Action");
		this->clear();
		for(int i=0; i<keys.size(); i++)
		{
			(*this)[keys[i]] = lsptr->GetLua<int>("Action/%s", keys[i].c_str());
		}
	}
	LuaMap(std::string path)
	{
		LuaCell_Sptr lsptr = LuaCell_Sptr( new LuaCell );
		lsptr->InputLuaFile(path.c_str());
		keys.clear();
		keys = lsptr->GetLuaTableKeys("Action");
		this->clear();
		for(int i=0; i<keys.size(); i++)
		{
			(*this)[keys[i]] = lsptr->GetLua<int>("Action/%s", keys[i].c_str());
		}
	}
	~LuaMap(){}

	strings GetKeys()
	{
		return keys;
	}
	void LoadHeroAction(LuaCell_Sptr lsptr)
	{
		keys.clear();
		keys = lsptr->GetLuaTableKeys("Action");
		this->clear();
		for(int i=0; i<keys.size(); i++)
		{
			(*this)[keys[i]] = lsptr->GetLua<int>("Action/%s", keys[i].c_str());
		}
	}
	void LoadHeroAction(std::string path)
	{
		LuaCell_Sptr lsptr = LuaCell_Sptr( new LuaCell );
		lsptr->InputLuaFile(path.c_str());
		keys.clear();
		keys = lsptr->GetLuaTableKeys("Action");
		this->clear();
		for(int i=0; i<keys.size(); i++)
		{
			(*this)[keys[i]] = lsptr->GetLua<int>("Action/%s", keys[i].c_str());
		}
	}
private:
	strings keys;
};
//typedef LuaMap HeroAction;

//必要的基本動作定義
struct HeroAction
{
	enum e
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

	        //預備攻擊
	        BEFORE_ATTACK,
	        //攻擊
	        ATTACKING,
	        //收招
	        AFTER_ATTACK,
	        //預備終結技
	        BEFORE_SUPER_ATTACK,
	        //終結技
	        SUPER_ATTACKING,
	        //收終結技
	        AFTER_SUPER_ATTACK,
	        //預備跳攻
	        BEFORE_JUMP_ATTACK,
	        //跳攻
	        JUMP_ATTACKING,
	        //收跳攻
	        AFTER_JUMP_ATTACK,
	        //預備跑攻
	        BEFORE_RUN_ATTACK,
	        //跑攻
	        RUN_ATTACKING,
	        //收跑攻
	        AFTER_RUN_ATTACK,
	        //預備衝跳攻
	        BEFORE_DASH_ATTACK,
	        //衝跳攻
	        DASH_ATTACKING,
	        //收衝跳攻
	        AFTER_DASH_ATTACK,
	        //空翻
	        FLIP,
	        //滾
	        ROllING,

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
	        //跳，剛進入此狀態的影格會得到向上的速度
	        JUMP,
	        //衝跳
	        DASH,
	        //蹲
	        CROUCH,
	        //受傷
	        INJURED,
	        //倒在地上
	        LYING,
	        //空中，方向鍵可改變面對方向
	        IN_THE_AIR,
	        //預備放招
	        BEFORE_SKILL,
	        //收招
	        AFTER_SKILL,
	        //空中絕招，方向鍵無效，無重力但會著地
	        AIR_SKILL,
	        //直線前進絕招，Z方向鍵有效
	        X_AXIS_SKILL,
	        //垂線前進絕招，X方向鍵有效
	        Z_AXIS_SKILL,
	        //地面絕招，方向鍵無效
	        GROUND_SKILL,
	        //地面任意移動絕招，四方向鍵有效
	        FREE_SKILL,

	        //特殊絕招，方向鍵無效，可以遁地且無重力
	        UNIQUE_SKILL,
	        //基本動作結束值
	        BASIC_ACTION_END
	};
};

const std::string HeroActionTable[] =
{
	"Standing",
	"Walking",
	"Running",
	"StopRunning",
	"HeavyWeaponWalk",
	"HeavyWeaponRun",
	"LightWeaponStandAttack",
	"LightWeaponJumpAttack",
	"LightWeaponRunAttack",
	"LightWeaponDashAttack",
	"LightWeaponThrow",
	"HeavyWeaponThrow",
	"LightWeaponJumpThrow",
	"HeavyWeaponJumpThrow",
	"Drink",
	"BeforeAttack",
	"Attacking",
	"AfterAttack",
	"BeforeSuperAttack",
	"SuperAttacking",
	"AfterSuperAttack",
	"BeforeJumpAttack",
	"JumpAttacking",
	"AfterJumpAttack",
	"BeforeRunAttack",
	"RunAttacking",
	"AfterRunAttack",
	"BeforeDashAttack",
	"DashAttacking",
	"AfterDashAttack",
	"Flip",
	"Rolling",
	"Defend",
	"DefendPunch",
	"DefendKick",
	"Catching",
	"Caught",
	"Falling",
	"Jump",
	"Dash",
	"Crouch",
	"Injured",
	"Lying",
	"InTheAir",
	"BeforeSkill",
	"AfterSkill",
	"AirSkill",
	"XAxisSkill",
	"ZAxisSkill",
	"GroundSkill",
	"UniqueSkill",
	"BasicActionEnd"
};