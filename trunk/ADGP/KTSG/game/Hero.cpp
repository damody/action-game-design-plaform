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
#include "StdGame.h"
#include <iostream>
#include <algo/nway.h>
#include <ball/homing.h>


#include "Hero.h"
#include "DX11/InputState.h"
#include "DX11/WaveSound.h"
#include "DX11/InitDirect3DApp.h"
#include "math/Quaternion.h"
#include "global.h"

bool isKeyUp(char r){
	switch(r){
	case '^':case 'v':case '<':case '>':case 'A':case 'B':case 'J':case 'D':
		return false;
	case '8':case '2':case '4':case '6':case 'a':case 'b':case 'j':case 'd':
		return true;
	default:
		throw "wrong hit key";
		return false;
	}
}

Hero::Hero()
{

}

Hero::Hero( std::string h ):
hero(h),m_Position(Vector3()),m_Team(0),m_FaceSide(true),m_FrameID(0),m_Texture(0),m_PicID(0),m_PicW(0),m_PicH(0),m_PicX(0),m_PicY(0),d_run(0),m_Effect(EffectType::NONE),m_EffectScale(1.0f),d_key()
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
	m_CenterX = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterX;
	m_CenterY = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterY;
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
	m_PastPos = m_Position;

	float ry = m_Position.y;
	m_Position += m_Vel;

	if(m_Position.y <= 0){	//地上
		//落地判定
		if( m_Action != HeroAction::UNIQUE_SKILL){
			m_Position.y = 0;
			m_Vel.y = 0;
			if(ry > 0 || m_Action == HeroAction::IN_THE_AIR || m_Action == HeroAction::DASH){
				//Frame 改到蹲
				m_Frame = "crouch";
				if( m_Action == HeroAction::DASH || m_Action == HeroAction::BEFORE_DASH_ATTACK ||
					m_Action == HeroAction::DASH_ATTACKING || m_Action == HeroAction::AFTER_DASH_ATTACK){
					m_FrameID = 1;
				}
				else{
					m_FrameID = 0;
				}
				FrameInfo *f = &m_HeroInfo->m_FramesMap[m_Frame][m_FrameID];
				if(f->m_ClearKeyQueue){
					m_KeyQue.clear();
				}
				m_PicID = f->m_PictureID;
				m_PicX = f->m_PictureX;
				m_PicY = f->m_PictureY;
				m_PicW = m_HeroInfo->m_PictureDatas[m_PicID].m_Column;
				m_PicH = m_HeroInfo->m_PictureDatas[m_PicID].m_Row;
				m_Texture = m_HeroInfo->m_PictureDatas[m_PicID].m_TextureID;
				m_Action = f->m_HeroAction;
				m_TimeTik = f->m_Wait;
				m_CenterX = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterX;
				m_CenterY = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterY;
				m_Bodys = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_Bodys;
				//m_Vel.x = 0;
				//m_Vel.z = 0;

				CreateEffect();
			}
		}
		//X方向摩擦力計算
		float sign = m_Vel.x/abs(m_Vel.x);
		m_Vel.x = abs(m_Vel.x);
		m_Vel.x -= FRICTION;
		if(m_Vel.x < 0) m_Vel.x = 0;
		else m_Vel.x *= sign;
		//Z方向摩擦力計算
		sign = m_Vel.z/abs(m_Vel.z);
		m_Vel.z = abs(m_Vel.z);
		m_Vel.z -= FRICTION;
		if(m_Vel.z < 0) m_Vel.z = 0;
		else m_Vel.z *= sign;
	}
	else{					//空中
		//重力加速度
		if(m_Action != HeroAction::AIR_SKILL && m_Action != HeroAction::UNIQUE_SKILL){
			m_Vel.y -= G_ACCE;
		}
		//掉落
		if(m_Action == HeroAction::STANDING){
			m_Frame = "in_the_air";
			m_FrameID = 0;
			FrameInfo *f = &m_HeroInfo->m_FramesMap[m_Frame][m_FrameID];
			if(f->m_ClearKeyQueue){
				m_KeyQue.clear();
			}
			m_PicID = f->m_PictureID;
			m_PicX = f->m_PictureX;
			m_PicY = f->m_PictureY;
			m_PicW = m_HeroInfo->m_PictureDatas[m_PicID].m_Column;
			m_PicH = m_HeroInfo->m_PictureDatas[m_PicID].m_Row;
			m_Texture = m_HeroInfo->m_PictureDatas[m_PicID].m_TextureID;
			m_Action = f->m_HeroAction;
			m_TimeTik = f->m_Wait;
			m_CenterX = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterX;
			m_CenterY = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_CenterY;
			m_Bodys = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_Bodys;
			CreateEffect();
		}
	}


	
}

void Hero::UpdateDataToDraw()
{
	float scale = 3.0f ;

	m_Pic.position.x = m_Position.x;
	m_Pic.position.y = m_Position.y;
	m_Pic.position.z = m_Position.z;

	m_Pic.center.x = scale * (m_CenterX  + 0.5f *(m_EffectScale-1) * (float)m_HeroInfo->m_PictureDatas[m_PicID].m_Width);
	m_Pic.center.y = scale * (m_CenterY  + 0.5f *(m_EffectScale-1) * (float)m_HeroInfo->m_PictureDatas[m_PicID].m_Height);

	m_Pic.angle = m_Angle;
	m_Pic.size.x = (float)m_HeroInfo->m_PictureDatas[m_PicID].m_Width * scale * m_EffectScale;
	m_Pic.size.y = (float)m_HeroInfo->m_PictureDatas[m_PicID].m_Height * scale * m_EffectScale;

	m_Pic.picpos.x = (float)m_PicX;
	m_Pic.picpos.y = (float)m_PicY;
	m_Pic.picpos.z = (float)m_PicH;
	m_Pic.picpos.w = (float)m_PicW;

	m_Pic.faceside = (float)(m_FaceSide ? 1 : -1);	
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
	FramesMap::iterator iframe = m_HeroInfo->m_FramesMap.find(m_Frame);
	if(iframe == m_HeroInfo->m_FramesMap.end() || (int)iframe->second.size() <= m_FrameID){
		printf("fatal error: can't find next frame \"%s\"[%d] !\n", m_Frame.c_str(), m_FrameID);
		system("pause");
		throw "No such frame";
	}
	f = &m_HeroInfo->m_FramesMap[m_Frame][m_FrameID];
	if(f->m_ClearKeyQueue){
			m_KeyQue.clear();
		}
	m_PicID = f->m_PictureID;
	m_PicX = f->m_PictureX;
	m_PicY = f->m_PictureY;
	m_PicW = m_HeroInfo->m_PictureDatas[m_PicID].m_Column;
	m_PicH = m_HeroInfo->m_PictureDatas[m_PicID].m_Row;
	m_Texture = m_HeroInfo->m_PictureDatas[m_PicID].m_TextureID;
	m_Action = f->m_HeroAction;
	m_TimeTik = f->m_Wait;
	m_Vel.x += f->m_DVX * (m_FaceSide ? 1 : -1);
	m_Vel.y += f->m_DVY * (m_FaceSide ? 1 : -1);
	for (KeyQueue::iterator i=m_KeyQue.begin(); i != m_KeyQue.end();++i)
	{
		if (i->key == CtrlKey::UP)
			m_Vel.z += f->m_DVZ;
		else if (i->key == CtrlKey::DOWN)
			m_Vel.z -= f->m_DVZ;
	}
	m_CenterX = f->m_CenterX;
	m_CenterY = f->m_CenterY;
	m_Bodys = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_Bodys;
	CreateEffect();
}

bool Hero::ScanKeyQue()
{
	std::string nFrame;
	int nFramID=0;
	//bool eeTime = true;	//換 frame 時是否更新 TimeTic
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
		//非方向按鍵判斷
		if(m_KeyQue.empty()){
			return false;
		}
		else if(m_KeyQue.back().key == CtrlKey::ATK1 && !d_key[0]){
			//拳
			nFrame = "punch";
			d_key[0] = true;
		}
		else if(m_KeyQue.back().key == CtrlKey::ATK2 && !d_key[1]){
			//腳
			nFrame = "kick";
			d_key[1] = true;
		}
		else if(m_KeyQue.back().key == CtrlKey::JUMP && !d_key[2]){
			//跳
			nFrame = "jump";
			d_key[2] = true;
		}
		else if(m_KeyQue.back().key == CtrlKey::DEF  && !d_key[3]){
			//擋
			nFrame = "defend";
			d_key[3] = true;
		}
	}
	else if(m_Action == HeroAction::WALKING )
	{
		while(i!=m_KeyQue.end()){
			if(i->key == CtrlKey::UP)
			{
				if(m_TimeTik == 0) nFrame = "walking";
				m_Vel.z = m_HeroInfo->m_WalkingSpeedZ;
			}
			else if(i->key == CtrlKey::DOWN)
			{
				if(m_TimeTik == 0) nFrame = "walking";
				m_Vel.z = -m_HeroInfo->m_WalkingSpeedZ;
			}
			else if(i->key == CtrlKey::LEFT)
			{
				if( d_run != 0 && g_Time + d_run < WAIT_FOR_KEY_RUN && !m_FaceSide){
					//跑
					nFrame = "running";
					m_Vel.x = -m_HeroInfo->m_RunningSpeed;
				}
				else{
					if(m_TimeTik == 0) nFrame = "walking";
					m_Vel.x = -m_HeroInfo->m_WalkingSpeed;
					m_FaceSide = false;
				}
			}
			else if(i->key == CtrlKey::RIGHT)
			{
				if( d_run != 0 && g_Time - d_run < WAIT_FOR_KEY_RUN && m_FaceSide){
					//跑
					nFrame = "running";
					m_Vel.x = m_HeroInfo->m_RunningSpeed;
				}else{
					if(m_TimeTik == 0) nFrame = "walking";
					m_Vel.x = m_HeroInfo->m_WalkingSpeed;
					m_FaceSide = true;
				}
			}
			i++;
		}
		if(!nFrame.empty() )
		{
			nFramID = (m_FrameID+1) % (m_HeroInfo->m_FramesMap[nFrame].size());
		}

		//非方向按鍵判斷
		if(m_KeyQue.empty()){
			return false;
		}
		else if(m_KeyQue.back().key == CtrlKey::ATK1 && !d_key[0]){
			//拳
			nFrame = "punch";
			nFramID = 0;
			d_key[0] = true;
		}
		else if(m_KeyQue.back().key == CtrlKey::ATK2 && !d_key[1]){
			//腳
			nFrame = "kick";
			nFramID = 0;
			d_key[1] = true;
		}
		else if(m_KeyQue.back().key == CtrlKey::JUMP && !d_key[2]){
			//跳
			nFrame = "jump";
			nFramID = 0;
			d_key[2] = true;
		}
		else if(m_KeyQue.back().key == CtrlKey::DEF  && !d_key[3]){
			//擋
			nFrame = "defend";
			nFramID = 0;
			d_key[3] = true;
		}
	}
	else if(m_Action == HeroAction::RUNNING){
		m_Vel.x = (m_FaceSide ? m_HeroInfo->m_RunningSpeed : -m_HeroInfo->m_RunningSpeed);
		while(i!=m_KeyQue.end()){
			if(i->key == CtrlKey::UP)
			{
				if(m_TimeTik == 0) nFrame = "running";
				nFramID = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_NextFrameIndex;
				m_Vel.z = m_HeroInfo->m_RunningSpeedZ;
			}
			else if(i->key == CtrlKey::DOWN)
			{
				if(m_TimeTik == 0) nFrame = "running";
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
		//非方向按鍵判斷
		if(m_KeyQue.empty()){
			return false;
		}
		else if(m_KeyQue.back().key == CtrlKey::ATK1 && !d_key[0]){
			//衝拳
			nFrame = "run_punch";
			nFramID= 0;
			d_key[0] = true;
		}
		else if(m_KeyQue.back().key == CtrlKey::ATK2 && !d_key[1]){
			//衝腳
			nFrame = "run_kick";
			nFramID= 0;
			d_key[1] = true;
		}
		else if(m_KeyQue.back().key == CtrlKey::JUMP && !d_key[2]){
			//衝跳
			nFrame = "dash_front";
			nFramID= 0;
			m_Vel.y = m_HeroInfo->m_DashHeight;
			m_Vel.x = m_FaceSide ? m_HeroInfo->m_DashDistance : -m_HeroInfo->m_DashDistance;
			if(m_Vel.z == m_HeroInfo->m_RunningSpeedZ){
				m_Vel.z = m_HeroInfo->m_DashDistanceZ;
			}
			else if(m_Vel.z == -m_HeroInfo->m_RunningSpeedZ){
				m_Vel.z = -m_HeroInfo->m_DashDistanceZ;
			}
		d_key[2] = true;
		}
		else if(m_KeyQue.back().key == CtrlKey::DEF  && !d_key[3]){
			//滾
			nFrame = "rolling";
			nFramID= 0;
			d_key[3] = true;
		}
	}
	else if(m_Action == HeroAction::JUMP && m_TimeTik < 2){
		m_Vel.y = m_HeroInfo->m_JumpHeight;
		while(i!=m_KeyQue.end()){
			if(i->key == CtrlKey::UP)
			{
				m_Vel.z = m_HeroInfo->m_JumpDistanceZ;
			}
			else if(i->key == CtrlKey::DOWN)
			{
				m_Vel.z = -m_HeroInfo->m_JumpDistanceZ;
			}
			else if(i->key == CtrlKey::LEFT)
			{
				m_Vel.x = -m_HeroInfo->m_JumpDistance;
				m_FaceSide = false;
			}
			else if(i->key == CtrlKey::RIGHT)
			{
				m_Vel.x = m_HeroInfo->m_JumpDistance;
				m_FaceSide = true;
			}
			i++;
		}
	}
	else if(m_Action == HeroAction::IN_THE_AIR){
		while(i!=m_KeyQue.end()){
			if(i->key == CtrlKey::LEFT ){
				m_FaceSide = false;
				break;
			}
			else if(i->key == CtrlKey::RIGHT ){
				m_FaceSide = true;
				break;
			}
			i++;
		}
		//非方向按鍵判斷
		if(m_KeyQue.empty()){
			return false;
		}
		else if(m_KeyQue.back().key == CtrlKey::ATK1 && !d_key[0]){
			//拳
			nFrame = "jump_punch";
			d_key[0] = true;
		}//*/
		else if(m_KeyQue.back().key == CtrlKey::ATK2 && !d_key[1]){
			//腳
			nFrame = "jump_kick";
			d_key[1] = true;
		}
		/*else if(m_KeyQue.back().key == CtrlKey::JUMP && !d_key[2]){
			//跳
		}//*/
		/*else if(m_KeyQue.back().key == CtrlKey::DEF  && !d_key[3]){
			//擋
		}//*/
	}
	else if(m_Action == HeroAction::DEFEND){
		while(i!=m_KeyQue.end()){
			if(i->key == CtrlKey::LEFT ){
				m_FaceSide = false;
				break;
			}
			else if(i->key == CtrlKey::RIGHT ){
				m_FaceSide = true;
				break;
			}
			i++;
		}
	}
	else if(m_Action == HeroAction::DASH){
		while(i!=m_KeyQue.end()){
			if(i->key == CtrlKey::LEFT && m_FaceSide){
				m_FaceSide = false;
				if(m_Frame.compare("dash_front") == 0){
					nFrame = "dash_back";
					nFramID= m_FrameID;
					//wwTime = false;
				}
				else if(m_Frame.compare("dash_back") == 0){
					nFrame = "dash_front";
					nFramID= m_FrameID;
					//wwTime = false;
				}
				break;
			}
			else if(i->key == CtrlKey::RIGHT && !m_FaceSide){
				m_FaceSide = true;
				if(m_Frame.compare("dash_front") == 0){
					nFrame = "dash_back";
					nFramID= m_FrameID;
					//wwTime = false;
				}
				else if(m_Frame.compare("dash_back") == 0){
					nFrame = "dash_front";
					nFramID= m_FrameID;
					//wwTime = false;
				}
				break;
			}
			i++;
		}
		//非方向按鍵判斷
		if(m_KeyQue.empty()){
			return false;
		}
		else if(m_KeyQue.back().key == CtrlKey::ATK1 && !d_key[0]){
			//拳
			nFrame = "dash_punch";
			d_key[0] = true;
		}//*/
		else if(m_KeyQue.back().key == CtrlKey::ATK2 && !d_key[1]){
			//腳
			nFrame = "dash_kick";
			nFramID= 0;
			d_key[1] = true;
		}
		/*else if(m_KeyQue.back().key == CtrlKey::JUMP && !d_key[2]){
			//跳
		}//*/
		/*else if(m_KeyQue.back().key == CtrlKey::DEF  && !d_key[3]){
			//擋
		}//*/
	}
	else if(m_Action == HeroAction::CROUCH){
		if(m_KeyQue.empty()){
			if(m_TimeTik == 0){
				m_Vel.x = 0, m_Vel.y = 0, m_Vel.z = 0;
			}
			return false;
		}
		else if(m_KeyQue.back().key == CtrlKey::DEF && m_Frame.compare("crouch") == 0 && m_FrameID == 0){
			m_Vel = Vector3(0,0,0);
			nFrame = "rolling";
		}
		else{
			//收集按鍵
			int dx=0,dz=0,dj=0;
			while(i!=m_KeyQue.end()){
				if(i->key == CtrlKey::LEFT ){
					dx = -1;
				}
				else if(i->key == CtrlKey::RIGHT ){
					dx = +1;
				}
				else if(i->key == CtrlKey::UP ){
					dz = +1;
				}
				else if(i->key == CtrlKey::DOWN ){
					dz = -1;
				}
				i++;
			}
			if(!m_KeyQue.empty() && m_KeyQue.back().key == CtrlKey::JUMP && !d_key[2]){
				dj = 1;
				d_key[2] = true;
			}
			//判斷
			if(dj == 1 && m_Frame.compare("crouch") == 0){
				if(m_FrameID == 0){
					//dash
					if(dx != 0){
						nFrame = "dash_front";
						m_FaceSide = dx > 0;
						m_Vel.x = dx * m_HeroInfo->m_DashDistance;
						m_Vel.y = m_HeroInfo->m_DashHeight;
						if(dz != 0) m_Vel.z = dz * m_HeroInfo->m_DashDistanceZ;
					}
					else if(m_Vel.x != 0 ){
						if((m_Vel.x > 0) == m_FaceSide){
							nFrame = "dash_front";
							m_Vel.x = m_FaceSide ? m_HeroInfo->m_DashDistance : -m_HeroInfo->m_DashDistance;
						}
						else{
							nFrame = "dash_back";
							m_Vel.x = m_FaceSide ? -m_HeroInfo->m_DashDistance : m_HeroInfo->m_DashDistance;
						}
						m_Vel.y = m_HeroInfo->m_DashHeight;
						if(dz != 0) m_Vel.z = dz * m_HeroInfo->m_DashDistanceZ;
					}else{
						nFrame = "jump";
					}
				}
				else{
					nFrame = "jump";
				}
			}
		}
		//蹲完速度歸零
		if(m_TimeTik == 0){
			m_Vel.x = 0, m_Vel.y = 0, m_Vel.z = 0;
		}
	}
	//決定招式按鍵動作
	int cface = 0;

	if(!m_KeyQue.empty()){
		HitDatas hit = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_HitDatas;
		for(unsigned int i=0; i< hit.size(); i++){
			KeyQueue::reverse_iterator riKey = m_KeyQue.rbegin();
			const char *pHit = hit[i].m_KeyQueue.c_str(), *rHit = pHit;
			bool flag = true;
			//char *rHit = pHit[0];
			while( *rHit != 0 ) rHit ++;
			rHit--;
			while( riKey != m_KeyQue.rend() && rHit+1 != pHit && flag){
				KeyQueue::reverse_iterator ho,ch;
				switch(*rHit){
				case '^':
					if(riKey->key != CtrlKey::UP && riKey->key != CtrlKey::UP_KEYUP){
						flag = false;
					}
					break;
				case 'v':
					if(riKey->key != CtrlKey::DOWN && riKey->key != CtrlKey::DOWN_KEYUP){
						flag = false;
					}
					break;
				/*case '<':
					if(riKey->key != CtrlKey::LEFT && riKey->key != CtrlKey::LEFT_KEYUP){
						flag = false;
					}
					break;//*/
				case '>':
					if( riKey->key == CtrlKey::RIGHT || riKey->key == CtrlKey::RIGHT_KEYUP){
						cface = 1;
					}
					else if(riKey->key == CtrlKey::LEFT || riKey->key == CtrlKey::LEFT_KEYUP){
						cface = -1;
					}
					else {
						flag = false;
					}
					break;
				case 'A':
					if(riKey->key != CtrlKey::ATK1 && riKey->key != CtrlKey::ATK1_KEYUP){
						flag = false;
					}
					break;
				case 'B':
					if(riKey->key != CtrlKey::ATK2 && riKey->key != CtrlKey::ATK2_KEYUP){
						flag = false;
					}
					break;
				case 'J':
					if(riKey->key != CtrlKey::JUMP && riKey->key != CtrlKey::JUMP_KEYUP){
						flag = false;
					}
					break;
				case 'D':
					if(riKey->key != CtrlKey::DEF && riKey->key != CtrlKey::DEF_KEYUP){
						flag = false;
					}
					break;
				case '8':	//UP_KEYUP
					if(riKey == m_KeyQue.rbegin()){
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::UP_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || ch->key != CtrlKey::UP_KEYUP){
							flag = false;
						}
					}
					else{
						ho = riKey - 1;
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::UP_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || ch->key != CtrlKey::UP_KEYUP || 
							((isKeyUp(rHit[1]) && ch->timeUp > ho->timeUp) || (!isKeyUp(rHit[1]) && ch->timeUp > ho->time))){
							flag = false;
						}
					}
					break;
				case '2':	//DOWN_KEYUP
					if(riKey == m_KeyQue.rbegin()){
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::DOWN_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || ch->key != CtrlKey::DOWN_KEYUP){
							flag = false;
						}
					}
					else{
						ho = riKey - 1;
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::DOWN_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || ch->key != CtrlKey::DOWN_KEYUP || 
							((isKeyUp(rHit[1]) && ch->timeUp > ho->timeUp) || (!isKeyUp(rHit[1]) && ch->timeUp > ho->time))){
							flag = false;
						}
					}
					break;
				case '6':	//RIGHT_KEYUP
					if(riKey == m_KeyQue.rbegin()){
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::RIGHT_KEYUP && ch->key != CtrlKey::LEFT_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || (ch->key != CtrlKey::RIGHT_KEYUP && ch->key != CtrlKey::LEFT_KEYUP)){
							flag = false;
						}
					}
					else{
						ho = riKey - 1;
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::RIGHT_KEYUP && ch->key != CtrlKey::LEFT_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || (ch->key != CtrlKey::RIGHT_KEYUP && ch->key != CtrlKey::LEFT_KEYUP) || 
							((isKeyUp(rHit[1]) && ch->timeUp > ho->timeUp) || (!isKeyUp(rHit[1]) && ch->timeUp > ho->time))){
							flag = false;
						}
					}
					break;
				case 'a':
					if(riKey == m_KeyQue.rbegin()){
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::ATK1_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || ch->key != CtrlKey::ATK1_KEYUP){
							flag = false;
						}
					}
					else{
						ho = riKey - 1;
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::ATK1_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || ch->key != CtrlKey::ATK1_KEYUP || 
							((isKeyUp(rHit[1]) && ch->timeUp > ho->timeUp) || (!isKeyUp(rHit[1]) && ch->timeUp > ho->time))){
							flag = false;
						}
					}
					break;
				case 'b':
					if(riKey == m_KeyQue.rbegin()){
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::ATK2_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || ch->key != CtrlKey::ATK2_KEYUP){
							flag = false;
						}
					}
					else{
						ho = riKey - 1;
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::ATK2_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || ch->key != CtrlKey::ATK2_KEYUP || 
							((isKeyUp(rHit[1]) && ch->timeUp > ho->timeUp) || (!isKeyUp(rHit[1]) && ch->timeUp > ho->time))){
							flag = false;
						}
					}
					break;
				case 'j':
					if(riKey == m_KeyQue.rbegin()){
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::JUMP_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || ch->key != CtrlKey::JUMP_KEYUP){
							flag = false;
						}
					}
					else{
						ho = riKey - 1;
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::JUMP_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || ch->key != CtrlKey::JUMP_KEYUP || 
							((isKeyUp(rHit[1]) && ch->timeUp > ho->timeUp) || (!isKeyUp(rHit[1]) && ch->timeUp > ho->time))){
							flag = false;
						}
					}
					break;
				case 'd':
					if(riKey == m_KeyQue.rbegin()){
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::DEF_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || ch->key != CtrlKey::DEF_KEYUP){
							flag = false;
						}
					}
					else{
						ho = riKey - 1;
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != CtrlKey::DEF_KEYUP; ch++);
						if( ch == m_KeyQue.rend() || ch->key != CtrlKey::DEF_KEYUP || 
							((isKeyUp(rHit[1]) && ch->timeUp > ho->timeUp) || (!isKeyUp(rHit[1]) && ch->timeUp > ho->time))){
							flag = false;
						}
					}
					break;
				}
				riKey ++;
				rHit --;
			}
			if(pHit == rHit+1 && flag){
				nFrame = hit[i].m_FrameName;
				nFramID= hit[i].m_FrameOffset;
				m_Vel.z = 0; // fix skill z up down problem
				m_KeyQue.clear();
				break;
			}
		}
	}
	//清理佇列
	i=m_KeyQue.begin();
	while( i != m_KeyQue.end()){
		/*  i->key > CtrlKey::ATK2 ：特殊按鍵放開事件要處理
		 *  i->key >=CtrlKey::DEF  ：特殊按鍵放開事件不處理 */
		if( i->key >=CtrlKey::ATK2 && g_Time - i->time > KEYLIFE_AFTER_KEYUP){
			i = m_KeyQue.erase(i);
		}else i++;
	}
	//下個影格
	FramesMap::iterator iframe = m_HeroInfo->m_FramesMap.find(nFrame);
	if(nFrame.empty()){
		return false;
	}
	else if(iframe == m_HeroInfo->m_FramesMap.end() || (int)iframe->second.size() <= nFramID){
		printf("error: can't find frame \"%s\"[%d] !\n", nFrame.c_str(), nFramID);
		return false;
	}
	else{
		if(cface != 0) m_FaceSide = cface > 0;
		//m_Vel += dv;
		m_Frame = nFrame;
		m_FrameID = nFramID;
		FrameInfo *f = &iframe->second[m_FrameID];
		if(f->m_ClearKeyQueue){
			m_KeyQue.clear();
		}
		m_PicID = f->m_PictureID;
		m_PicX = f->m_PictureX;
		m_PicY = f->m_PictureY;
		m_PicW = m_HeroInfo->m_PictureDatas[m_PicID].m_Column;
		m_PicH = m_HeroInfo->m_PictureDatas[m_PicID].m_Row;
		m_Texture = m_HeroInfo->m_PictureDatas[m_PicID].m_TextureID;
		m_Action = f->m_HeroAction;
		m_TimeTik = f->m_Wait;
		m_Vel.x += f->m_DVX * (m_FaceSide ? 1 : -1);
		m_Vel.y += f->m_DVY;
		
		for (i=m_KeyQue.begin(); i != m_KeyQue.end();++i)
		{
			if (i->key == CtrlKey::UP)
				m_Vel.z += f->m_DVZ;
			else if (i->key == CtrlKey::DOWN)
				m_Vel.z -= f->m_DVZ;
		}
		
		m_CenterX = f->m_CenterX;
		m_CenterY = f->m_CenterY;
		m_Bodys = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_Bodys;
		CreateEffect();
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

	/*if(k.key >= CtrlKey::DEF_KEYUP){
		//忽略特殊按鍵放開事件
		return;
	}
	//*特殊按鍵放開*/
	if(k.key == CtrlKey::ATK1_KEYUP){
		//printf("ATK1_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::ATK1){
				i->key = k.key;
				i->timeUp = k.time;
				break;
			}
		}
	}
	else if(k.key == CtrlKey::ATK2_KEYUP){
		//printf("ATK2_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::ATK2){
				i->key = k.key;
				i->timeUp = k.time;
				break;
			}
		}
	}
	else if(k.key == CtrlKey::DEF_KEYUP){
		//printf("DEF_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::DEF){
				i->key = k.key;
				i->timeUp = k.time;
				break;
			}
		}
	}
	else if(k.key == CtrlKey::JUMP_KEYUP){
		//printf("JUMP_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::JUMP){
				i->key = k.key;
				i->timeUp = k.time;
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
				i->timeUp = k.time;
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
				i->timeUp = k.time;
				break;
			}
		}
	}
	else if(k.key == CtrlKey::UP_KEYUP){
		//printf("UP_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::UP){
				i->key = k.key;
				i->timeUp = k.time;
				break;
			}
		}
	}
	else if(k.key == CtrlKey::DOWN_KEYUP){
		//printf("DOWN_KEYUP\n");
		for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
			if(i->key == CtrlKey::DOWN){
				i->key = k.key;
				i->timeUp = k.time;
				break;
			}
		}
	}
	else{
		m_KeyQue.push_back(k);
		//若非方向鍵，將判斷非方向鍵之值歸零
		if(k.key == CtrlKey::ATK1){
			d_key[0] = false;
		}
		else if(k.key == CtrlKey::ATK2){
			d_key[1] = false;
		}
		else if(k.key == CtrlKey::JUMP){
			d_key[2] = false;
		}
		else if(k.key == CtrlKey::DEF){
			d_key[3] = false;
		}
		//若是方向鍵，將與其相反方向的按鍵事件取消
		else if(k.key == CtrlKey::UP){
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
			for(i = m_KeyQue.begin();i!=m_KeyQue.end();i++) {
				if(i->key == CtrlKey::RIGHT){
					m_KeyQue.erase(i);
					break;
				}
			}
		}
		else if(k.key == CtrlKey::RIGHT){
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

const Vector3& Hero::Position()
{
	return m_Position;
}

int Hero::Team()
{
	return m_Team;
}

void Hero::SetEffect( EffectType::e effect )
{
	m_Effect = effect;
}

void Hero::CreateEffect()
{
	if(m_Effect != EffectType::NONE){
		D3DXVECTOR4 v = D3DXVECTOR4((float)m_PicX,(float)m_PicY,(float)m_PicH,(float)m_PicW);
		m_Texture = g_EffectMG->CreateEffect(m_Effect,m_Texture,&v);
		m_PicX = (int)v.x;
		m_PicY = (int)v.y;
		m_PicH = (int)v.z;
		m_PicW = (int)v.w;

	}
	m_EffectScale = g_EffectMG->EffectScale(m_Effect);
}

BodyVerteices Hero::GetBodyVerteices()
{
	float scale = 3.0f;

	BodyVerteices bvs;
	BodyVertex bv;
	bv.position.x = m_Position.x;
	bv.position.y = m_Position.y;
	bv.position.z = m_Position.z;

	bv.center.x = m_CenterX * scale;
	bv.center.y = m_CenterY * scale;

	bv.angle = m_Angle;
	if(m_FaceSide){
		bv.faceside = 1;
	}else{
		bv.faceside = -1;
	}

	for (Bodys::iterator it = m_Bodys.begin();it != m_Bodys.end();it++)
	{
		Vec2s points_2D= it->m_Area.Points();
		for (unsigned int i=1; i+1 < points_2D.size();i++)
		{
			bv.body.x= points_2D[0].x *scale;
			bv.body.y = points_2D[0].y *scale;
			bvs.push_back(bv);

			bv.body.x= points_2D[i].x *scale;
			bv.body.y = points_2D[i].y *scale;
			bvs.push_back(bv);

			bv.body.x= points_2D[i+1].x *scale;
			bv.body.y = points_2D[i+1].y *scale;
			bvs.push_back(bv);
		}
	}

	return bvs;
}

BodyVerteices Hero::GetBodyLineVerteices()
{
	float scale = 3.0f;

	BodyVerteices bvs;
	BodyVertex bv;
	bv.position.x = m_Position.x;
	bv.position.y = m_Position.y;
	

	bv.center.x = m_CenterX * scale;
	bv.center.y = m_CenterY * scale;

	bv.angle = m_Angle;
	if(m_FaceSide){
		bv.faceside = 1;
	}else{
		bv.faceside = -1;
	}

	for (Bodys::iterator it = m_Bodys.begin();it != m_Bodys.end();it++)
	{
		Vec2s points_2D= it->m_Area.Points();
		for (unsigned int i=0; i < points_2D.size();i++)
		{
			bv.body.x= points_2D[i].x *scale;
			bv.body.y = points_2D[i].y *scale;
			bv.position.z = m_Position.z;
			bvs.push_back(bv);
			bv.position.z = m_Position.z + it->m_ZWidth;
			bvs.push_back(bv);
		}
		bv.position.z = m_Position.z + it->m_ZWidth;
		for (unsigned int i=0; i < points_2D.size();i++)
		{
			bv.body.x= points_2D[i].x *scale;
			bv.body.y = points_2D[i].y *scale;
			
			bvs.push_back(bv);
			bv.body.x= points_2D[(i+1)%points_2D.size()].x *scale;
			bv.body.y = points_2D[(i+1)%points_2D.size()].y *scale;
			bvs.push_back(bv);
		}
	}

	return bvs;
}

void Hero::GetBack()
{
	m_Position = m_PastPos;
}

void Hero::Stop()
{
	m_Vel = Vector3(0,0,0);
}

const Vector3& Hero::Past_Position()
{
	return m_PastPos;
}

const Vector3& Hero::Velocity()
{
	return m_Vel;
}

void Hero::OnGround()
{
	m_Vel.y=0;
	d_Ground=true;
}












bool SortHero( Hero_RawPtr a,Hero_RawPtr b )
{
	return a->GetTextureID()<b->GetTextureID();
}



