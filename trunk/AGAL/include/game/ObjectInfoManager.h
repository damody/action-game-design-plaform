#pragma once
#include <string>
#include "game/ObjectInfo.h"

class ObjectInfoMG
{
private: 
	ObjectInfoMap m_ObjectInfoMap;
public:
	ObjectInfoMG(void);
	~ObjectInfoMG(void);

	void AddObjectInfo(std::string name,ObjectInfo_Sptr info);
	ObjectInfo_Sptr GetObjectInfo(std::string name);
};

