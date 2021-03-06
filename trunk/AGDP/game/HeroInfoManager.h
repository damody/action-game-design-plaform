#pragma once
#include <cstdio>
#include <windows.h>

#include "common\shared_ptr.h"
#include "game\HeroInfo.h"
namespace boost {namespace serialization {class access;}}
class HeroInfoManager
{
public:
	HeroInfoManager( void ) {}
	~HeroInfoManager( void ) {}
	void AddHeroInfo( std::wstring name, HeroInfo_Sptr info );
	HeroInfo_Sptr GetHeroInfo( std::wstring name );
	const std::vector<std::wstring> GetList();

private:
	std::vector<std::wstring> m_List;
	HeroInfoMap		 m_HeroInfoMaps;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& 	m_List;
		ar& 	m_HeroInfoMaps;
	}
};












