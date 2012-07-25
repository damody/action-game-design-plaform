#pragma once

//必要的基本動作定義
namespace HeroAction{
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
};

