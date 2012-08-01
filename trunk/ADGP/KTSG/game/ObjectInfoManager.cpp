#include "ObjectInfoManager.h"


ObjectInfoMG::ObjectInfoMG(void)
{
}


ObjectInfoMG::~ObjectInfoMG(void)
{
}

void ObjectInfoMG::AddObjectInfo( std::string name,ObjectInfo_Sptr info )
{
	m_ObjectInfoMap[name]=info;
}

ObjectInfo_Sptr ObjectInfoMG::GetObjectInfo( std::string name )
{
	return m_ObjectInfoMap[name];
}
