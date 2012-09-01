#include "StdGame.h"
#include "BGManager.h"

BGManager::BGManager(void):m_CurrentBG(NULL),m_CurrentBGM(0)
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



int BGManager::AddBGM( const std::string& name, int index )
{
	m_BGMList.push_back(name);
	m_BGMMap[name]=index;
	return m_BGMList.size()-1;
}

std::vector<std::string> BGManager::GetBGMList()
{
	return m_BGMList;
}

void BGManager::SetCurrentBGM( const std::string& name )
{
	m_CurrentBGM = m_BGMMap[name];
}

int BGManager::CurrentBGM()
{
	return m_CurrentBGM;
}
