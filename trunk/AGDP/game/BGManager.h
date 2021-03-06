#pragma once

#include <string>
#include <map>
#include <vector>
#include <game/Background.h>
#include "DX11/BGMPlayer.h"

namespace boost {namespace serialization {class access;}}
class BackgroundManager
{
private:
	std::vector<std::wstring> m_BackgroundList;
	BackgroundMaps			  m_BackgroundMaps;
	//Background Music list & map

	BGMPlayer m_BGM_Player;
	std::vector<std::wstring> m_BGM_PathList;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& m_BGList;
		ar& m_BackgroundMaps
	}


	Background* m_Current_Background;
	int	        m_Current_BGM;
public:
	BackgroundManager( void );
	~BackgroundManager( void );

	unsigned int AddBackground( const std::wstring& name, Background_Sptr bg );

	std::vector<std::wstring> GetBackgroundList();

	void SetCurrentBackground( const std::wstring& name );
	Background* GetCurrentBackground();

	void Set_BGM_PathList( const std::vector<std::wstring>& list );
	void Set_BGM_Play( int index );
	void Set_BGM_Pause();
	void Set_BGM_Stop();
	void Set_BGM_Voleum( int voleum );

};

