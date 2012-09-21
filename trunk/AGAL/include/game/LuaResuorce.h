#pragma once
#include "Lua/LuaCell.h"
#include <vector>
#include <string>
#include <iostream>

namespace LuaResource{
	template <class T>
	std::vector< boost::shared_ptr<T> > LoadLua(std::string objectType)
	{
		static LuaCell_Sptr luaResource;
		bool result;
		int idx;// luaResource's array index
		std::string luaPath;// loaded path    ex: hero[0] , object[1] ...
		std::vector< boost::shared_ptr<T> > data;// returned data
		boost::shared_ptr<T> dataTemp;// data's temp
		LuaCell_Sptr luaTemp;// lua's temp
		

		if (luaResource.get() == NULL)
		{
			luaResource = LuaCell_Sptr( new LuaCell );
			result = luaResource->InputLuaFile("Script/luaResource.lua");
			if(!result)
			{
				return data;//inputLua fail. So return empty vector.
			}
		}
		
		idx = 1;// Lua array begin is 1
		while( luaResource->HasValue("%s/%d",objectType.c_str(),idx) )
		{
			// initialize ptr
			luaTemp = LuaCell_Sptr( new LuaCell );
			dataTemp = boost::shared_ptr<T>( new T );
			// get lua path
			luaPath = luaResource->GetLua<const char*>("%s/%d",objectType.c_str(),idx);
			// set lua file
			luaTemp->InputLuaFile( luaPath.c_str() );
			// load lua's content
			dataTemp->LoadData( luaTemp );
			data.push_back(dataTemp);
			idx++;
		}


		return data;
	}
}


