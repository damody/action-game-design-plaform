#include "StdGame.h"
#include "AI.h"

AI::AI( Hero* hero ):m_Enable(0)
{
	m_Hero = hero;
	if ( !RegisterLua(L"Script\\AI\\AITest.lua") )
	{
		wprintf(L"Register AI failed .Check %s",L"Script\\AI\\AITest.lua");
	}
}

AI::AI( Hero* hero , std::wstring luaPath ):m_Enable(0)
{
	m_Hero = hero;
	if ( !RegisterLua(luaPath) )
	{
		wprintf(L"Register AI failed .Check %s",luaPath.c_str());
	}
}

bool AI::RegisterLua( std::wstring luaPath )
{
	//Get Lua
	if( m_LuaCell.get() == NULL )
	{
		m_LuaCell = LuaCell_Sptr( new LuaCell );
		if ( !m_LuaCell->InputLuaFile( luaPath.c_str() ) )
		{
			wprintf(L"fatal error: can't load Lua file.  %s" , luaPath.c_str());
			system("pause");
			throw "can't load Lua file";
			return false;
		}
	}
	
	luabind::module( m_LuaCell->GetLuaState() )
		[
			luabind::class_<Hero>("Hero")
			.def(luabind::constructor<>())
			.def("GetHP", &Hero::GetHP)
			.def("GetMP", &Hero::GetMP)
		];

}
