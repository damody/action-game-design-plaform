#pragma once

#include <string>
#include <vector>
#include <game/BackGround.h>

namespace boost{namespace serialization{class access;}}
class BGManager
{
private:
	
	std::vector<std::string> m_BGList;
	BGMaps			 m_BGMaps;
	//Background Music list & map

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & m_BGList;
		ar & m_BGMaps;
	}


	BackGround* m_CurrentBG;
public:
	BGManager(void);
	~BGManager(void);

	unsigned int AddBG(const std::string& name,BackGround_RawPtr bg);

	std::vector<std::string> GetBGList();
	void SetCurrentBG(const std::string& name);
	BackGround* CurrentBG();
};

