//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : MainPlane.cpp
//  @ Date : 2011/8/30
//  @ Author : 
//
//
#include <iostream>
#include <algo/nway.h>
#include <ball/homing.h>


#include "Hero.h"
#include "DX11/InputState.h"
#include "DX11/WaveSound.h"
#include "DX11/InitDirect3DApp.h"
#include "math/Quaternion.h"
#include "global.h"

Hero::Hero()
{

}

Hero::Hero( std::string h ):hero(h),m_Position(Vector3()),m_Team(0)
{
	m_HeroInfo = g_HeroInfoMG.GetHeroInfo(hero);
	if(m_HeroInfo.get())
			this->Init();
	else{
		std::cout<<"Cannot find "<<h<<std::endl;
	}
}

void Hero::Init()
{
	m_Angle = 0;

	m_HP = m_HeroInfo->m_MaxHP;
	m_MaxRecoverHP = m_HeroInfo->m_MaxHP;
	m_MP = m_HeroInfo->m_MaxMP;

	m_Frame = "default";
	m_FrameID = 0;
	m_PicID = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_PictureID;
	m_PicX = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_PictureX;
	m_PicY = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_PictureY;
	m_PicW = m_HeroInfo->m_PictureDatas[m_PicID].m_Column;
	m_PicH = m_HeroInfo->m_PictureDatas[m_PicID].m_Row;
	m_Texture = m_HeroInfo->m_PictureDatas[m_PicID].m_TextureID;
	m_Action = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_HeroAction;
	m_TimeTik = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_Wait;
	m_Bodys = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_Bodys;
	this->UpdateDataToDraw();
}

void Hero::Update(float dt) 
{
	if(!ScanKeyQue())//無控制動作時，跑Wait Time
	{
		if(m_TimeTik <= 0)
		{
			NextFrame();
		}else
		{
			m_TimeTik--;
		}
	}
	this->UpdateDataToDraw();
}

void Hero::UpdateDataToDraw()
{
// 	m_Pic.position.x = m_Position.x - (m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterX / 1280);
// 	m_Pic.position.y = m_Position.y - (m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterY / 800);
	m_Pic.position.x = m_Position.x;
	m_Pic.position.y = m_Position.y;
	m_Pic.position.z = m_Position.z;
	m_Pic.angle = m_Angle;
	m_Pic.size.x = m_HeroInfo->m_PictureDatas[m_PicID].m_Width *2.0f ;
	m_Pic.size.y = m_HeroInfo->m_PictureDatas[m_PicID].m_Height *2.0f ;

	m_Pic.picpos.x = (float)m_PicX;
	m_Pic.picpos.y = (float)m_PicY;
	m_Pic.picpos.z = (float)m_PicH;
	m_Pic.picpos.w = (float)m_PicW;
	
}

Texture_Sptr Hero::GetTexture()
{
	return g_TextureManager.GetTexture(m_Texture);
}

ClipVertex Hero::GetPic()
{
	return m_Pic;
}

int Hero::GetTextureID()
{
	return m_Texture;
}

void Hero::NextFrame()
{
	m_Frame = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_NextFrameName;
	m_FrameID = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_NextFrameIndex;

	m_PicID = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_PictureID;
	m_PicX = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_PictureX;
	m_PicY = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_PictureY;
	m_PicW = m_HeroInfo->m_PictureDatas[m_PicID].m_Column;
	m_PicH = m_HeroInfo->m_PictureDatas[m_PicID].m_Row;
	m_Texture = m_HeroInfo->m_PictureDatas[m_PicID].m_TextureID;
	m_Action = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_HeroAction;
	m_TimeTik = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_Wait;
}

bool Hero::ScanKeyQue()
{
	//Undo
	return false;
}

void Hero::Position( Vector3 pos )
{
	m_Position =pos;
}

void Hero::SetRecord( Record_Sptr r )
{
	m_Record = r;
}

void Hero::PushKey( KeyInfo k )
{
	m_KeyQue.push_back(k);
}

void Hero::SetTeam( int team )
{
	m_Team = team;
}


bool SortHero( Hero_RawPtr a,Hero_RawPtr b )
{
	return a->GetTextureID()<b->GetTextureID();
}



