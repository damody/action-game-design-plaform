#pragma once

#include <string>
#include <map>
#include <vector>
#include <game/BackGround.h>

namespace boost {namespace serialization {class access;}}
class BGManager
{
private:

	std::vector<std::string> m_BGList;
	BGMaps			 m_BGMaps;
	//Background Music list & map

	std::vector<std::string> m_BGMList;
	std::map<std::string, int> m_BGMMap;

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

	unsigned int AddBG( const std::string& name, BackGround_RawPtr bg );
	int AddBGM( const std::string& name, int index );

	std::vector<std::string> GetBGList();
	std::vector<std::string> GetBGMList();

	void SetCurrentBGM( const std::string& name );
	void SetCurrentBG( const std::string& name );
	int CurrentBGM();
	BackGround* CurrentBG();
};

