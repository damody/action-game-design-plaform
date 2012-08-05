#include <windows.h>
#include "WaveSound.h"
#include "..\ConvStr.h"
dsSound::dsSound()
{
	m_Buffer = NULL ;
}

dsSound::~dsSound()
{
	Release();
}

//建立聲音檔
bool dsSound::Create(LPCTSTR file , DWORD flags, LPDIRECTSOUND8 ds_DS,bool isLooping)
{
	HMMIO mmIO = NULL;
	MMCKINFO mmRiff ;
	MMCKINFO mmChunk ;
	bool ok ;
	LPDIRECTSOUNDBUFFER buffer1=NULL;
	//判定介面是否已建立
	if( !ds_DS ) 
		return false ;
	//移除舊介面
	Release();
	//開檔
	mmIO = mmioOpen((LPWSTR) file , NULL , MMIO_ALLOCBUF | MMIO_READ );
	if( mmIO == NULL )
		return false ;
	//取得聲音檔開頭
	mmRiff.fccType = mmioFOURCC( 'W' , 'A' , 'V' , 'E' );
	ok = mmioDescend( mmIO , &mmRiff , NULL , MMIO_FINDRIFF ) == MMSYSERR_NOERROR ;
	//取得音檔格式
	if( ok )
	{
		mmChunk.ckid = mmioFOURCC( 'f' , 'm' , 't' , ' ' );
		ok = mmioDescend( mmIO , &mmChunk , &mmRiff , MMIO_FINDCHUNK ) == MMSYSERR_NOERROR ;
	}
	if( ok )
		ok = mmioRead( mmIO , (char*)&m_Format , sizeof( WAVEFORMATEX )) != -1 ;
	if( ok )
		ok = mmioAscend( mmIO , &mmChunk , 0 ) == MMSYSERR_NOERROR ;
	//取得音檔資料開頭
	if( ok )
	{
		mmChunk.ckid = mmioFOURCC( 'd' , 'a' , 't' , 'a' );
		ok = mmioDescend( mmIO , &mmChunk , &mmRiff , MMIO_FINDCHUNK ) == MMSYSERR_NOERROR ;
		m_Size = mmChunk.cksize ;
	}
	//建立聲音緩衝區
	DSBUFFERDESC desc;
	if( ok )
	{
		memset( &desc , 0 , sizeof( desc ));
		desc.dwSize = sizeof( desc );
		desc.dwBufferBytes = m_Size ;
		desc.lpwfxFormat = &m_Format ;
		desc.dwFlags = flags ;
		ok = ds_DS->CreateSoundBuffer( &desc , &buffer1 , NULL ) == DS_OK;
	}
	//建立DX8聲音緩衝區
	if( ok )
		if( buffer1->QueryInterface( IID_IDirectSoundBuffer8 , (LPVOID*)&m_Buffer ) == DS_OK )
			buffer1->Release();
		else ok = false ;

		//取得聲音資料
		if( ok )
		{
			LPVOID pPtrl ;
			DWORD size ;
			if( m_Buffer->Lock( 0 , m_Size , &pPtrl , &size , 0 , 0 , 0 ) == DS_OK )
			{
				ok = mmioRead( mmIO , (char*)pPtrl , size ) != -1 ;
				m_Buffer->Unlock( pPtrl , size , 0 , 0 );
			}
		}
		//關掉音檔
		mmioClose( mmIO , 0 );

		m_isLooping = isLooping;

		return ok ;
}

//是否正在播放
bool dsSound::isPlaying()
{
	DWORD dwStatus;
	//如果取得播放狀態失敗的話就傳回false
	if (m_Buffer->GetStatus(&dwStatus) != DS_OK)
		return false;
	//如果播放中就傳回true
	if(dwStatus & DSBSTATUS_PLAYING)
		return true;
	return false;
}


// 播放
bool dsSound::Play()
{
	if( m_Buffer )
	{
		Restore(m_Buffer);
		//如果非播放中就播放,否則不做任何事
		if(!isPlaying())
			m_Buffer->Play(0 , 0 , m_isLooping);
		return true;
	}
	return false;
}

//停止播放
bool dsSound::Stop()
{
	if( m_Buffer ) 
	{
		//停止並把播放時間設為0
		m_Buffer->Stop(); 
		m_Buffer->SetCurrentPosition(0);
		return true;
	}
	return false;
}

//重播
bool dsSound::RePlay()
{
	if(m_Buffer) 
	{
		//停止並把播放時間設為0,然後在播放
		m_Buffer->Stop(); 
		m_Buffer->SetCurrentPosition(0);
		m_Buffer->Play(0 , 0 , m_isLooping);
		return true;
	}
	return false;
}

//暫停
bool dsSound::Pause()
{
	if( m_Buffer ) 
	{
		//停止播放
		m_Buffer->Stop(); 
		return true;
	}
	return false;
}

//恢復聲音緩衝區
void dsSound::Restore(LPDIRECTSOUNDBUFFER8 buffer)
{
	DWORD dwStatus;

	//取得緩衝區狀態
	if( buffer->GetStatus( &dwStatus ) != DS_OK )
		return ;
	//判定緩衝區是否遺失
	if( dwStatus & DSBSTATUS_BUFFERLOST )
	{
		//每隔10ms試著回複緩衝區
		do 
		{
			if( buffer->Restore() == DSERR_BUFFERLOST )
				Sleep( 10 );
			else 
				break ;
		}while( buffer->Restore() != DS_OK );
	}
}

void dsSound::MoveParameters( DWORD Frequency, LONG Pan, LONG Volume)
{
	DWORD oF ;
	LONG oP ;
	LONG oV	;
	if( !m_Buffer )
		return ;
	//頻率
	if(m_Buffer->GetFrequency(&oF) == DS_OK)
		if (Frequency + oF >= 100 && Frequency + oF <= 200000)
			m_Buffer->SetFrequency(Frequency + oF);
	//聲道
	if(m_Buffer->GetPan(&oP) == DS_OK)
		if (Pan + oP >= -10000 && Pan + oP <= 10000)
			m_Buffer->SetPan(Pan + oP);
	//音量
	if(m_Buffer->GetVolume(&oV) == DS_OK)
		if (Volume + oV >= -10000 && Volume + oV <= 0)
			m_Buffer->SetVolume(Volume + oV);
}

void dsSound::Release()
{
	if(m_Buffer) m_Buffer->Release();
	m_Buffer = NULL ;
}

void dsSound::SetVolume( LONG Volume )
{
	LONG oV	;
	if( !m_Buffer )
		return ;
	//音量
	if(m_Buffer->GetVolume(&oV) == DS_OK)
	{
		if (Volume < -10000)
			m_Buffer->SetVolume(-10000);
		else if (Volume > 0)
			m_Buffer->SetVolume(0);
		else
			m_Buffer->SetVolume(Volume);
	}
}
LONG dsSound::GetVolume()
{
	LONG oV	= 1;
	if( !m_Buffer )
		return oV;
	//音量
	m_Buffer->GetVolume(&oV);
	return oV;
}


///////////////////////////////////////////////////////////////////////////////////
//重複播放物件

dsDuplicate::dsDuplicate()
{
	Init();
}

void dsDuplicate::Init()
{
	m_Num = 0 ;
	m_Duplicate = NULL ;
}

dsDuplicate::~dsDuplicate()
{
	Release();
}

void dsDuplicate::Release()
{
	int i ;
	//移除複製緩衝區
	if(m_Duplicate)
		for(i = 0 ; i < m_Num ; i++)
			if(m_Duplicate[i])
				m_Duplicate[i]->Release();
	//移除複製緩衝的介面記憶體
	free(m_Duplicate);
	//移除實體緩衝區
	dsSound::Release();
	//歸零
	Init();
}

bool dsDuplicate::isPlaying(int index)
{
	if (!IsExist(index))
		return false;
	DWORD dwStatus;
	//如果取得播放狀態失敗的話就傳回false
	if (m_Duplicate[index]->GetStatus(&dwStatus))
		return false;
	//如果播放中就傳回true
	if(dwStatus & DSBSTATUS_PLAYING)
		return true;
	return false;
}

bool dsDuplicate::Play()
{
	for (int index=0;index < m_Num;index++)
	{
		if(m_Duplicate[index])
		{
			Restore(m_Duplicate[index]);
			//如果非播放中就播放,否則不做任何事
			if(!isPlaying(index))
			{
				m_Duplicate[index]->Play(0 , 0 , GetIsLooping());
				return true;
			}
		}
	}
	return false;
}

//停止播放
bool dsDuplicate::Stop()
{
	for (int index=0;index < m_Num;index++)
	{
		if(m_Duplicate[index])
		{
			m_Duplicate[index]->Stop(); 
			m_Duplicate[index]->SetCurrentPosition(0);
		}
	}
	return false;
}

//重播
bool dsDuplicate::RePlay(int index)
{
	if (!IsExist(index))
		return false;
	if(m_Duplicate[index]) 
	{
		//停止並把播放時間設為0,然後在播放
		m_Duplicate[index]->Stop(); 
		m_Duplicate[index]->SetCurrentPosition(0);
		m_Duplicate[index]->Play(0, 0, GetIsLooping());
		return true;
	}
	return false;
}

//暫停
bool dsDuplicate::Pause(int index)
{
	if (!IsExist(index))
		return false;
	if(m_Duplicate[index]) 
	{
		//停止播放
		m_Duplicate[index]->Stop(); 
		return true;
	}
	return false;
}
// 建立

bool dsDuplicate::Duplicate(LPCTSTR file , DWORD flags, int num, LPDIRECTSOUND8 ds_DS, bool isLooping)
{
	int i ;
	Release();
	//建立資料緩衝區
	if( !Create(file , flags, ds_DS, isLooping))
		return false;
	//建立重複播放緩衝區介面記憶體
	m_Duplicate = (LPDIRECTSOUNDBUFFER8*)malloc(sizeof( LPDIRECTSOUNDBUFFER ) * num);
	memset(m_Duplicate, 0, sizeof(LPDIRECTSOUNDBUFFER) * num);
	//建立緩衝區
	for(i = 0 ; i < num ; i++)
	{
		if( ds_DS->DuplicateSoundBuffer(GetBuffer() , (LPDIRECTSOUNDBUFFER*)&m_Duplicate[i] )!= DS_OK)
		{
			//如果有一個建立失敗就把之前的release然後傳回false
			for (int i2 = 0; i2 < i; i2++)
				m_Duplicate[i2]->Release();
			return false ;
		}

	}
	m_Num = num ;
	return true ;
}



/*/////////////////////////////////////////////

控制

/*/////////////////////////////////////////////
void dsDuplicate::MoveDuplicateParameters( int index , DWORD Frequency, LONG Pan, LONG Volume)
{
	if (!IsExist(index))
		return;
	DWORD oF ;
	LONG oP ;
	LONG oV	;
	//頻率
	if(m_Duplicate[index]->GetFrequency(&oF) == DS_OK)
		if (Frequency + oF >= 100 && Frequency + oF <= 200000)
			m_Duplicate[index]->SetFrequency(Frequency + oF);
	//聲道
	if(m_Duplicate[index]->GetPan(&oP) == DS_OK)
		if (Pan + oP >= -10000 && Pan + oP <= 10000)
			m_Duplicate[index]->SetPan(Pan + oP);
	//音量
	if(m_Duplicate[index]->GetVolume(&oV) == DS_OK)
		if (Volume >= -10000 && Volume <= 0)
			m_Duplicate[index]->SetVolume(Volume);

}

bool dsDuplicate::IsExist(int index)
{
	if (index >= m_Num)
		return false;
	return true;
}

void dsDuplicate::SetVolume( LONG Volume )
{
	for (int index=0;index < m_Num;index++)
	{
		if(m_Duplicate[index])
		{
			LONG oV	;
			//音量
			if(m_Duplicate[index]->GetVolume(&oV) == DS_OK)
			{
				if (Volume < -10000)
					m_Duplicate[index]->SetVolume(-10000);
				else if (Volume > 0)
					m_Duplicate[index]->SetVolume(0);
				else
					m_Duplicate[index]->SetVolume(Volume);
			}
		}
	}
}


bool WavSound::CreatSound(const char* filename, int index)
{
	if(m_SoundMap.find(index) != m_SoundMap.end())
		return false;
	dsSound *newsound = new dsSound();
	if (!newsound->Create(ConvStr::GetWstr(filename).c_str(), DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | 
		DSBCAPS_CTRLPAN  , ds_DS))
	{
		return false;
	}
	newsound->SetVolume(m_soundloud);
	m_SoundMap.insert(std::make_pair(index, newsound));
	return true;
}

bool WavSound::CreatSound(const char* filename, int index, int dupnum)
{
	if(m_SoundMap.find(index) != m_SoundMap.end())
		return false;
	dsDuplicate *newdupsound = new dsDuplicate();
	if(!newdupsound->Duplicate(ConvStr::GetWstr(filename).c_str(), DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | 
		DSBCAPS_CTRLPAN , dupnum, ds_DS))
	{
		return false;
	}
	newdupsound->SetVolume(m_soundloud);
	m_DupSoundMap.insert(std::make_pair(index, newdupsound));
	return true;
}

bool WavSound::CreatSound(const wchar_t* filename, int index)
{
	if(m_SoundMap.find(index) != m_SoundMap.end())
		return false;
	dsSound *newsound = new dsSound();
	if (!newsound->Create(filename, DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | 
		DSBCAPS_CTRLPAN , ds_DS))
	{
		return false;
	}
	newsound->SetVolume(m_soundloud);
	m_SoundMap.insert(std::make_pair(index, newsound));
	return true;
}

bool WavSound::CreatSound(const wchar_t* filename, int index, int dupnum)
{
	if(m_SoundMap.find(index) != m_SoundMap.end())
		return false;
	dsDuplicate *newdupsound = new dsDuplicate();
	if(!newdupsound->Duplicate((LPCTSTR)filename, DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | 
		DSBCAPS_CTRLPAN , dupnum, ds_DS))
	{
		return false;
	}
	newdupsound->SetVolume(m_soundloud);
	m_DupSoundMap.insert(std::make_pair(index, newdupsound));
	return true;
}

bool WavSound::Play(int index)
{
	//如果能成功執行play就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		if(m_SoundMapPos->second->Play())
			return true;
	}
	return false;
}

bool WavSound::PlayDup(int index)
{
	//如果能成功執行play就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		if(m_DupSoundMapPos->second->Play())
			return true;
	}
	return false;
}


bool WavSound::Stop(int index)
{
	//如果能成功執行stop就傳回true,其餘皆傳false
	if (!isStart || !index)
		return false;
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		if(m_SoundMapPos->second->Stop())
			return true;
	}
	return false;
}

bool WavSound::StopDup(int index)
{
	//如果能成功執行stop就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		if(m_DupSoundMapPos->second->Stop())
			return true;
	}
	return false;
}

bool WavSound::RePlay(int index)
{
	//如果能成功執行replay就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		if(m_SoundMapPos->second->RePlay())
			return true;
	}
	return false;
}


bool WavSound::RePlay(int index, int index2)
{
	//如果能成功執行replay就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		if(m_DupSoundMapPos->second->RePlay(index2))
			return true;
	}
	return false;
}

bool WavSound::Pause(int index)
{
	//如果能成功執行pause就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		if(m_SoundMapPos->second->Pause())
			return true;
	}
	return false;
}


bool WavSound::Pause(int index, int index2)
{
	//如果能成功執行pause就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		if(m_DupSoundMapPos->second->Pause(index2))
			return true;
	}
	return false;
}

void WavSound::MoveParameters(int index, DWORD Frequency, LONG Pan, LONG Volume)
{
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		m_SoundMapPos->second->MoveParameters(Frequency, Pan, Volume);
		return;
	}
}

void WavSound::MoveParameters(int index, int index2, DWORD Frequency, LONG Pan, LONG Volume)
{
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		m_DupSoundMapPos->second->MoveDuplicateParameters(index2, Frequency, Pan, Volume);
		return;
	}
}

void WavSound::Release()
{
	for(m_SoundMapPos = m_SoundMap.begin(); m_SoundMapPos != m_SoundMap.end(); m_SoundMapPos++)
	{
		m_SoundMapPos->second->Release();
		delete (m_SoundMapPos->second);
		m_SoundMapPos->second = NULL;
	}
	m_SoundMap.clear();
	for(m_DupSoundMapPos = m_DupSoundMap.begin(); m_DupSoundMapPos != m_DupSoundMap.end(); m_DupSoundMapPos++)
	{
		m_DupSoundMapPos->second->Release();
		delete (m_DupSoundMapPos->second);
		m_DupSoundMapPos->second = NULL;
	}
	m_DupSoundMap.clear();
	m_vSound.clear();
	m_mDupSound.clear();
}

void WavSound::Release(int index )
{
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		m_SoundMapPos->second->Release();
		m_SoundMap.erase(m_SoundMapPos);
		return;
	}
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		m_DupSoundMapPos->second->Release();
		m_DupSoundMap.erase(m_DupSoundMapPos);
		return;
	}
}

WavSound::~WavSound()
{
	Release();
	if (ds_DS)
		ds_DS->Release();
}

void WavSound::StopDevice()
{
	if (!isStart)
		return;
	int forindex;
	for (m_SoundMapPos = m_SoundMap.begin(); m_SoundMapPos != m_SoundMap.end(); m_SoundMapPos++)
	{
		if (m_SoundMapPos->second->isPlaying())
		{
			//停止播放目前播放中的音檔,然後放入vector裡
			m_SoundMapPos->second->Pause();
			m_vSound.push_back(m_SoundMapPos->second);
		}
	}
	for (m_DupSoundMapPos = m_DupSoundMap.begin(); m_DupSoundMapPos != m_DupSoundMap.end(); m_DupSoundMapPos++)
	{
		for (forindex=0; forindex < m_DupSoundMapPos->second->GetNum(); forindex++)
		{
			if (m_DupSoundMapPos->second->isPlaying(forindex))
			{
				m_DupSoundMapPos->second->Pause(forindex);
				m_mDupSound.insert(std::make_pair(forindex, m_DupSoundMapPos->second));
			}
		}
	}
	isStart = false;
}

void WavSound::StartDevice()
{
	if (isStart)
		return;
	for (m_vSoundPos = m_vSound.begin(); m_vSoundPos != m_vSound.end(); m_vSoundPos++)
	{
		(*m_vSoundPos)->Play();
	}
	m_vSound.clear();
	for (m_mDupSoundPos = m_mDupSound.begin(); m_mDupSoundPos != m_mDupSound.end(); m_mDupSoundPos++)
	{
		m_mDupSoundPos->second->Play();
	}
	m_mDupSound.clear();
	isStart = true;
}

void WavSound::SetLooping(int index, bool isLooping)
{
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		m_SoundMapPos->second->SetLooping(isLooping);
		return;
	}
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
		m_mDupSoundPos->second->SetLooping(isLooping);
}

void WavSound::AnsiToUnicode(wchar_t *unicode, const char *ansi)
{
	int n;
	n = MultiByteToWideChar(CP_ACP, 0, ansi, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, ansi, -1, unicode, n);
} 

void WavSound::Initialize( HWND hWnd , DWORD Channels /*= 2 */, DWORD Freq /*= 22050 */, DWORD BitRate /*= 16*/ )
{
	//Com物件初使化
	CoInitialize(0);
	if( DirectSoundCreate8( NULL, &ds_DS, NULL ) != DS_OK )
		return ;
	// 設定存取等級 
	if( ds_DS->SetCooperativeLevel( hWnd, DSSCL_PRIORITY ) != DS_OK )
		return ;
	//設定播放緩衝區格式
	LPDIRECTSOUNDBUFFER Primary ;

	//建立播放緩衝區 
	DSBUFFERDESC dsbd;
	ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
	dsbd.dwSize        = sizeof(DSBUFFERDESC);
	dsbd.dwFlags       = DSBCAPS_PRIMARYBUFFER;
	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat   = NULL;

	if( ds_DS->CreateSoundBuffer( &dsbd, &Primary, NULL ) != DS_OK )
		return ;
	//設定播放格式 
	WAVEFORMATEX wfx;
	ZeroMemory( &wfx, sizeof(WAVEFORMATEX) ); 
	wfx.wFormatTag      = (WORD) WAVE_FORMAT_PCM; 
	wfx.nChannels       = (WORD) Channels; 
	wfx.nSamplesPerSec  = (DWORD) Freq; 
	wfx.wBitsPerSample  = (WORD) BitRate; 
	wfx.nBlockAlign     = (WORD) (wfx.wBitsPerSample / 8 * wfx.nChannels);
	wfx.nAvgBytesPerSec = (DWORD) (wfx.nSamplesPerSec * wfx.nBlockAlign);

	if( Primary->SetFormat(&wfx) != DS_OK )
	{
		Primary->Release();
		return  ;
	}
	//設定完成，移除介面
	Primary->Release();
	isStart = true;
}

void WavSound::SetVolume(int index, LONG Volume )
{	
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		m_SoundMapPos->second->SetVolume(Volume);
		m_soundloud = Volume;
		return;
	}
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		m_DupSoundMapPos->second->SetVolume(Volume);
		m_soundloud = Volume;
		return;
	}
}

void WavSound::SetVolume( LONG Volume )
{
	for (m_SoundMapPos = m_SoundMap.begin(); m_SoundMapPos != m_SoundMap.end();
		m_SoundMapPos++)
		m_SoundMapPos->second->SetVolume(Volume);

	for (m_DupSoundMapPos = m_DupSoundMap.begin(); m_DupSoundMapPos != m_DupSoundMap.end();
		m_DupSoundMapPos++)
		m_DupSoundMapPos->second->SetVolume(Volume);

	m_soundloud = Volume;
}

LONG WavSound::GetVolume(int index )
{	
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		return m_SoundMapPos->second->GetVolume();
	}
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		return m_DupSoundMapPos->second->GetVolume();
	}
		return 1;
}

LONG WavSound::GetVolume()
{
	return m_soundloud;
}

bool WavSound::isExist(int index )
{
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
		return true;
	
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
		return true;
	return false;
}


int WavPlayer::CreatSound(const std::string& filename, int dupnum)
{
	dsDuplicate *newdupsound = new dsDuplicate();

	for (int i=0;i<m_List.size();i++)
	{
		if(filename == m_List[i])
		{
			return i;
		}
	}
	

	if(!newdupsound->Duplicate(ConvStr::GetWstr(filename).c_str(), DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | 
		DSBCAPS_CTRLPAN , dupnum, ds_DS))
	{
		return -1;
	}
	newdupsound->SetVolume(m_soundloud);
	m_List.push_back(filename);
	m_DupSounds.push_back(newdupsound);
	return m_DupSounds.size()-1;
}

bool WavPlayer::Play(int index)
{
	//如果能成功執行play就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	if (index>=0 && index<(int)m_DupSounds.size())
	{
		m_DupSounds[index]->Play();
		return true;
	}
	return false;
}

bool WavPlayer::Stop(int index)
{
	//如果能成功執行stop就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	if (index>=0 && index<(int)m_DupSounds.size())
	{
		m_DupSounds[index]->Stop();
		return true;
	}
	return false;
}


bool WavPlayer::RePlay(int index, int index2)
{
	//如果能成功執行replay就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	if (index>=0 && index<(int)m_DupSounds.size())
	{
		m_DupSounds[index]->RePlay(index2);
		return true;
	}
	return false;
}

bool WavPlayer::Pause(int index, int index2)
{
	//如果能成功執行pause就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	if (index>=0 && index<(int)m_DupSounds.size())
	{
		m_DupSounds[index]->Pause(index2);
		return true;
	}
	return false;
}

void WavPlayer::MoveParameters(int index, int index2, DWORD Frequency, LONG Pan, LONG Volume)
{
	if (index>=0 && index<(int)m_DupSounds.size())
	{
		m_DupSounds[index]->MoveDuplicateParameters(index2, Frequency, Pan, Volume);
	}
}

void WavPlayer::Release()
{
	for(std::vector<dsDuplicate*>::iterator it = m_DupSounds.begin(); it != m_DupSounds.end(); it++)
	{
		(*it)->Release();
		delete ((*it));
		(*it) = NULL;
	}
	m_DupSounds.clear();
	m_mDupSound.clear();
}

WavPlayer::~WavPlayer()
{
	Release();
	if (ds_DS)
		ds_DS->Release();
}

void WavPlayer::StopDevice()
{
	if (!isStart)
		return;
	for(std::vector<dsDuplicate*>::iterator it = m_DupSounds.begin(); it != m_DupSounds.end(); it++)
	{
		(*it)->Stop();
	}
	isStart = false;
}

void WavPlayer::PauseDevice()
{
	if (!isStart)
		return;
	int forindex;
	for(std::vector<dsDuplicate*>::iterator it = m_DupSounds.begin(); it != m_DupSounds.end(); it++)
	{
		for (forindex=0; forindex < (*it)->GetNum(); forindex++)
		{
			if ((*it)->isPlaying(forindex))
			{
				(*it)->Pause(forindex);
				m_mDupSound.push_back((*it));
			}
		}
	}
	isStart = false;
}

void WavPlayer::StartDevice()
{
	if (isStart)
		return;
	for(std::vector<dsDuplicate*>::iterator it = m_mDupSound.begin(); it != m_mDupSound.end(); it++)
	{
		(*it)->Play();
	}
	m_mDupSound.clear();
	isStart = true;
}

void WavPlayer::SetLooping(int index, bool isLooping)
{
	if (index>=0 && index<(int)m_DupSounds.size())
		m_DupSounds[index]->SetLooping(isLooping);
}

void WavPlayer::Initialize( HWND hWnd , DWORD Channels, DWORD Freq , DWORD BitRate  )
{
	//Com物件初使化
	CoInitialize(0);
	if( DirectSoundCreate8( NULL, &ds_DS, NULL ) != DS_OK )
		return ;
	// 設定存取等級 
	if( ds_DS->SetCooperativeLevel( hWnd, DSSCL_PRIORITY ) != DS_OK )
		return ;
	//設定播放緩衝區格式
	LPDIRECTSOUNDBUFFER Primary ;

	//建立播放緩衝區 
	DSBUFFERDESC dsbd;
	ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
	dsbd.dwSize        = sizeof(DSBUFFERDESC);
	dsbd.dwFlags       = DSBCAPS_PRIMARYBUFFER;
	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat   = NULL;

	if( ds_DS->CreateSoundBuffer( &dsbd, &Primary, NULL ) != DS_OK )
		return ;
	//設定播放格式 
	WAVEFORMATEX wfx;
	ZeroMemory( &wfx, sizeof(WAVEFORMATEX) ); 
	wfx.wFormatTag      = (WORD) WAVE_FORMAT_PCM; 
	wfx.nChannels       = (WORD) Channels; 
	wfx.nSamplesPerSec  = (DWORD) Freq; 
	wfx.wBitsPerSample  = (WORD) BitRate; 
	wfx.nBlockAlign     = (WORD) (wfx.wBitsPerSample / 8 * wfx.nChannels);
	wfx.nAvgBytesPerSec = (DWORD) (wfx.nSamplesPerSec * wfx.nBlockAlign);

	if( Primary->SetFormat(&wfx) != DS_OK )
	{
		Primary->Release();
		return  ;
	}
	//設定完成，移除介面
	Primary->Release();
	isStart = true;
}

void WavPlayer::SetVolume(int index, LONG Volume )
{	
	if (index>=0 && index<(int)m_DupSounds.size())
		m_DupSounds[index]->SetVolume(Volume);
}


void WavPlayer::SetVolume( LONG Volume )
{
	for(std::vector<dsDuplicate*>::iterator it = m_DupSounds.begin(); it != m_DupSounds.end(); it++)
		(*it)->SetVolume(Volume);

	m_soundloud = Volume;
}

LONG WavPlayer::GetVolume(int index )
{	
	if (index>=0 && index<(int)m_DupSounds.size())
		return m_DupSounds[index]->GetVolume();
	return 1;
}

LONG WavPlayer::GetVolume()
{
	return m_soundloud;
}

int WavPlayer::GetIndex( std::string name )
{
	int index=-1;
	for(std::vector<std::string>::iterator it = m_List.begin();it != m_List.end(); it++)
	{
		index++;
		if((*it)==name)return index;
	}
	return -1;// Not Found
}
