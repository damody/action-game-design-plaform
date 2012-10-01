#pragma once
#include <string>
#include <map>
#include "Lua/LuaCell.h"

class LuaMap : public std::map<int, std::string>
{
public:
	LuaMap() {}
	LuaMap( LuaCell_Sptr lsptr, std::string tableName );
	LuaMap( std::string path, std::string tableName );
	~LuaMap() {}

	void LoadData( LuaCell_Sptr lsptr, std::string tableName );
	void LoadData( std::string path, std::string tableName );

	int FindKey( std::string strValue );
	static bool WriteLua ( std::string path, std::string formatString, ... );
};
//typedef LuaMap HeroAction;

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
	"FallingFront",
	"FallingBack",
	"BasicActionEnd"
};