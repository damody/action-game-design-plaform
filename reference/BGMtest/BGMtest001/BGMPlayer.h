#ifndef _BGMPlayer_H_
#define _BGMPlayer_H_

#include <windows.h>
#include <mmsystem.h>
#include <string>
#pragma comment(lib,"winmm.lib")

enum BGMState
{
	NotReady = 0,
	Ready,
	Playing,
	Stopping,
	Pausing
};

class BGMPlayer
{
private:
	BGMState m_State;

	wchar_t  buf[128];
	std::wstring t_command;
protected:
	inline void mciSend(std::wstring command){mciSendString(command.c_str(), buf, sizeof(buf), NULL);};

public:
	void OpenBGM(std::wstring path);
	
	void PlayBGM();
	void StopBGM();
	void PauseBGM();
	void SetVolume(std::wstring volume);

	void CloseBGM();
};

void BGMPlayer::OpenBGM( std::wstring path)
{
	if(m_State != NotReady) CloseBGM();
	mciSend( L"open \""+path+L"\" Alias BGM" );
	m_State = Ready;
}

void BGMPlayer::PlayBGM()
{
	if(m_State == NotReady) return;
	mciSend( L"play BGM repeat" );
	m_State = Playing;
}

void BGMPlayer::StopBGM()
{
	if(m_State == NotReady) return;
	mciSend( L"stop BGM" );
	mciSend( L"seek BGM to start" );
	m_State = Stopping;
}


void BGMPlayer::PauseBGM()
{
	if(m_State == NotReady) return;
	mciSend( L"pause BGM" );
	m_State = Pausing;
}

void BGMPlayer::SetVolume(std::wstring volume )
{
	if(m_State == NotReady) return;
	t_command = L"setaudio BGM volume to "+volume;
	mciSend(t_command);
}


void BGMPlayer::CloseBGM()
{
	if(m_State == NotReady) return;
	mciSend( L"close BGM" );
	m_State = NotReady;
}



#endif // _BGMPlayer_H_