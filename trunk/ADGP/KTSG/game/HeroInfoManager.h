#pragma once
#include "stdafx.h"
#include <cstdio>
#include <windows.h>

#include "common\shared_ptr.h"
#include "game/HeroInfo.h"
namespace boost{namespace serialization{class access;}}
class HeroInfoMG
{
public:
	HeroInfoMG(void){}
	~HeroInfoMG(void){}
	void AddHeroInfo(std::string name, HeroInfo_Sptr info);
	HeroInfo_Sptr GetHeroInfo(std::string name);
	const std::vector<std::string> GetList();
private:
	std::vector<std::string> m_List;
	HeroInfoMap		 m_HeroInfoMaps;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar &	m_List;
		ar &	m_HeroInfoMaps;
	}
};












