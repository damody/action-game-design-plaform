#include "StdGame.h"
#include "BGManager.h"
#include "ConvStr.h"

BackGroundManager::BackGroundManager( void ): m_Current_BackGround( NULL ), m_Current_BGM( 0 )
{
}


BackGroundManager::~BackGroundManager( void )
{
}

unsigned int BackGroundManager::AddBackGround( const std::string& name, BackGround_Sptr bg )
{
	m_BackGroundList.push_back( name );
	m_BackGroundMaps[name] = bg;
	return m_BackGroundList.size() - 1;
}

std::vector<std::string> BackGroundManager::GetBackGroundList()
{
	return m_BackGroundList;
}

BackGround* BackGroundManager::GetCurrentBackGround()
{
	return m_Current_BackGround;
}

void BackGroundManager::SetCurrentBackGround( const std::string& name )
{
	m_Current_BackGround = m_BackGroundMaps[name].get();
}

void BackGroundManager::Set_BGM_PathList( const std::vector<std::string>& list )
{
	m_BGM_PathList.assign( list.begin(), list.end() );
}

void BackGroundManager::Set_BGM_Play( int index )
{
	if ( index >= ( int )m_BGM_PathList.size() || index < 0 ) {return;}

	m_BGM_Player.OpenBGM( ConvStr::GetWstr( m_BGM_PathList[index] ) );
	m_BGM_Player.PlayBGM();
}

void BackGroundManager::Set_BGM_Pause()
{
	m_BGM_Player.PauseBGM();
}

void BackGroundManager::Set_BGM_Stop()
{
	m_BGM_Player.StopBGM();
}

void BackGroundManager::Set_BGM_Voleum( int voleum )
{
	wchar_t buff[10];
	wsprintf( buff, L"%d", voleum );
	m_BGM_Player.SetVolume( std::wstring( buff ) );
}






