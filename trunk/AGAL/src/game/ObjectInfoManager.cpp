
#include "game\ObjectInfoManager.h"

ObjectInfoMG::ObjectInfoMG( void )
{
}

ObjectInfoMG::~ObjectInfoMG( void )
{
}

void ObjectInfoMG::AddObjectInfo( std::string name, ObjectInfo_Sptr info )
{
	m_ObjectInfoMap[name] = info;
}

ObjectInfo_Sptr ObjectInfoMG::GetObjectInfo( std::string name )
{
	ObjectInfoMap::iterator i = m_ObjectInfoMap.find( name );

	if ( i == m_ObjectInfoMap.end() )
	{
		return ObjectInfo_Sptr();
	}

	return i->second;
}
