#pragma once
#include "Lua/LuaCell.h"
#include <vector>
#include <string>
#include <iostream>

namespace LuaResource
{
template <class T>
std::vector< boost::shared_ptr<T> > LoadLua( std::string objectType )
	//if load fail , this function will return empty vector
{
	static LuaCell_Sptr luaResource;
	int idx;// luaResource's array index
	std::string luaPath;// loaded path    ex: hero[0] , object[1] ...
	std::vector< boost::shared_ptr<T> > data;// returned data
	boost::shared_ptr<T> dataTemp;// data's temp
	LuaCell_Sptr luaTemp;// lua's temp

	// avoid load luaResource again
	if ( luaResource.get() == NULL )
	{
		luaResource = LuaCell_Sptr( new LuaCell );
		if ( !luaResource->InputLuaFile( "Script/luaResource.lua" ) )
		{
			return data;//inputLua fail. So return empty vector.
		}
	}
	// 字首統一小寫
	if( objectType.size()!=0 )
	{
		if( objectType[0]>='A' && objectType[0]<='Z' )
		{
			objectType[0] = objectType[0] + ( 'a' - 'A' );
		}
	}
	else
	{
		return data;
	}
	// Load Lua data
	idx = 1;// Lua array begin is 1
	while ( luaResource->HasValue( "%s/%d", objectType.c_str(), idx ) )
	{
		// initialize ptr
		luaTemp = LuaCell_Sptr( new LuaCell );
		dataTemp = boost::shared_ptr<T>( new T );
		// get lua path
		luaPath = luaResource->GetLua<const char*>( "%s/%d", objectType.c_str(), idx );
		// set lua file
		if( !luaTemp->InputLuaFile( luaPath.c_str() ) )
		{
			std::vector< boost::shared_ptr<T> > t;
			return t;
		}
		// load lua's content
		dataTemp->LoadData( luaTemp );
		//--------
		data.push_back( dataTemp );
		idx++;
	}

	return data;
}
std::vector<std::string> LoadMusic( std::string musicType )
	//musicType: "mp3" or "wav"
{
	static LuaCell_Sptr luaResource;
	int idx;// luaResource's array index
	std::vector<std::string> data;

	// if musicType isn't mp3 or wav, return empty data
	if( musicType != "mp3" && musicType != "wav" )
	{
		return data;
	}

	// avoid load luaResource again
	if ( luaResource.get() == NULL )
	{
		luaResource = LuaCell_Sptr( new LuaCell );
		if ( !luaResource->InputLuaFile( "Script/luaResource.lua" ) )
		{
			return data;//inputLua fail. So return empty vector.
		}
	}

	// 字首統一小寫
	if( musicType.size()!=0 )
	{
		if( musicType[0]>='A' && musicType[0]<='Z' )
		{
			musicType[0] = musicType[0] + ( 'a' - 'A' );
		}
	}
	else
	{
		return data;
	}

	// Load Lua data
	idx = 1;// Lua array begin is 1
	while ( luaResource->HasValue( "%s/%d", musicType.c_str(), idx ) )
	{
		std::string pathTemp;
		pathTemp = luaResource->GetLua<const char*>( "%s/%d", musicType.c_str(), idx );
		data.push_back( pathTemp );
		idx++;
	}

	return data;

}

bool loadKeyMap(KeyMap& rmap){
	static LuaCell_Sptr luaResource, luaKeyMap;
	int idx;// luaResource's array index
	char uku,ukd,dku,dkd,lku,lkd,rku,rkd;	//KeyMap 建構參數

	// avoid load luaResource again
	if ( luaResource.get() == NULL )
	{
		luaResource = LuaCell_Sptr( new LuaCell );
		luaKeyMap = LuaCell_Sptr( new LuaCell );
		if ( !luaResource->InputLuaFile( "Script/luaResource.lua" ) ||
			!luaResource->HasValue("keymap") ||
			!luaKeyMap->InputLuaFile(luaResource->GetLua<const char*>("keymap"))
			)
		{
			return false;//inputLua fail. So return empty vector.
		}
	}

	// Load Lua data
	ukd = *luaKeyMap->GetLua<const char*>( "keymap/UP/1");
	uku = *luaKeyMap->GetLua<const char*>( "keymap/UP/2");
	dkd = *luaKeyMap->GetLua<const char*>( "keymap/DOWN/1");
	dku = *luaKeyMap->GetLua<const char*>( "keymap/DOWN/2");
	lkd = *luaKeyMap->GetLua<const char*>( "keymap/LEFT/1");
	lku = *luaKeyMap->GetLua<const char*>( "keymap/LEFT/2");
	rkd = *luaKeyMap->GetLua<const char*>( "keymap/RIGHT/1");
	rku = *luaKeyMap->GetLua<const char*>( "keymap/RIGHT/2");
	rmap = KeyMap(ukd,uku,dkd,dku,lkd,lku,rkd,rku);
	idx = 1;// Lua array begin is 1
	while ( luaKeyMap->HasValue( "keymap/SKey/%d", idx ) )
	{
		char tUp,tDn;
		std::string tsn;
		tDn = *luaKeyMap->GetLua<const char*>( "keymap/SKey/%d/1", idx );
		tUp = *luaKeyMap->GetLua<const char*>( "keymap/SKey/%d/2", idx );
		tsn = luaKeyMap->GetLua<const char*>( "keymap/SKey/%d/3", idx );
		std::wstring twn(tsn.begin(), tsn.end());
		rmap.pushKeyMap(tDn,tUp,twn);
		idx++;
	}
	return true;
}

}


