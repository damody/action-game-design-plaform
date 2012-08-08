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
	//趴在地上
	FORWARD_LYING,
	//躺在地上
	BACKWARD_LYING,
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
	//FREE_SKILL, 可以直接使用walking

	//特殊絕招，方向鍵無效，可以遁地且無重力
	UNIQUE_SKILL,
	//基本動作結束值
	BASIC_ACTION_END
};
};

