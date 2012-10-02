#pragma once
#include "Lua/LuaCell.h"
#include <vector>
#include <string>
#include <iostream>

namespace LuaResource
{
template <class T>
std::vector< boost::shared_ptr<T> > LoadLua( std::wstring objectType )
	//if load fail , this function will return empty vector
{
	static LuaCell_Sptr luaResource;
	int idx;// luaResource's array index
	std::wstring luaPath;// loaded path    ex: hero[0] , object[1] ...
	std::vector< boost::shared_ptr<T> > data;// returned data
	boost::shared_ptr<T> dataTemp;// data's temp
	LuaCell_Sptr luaTemp;// lua's temp

	// avoid load luaResource again
	if ( luaResource.get() == NULL )
	{
		luaResource = LuaCell_Sptr( new LuaCell );
		if ( !luaResource->InputLuaFile( L"Script/luaResource.lua" ) )
		{
			printf("fatal error: can't find Script/luaResource.lua");
			system("pause");
			throw "can't find luaResource";
			return data;//inputLua fail. So return empty vector.
		}
	}
	// 参糶
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
	std::string sot(objectType.begin(), objectType.end());
	while ( luaResource->HasValue( "%s/%d", sot.c_str(), idx ) )
	{
		// initialize ptr
		luaTemp = LuaCell_Sptr( new LuaCell );
		dataTemp = boost::shared_ptr<T>( new T );
		// get lua path
		const char* tcs = luaResource->GetLua<const char*>( "%s/%d", sot.c_str(), idx );
		luaPath = std::wstring(tcs, tcs + strlen(tcs));
		// set lua file
		if( !luaTemp->InputLuaFile( luaPath.c_str() ) )
		{
			wprintf(L"error: тぃ %s",luaPath.c_str());
			continue;
		}
		// load lua's content
		dataTemp->LoadData( luaTemp );
		//--------
		data.push_back( dataTemp );
		idx++;
	}

	return data;
}
std::vector<std::wstring> LoadMusic( std::wstring musicType )
	//musicType: "mp3" or "wav"
{
	static LuaCell_Sptr luaResource;
	int idx;// luaResource's array index
	std::vector<std::wstring> data;

	// if musicType isn't mp3 or wav, return empty data
	if( musicType != L"mp3" && musicType != L"wav" )
	{
		return data;
	}

	// avoid load luaResource again
	if ( luaResource.get() == NULL )
	{
		luaResource = LuaCell_Sptr( new LuaCell );
		if ( !luaResource->InputLuaFile( L"Script/luaResource.lua" ) )
		{
			printf("fatal error: can't find Script/luaResource.lua");
			system("pause");
			throw "can't find luaResource";
			return data;//inputLua fail. So return empty vector.
		}
	}

	// 参糶
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
	while ( luaResource->HasValue( "%s/%d", std::string(musicType.begin(), musicType.end()).c_str(), idx ) )
	{
		std::wstring pathTemp;
		const char* tcs = luaResource->GetLua<const char*>( "%s/%d", std::string(musicType.begin(), musicType.end()).c_str(), idx );
		pathTemp = std::wstring(tcs, tcs + strlen(tcs));
		data.push_back( pathTemp );
		idx++;
	}

	return data;

}

bool loadKeyMap(KeyMap& rmap){
	static LuaCell_Sptr luaResource, luaKeyMap;
	int idx;// luaResource's array index
	char uku,ukd,dku,dkd,lku,lkd,rku,rkd;	//KeyMap 篶把计

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
			printf("fatal error: тぃ keymap\n");
			system("pause");
			throw "тぃ keymap";
			return false;//inputLua fail. So return empty vector.
		}
	}

	// Load Lua data
	bool avali = true;
	avali &= luaKeyMap->HasValue("keymap/UP/1");
	avali &= luaKeyMap->HasValue("keymap/UP/2");
	avali &= luaKeyMap->HasValue("keymap/DOWN/1");
	avali &= luaKeyMap->HasValue("keymap/DOWN/2");
	avali &= luaKeyMap->HasValue("keymap/LEFT/1");
	avali &= luaKeyMap->HasValue("keymap/LEFT/2");
	avali &= luaKeyMap->HasValue("keymap/RIGHT/1");
	avali &= luaKeyMap->HasValue("keymap/RIGHT/2");
	if(!avali){
		printf("fatal error: keymap Α岿粇\n");
		system("pause");
		throw "keymap Α岿粇";
		return false;
	}

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


