#include "BGManager.h"


BGManager::BGManager(void)
{
}


BGManager::~BGManager(void)
{
}

unsigned int BGManager::AddBG( std::string name,BackGround_RawPtr bg )
{
	m_BGList.push_back(name);
	m_BGMaps[name]=bg;
	return m_BGList.size()-1;
}

std::vector<std::string> BGManager::GetBGList()
{
	return m_BGList;
}

BackGround_RawPtr BGManager::GetBG( std::string name )
{
	return m_BGMaps[name];
}

BackGround_RawPtr BGManager::GetBG(unsigned int id )
{
	if(id < m_BGList.size())
		return m_BGMaps[m_BGList[id]];
	else
		return NULL;
}
