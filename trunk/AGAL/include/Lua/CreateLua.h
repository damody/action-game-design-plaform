/*! @brief 製造一個lua檔的類別
可以簡單的把全域的變數輸出成文字檔
*/

#pragma once
#include <vector>
#include <map>
#include <cstring>
#include <iostream>
#include <fstream>

class CreateLua
{
public:
	typedef std::vector< std::pair<std::string, int> > siVector;
	typedef std::vector< std::pair<std::string, double> > sdVector;
	typedef std::vector< std::pair<std::string, std::string> > ssVector;
	/// 加入int型態的變數到全域
	void AddInt(std::string name, int num);
	/// 加入double型態的變數到全域
	void AddDouble(std::string name, double num);
	/// 加入字串型態的變數到全域
	void AddString(std::string name, std::string num);
	/// 加入原始字串的到全域，會換行
	void AddRawString(std::string name, std::string num);
	/// 存檔，傳入要儲存的路徑
	void SaveLua(std::wstring str);
	/// 清除記錄
	void clear();
private:
	siVector siv;
	sdVector sdv;
	ssVector ssv,rsv;
};
