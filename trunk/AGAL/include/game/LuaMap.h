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

class KeyMap{
public:
	struct _KeyMap{
		char keyDown,keyUp;
		std::wstring keyName;
		_KeyMap(char down, char up, std::wstring name) : keyDown(down), keyUp(up), keyName(name) {}
	};
	typedef std::vector<_KeyMap> _KeyMaps;

	KeyMap(char upKeyDown, char upKeyUp, char downKeyDown, char downKeyUp, char leftKeyDown, char leftKeyUp, char rightKeyDown, char rightKeyUp)
		:up( upKeyDown, upKeyUp, L"Up" ), down(downKeyDown, downKeyUp, L"Down"), left(leftKeyDown, leftKeyUp, L"Left"), right(rightKeyDown, rightKeyUp, L"Right")
	{}
	void pushKeyMap(char down, char up, std::wstring name);
	bool isSKey(char);
	bool isKeyUp(char);
	bool isKeyExist(char);
	size_t sKeySize();
	std::wstring keyName(char);
private:
	_KeyMaps SKeys;
	_KeyMap up;
	_KeyMap down;
	_KeyMap left;
	_KeyMap right;
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
	"FallingFront",
	"FallingBack",
	"BasicActionEnd"
};