#pragma once
#include <string>
#include <map>
#include "Lua/LuaCell.h"

class LuaMap : public std::map<int, std::string>
{
public:
	LuaMap() {}
	LuaMap( LuaCell_Sptr lsptr, std::string tableName )
	{
		strings keys = lsptr->GetLuaTableKeys( tableName.c_str() );
		this->clear();

		for ( int i = 0; i < ( int )keys.size(); i++ )
		{
			int _tmpKey = lsptr->GetLua<int>( "%s/%s", tableName.c_str(), keys[i].c_str() );
			( *this )[_tmpKey] = keys[i];
		}
	}
	LuaMap( std::string path, std::string tableName )
	{
		LuaCell_Sptr lsptr = LuaCell_Sptr( new LuaCell );
		lsptr->InputLuaFile( path.c_str() );
		strings keys = lsptr->GetLuaTableKeys( tableName.c_str() );
		this->clear();

		for ( int i = 0; i < ( int )keys.size(); i++ )
		{
			int _tmpKey = lsptr->GetLua<int>( "%s/%s", tableName.c_str(), keys[i].c_str() );
			( *this )[_tmpKey] = keys[i];
		}
	}
	~LuaMap() {}

	void LoadData( LuaCell_Sptr lsptr, std::string tableName )
	{
		strings keys = lsptr->GetLuaTableKeys( tableName.c_str() );
		this->clear();

		for ( int i = 0; i < ( int )keys.size(); i++ )
		{
			int _tmpKey = lsptr->GetLua<int>( "%s/%s", tableName.c_str(), keys[i].c_str() );
			( *this )[_tmpKey] = keys[i];
		}
	}
	void LoadData( std::string path, std::string tableName )
	{
		LuaCell_Sptr lsptr = LuaCell_Sptr( new LuaCell );
		lsptr->InputLuaFile( path.c_str() );
		strings keys = lsptr->GetLuaTableKeys( tableName.c_str() );
		this->clear();

		for ( int i = 0; i < ( int )keys.size(); i++ )
		{
			int _tmpKey = lsptr->GetLua<int>( "%s/%s", tableName.c_str(), keys[i].c_str() );
			( *this )[_tmpKey] = keys[i];
		}
	}
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
	"BasicActionEnd"
};