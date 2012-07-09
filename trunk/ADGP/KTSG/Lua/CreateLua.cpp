#include "CreateLua.h"

void CreateLua::AddInt( std::string name, int num )
{
	siv.push_back(std::make_pair(name,num));
}

void CreateLua::AddDouble( std::string name, double num )
{

	sdv.push_back(std::make_pair(name,num));
}

void CreateLua::AddString( std::string name, std::string str )
{
	ssv.push_back(std::make_pair(name,str));
}

void CreateLua::AddRawString( std::string name, std::string str )
{
	rsv.push_back(std::make_pair(name,str));
}

void CreateLua::SaveLua( std::wstring str )
{
	std::ofstream fout;
	fout.open(str.c_str());
	if (!fout.is_open()) return;
	for (siVector::iterator it = siv.begin();it != siv.end();it++)
	{
		fout << it->first.c_str() << "=" << it->second << std::endl;
	}
	for (sdVector::iterator it = sdv.begin();it != sdv.end();it++)
	{
		fout << it->first.c_str() << "=" << it->second << std::endl;
	}
	for (ssVector::iterator it = ssv.begin();it != ssv.end();it++)
	{
		fout << it->first.c_str() << "=\"" << it->second.c_str() << "\"" << std::endl;
	}
	for (ssVector::iterator it = rsv.begin();it != rsv.end();it++)
	{
		fout << it->first.c_str() << "=" << it->second.c_str() << std::endl;
	}
	fout.close();
}

void CreateLua::clear()
{
	siv.clear();
	sdv.clear();
	ssv.clear();
	rsv.clear();
}
