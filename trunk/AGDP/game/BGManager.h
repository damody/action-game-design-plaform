#pragma once

#include <string>
#include <map>
#include <vector>
#include <game/BackGround.h>
#include "DX11/BGMPlayer.h"

namespace boost {namespace serialization {class access;}}
class BackGroundManager
{
private:
	std::vector<std::string> m_BackGroundList;
	BackGroundMaps			 m_BackGroundMaps;
	//Background Music list & map

	BGMPlayer m_BGM_Player;
	std::vector<std::string> m_BGM_PathList;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& m_BGList;
		ar& m_BackGroundMaps
	}


	BackGround* m_Current_BackGround;
	int	    m_Current_BGM;
public:
	BackGroundManager( void );
	~BackGroundManager( void );

	unsigned int AddBackGround( const std::string& name, BackGround_Sptr bg );

	std::vector<std::string> GetBackGroundList();

	void SetCurrentBackGround( const std::string& name );
	BackGround* GetCurrentBackGround();

	void Set_BGM_PathList( const std::vector<std::string>& list );
	void Set_BGM_Play( int index );
	void Set_BGM_Pause();
	void Set_BGM_Stop();
	void Set_BGM_Voleum( int voleum );

};

