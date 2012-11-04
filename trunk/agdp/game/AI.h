#pragma once
#include "Lua/LuaCell.h"
#include "game/Hero.h"
#include "Lua/LuaCell.h"
#include <string.h>

class AI
{
public:
	AI( Hero* hero );
	AI( Hero* hero , std::wstring luaPath );
	bool RegisterLua( std::wstring luaPath );
	//
	inline void SetON(){ m_Enable = true; }
	inline void SetOFF(){ m_Enable = false; }
	inline bool IsEnable(){ return m_Enable; }
	void Update();
public:
	Hero* m_Hero;
private:
	bool m_Enable;
	LuaCell_Sptr m_LuaCell;

};