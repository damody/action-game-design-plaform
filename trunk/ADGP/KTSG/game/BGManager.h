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

public:
	BGManager(void);
	~BGManager(void);

	unsigned int AddBG(std::string name,BackGround_RawPtr bg);

	std::vector<std::string> GetBGList();
	BackGround_RawPtr	 GetBG(unsigned int id);
	BackGround_RawPtr	 GetBG(std::string name);
};

