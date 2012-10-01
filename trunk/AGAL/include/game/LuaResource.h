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
}


