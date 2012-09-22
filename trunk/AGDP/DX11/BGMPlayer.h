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
#endif // _BGMPlayer_H_