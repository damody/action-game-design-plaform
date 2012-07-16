#include "HeroInfoManager.h"

void HeroInfoMG::AddHeroInfo( std::string name, HeroInfo_Sptr info )
{
	m_List.push_back(name);
	m_HeroInfoMaps[name] = info;
}

HeroInfo_Sptr HeroInfoMG::GetHeroInfo( std::string name )
{
	return m_HeroInfoMaps[name];
}

const std::vector<std::string> HeroInfoMG::GetList()
{
	return (const std::vector<std::string>)m_List;
}