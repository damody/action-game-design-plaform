
#if !defined(WAVESOUND_H_)
#define WAVESOUND_H_

#include <mmsystem.h>
#include <dsound.h>
#include <map>
#include <vector>
#include <algorithm>
#include <wtypes.h>
#include <cstring>
#include <string>
#include <boost/thread/detail/singleton.hpp>

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"winmm.lib")
namespace
{
	/*! @brief 單一播放物件
	*/
	class dsSound
	{
	private :
		DWORD			m_Size ;/// 音檔大小
		WAVEFORMATEX		m_Format ;/// 音效檔格式
		LPDIRECTSOUNDBUFFER8	m_Buffer ;/// 播放緩衝區
		bool m_isLooping;
	public :
		/// 判斷緩衝區資料是否遺失,有就自動作嘗試修復
		void Restore(LPDIRECTSOUNDBUFFER8 buffer );
		/// 加減頻率、聲道、音量
		void MoveParameters(DWORD Frequency, LONG Pan, LONG Volume);
		///加減音量
		virtual void SetVolume(LONG Volume);
		/// 判斷是否播放中
		bool isPlaying();
		/// 以下4個分別是停止、播放、重播、暫停的函數
		bool Stop();
		bool Play();
		bool RePlay();
		bool Pause();
		/// 載入音檔並建立
		bool Create( LPCTSTR file, DWORD flags, LPDIRECTSOUND8 ds_DS, bool isLooping = false);
		/// 釋放建立的音檔
		void Release();
		/// 設定是否進行循環
		inline void SetLooping(bool isLooping){m_isLooping = isLooping;}
		/// 取得建立音檔的緩衝區, 因為m_Buffer是private, dsDuplicate不能直接取得
		inline LPDIRECTSOUNDBUFFER8 GetBuffer(){return m_Buffer;};
		/// 取得音檔是否為循環
		inline bool GetIsLooping(){return m_isLooping;}
		dsSound();
		~dsSound();
		LONG GetVolume( );
	};

	/*! @brief 重複播放物件 */
	class dsDuplicate : public dsSound 
	{
	private :
		int m_Num ;/// 總數量
		LPDIRECTSOUNDBUFFER8 *m_Duplicate ;
		/// 判斷此index是否有效
		bool IsExist(int index);
	public :
		/// 以下4個分別是停止、播放、重播、暫停的函數
		bool Stop();
		bool Play();
		bool RePlay(int index);
		bool Pause(int index);
		void SetVolume(LONG Volume);
		/// 建立多重音檔的函數
		bool Duplicate( LPCTSTR file, DWORD flags, int num, LPDIRECTSOUND8 ds_DS, bool isLooping = false);
		/// 加減頻率、聲道、音量
		void MoveDuplicateParameters( int index, DWORD Frequency, LONG Pan, LONG Volume);
		/// 對此class做初始化
		void Init();
		/// 釋放此多重音檔
		void Release();
		/// 判斷是否播放中
		bool isPlaying(int index);
		/// 取得此多重音檔的個數
		inline int GetNum(){return m_Num;};
		dsDuplicate();
		~dsDuplicate();
	};
}
/*! @brief 快速的音效播放器
*/
class WavSound
{
private:
	bool isStart;
	LPDIRECTSOUND8 ds_DS;
	int m_soundloud;
	std::map<int, dsSound*> m_SoundMap;
	std::map<int, dsSound*>::iterator m_SoundMapPos;
	std::map<int, dsDuplicate*> m_DupSoundMap;
	std::map<int, dsDuplicate*>::iterator m_DupSoundMapPos;
	std::vector<dsSound*> m_vSound;
	std::vector<dsSound*>::iterator m_vSoundPos;
	std::map<int, dsDuplicate*> m_mDupSound;
	std::map<int, dsDuplicate*>::iterator m_mDupSoundPos;
	void AnsiToUnicode(wchar_t *unicode, const char *ansi);
public:
	WavSound():ds_DS(NULL), m_soundloud(-100){}
	void Initialize(HWND hWnd , DWORD Channels = 2 , DWORD Freq =  22050 , DWORD BitRate = 16);
	~WavSound();
	/// 載入並建立一個單一音檔,檔名用char*
	bool CreatSound(const char* filename, int index);
	/// 載入並建立一個有dupnum個內容的多重音檔,檔名用char*
	bool CreatSound(const char* filename, int index, int dupnum);
	/// 載入並建立一個單一音檔,檔名用wchar_t*
	bool CreatSound(const wchar_t* filename, int index);
	/// 載入並建立一個有dupnum個內容的多重音檔,檔名用wchar_t*  start from number 1 , don't set zero be start number
	bool CreatSound(const wchar_t* filename, int index, int dupnum);
	/// 停止目前所有音檔
	void StopDevice();
	/// 播放使用StopDevice()之前還在播放的音檔
	void StartDevice();
	/// 以下4個是單一音檔用的播放、停止、重播、暫停
	bool Play(int index);
	bool Stop(int index);
	bool RePlay(int index);
	bool Pause(int index);
	/// 以下4個是多重音檔用的播放、停止、重播、暫停
	bool PlayDup(int index);
	bool StopDup(int index);
	bool RePlay(int index, int index2);
	bool Pause(int index, int index2);
	/// 設定某個單一音檔或多重音檔是否循環播放
	void SetLooping(int index, bool isLooping);
	/// 增減某個單一音檔的頻率、聲道、音量
	void MoveParameters(int index, DWORD Frequency, LONG Pan, LONG Volume);
	/// 增減某個多重音檔的頻率、聲道、音量
	void MoveParameters(int index, int index2, DWORD Frequency, LONG Pan, LONG Volume);
	/// 釋放所有音檔
	void Release();
	void Release(int index);
	LONG GetVolume(int index );
	LONG GetVolume();

	void SetVolume(int index, LONG Volume);
	void SetVolume(LONG Volume);
	bool isExist(int index);
};
typedef boost::detail::thread::singleton<WavSound> WavSoundS;

class WavPlayer{
private:
	bool isStart;
	LPDIRECTSOUND8 ds_DS;
	int m_soundloud;

	std::vector<std::string> m_List;
	std::vector<dsDuplicate*> m_DupSounds;
	std::vector<dsDuplicate*> m_mDupSound;

public:
	WavPlayer():ds_DS(NULL), m_soundloud(-100){}
	void Initialize(HWND hWnd , DWORD Channels = 2 , DWORD Freq =  22050 , DWORD BitRate = 16);
	~WavPlayer();

	int CreatSound(const std::string& filename, int dupnum);

	void StopDevice();
	void PauseDevice();
	void StartDevice();

	bool Play(int index);
	bool Stop(int index);
	bool RePlay(int index, int index2);
	bool Pause(int index, int index2);

	void SetLooping(int index, bool isLooping);
	void MoveParameters(int index, int index2, DWORD Frequency, LONG Pan, LONG Volume);

	void Release();

	LONG GetVolume(int index );
	LONG GetVolume();

	void SetVolume(int index, LONG Volume);
	void SetVolume(LONG Volume);

	int GetIndex(std::string name);
};
#endif
