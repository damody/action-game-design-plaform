/*! @brief 這個類別是用來與lua做簡單的溝通的類別
使用了void*與template做了同樣的功能
對lua做的包裝，用法大致如下
double a = cell.getLua<double>("table2\\table23\\table2\\1");
cell.setLua<int>("table2\\table23\\table2\\1",100);
const char* b = cell.getLua<const char*>("table2\\table23\\table2\\1");
*/
#pragma once
#include "lua.hpp"
#include <string>
#include <cstdarg>
#include <vector>
#include <common/shared_ptr.h>

#if defined (WIN32) || defined (WIN64)
#include "windows.h"
#endif

typedef std::vector<std::string> strings;


class LuaCell
{
public:
	enum BackType {INTEGER,LONGFLOAT,STRING};
	/// 初始化函數，會製造一個lua狀態機
	LuaCell();
	~LuaCell();
	/// 呼叫lua無參數的function
	bool CallLuaFunction(const char* functionName);
	/// 呼叫lua無參數的function
	bool CallLuaFunction(const char* functionName, const char* signString, ...);
	/// 讀入一個lua檔，得到這個檔的函數與變數
	bool InputLuaFile(const char* path);
#if defined(WIN32) || defined(WIN64)
	bool InputLuaFile(const wchar_t* path);
#endif
	/// 讀取lua中的變數，不可使用超過1024字元的可變字串
	template <class T> T GetLua(const char* pathString, ...);
	/// 設定lua中的變數，不可使用超過1024字元的可變字串
	template <class T> void SetLua(T data, const char* pathString, ...);
	bool AddNewTable(const char* table);
	bool HasValue(const char* pathString, ...);
	void RegisterFunction(std::string libname, const luaL_reg* reg);
	void LuaYield();
	void LuaResume();
	strings GetLuaTableKeys(const char* pathString, ...);
private:
	void 		SetValueUsePath(const char* pathString, int type, void* data);
	void*		GetValueUsePath(const char* pathString, int type );
	void*		GetValue(const char* pathString, int type, va_list vlist);
	template <class T> T GetLua() {return NULL;}
	template <> int		GetLua<int>();
	template <> double	GetLua<double>();
	template <> const char*	GetLua<const char*>();
	template <class T> void SetLua(T data) {}
	template <> void SetLua<int>(int data);
	template <> void SetLua<double>(double data);
	template <> void SetLua<const char*>(const char* data);
	bool IsDigitString(const char *str);
	lua_State* m_LuaState;
	char	m_buffer[10];
};
//要預先宣告偏特化才不會連結錯誤
template int LuaCell::GetLua<int>(const char* pathString, ...);
template double LuaCell::GetLua<double>(const char* pathString, ...);
template const char* LuaCell::GetLua<const char*>(const char* pathString, ...);
template void LuaCell::SetLua(int data, const char* pathString, ...);
template void LuaCell::SetLua(double data, const char* pathString, ...);
template void LuaCell::SetLua(const char* data, const char* pathString, ...);

SHARE_PTR(LuaCell)
