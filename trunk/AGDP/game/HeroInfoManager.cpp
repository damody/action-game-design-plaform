#include "game\HeroInfoManager.h"
#include "global.h"

void HeroInfoManager::AddHeroInfo( std::string name, HeroInfo_Sptr info )
{
	for ( unsigned int i = 0 ; i < info->m_PictureDatas.size(); ++i )
	{
		info->m_PictureDatas[i].m_TextureID =  g_TextureManager.AddTexture( info->m_PictureDatas[i].m_Path );
	}

	m_List.push_back( name );
	m_HeroInfoMaps[name] = info;
}

HeroInfo_Sptr HeroInfoManager::GetHeroInfo( std::string name )
{
	HeroInfoMap::iterator i = m_HeroInfoMaps.find( name );

	if ( i == m_HeroInfoMaps.end() )
	{
		return HeroInfo_Sptr();
	}

	return i->second;
}

const std::vector<std::string> HeroInfoManager::GetList()
{
	return ( const std::vector<std::string> )m_List;
}