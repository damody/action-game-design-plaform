#pragma once
#include <string>
#include "game/ObjectInfo.h"

class ObjectInfoManager
{
private:
	ObjectInfoMap m_ObjectInfoMap;
public:
	ObjectInfoManager( void );
	~ObjectInfoManager( void );

	void AddObjectInfo( std::string name, ObjectInfo_Sptr info );
	ObjectInfo_Sptr GetObjectInfo( std::string name );
};

