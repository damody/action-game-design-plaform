#include "Weapon.h"


Weapon::Weapon(void)
{
}

Weapon::Weapon( std::string w ):
weapon(w),m_Position(Vector3()),m_Team(0),m_FaceSide(true),m_FrameID(0),m_Texture(0),m_PicID(0),m_PicW(0),m_PicH(0),m_PicX(0),m_PicY(0)
{
	m_ObjectInfo = g_ObjectInfoMG.GetObjectInfo(weapon);
	if(m_ObjectInfo.get())
		this->Init();
	else{
		std::cout<<"Cannot find "<<w<<std::endl;
	}
}


Weapon::~Weapon(void)
{
}

void Weapon::Init()
{
	m_Angle = 0;

	m_HP = m_ObjectInfo->m_MaxHP;

	m_Frame = "default";
	m_FrameID = 0;
	FrameInfo *f = &m_ObjectInfo->m_FramesMap[m_Frame][m_FrameID];
	m_PicID = f->m_PictureID;
	m_PicX = f->m_PictureX;
	m_PicY = f->m_PictureY;
	m_PicW = m_ObjectInfo->m_PictureDatas[m_PicID].m_Column;
	m_PicH = m_ObjectInfo->m_PictureDatas[m_PicID].m_Row;
	m_Texture = m_ObjectInfo->m_PictureDatas[m_PicID].m_TextureID;
	m_Action = f->m_HeroAction;
	m_TimeTik = f->m_Wait;
	m_Bodys = f->m_Bodys;
}


void Weapon::NextFrame()
{
	FrameInfo *f = &m_ObjectInfo->m_FramesMap[m_Frame][m_FrameID];
	m_Frame = f->m_NextFrameName;
	m_FrameID = f->m_NextFrameIndex;
	f = &m_ObjectInfo->m_FramesMap[m_Frame][m_FrameID];

	m_PicID = f->m_PictureID;
	m_PicX = f->m_PictureX;
	m_PicY = f->m_PictureY;
	m_PicW = m_ObjectInfo->m_PictureDatas[m_PicID].m_Column;
	m_PicH = m_ObjectInfo->m_PictureDatas[m_PicID].m_Row;
	m_Texture = m_ObjectInfo->m_PictureDatas[m_PicID].m_TextureID;
	m_Action = f->m_HeroAction;
	m_TimeTik = f->m_Wait;
	m_Vel.x +=f->m_DVX;
	m_Vel.y +=f->m_DVY;
	m_Vel.z +=f->m_DVZ;
}

void Weapon::Update( float dt )
{
	if(m_TimeTik <= 0)
	{
		NextFrame();
	}else
	{
		m_TimeTik--;
	}
}

void Weapon::UpdateDataToDraw()
{
	float scale = 1.5f;

	float offsetX,offsetY;

	if(m_FaceSide){
		offsetX= (m_ObjectInfo->m_PictureDatas[m_PicID].m_Width - 2*m_ObjectInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterX)*scale;
	}else{
		offsetX=-(m_ObjectInfo->m_PictureDatas[m_PicID].m_Width - 2*m_ObjectInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterX)*scale;
	}
	offsetY = - 2*(m_ObjectInfo->m_PictureDatas[m_PicID].m_Height-m_ObjectInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterY)*scale;

	m_Pic.position.x = m_Position.x+offsetX;
	m_Pic.position.y = m_Position.y+offsetY;
	m_Pic.position.z = m_Position.z;

	m_Pic.angle = m_Angle;
	m_Pic.size.x = m_ObjectInfo->m_PictureDatas[m_PicID].m_Width *scale;
	m_Pic.size.y = m_ObjectInfo->m_PictureDatas[m_PicID].m_Height *scale;

	m_Pic.picpos.x = (float)m_PicX;
	m_Pic.picpos.y = (float)m_PicY;
	m_Pic.picpos.z = (float)m_PicH;
	m_Pic.picpos.w = (float)m_PicW;

	if(m_FaceSide){
		m_Pic.faceside = 1;
	}else{
		m_Pic.faceside = -1;
	}
}

void Weapon::SetTeam( int index )
{
	m_Team = index;
}

void Weapon::SetPosition( Vector3 p )
{
	m_Position = p;
}

void Weapon::Translation( Vector3 t )
{
	m_Position += t;
}

void Weapon::SetVelocity( Vector3 v )
{
	m_Vel = v;
}



