#include "StdGame.h"
#include "HeroInfoManager.h"

void HeroInfoMG::AddHeroInfo( std::string name, HeroInfo_Sptr info )
{
	m_List.push_back(name);
	m_HeroInfoMaps[name] = info;
}

HeroInfo_Sptr HeroInfoMG::GetHeroInfo( std::string name )
{
	HeroInfoMap::iterator i = m_HeroInfoMaps.find(name);
	if(i==m_HeroInfoMaps.end()){
		return HeroInfo_Sptr();
	}
	return i->second;
}

const std::vector<std::string> HeroInfoMG::GetList()
{
	return (const std::vector<std::string>)m_List;
}