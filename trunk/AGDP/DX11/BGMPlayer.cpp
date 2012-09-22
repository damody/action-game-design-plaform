#include "BGMPlayer.h"

void BGMPlayer::OpenBGM( std::wstring path )
{
	if ( m_State != NotReady ) { CloseBGM(); }

	mciSend( L"open \"" + path + L"\" Alias BGM" );
	m_State = Ready;
}

void BGMPlayer::PlayBGM()
{
	if ( m_State == NotReady ) { return; }

	mciSend( L"play BGM repeat" );
	m_State = Playing;
}

void BGMPlayer::StopBGM()
{
	if ( m_State == NotReady ) { return; }

	mciSend( L"stop BGM" );
	mciSend( L"seek BGM to start" );
	m_State = Stopping;
}


void BGMPlayer::PauseBGM()
{
	if ( m_State == NotReady ) { return; }

	mciSend( L"pause BGM" );
	m_State = Pausing;
}

void BGMPlayer::SetVolume( std::wstring volume )
{
	if ( m_State == NotReady ) { return; }

	t_command = L"setaudio BGM volume to " + volume;
	mciSend( t_command );
}


void BGMPlayer::CloseBGM()
{
	if ( m_State == NotReady ) { return; }

	mciSend( L"close BGM" );
	m_State = NotReady;
}
