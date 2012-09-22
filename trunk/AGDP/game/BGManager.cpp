#include "StdGame.h"
#include "BGManager.h"
#include "ConvStr.h"

BGManager::BGManager( void ): m_CurrentBG( NULL ), m_CurrentBGM( 0 )
{
}


BGManager::~BGManager( void )
{
}

unsigned int BGManager::AddBG( const std::string& name, BackGround_Sptr bg )
{
	m_BGList.push_back( name );
	m_BGMaps[name] = bg;
	return m_BGList.size() - 1;
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
	m_CurrentBG = m_BGMaps[name].get();
}

void BGManager::SetBGMPathList( const std::vector<std::string>& list )
{
	m_BGMPathList.assign(list.begin(),list.end());
}

void BGManager::BGMPlay( int index )
{
	if (index>=(int)m_BGMPathList.size() || index<0){return;}
	m_BGMPlayer.OpenBGM(ConvStr::GetWstr(m_BGMPathList[index]));
	m_BGMPlayer.PlayBGM();
}

void BGManager::BGMPause()
{
	m_BGMPlayer.PauseBGM();
}

void BGManager::BGMStop()
{
	m_BGMPlayer.StopBGM();
}

void BGManager::SetBGMVoleum( int voleum )
{
	wchar_t buff[10];
	wsprintf(buff,L"%d",voleum);
	m_BGMPlayer.SetVolume(std::wstring(buff));
}






