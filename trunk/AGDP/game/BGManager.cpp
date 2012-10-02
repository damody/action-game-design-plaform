#include "StdGame.h"
#include "BGManager.h"
#include "ConvStr.h"

BackgroundManager::BackgroundManager( void ): m_Current_Background( NULL ), m_Current_BGM( 0 )
{
}


BackgroundManager::~BackgroundManager( void )
{
}

unsigned int BackgroundManager::AddBackground( const std::wstring& name, Background_Sptr bg )
{
	m_BackgroundList.push_back( name );
	m_BackgroundMaps[name] = bg;
	return m_BackgroundList.size() - 1;
}

std::vector<std::wstring> BackgroundManager::GetBackgroundList()
{
	return m_BackgroundList;
}

Background* BackgroundManager::GetCurrentBackground()
{
	return m_Current_Background;
}

void BackgroundManager::SetCurrentBackground( const std::wstring& name )
{
	m_Current_Background = m_BackgroundMaps[name].get();
}

void BackgroundManager::Set_BGM_PathList( const std::vector<std::wstring>& list )
{
	m_BGM_PathList.assign( list.begin(), list.end() );
}

void BackgroundManager::Set_BGM_Play( int index )
{
	if ( index >= ( int )m_BGM_PathList.size() || index < 0 ) {return;}

	m_BGM_Player.OpenBGM( ConvStr::GetWstr( m_BGM_PathList[index] ) );
	m_BGM_Player.PlayBGM();
}

void BackgroundManager::Set_BGM_Pause()
{
	m_BGM_Player.PauseBGM();
}

void BackgroundManager::Set_BGM_Stop()
{
	m_BGM_Player.StopBGM();
}

void BackgroundManager::Set_BGM_Voleum( int voleum )
{
	wchar_t buff[10];
	wsprintf( buff, L"%d", voleum );
	m_BGM_Player.SetVolume( std::wstring( buff ) );
}






