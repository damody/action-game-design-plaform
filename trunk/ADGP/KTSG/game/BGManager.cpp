#include "BGManager.h"


BGManager::BGManager(void):m_CurrentBG(NULL)
{
}


BGManager::~BGManager(void)
{
}

unsigned int BGManager::AddBG(const std::string& name,BackGround_RawPtr bg )
{
	m_BGList.push_back(name);
	m_BGMaps[name]=bg;
	return m_BGList.size()-1;
}

std::vector<std::string> BGManager::GetBGList()
{
	return m_BGList;
}

BackGround* BGManager::CurrentBG()
{
	return m_CurrentBG;
}

void BGManager::SetCurrentBG( const std::string& name )
{
	m_CurrentBG = m_BGMaps[name];
	
}


