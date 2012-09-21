#pragma once

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
/*! @brief ��@���񪫥�
*/
class dsSound
{
private :
	DWORD			m_Size ;/// ���ɤj�p
	WAVEFORMATEX		m_Format ;/// �����ɮ榡
	LPDIRECTSOUNDBUFFER8	m_Buffer ;/// ����w�İ�
	bool m_isLooping;
public :
	/// �P�_�w�İϸ�ƬO�_��,���N�۰ʧ@���խ״_
	void Restore( LPDIRECTSOUNDBUFFER8 buffer );
	/// �[���W�v�B�n�D�B���q
	void MoveParameters( DWORD Frequency, LONG Pan, LONG Volume );
	///�[��q
	virtual void SetVolume( LONG Volume );
	/// �P�_�O�_����
	bool isPlaying();
	/// �H�U4�Ӥ��O�O����B����B�����B�Ȱ������
	bool Stop();
	bool Play();
	bool RePlay();
	bool Pause();
	/// ���J���ɨëإ�
	bool Create( LPCTSTR file, DWORD flags, LPDIRECTSOUND8 ds_DS, bool isLooping = false );
	/// ����إߪ�����
	void Release();
	/// �]�w�O�_�i��`��
	inline void SetLooping( bool isLooping ) {m_isLooping = isLooping;}
	/// ���o�إ߭��ɪ��w�İ�, �]��m_Buffer�Oprivate, dsDuplicate���ઽ�����o
	inline LPDIRECTSOUNDBUFFER8 GetBuffer() {return m_Buffer;};
	/// ���o���ɬO�_���`��
	inline bool GetIsLooping() {return m_isLooping;}
	dsSound();
	~dsSound();
	LONG GetVolume( );
};

/*! @brief ���Ƽ��񪫥� */
class dsDuplicate : public dsSound
{
private :
	int m_Num ;/// �`�ƶq
	LPDIRECTSOUNDBUFFER8* m_Duplicate ;
	/// �P�_��index�O�_����
	bool IsExist( int index );
public :
	/// �H�U4�Ӥ��O�O����B����B�����B�Ȱ������
	bool Stop();
	bool Play();
	bool RePlay( int index );
	bool Pause( int index );
	void SetVolume( LONG Volume );
	/// �إߦh�����ɪ����
	bool Duplicate( LPCTSTR file, DWORD flags, int num, LPDIRECTSOUND8 ds_DS, bool isLooping = false );
	/// �[���W�v�B�n�D�B���q
	void MoveDuplicateParameters( int index, DWORD Frequency, LONG Pan, LONG Volume );
	/// �惡class����l��
	void Init();
	/// ���񦹦h������
	void Release();
	/// �P�_�O�_����
	bool isPlaying( int index );
	/// ���o���h�����ɪ��Ӽ�
	inline int GetNum() {return m_Num;};
	dsDuplicate();
	~dsDuplicate();
};
}
/*! @brief �ֳt�����ļ���
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
	void AnsiToUnicode( wchar_t* unicode, const char* ansi );
public:
	WavSound(): ds_DS( NULL ), m_soundloud( -100 ) {}
	void Initialize( HWND hWnd , DWORD Channels = 2 , DWORD Freq =  22050 , DWORD BitRate = 16 );
	~WavSound();
	/// ���J�ëإߤ@�ӳ�@����,�ɦW��char*
	bool CreatSound( const char* filename, int index );
	/// ���J�ëإߤ@�Ӧ�dupnum�Ӥ��e���h������,�ɦW��char*
	bool CreatSound( const char* filename, int index, int dupnum );
	/// ���J�ëإߤ@�ӳ�@����,�ɦW��wchar_t*
	bool CreatSound( const wchar_t* filename, int index );
	/// ���J�ëإߤ@�Ӧ�dupnum�Ӥ��e���h������,�ɦW��wchar_t*  start from number 1 , don't set zero be start number
	bool CreatSound( const wchar_t* filename, int index, int dupnum );
	/// ����ثe�Ҧ�����
	void StopDevice();
	/// ����ϥ�StopDevice()���e�٦b���񪺭���
	void StartDevice();
	/// �H�U4�ӬO��@���ɥΪ�����B����B�����B�Ȱ�
	bool Play( int index );
	bool Stop( int index );
	bool RePlay( int index );
	bool Pause( int index );
	/// �H�U4�ӬO�h�����ɥΪ�����B����B�����B�Ȱ�
	bool PlayDup( int index );
	bool StopDup( int index );
	bool RePlay( int index, int index2 );
	bool Pause( int index, int index2 );
	/// �]�w�Y�ӳ�@���ɩΦh�����ɬO�_�`������
	void SetLooping( int index, bool isLooping );
	/// �W��Y�ӳ�@���ɪ��W�v�B�n�D�B���q
	void MoveParameters( int index, DWORD Frequency, LONG Pan, LONG Volume );
	/// �W��Y�Ӧh�����ɪ��W�v�B�n�D�B���q
	void MoveParameters( int index, int index2, DWORD Frequency, LONG Pan, LONG Volume );
	/// ����Ҧ�����
	void Release();
	void Release( int index );
	LONG GetVolume( int index );
	LONG GetVolume();

	void SetVolume( int index, LONG Volume );
	void SetVolume( LONG Volume );
	bool isExist( int index );
};
typedef boost::detail::thread::singleton<WavSound> WavSoundS;

class WavPlayer
{
private:
	bool isStart;
	LPDIRECTSOUND8 ds_DS;
	int m_soundloud;

	std::vector<std::string> m_List;
	std::vector<dsDuplicate*> m_DupSounds;
	std::vector<dsDuplicate*> m_mDupSound;

public:
	WavPlayer(): ds_DS( NULL ), m_soundloud( -100 ) {}
	void Initialize( HWND hWnd , DWORD Channels = 2 , DWORD Freq =  22050 , DWORD BitRate = 16 );
	~WavPlayer();

	int CreatSound( const std::string& filename, int dupnum = 20);

	void StopDevice();
	void PauseDevice();
	void StartDevice();

	bool Play( int index );
	bool Stop( int index );
	bool RePlay( int index, int index2 );
	bool Pause( int index, int index2 );

	void SetLooping( int index, bool isLooping );
	void MoveParameters( int index, int index2, DWORD Frequency, LONG Pan, LONG Volume );

	void Release();

	LONG GetVolume( int index );
	LONG GetVolume();

	void SetVolume( int index, LONG Volume );
	void SetVolume( LONG Volume );

	int GetIndex( std::string name );
};
