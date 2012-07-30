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

Hero::Hero( std::string h ):
hero(h),m_Position(Vector3()),m_Team(0),m_FaceSide(true),m_FrameID(0),m_Texture(0),m_PicID(0),m_PicW(0),m_PicH(0),m_PicX(0),m_PicY(0),d_run(0)
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
	//物理
	m_Position += m_Vel;

	float sign = m_Vel.x/abs(m_Vel.x);
	m_Vel.x = abs(m_Vel.x);
	m_Vel.x -= FRICTION;
	if(m_Vel.x < 0) m_Vel.x = 0;
	else m_Vel.x *= sign;

	sign = m_Vel.y/abs(m_Vel.y);
	m_Vel.y = abs(m_Vel.y);
	m_Vel.y -= FRICTION;
	if(m_Vel.y < 0) m_Vel.y = 0;
	else m_Vel.y *= sign;

	sign = m_Vel.z/abs(m_Vel.z);
	m_Vel.z = abs(m_Vel.z);
	m_Vel.z -= FRICTION;
	if(m_Vel.z < 0) m_Vel.z = 0;
	else m_Vel.z *= sign;

}

void Hero::UpdateDataToDraw()
{
// 	m_Pic.position.x = m_Position.x - (m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterX / 1280);
// 	m_Pic.position.y = m_Position.y - (m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterY / 800);
	m_Pic.position.x = m_Position.x;
	m_Pic.position.y = m_Position.y;
	m_Pic.position.z = m_Position.z;
	m_Pic.angle = m_Angle;
	m_Pic.size.x = m_HeroInfo->m_PictureDatas[m_PicID].m_Width *1.5f ;
	m_Pic.size.y = m_HeroInfo->m_PictureDatas[m_PicID].m_Height *1.5f ;

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
	FrameInfo *f = &m_HeroInfo->m_FramesMap[m_Frame][m_FrameID];
	m_Frame = f->m_NextFrameName;
	m_FrameID = f->m_NextFrameIndex;
	f = &m_HeroInfo->m_FramesMap[m_Frame][m_FrameID];

	m_PicID = f->m_PictureID;
	m_PicX = f->m_PictureX;
	m_PicY = f->m_PictureY;
	m_PicW = m_HeroInfo->m_PictureDatas[m_PicID].m_Column;
	m_PicH = m_HeroInfo->m_PictureDatas[m_PicID].m_Row;
	m_Texture = m_HeroInfo->m_PictureDatas[m_PicID].m_TextureID;
	m_Action = f->m_HeroAction;
	m_TimeTik = f->m_Wait;
	m_Vel.x +=f->m_DVX;
	m_Vel.y +=f->m_DVY;
	m_Vel.z +=f->m_DVZ;
}

bool Hero::ScanKeyQue()
{
	std::string nFrame;
	int nFramID=0;
	//Vector3 dv;
	KeyQueue::iterator i=m_KeyQue.begin();

	//決定方向按鍵動作
	if(m_Action == HeroAction::STANDING)
	{
		while(i!=m_KeyQue.end())
		{
			if(i->key == CtrlKey::UP)
			{
				nFrame = "walking";
				m_Vel.z = m_HeroInfo->m_WalkingSpeedZ;
			}
			else if(i->key == CtrlKey::DOWN)
			{
				nFrame = "walking";
				m_Vel.z = -m_HeroInfo->m_WalkingSpeedZ;
			}
			else if(i->key == CtrlKey::LEFT)
			{
				printf("d_run:%d\n",d_run);
				if( d_run != 0 && g_Time + d_run < WAIT_FOR_KEY_RUN && !m_FaceSide){
					//跑
					nFrame = "running";
					m_Vel.x = -m_HeroInfo->m_RunningSpeed;
				}else{
					//走
					nFrame = "walking";
					m_Vel.x = -m_HeroInfo->m_WalkingSpeed;
					m_FaceSide = false;
				}
			}
			else if(i->key == CtrlKey::RIGHT)
			{
				printf("d_run:%d\n",d_run);
				if( d_run != 0 && g_Time - d_run < WAIT_FOR_KEY_RUN && m_FaceSide){
					//跑
					nFrame = "running";
					m_Vel.x = m_HeroInfo->m_RunningSpeed;
				}
				else{
					//走
					nFrame = "walking";
					m_Vel.x = m_HeroInfo->m_WalkingSpeed;
					m_FaceSide = true;
				}
			}
			i++;
		}
	}
	else if(m_Action == HeroAction::WALKING )
	{
		//if(m_TimeTik < 2){
		while(i!=m_KeyQue.end()){
			if(i->key == CtrlKey::UP)
			{
				if(m_TimeTik < 2) nFrame = "walking";
				m_Vel.z = m_HeroInfo->m_WalkingSpeedZ;
			}
			else if(i->key == CtrlKey::DOWN)
			{
				if(m_TimeTik < 2) nFrame = "walking";
				m_Vel.z = -m_HeroInfo->m_WalkingSpeedZ;
			}
			else if(i->key == CtrlKey::LEFT)
			{
				printf("d_run:%d\n",d_run);
				if( d_run != 0 && g_Time + d_run < WAIT_FOR_KEY_RUN && !m_FaceSide){
					//跑
					nFrame = "running";
					m_Vel.x = -m_HeroInfo->m_RunningSpeed;
				}
				else{
					if(m_TimeTik < 2) nFrame = "walking";
					m_Vel.x = -m_HeroInfo->m_WalkingSpeed;
					m_FaceSide = false;
				}
			}
			else if(i->key == CtrlKey::RIGHT)
			{
				printf("d_run:%d\n",d_run);
				if( d_run != 0 && g_Time - d_run < WAIT_FOR_KEY_RUN && m_FaceSide){
					//跑
					nFrame = "running";
					m_Vel.x = m_HeroInfo->m_RunningSpeed;
				}else{
					if(m_TimeTik < 2) nFrame = "walking";
					m_Vel.x = m_HeroInfo->m_WalkingSpeed;
					m_FaceSide = true;
				}
			}
			i++;
		}
		//}
		if(!nFrame.empty() )
		{
			nFramID = (m_FrameID+1) % (m_HeroInfo->m_FramesMap[nFrame].size());
		}
		/*else 
		{
			nFrame.clear();
		}//*/
	}
	else if(m_Action == HeroAction::RUNNING){
		m_Vel.x = (m_FaceSide ? m_HeroInfo->m_RunningSpeed : -m_HeroInfo->m_RunningSpeed);
		while(i!=m_KeyQue.end()){
			if(i->key == CtrlKey::UP)
			{
				if(m_TimeTik < 2) nFrame = "running";
				nFramID = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_NextFrameIndex;
				m_Vel.z = m_HeroInfo->m_RunningSpeedZ;
			}
			else if(i->key == CtrlKey::DOWN)
			{
				if(m_TimeTik < 2) nFrame = "running";
				nFramID = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_NextFrameIndex;
				m_Vel.z = -m_HeroInfo->m_RunningSpeedZ;
			}
			else if(i->key == CtrlKey::LEFT  && m_FaceSide){
				nFrame = "stop_running";
				nFramID = 0;
				d_run = 0;
				break;
			}
			else if(i->key == CtrlKey::RIGHT && !m_FaceSide){
				nFrame = "stop_running";
				nFramID = 0;
				d_run = 0;
				break;
			}
			i++;
		}
	}
	//決定招式按鍵動作

		/*未開工*/

	//清理佇列
	i=m_KeyQue.begin();
	while( i != m_KeyQue.end()){
		/*  i->key > CtrlKey::ATK2 ：特殊按鍵放開事件要處理
		 *  i->key >=CtrlKey::DEF  ：特殊按鍵放開事件不處理 */
		if( i->key >=CtrlKey::DEF && g_Time - i->time > KEYLIFE_AFTER_KEYUP){
			i = m_KeyQue.erase(i);
		}else i++;
	}
	//下個影格
	if(nFrame.empty()) return false;
	else{
		//m_Vel += dv;
		m_Frame = nFrame;
		m_FrameID = nFramID;
		FrameInfo *f = &m_HeroInfo->m_FramesMap[m_Frame][m_FrameID];

		m_PicID = f->m_PictureID;
		m_PicX = f->m_PictureX;
		m_PicY = f->m_PictureY;
		m_PicW = m_HeroInfo->m_PictureDatas[m_PicID].m_Column;
		m_PicH = m_HeroInfo->m_PictureDatas[m_PicID].m_Row;
		m_Texture = m_HeroInfo->m_PictureDatas[m_PicID].m_TextureID;
		m_Action = f->m_HeroAction;
		m_TimeTik = f->m_Wait;
		m_Vel.x +=f->m_DVX;
		m_Vel.y +=f->m_DVY;
		m_Vel.z +=f->m_DVZ;
		return true;
	}
}

void Hero::SetPosition( Vector3 pos )
{
	m_Position =pos;
}

void Hero::SetRecord( Record_Sptr r )
{
	m_Record = r;
}

void Hero::PushKey( KeyInfo k )
{
	KeyQueue::iterator i;

	if(k.key >= CtrlKey::DEF_KEYUP){
		//忽略特殊按鍵放開事件
		return;
	}
	/*特殊按鍵放開
	if(k.key == CtrlKey::ATK1_KEYUP){
		//printf("ATK1_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::ATK1){
				i->key = k.key;
				i->time= k.time;
				break;
			}
		}
	}
	else if(k.key == CtrlKey::ATK2_KEYUP){
		//printf("ATK2_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::ATK2){
				i->key = k.key;
				i->time= k.time;
				break;
			}
		}
	}
	else if(k.key == CtrlKey::DEF_KEYUP){
		//printf("DEF_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::DEF){
				i->key = k.key;
				i->time= k.time;
				break;
			}
		}
	}
	else if(k.key == CtrlKey::JUMP_KEYUP){
		//printf("JUMP_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::JUMP){
				i->key = k.key;
				i->time= k.time;
				break;
			}
		}
	}//特殊按鍵放開*/
	else if(k.key == CtrlKey::LEFT_KEYUP){
		//printf("LEFT_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::LEFT){
				d_run = -i->time;
				i->key = k.key;
				i->time= k.time;
				break;
			}
		}
	}
	else if(k.key == CtrlKey::RIGHT_KEYUP){
		//printf("RIGHT_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::RIGHT){
				d_run = i->time;
				i->key = k.key;
				i->time= k.time;
				break;
			}
		}
	}
	else if(k.key == CtrlKey::UP_KEYUP){
		//printf("UP_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::UP){
				i->key = k.key;
				i->time= k.time;
				break;
			}
		}
	}
	else if(k.key == CtrlKey::DOWN_KEYUP){
		//printf("DOWN_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::DOWN){
				i->key = k.key;
				i->time= k.time;
				break;
			}
		}
	}
	else{
		m_KeyQue.push_back(k);
		//若是上下左右，將與其相反方向的按鍵事件取消
		if(k.key == CtrlKey::UP){
			for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
				if(i->key == CtrlKey::DOWN){
					m_KeyQue.erase(i);
					break;
				}
			}
		}
		else if(k.key == CtrlKey::DOWN){
			for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
				if(i->key == CtrlKey::UP){
					m_KeyQue.erase(i);
					break;
				}
			}
		}
		else if(k.key == CtrlKey::LEFT){
			//d_run = -k.time;
			printf("LEFT, k.time = %d, d_run = %d, g_Time: %d\n",k.time,d_run,g_Time);
			for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
				if(i->key == CtrlKey::RIGHT){
					m_KeyQue.erase(i);
					break;
				}
			}
		}
		else if(k.key == CtrlKey::RIGHT){
			//d_run = k.time;
			printf("RIGHT, k.time = %d, d_run = %d, g_Time: %d\n",k.time,d_run,g_Time);
			for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
				if(i->key == CtrlKey::LEFT){
					m_KeyQue.erase(i);
					break;
				}
			}
		}
		//*/
	}
}

void Hero::SetTeam( int team )
{
	m_Team = team;
}

Vector3 Hero::Position()
{
	return m_Position;
}

bool SortHero( Hero_RawPtr a,Hero_RawPtr b )
{
	return a->GetTextureID()<b->GetTextureID();
}



