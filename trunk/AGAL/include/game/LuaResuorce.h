#pragma once
#include "Lua/LuaCell.h"
#include <vector>

namespace LuaResource{
	template <class T>
	std::vector<T> LoadLua()
	{
		bool result;
		int idx;
		std::vector<T> data;
		static LuaCell_Sptr luaResource;

		if (luaResource.get() == NULL)
		{
			luaResource = LuaCell_Sptr( new LuaCell );
			result = luaResource->InputLuaFile("Script/luaResource.lua");
			if(!result)
			{
				return data;//inputLua fail. So return empty vector.
			}
		}
		



		return data;
	}
}


