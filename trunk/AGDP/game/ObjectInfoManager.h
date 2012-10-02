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

	void AddObjectInfo( std::wstring name, ObjectInfo_Sptr info );
	ObjectInfo_Sptr GetObjectInfo( std::wstring name );
};

