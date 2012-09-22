#pragma once

#include <string>
#include <map>
#include <vector>
#include <game/BackGround.h>
#include "DX11/BGMPlayer.h"

namespace boost {namespace serialization {class access;}}
class BGManager
{
private:
	std::vector<std::string> m_BGList;
	BGMaps			 m_BGMaps;
	//Background Music list & map

	BGMPlayer m_BGMPlayer;
	std::vector<std::string> m_BGMPathList;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& m_BGList;
		ar& m_BGMaps
	}


	BackGround* m_CurrentBG;
	int	    m_CurrentBGM;
public:
	BGManager( void );
	~BGManager( void );

	unsigned int AddBG( const std::string& name, BackGround_Sptr bg );

	std::vector<std::string> GetBGList();

	void SetCurrentBG( const std::string& name );
	BackGround* CurrentBG();

	void SetBGMPathList(const std::vector<std::string>& list);
	void BGMPlay(int index);
	void BGMPause();
	void BGMStop();
	void SetBGMVoleum(int voleum);

};

