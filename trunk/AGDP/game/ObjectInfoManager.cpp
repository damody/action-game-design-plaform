
#include "game\ObjectInfoManager.h"
#include "global.h"

ObjectInfoMG::ObjectInfoMG( void )
{
}

ObjectInfoMG::~ObjectInfoMG( void )
{
}

void ObjectInfoMG::AddObjectInfo( std::string name, ObjectInfo_Sptr info )
{
	for (unsigned int i=0 ; i < info->m_PictureDatas.size(); ++i)
	{
		info->m_PictureDatas[i].m_TextureID =  g_TextureManager.AddTexture(info->m_PictureDatas[i].m_Path);
	}
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
