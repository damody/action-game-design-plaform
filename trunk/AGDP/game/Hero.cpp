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

#define KEYLIFE_AFTER_KEYUP 60
#define WAIT_FOR_KEY_RUN 30
#define FRICTION 0.5f
#define G_ACCE g_BackgroundManager.GetCurrentBackground()->Gravity()
#define SCALE 3.0f
#define CONDITION_MAX 20

Hero::Hero() {}

Hero::Hero( std::wstring h ):
	hero( h ), m_Position( Vector3() ), m_Team( 0 ), m_FaceSide( true ), m_FrameID( 0 ), m_Texture( 0 ), m_PicID( 0 ), m_PicW( 0 ), m_PicH( 0 ), m_PicX( 0 ), m_PicY( 0 ), d_run( 0 ), m_EffectScale( 1.0f ), d_key(g_KeyMap.sKeySize()), m_Fall( 70 ), m_FrontDefence( 0 ), m_BackDefence( 0 ), m_AtkRest(),m_Condition(0)
{
	m_HeroInfo = g_HeroInfoManager.GetHeroInfo( hero );
	m_Record = Record_Sptr( new Record() );
	

	if ( m_HeroInfo.get() )
	{
		this->Init();
	}
	else
	{
		std::wcout << L"Cannot find " << h << std::endl;
	}
}

void Hero::Init()
{
	m_Angle = 0;
	m_HP = m_HeroInfo->m_MaxHP;
	m_MaxRecoverHP = m_HeroInfo->m_MaxHP;
	m_MP = m_HeroInfo->m_MaxMP;
	m_Frame = L"default";
	m_FrameID = 0;
	FrameInfo* f = &m_HeroInfo->m_FramesMap[m_Frame][m_FrameID];
	m_PicID = f->m_PictureID;
	m_PicX = f->m_PictureX;
	m_PicY = f->m_PictureY;
	m_PicW = m_HeroInfo->m_PictureDatas[m_PicID].m_Column;
	m_PicH = m_HeroInfo->m_PictureDatas[m_PicID].m_Row;
	m_Texture = m_HeroInfo->m_PictureDatas[m_PicID].m_TextureID;
	m_Action = f->m_HeroAction;
	m_TimeTik = f->m_Wait;
	m_FrameInfo = f;
	m_CenterX = f->m_CenterX;
	m_CenterY = f->m_CenterY;
	//Get Hero Function Lua
	if( m_HeroFunctionLua.get() == NULL )
	{
		m_HeroFunctionLua = LuaCell_Sptr( new LuaCell );
		if ( !m_HeroFunctionLua->InputLuaFile( m_HeroInfo->m_HeroFunctionLuaPath.c_str() ) )
		{
			wprintf(L"fatal error: can't load lua file. m_HeroFunctionLuaPath: %s" , m_HeroInfo->m_HeroFunctionLuaPath.c_str());
			system("pause");
			throw "can't load lua file";
		}
	}
	//Register Hero Function to Lua
	RegisterFunctionToLua(m_HeroFunctionLua);
	//Creat Condition Object
	if( !m_Condition )
	{
		m_Condition = new Condition( this , m_HeroFunctionLua );
	}
	

}

void Hero::Update( float dt )
{
	bool d_next;

	if ( m_HP > 0 )
	{
		Recover();
		d_next = !ScanKeyQue();
	}
	else { 
		 d_next = m_Action != 42;
	}

	if ( d_next )  //無控制動作時，跑Wait Time
	{
		if ( m_TimeTik <= 0 ) { NextFrame(); }
		else { m_TimeTik--; }
	}

	//物理
	Vector3 pastPos = m_Position;
	//m_Position += m_Vel;
	bool pastInAir = false;
	bool inAir = false;

	//reAttack
	if(m_AtkRest.d != NULL){
		m_AtkRest.t --;
		if(m_AtkRest.t == 0){
			m_AtkRest.d = NULL;
		}
	}

	//場地限制
	if ( g_BackgroundManager.GetCurrentBackground() != NULL )
	{
		pastInAir = g_BackgroundManager.GetCurrentBackground()->AboveGround( pastPos ) == 1;
		inAir = !g_BackgroundManager.GetCurrentBackground()->isOnGround( pastPos, m_Vel, &m_Position );
		//SetPosition(g_BGManager.GetCurrentBackground()->AlignmentSpace(m_Position));
		//SetPosition(g_BGManager.GetCurrentBackground()->AlignmentBan(m_Position,pastPos));
		//inAir	= g_BGManager.GetCurrentBackground()->AboveGround(m_Position) == 1;
	}

	if ( !inAir )  	//地上
	{
		//落地判定
		if ( m_Action != 51 ) //HeroAction::UNIQUE_SKILL
		{
			bool flag = false;
			if( (m_Action == 33 || m_Action == 34) && m_Vel.y < -10.0){
				//摔落地面
				m_Vel.y = 5;
				m_Vel.x /= 2;
				SwitchFrame( m_Frame, 5);
				flag = true;
			}
			else{
				//Frame 改到 CrouchMap 中對應的 Frame
				CrouchMap::iterator icm = m_HeroInfo->m_CrouchMap.find( m_Action );

				if ( icm != m_HeroInfo->m_CrouchMap.end() ){
					m_Vel.y = 0;
					SwitchFrame( icm->second.m_FrameName, icm->second.m_FrameOffset );
					flag = true;
				}
			}
			if ( pastInAir && !flag ){
				m_Vel.y = 0;
				SwitchFrame( L"crouch", 0 );
			}
		}
		else { m_Position = pastPos + m_Vel; }
		//蹲與躺
		if(m_Action == 40 || m_Action == 42){
			if(m_Vel.x > 7.0) m_Vel.x = 7.0;
			else if(m_Vel.x < -7.0) m_Vel.x = -7.0;
			if(m_Vel.z > 7.0) m_Vel.z = 7.0;
			else if(m_Vel.z < -7.0) m_Vel.z = -7.0;
		}
		//X方向摩擦力計算
		float sign = m_Vel.x / abs( m_Vel.x );
		m_Vel.x = abs( m_Vel.x );
		m_Vel.x -= FRICTION;
		if ( m_Vel.x < 0 ) { m_Vel.x = 0; }
		else { m_Vel.x *= sign; }
		//Z方向摩擦力計算
		sign = m_Vel.z / abs( m_Vel.z );
		m_Vel.z = abs( m_Vel.z );
		m_Vel.z -= FRICTION;
		if ( m_Vel.z < 0 ) { m_Vel.z = 0; }
		else { m_Vel.z *= sign; }
	}
	else 					//空中
	{
		//重力加速度
		//if ( m_Action != HeroAction::AIR_SKILL && m_Action != HeroAction::UNIQUE_SKILL )
		if ( m_Action != 46 && m_Action != 51 )
		{	m_Vel.y -= G_ACCE;	}

		//掉落
		if ( m_Action == 0 ) //HeroAction::STANDING )
		{
			SwitchFrame( L"in_the_air", 0 );
		}
	}

	const Bodys& bodys = GetBodys();

	if ( !bodys.empty() )
	{
		m_BodyAABB.ReBuild( bodys.front().m_Area );

		for ( auto it = ++bodys.begin(); it != bodys.end(); it++ )
		{
			m_BodyAABB.AddPolygon2D( it->m_Area );
		}
		m_BodyAABB.Move(-m_CenterX, m_CenterY);
		if (!m_FaceSide) m_BodyAABB.ChangeFace();
		m_BodyAABB.Scale(SCALE);
		m_BodyAABB.Move(m_Position.x, m_Position.y);
		//printf("bodys: %f\t%f\n", m_BodyAABB.m_Max.x, m_BodyAABB.m_Min.x);
		//以後開printf或者cout 請在push前關掉
	}
	else
	{
		m_BodyAABB.SetBounding((float)-1e20);
	}

	const Attacks& attacks = GetAttacks();

	if ( !attacks.empty() )
	{
		m_AttackAABB.ReBuild( attacks.front().m_Area );

		for ( auto it = ++attacks.begin(); it != attacks.end(); it++ )
		{
			m_AttackAABB.AddPolygon2D( it->m_Area );
		}
		m_AttackAABB.Move(-m_CenterX, m_CenterY);
		if (!m_FaceSide) m_AttackAABB.ChangeFace();
		m_AttackAABB.Scale(SCALE);
		m_AttackAABB.Move(m_Position.x, m_Position.y);
		//printf("attck: %f\t%f\n", m_AttackAABB.m_Max.x, m_AttackAABB.m_Min.x);
		//以後開printf或者cout 請在push前關掉
	}
	else
	{
		m_AttackAABB.SetBounding((float)1e20);
	}

	//Condition Update
	ConditionUpdate(dt);

	//wprintf(L"beAttack MaxHP=%d\tHP=%d\tMP=%d\tFall=%d\tfrontDef=%d\tbackDef=%d\n",m_MaxRecoverHP, m_HP, m_MP, m_Fall, m_FrontDefence, m_BackDefence);
}

void Hero::UpdateDataToDraw()
{
	m_Pic.position.x = m_Position.x;
	m_Pic.position.y = m_Position.y;
	m_Pic.position.z = m_Position.z;
	m_Pic.center.x = SCALE * ( m_CenterX  + 0.5f * ( m_EffectScale - 1 ) * ( float )m_HeroInfo->m_PictureDatas[m_PicID].m_Width );
	m_Pic.center.y = SCALE * ( m_CenterY  + 0.5f * ( m_EffectScale - 1 ) * ( float )m_HeroInfo->m_PictureDatas[m_PicID].m_Height );
	m_Pic.angle = m_Angle;
	m_Pic.size.x = ( float )m_HeroInfo->m_PictureDatas[m_PicID].m_Width * SCALE * m_EffectScale;
	m_Pic.size.y = ( float )m_HeroInfo->m_PictureDatas[m_PicID].m_Height * SCALE * m_EffectScale;
	m_Pic.picpos.x = ( float )m_PicX;
	m_Pic.picpos.y = ( float )m_PicY;
	m_Pic.picpos.z = ( float )m_PicH;
	m_Pic.picpos.w = ( float )m_PicW;
	m_Pic.faceside = ( float )( m_FaceSide ? 1 : -1 );
}

Texture_Sptr Hero::GetTexture() const
{
	return g_TextureManager.GetTexture( m_Texture );
}

ClipVertex Hero::GetPic() const {	return m_Pic; }

int Hero::GetTextureID() const {	return m_Texture; }

void Hero::NextFrame()
{
	FrameInfo *f = m_FrameInfo;
	if( (m_Action == 33 || m_Action == 34) && m_FrameID != 5){
		if( m_Vel.y < 10.0 && m_Vel.y > 5.0 && m_FrameID != 1 ) m_FrameID = 1;
		else if( m_Vel.y < 5.0 && m_Vel.y > -7.0 && m_FrameID != 2 ) m_FrameID = 2;
		else if( m_Vel.y < -7.0 && m_FrameID != 3 ) m_FrameID = 3;
		else return;
	}
	else {
		m_Frame = f->m_NextFrameName;
		m_FrameID = f->m_NextFrameIndex;
	}
NextLoop:
	FramesMap::iterator iframe = m_HeroInfo->m_FramesMap.find( m_Frame );

	if ( iframe == m_HeroInfo->m_FramesMap.end() || ( int )iframe->second.size() <= m_FrameID )
	{
		wprintf( L"fatal error: can't find next frame \"%s\"[%d] !\n", m_Frame.c_str(), m_FrameID );
		system( "pause" );
		throw "No such frame";
	}

	f = &iframe->second[m_FrameID];

	if ( f->m_Consume.m_JumpRule <= 0 && f->m_Consume.m_HP != 0 && f->m_Consume.m_MP != 0)
	{
		wprintf( L"MaxHP:%d\tHP:%d\tMP:%d\n", m_MaxRecoverHP, m_HP, m_MP );

		if ( m_HP >= f->m_Consume.m_HP && m_MP >= f->m_Consume.m_MP )
		{
			m_HP -= f->m_Consume.m_HP;
			m_MP -= f->m_Consume.m_MP;
		}
		else
		{
			m_Frame = f->m_Consume.m_NotEnoughFrameName;
			m_FrameID = f->m_Consume.m_NotEnoughFrame;
			goto NextLoop;
		}
	}

	//clear keyQue
	if ( m_KeyQue.empty() ) {}
	else if ( f->m_ClearKeyQueue == 1 )
	{
		m_KeyQue.pop_back();
	}
	else if ( f->m_ClearKeyQueue == 2 )
	{
		m_KeyQue.clear();
	}

	//sound
	if ( !f->m_sound.empty() )
	{
		g_WavPlayer.Play ( g_WavPlayer.CreatSound( f->m_sound ) );
	}

	m_PicID = f->m_PictureID;
	m_PicX = f->m_PictureX;
	m_PicY = f->m_PictureY;
	m_PicW = m_HeroInfo->m_PictureDatas[m_PicID].m_Column;
	m_PicH = m_HeroInfo->m_PictureDatas[m_PicID].m_Row;
	m_Texture = m_HeroInfo->m_PictureDatas[m_PicID].m_TextureID;
	m_Action = f->m_HeroAction;
	m_TimeTik = f->m_Wait;
	m_CenterX = f->m_CenterX;
	m_CenterY = f->m_CenterY;
	m_FrameInfo = f;
	KeyQueue::iterator i = m_KeyQue.begin();
	int dx = 0, dz = 0;

	while ( i != m_KeyQue.end() )
	{
		if ( i->key == g_KeyMap.LeftKey().keyDown ) { dx = -1;}
		else if ( i->key == g_KeyMap.RightKey().keyDown ) { dx = +1;}
		else if ( i->key == g_KeyMap.UpKey().keyDown ) { dz = +1;}
		else if ( i->key == g_KeyMap.DownKey().keyDown ) { dz = -1;}

		i++;
	}

	UpdateVel( dx, dz );
	//創造物件
	float df = m_FaceSide ? 1.f : -1.f;

	if ( !f->m_Creations.empty() )
	{
		Creations::iterator ic = f->m_Creations.begin();

		while ( ic != f->m_Creations.end() )
		{
			Vector3 pos( df * ( ic->x - m_CenterX ) * SCALE + m_Position.x, ( ic->y + m_CenterY ) * SCALE + m_Position.y, m_Position.z ); //vel(ic->dvx,ic->dvy,ic->dvz);
			Creat( pos, *ic, m_FaceSide, m_Record );
			ic++;
		}
	}

	CreateEffect();
}

/**
 * 切換到指定 Frame ，不處理任何消耗，若找不到目標會中止程式
 * rFrame	:目標 Frame 名稱
 * rFrameID	:目標 Frame 序號
 */
void Hero::SwitchFrame( std::wstring rFrame, int rFrameID )
{
	FramesMap::iterator iframe = m_HeroInfo->m_FramesMap.find( rFrame );

	if ( iframe == m_HeroInfo->m_FramesMap.end() || ( int )iframe->second.size() <= rFrameID )
	{
		wprintf( L"fatal error: can't find next frame \"%s\"[%d] !\n", rFrame.c_str(), rFrameID );
		system( "pause" );
		throw "No such frame";
	}

	FrameInfo* f = &iframe->second[rFrameID];

	//clear keyQue
	if ( m_KeyQue.empty() ) {}
	else if ( f->m_ClearKeyQueue == 1 )
	{
		m_KeyQue.pop_back();
	}
	else if ( f->m_ClearKeyQueue == 2 )
	{
		m_KeyQue.clear();
	}

	//sound
	if ( !f->m_sound.empty() )
	{
		g_WavPlayer.Play ( g_WavPlayer.CreatSound( f->m_sound ) );
	}

	m_Frame = rFrame;
	m_FrameID = rFrameID;
	m_PicID = f->m_PictureID;
	m_PicX = f->m_PictureX;
	m_PicY = f->m_PictureY;
	m_PicW = m_HeroInfo->m_PictureDatas[m_PicID].m_Column;
	m_PicH = m_HeroInfo->m_PictureDatas[m_PicID].m_Row;
	m_Texture = m_HeroInfo->m_PictureDatas[m_PicID].m_TextureID;
	m_Action = f->m_HeroAction;
	m_TimeTik = f->m_Wait;
	m_CenterX = f->m_CenterX;
	m_CenterY = f->m_CenterY;
	m_FrameInfo = f;
	//創造物件
	float df = m_FaceSide ? 1.f : -1.f;

	if ( !f->m_Creations.empty() )
	{
		Creations::iterator ic = f->m_Creations.begin();

		while ( ic != f->m_Creations.end() )
		{
			Vector3 pos( df * ( ic->x - m_CenterX ) * SCALE + m_Position.x, ( ic->y + m_CenterY ) * SCALE + m_Position.y, m_Position.z ); //vel(ic->dvx,ic->dvy,ic->dvz);
			Creat( pos, *ic, m_FaceSide, m_Record );
			ic++;
		}
	}

	CreateEffect();
}

bool Hero::ScanKeyQue()
{
	std::wstring nFrame;
	int nFramID = 0;
	KeyQueue::iterator i = m_KeyQue.begin();
	int dx = 0, dz = 0;

	while ( i != m_KeyQue.end() )
	{
		if ( i->key == g_KeyMap.LeftKey().keyDown ) { dx = -1;}
		else if ( i->key == g_KeyMap.RightKey().keyDown ) { dx = +1;}
		else if ( i->key == g_KeyMap.UpKey().keyDown ) { dz = +1;}
		else if ( i->key == g_KeyMap.DownKey().keyDown ) { dz = -1;}

		i++;
	}

	//決定方向按鍵動作
	if ( m_Action == 0 ) //HeroAction::STANDING )
	{
		if ( dz > 0 )
		{
			nFrame = L"walking";
			m_Vel.z = m_HeroInfo->m_WalkingSpeedZ;
		}
		else if ( dz < 0 )
		{
			nFrame = L"walking";
			m_Vel.z = -m_HeroInfo->m_WalkingSpeedZ;
		}

		if ( dx > 0 )
		{
			if ( d_run != 0 && g_Time - d_run < WAIT_FOR_KEY_RUN && m_FaceSide )
			{
				//跑
				nFrame = L"running";
				m_Vel.x = m_HeroInfo->m_RunningSpeed;
			}
			else
			{
				//走
				nFrame = L"walking";
				m_Vel.x = m_HeroInfo->m_WalkingSpeed;
				m_FaceSide = true;
			}
		}
		else if ( dx < 0 )
		{
			if ( d_run != 0 && g_Time + d_run < WAIT_FOR_KEY_RUN && !m_FaceSide )
			{
				//跑
				nFrame = L"running";
				m_Vel.x = -m_HeroInfo->m_RunningSpeed;
			}
			else
			{
				//走
				nFrame = L"walking";
				m_Vel.x = -m_HeroInfo->m_WalkingSpeed;
				m_FaceSide = false;
			}
		}
	}
	else if ( m_Action == 1 ) //HeroAction::WALKING )
	{
		if ( dz > 0 )
		{
			if ( m_TimeTik == 0 ) { nFrame = L"walking"; }

			m_Vel.z = m_HeroInfo->m_WalkingSpeedZ;
		}
		else if ( dz < 0 )
		{
			if ( m_TimeTik == 0 ) { nFrame = L"walking"; }

			m_Vel.z = -m_HeroInfo->m_WalkingSpeedZ;
		}

		if ( dx > 0 )
		{
			if ( d_run != 0 && g_Time - d_run < WAIT_FOR_KEY_RUN && m_FaceSide )
			{
				//跑
				nFrame = L"running";
				m_Vel.x = m_HeroInfo->m_RunningSpeed;
			}
			else
			{
				//走
				if ( m_TimeTik == 0 ) { nFrame = L"walking"; }

				m_Vel.x = m_HeroInfo->m_WalkingSpeed;
				m_FaceSide = true;
			}
		}
		else if ( dx < 0 )
		{
			if ( d_run != 0 && g_Time + d_run < WAIT_FOR_KEY_RUN && !m_FaceSide )
			{
				//跑
				nFrame = L"running";
				m_Vel.x = -m_HeroInfo->m_RunningSpeed;
			}
			else
			{
				//走
				if ( m_TimeTik == 0 ) { nFrame = L"walking"; }

				m_Vel.x = -m_HeroInfo->m_WalkingSpeed;
				m_FaceSide = false;
			}
		}

		if ( nFrame.compare(L"walking") == 0 )
		{
			nFramID = ( m_FrameID + 1 ) % ( m_HeroInfo->m_FramesMap[nFrame].size() );
		}
	}
	else if ( m_Action == 2 ) //HeroAction::RUNNING )
	{
		m_Vel.x = ( m_FaceSide ? m_HeroInfo->m_RunningSpeed : -m_HeroInfo->m_RunningSpeed );

		if ( dz > 0 )
		{
			m_Vel.z = m_HeroInfo->m_RunningSpeedZ;
		}
		else if ( dz < 0 )
		{
			m_Vel.z = -m_HeroInfo->m_RunningSpeedZ;
		}

		if ( ( dx > 0 && !m_FaceSide ) || ( dx < 0 && m_FaceSide ) )
		{
			nFrame = L"stop_running";
			nFramID = 0;
			d_run = 0;
		}
	}
	else if ( m_Action == 43 ) //HeroAction::IN_THE_AIR )
	{
		if ( dx > 0 )
		{
			m_FaceSide = true;
		}
		else if ( dx < 0 )
		{
			m_FaceSide = false;
		}
	}
	else if ( m_Action == 32 ) //HeroAction::DEFEND )
	{
		if ( dx > 0 )
		{
			m_FaceSide = true;
		}
		else if ( dx < 0 )
		{
			m_FaceSide = false;
		}
	}
	else if ( m_Action == 39 ) //HeroAction::DASH )
	{
		if ( dx < 0 && m_FaceSide )
		{
			m_FaceSide = false;

			if ( m_Frame.compare( L"dash_front" ) == 0 )
			{
				nFrame = L"dash_back";
				nFramID = m_FrameID;
			}
			else if ( m_Frame.compare( L"dash_back" ) == 0 )
			{
				nFrame = L"dash_front";
				nFramID = m_FrameID;
			}
		}
		else if ( dx > 0 && !m_FaceSide )
		{
			m_FaceSide = true;

			if ( m_Frame.compare( L"dash_front" ) == 0 )
			{
				nFrame = L"dash_back";
				nFramID = m_FrameID;
			}
			else if ( m_Frame.compare( L"dash_back" ) == 0 )
			{
				nFrame = L"dash_front";
				nFramID = m_FrameID;
			}
		}
	}
	else if ( m_Action == 40 ) //HeroAction::CROUCH )
	{
		if ( m_KeyQue.empty() )
		{
			return false;
		}
		else if ( m_KeyQue.back().key == g_KeyMap.FindKeyDown(L"JUMP") && !isKeyUsed(m_KeyQue.back().key) && m_Frame.compare( L"crouch" ) == 0 )
		{
			d_key[2] = true;

			if ( m_FrameID == 0 )
			{
				//dash
				if ( dx != 0 )
				{
					nFrame = L"dash_front";
					m_FaceSide = dx > 0;
				}
				else if ( m_Vel.x != 0 )
				{
					if ( ( m_Vel.x > 0 ) == m_FaceSide )
					{
						nFrame = L"dash_front";
					}
					else
					{
						nFrame = L"dash_back";
					}
				}
				else
				{
					nFrame = L"jump";
				}
			}
			else
			{
				nFrame = L"jump";
			}
		}
	}

	//決定招式按鍵動作
	int cface = 0;

	if ( !m_KeyQue.empty() )
	{
		HitDatas hit = m_HeroInfo->m_FramesMap[m_Frame][m_FrameID].m_HitDatas;

		for ( unsigned int i = 0; i < hit.size(); i++ )
		{
			KeyQueue::reverse_iterator riKey = m_KeyQue.rbegin();		//倒著走 keyQue
			const char* pHit = hit[i].m_KeyQueue.c_str(), *rHit = pHit;	//pHit = hit 頭，rHit 倒著走 hit
			bool flag = true;

			//char *rHit = pHit[0];
			while ( *rHit != 0 ) { rHit ++; }

			int nKey = rHit - pHit, hoKeyUpT = -1;			//hoKeyUpT: 前一個 KeyUp 時間
			rHit--;

			if ( nKey == 1 && g_KeyMap.isSKey( *rHit ) && isKeyUsed( *rHit ) ) { continue;}

			while ( riKey != m_KeyQue.rend() && rHit + 1 != pHit && flag )
			{
				if(g_KeyMap.isKeyUp(*rHit)){
					char rhd = g_KeyMap.FindKeyDown(*rHit);
					if( rhd == 0){
						wprintf(L"錯誤：hit 使用了不存在的按鍵\n");
						wprintf(L"frame: %s, frameID: %d, ", m_Frame, m_FrameID);
						printf("hit: %s\n", pHit);
						system("pause");
						flag = false;
						break;
					}
					if(!m_FaceSide){
						if(rhd == g_KeyMap.LeftKey().keyDown) rhd = g_KeyMap.RightKey().keyDown;
						else if( rhd == g_KeyMap.RightKey().keyDown) rhd = g_KeyMap.LeftKey().keyDown;
					}
					if(riKey == m_KeyQue.rbegin()){
						KeyQueue::reverse_iterator ch;
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != rhd; ch++);

						if( ch == m_KeyQue.rend() || ch->key != rhd){ flag = false; }
						else { hoKeyUpT = ch->timeUp;}
					}
					else{
						KeyQueue::reverse_iterator ch, ho = riKey - 1;
						for(ch = riKey; ch != m_KeyQue.rend() && ch->key != rhd; ch++);

						if( ch == m_KeyQue.rend() || ch->key != rhd ||
							(g_KeyMap.isKeyUp(rHit[1]) ? ch->timeUp > hoKeyUpT : ch->timeUp > ho->timeUp ) ) 
						{ flag = false; }
						else { hoKeyUpT = ch->timeUp;}
					}
				}
				else{
					if(*rHit == g_KeyMap.LeftKey().keyDown){
						//反向方向鍵
						char up, dn;
						if(!m_FaceSide){
							up = g_KeyMap.RightKey().keyUp;
							dn = g_KeyMap.RightKey().keyDown;
						}
						else{
							up = g_KeyMap.LeftKey().keyUp;
							dn = g_KeyMap.LeftKey().keyDown;
						}
						if(riKey->key != dn && riKey->key != up ){ flag = false; }
					}
					else if(*rHit == g_KeyMap.RightKey().keyDown){
						//正向方向鍵
						char up, dn;
						if(m_FaceSide){
							up = g_KeyMap.RightKey().keyUp;
							dn = g_KeyMap.RightKey().keyDown;
						}
						else{
							up = g_KeyMap.LeftKey().keyUp;
							dn = g_KeyMap.LeftKey().keyDown;
						}
						if(riKey->key != dn && riKey->key != up ){ flag = false; }
					}
					else {
						char rhu = g_KeyMap.FindKeyUp(*rHit);
						if( rhu == 0){
							wprintf(L"錯誤：hit 使用了不存在的按鍵\n");
							wprintf(L"frame: %s, frameID: %d, ", m_Frame, m_FrameID);
							printf("hit: %s\n", pHit);
							system("pause");
							flag = false;
							break;
						}
						if(*rHit != riKey->key && rhu != riKey->key){ flag = false; }
					}
					riKey ++;
				}

				rHit --;
			}

			if ( pHit == rHit + 1 && flag )
			{
				nFrame = hit[i].m_FrameName;
				nFramID = hit[i].m_FrameOffset;

				if ( nKey == 1 && g_KeyMap.isSKey( *pHit ) )
				{
					keyUsed( *pHit );
				}
				else
				{
					m_Vel.z = 0; // fix skill z up down problem
					m_KeyQue.pop_back();
					break;
				}
			}
		}
	}

	//清理佇列
	i = m_KeyQue.begin();
	//printf("keymap: ");
	while ( i != m_KeyQue.end() )
	{
		//printf("%c, %d, %d\t",i->key,i->time,i->timeUp);
		if ( g_KeyMap.isKeyUp(i->key) && g_Time - i->timeUp > KEYLIFE_AFTER_KEYUP )
		{
			i = m_KeyQue.erase( i );
		}
		else { i++; }
	}
	//putchar('\n');
	//下個影格
	if ( nFrame.empty() )
	{
		return false;
	}

KeyLoop:
	FramesMap::iterator iframe = m_HeroInfo->m_FramesMap.find( nFrame );

	if ( iframe == m_HeroInfo->m_FramesMap.end() || ( int )iframe->second.size() <= nFramID )
	{
		wprintf( L"error: can't find frame \"%s\"[%d] !\n", nFrame.c_str(), nFramID );
		return false;
	}
	else
	{
		if ( cface != 0 ) { m_FaceSide = cface > 0; }

		//m_Vel += dv;
		FrameInfo* f = &iframe->second[nFramID];

		//消耗
		if ( f->m_Consume.m_JumpRule >= 0 )
		{
			wprintf( L"MaxHP:%d\tHP:%d\tMP:%d\n", m_MaxRecoverHP, m_HP, m_MP );

			//printf("consume: rule=%d, MP=%d, HP=%d, backFrame=%s, backFrameID=%d\n",f->m_Consume.m_JumpRule,f->m_Consume.m_MP,f->m_Consume.m_HP,f->m_Consume.m_NotEnoughFrameName.c_str(),f->m_Consume.m_NotEnoughFrame);
			if ( m_HP >= f->m_Consume.m_HP && m_MP >= f->m_Consume.m_MP )
			{
				m_HP -= f->m_Consume.m_HP;
				m_MP -= f->m_Consume.m_MP;
			}
			else
			{
				if ( f->m_Consume.m_NotEnoughFrameName.compare( L"default" ) == 0 )
				{	return false;	}

				nFrame = f->m_Consume.m_NotEnoughFrameName;
				nFramID = f->m_Consume.m_NotEnoughFrame;
				goto KeyLoop;
			}
		}

		m_Frame = nFrame;
		m_FrameID = nFramID;

		//clear keyQue
		if ( m_KeyQue.empty() ) {}
		else if ( f->m_ClearKeyQueue == 1 )
		{
			m_KeyQue.pop_back();
		}
		else if ( f->m_ClearKeyQueue == 2 )
		{
			m_KeyQue.clear();
		}

		//蹲的煞車效果
		if ( m_Action == 40 ) //HeroAction::CROUCH )
		{
			m_Vel = Vector3( 0, 0, 0 );
		}

		//sound
		if ( !f->m_sound.empty() )
		{
			g_WavPlayer.Play ( g_WavPlayer.CreatSound( f->m_sound ) );
		}

		m_PicID = f->m_PictureID;
		m_PicX = f->m_PictureX;
		m_PicY = f->m_PictureY;
		m_PicW = m_HeroInfo->m_PictureDatas[m_PicID].m_Column;
		m_PicH = m_HeroInfo->m_PictureDatas[m_PicID].m_Row;
		m_Texture = m_HeroInfo->m_PictureDatas[m_PicID].m_TextureID;
		m_Action = f->m_HeroAction;
		m_TimeTik = f->m_Wait;
		m_CenterX = f->m_CenterX;
		m_CenterY = f->m_CenterY;
		m_FrameInfo = f;
		UpdateVel( dx, dz );
		//創造物件
		float df = m_FaceSide ? 1.f : -1.f;

		if ( !f->m_Creations.empty() )
		{
			Creations::iterator ic = f->m_Creations.begin();

			while ( ic != f->m_Creations.end() )
			{
				Vector3 pos( df * ( ic->x - m_CenterX ) * SCALE + m_Position.x, ( ic->y + m_CenterY ) * SCALE + m_Position.y, m_Position.z ); //vel(ic->dvx,ic->dvy,ic->dvz);
				Creat( pos, *ic, m_FaceSide, m_Record );
				ic++;
			}
		}

		CreateEffect();
		return true;
	}
}

void Hero::UpdateVel( int dx, int dz )
{
	m_Vel.y += m_FrameInfo->m_DVY;

	//if ( m_Action == HeroAction::JUMP || m_Action == HeroAction::FREE_SKILL ){
	if ( m_Action == 38 || m_Action == 50 )
	{
		if ( dx != 0 )
		{
			m_Vel.x += m_FrameInfo->m_DVX * ( m_FaceSide ? 1 : -1 );
		}

		if ( dz > 0 )
		{
			m_Vel.z += m_FrameInfo->m_DVZ;
		}
		else if ( dz < 0 )
		{
			m_Vel.z -= m_FrameInfo->m_DVZ;
		}
	}
	else if ( m_Action == 48 )	//HeroAction::Z_AXIS_SKILL )
	{
		if ( dx != 0 )
		{
			m_Vel.x += m_FrameInfo->m_DVX * ( m_FaceSide ? 1 : -1 );
		}

		m_Vel.z += m_FrameInfo->m_DVZ;
	}
	else if ( m_Action == 49 )	//HeroAction::GROUND_SKILL )
	{
		m_Vel.x += m_FrameInfo->m_DVX * ( m_FaceSide ? 1 : -1 );
		m_Vel.z += m_FrameInfo->m_DVZ;
	}
	else						//X_AXIS_SKILL = Normal
	{
		m_Vel.x += m_FrameInfo->m_DVX * ( m_FaceSide ? 1 : -1 );

		if ( dz > 0 )
		{
			m_Vel.z += m_FrameInfo->m_DVZ;
		}
		else if ( dz < 0 )
		{
			m_Vel.z -= m_FrameInfo->m_DVZ;
		}
	}
}

FrameInfo* Hero::FindFrame( std::wstring rframe, int rframeID )
{
	FramesMap::iterator iframe = m_HeroInfo->m_FramesMap.find( rframe );

	if ( iframe == m_HeroInfo->m_FramesMap.end() || ( int )iframe->second.size() <= rframeID )
	{
		wprintf( L"error: can't find frame \"%s\"[%d] !\n", rframe.c_str(), rframeID );
		return NULL;
	}

	return &iframe->second[rframeID];
}

void Hero::SetPosition( const Vector3& pos )
{	m_Position = pos; }

void Hero::SetRecord( Record_Sptr r ) { m_Record = r; }

void Hero::PushKey( KeyInfo& k )
{
	if(g_KeyMap.isKeyUp(k.key)){
		char kdn = g_KeyMap.FindKeyDown(k.key);
		if(kdn != 0){
			KeyQueue::iterator i;
			for(i = m_KeyQue.begin(); i != m_KeyQue.end(); i++){
				if(kdn == i->key){
					i->key = k.key;
					i->timeUp = k.time;

					if(k.key == g_KeyMap.LeftKey().keyUp) d_run = -i->time;
					else if(k.key == g_KeyMap.RightKey().keyUp) d_run = i->time;
					break;
				}
			}
		}
		else{
			printf("收到不存在的按鍵 %c\n", k.key);
		}
	}
	else{
		m_KeyQue.push_back(k);
		
		if(g_KeyMap.isSKey(k.key)){
			newKey(k.key);
		}
		else if( k.key == g_KeyMap.UpKey().keyDown){
			for(KeyQueue::iterator i = m_KeyQue.begin(); i!= m_KeyQue.end(); i++){
				if(i->key == g_KeyMap.DownKey().keyDown){
					m_KeyQue.erase(i);
					break;
				}
			}
		}
		else if( k.key == g_KeyMap.DownKey().keyDown){
			for(KeyQueue::iterator i = m_KeyQue.begin(); i!= m_KeyQue.end(); i++){
				if(i->key == g_KeyMap.UpKey().keyDown){
					m_KeyQue.erase(i);
					break;
				}
			}
		}
		else if( k.key == g_KeyMap.LeftKey().keyDown){
			for(KeyQueue::iterator i = m_KeyQue.begin(); i!= m_KeyQue.end(); i++){
				if(i->key == g_KeyMap.RightKey().keyDown){
					m_KeyQue.erase(i);
					break;
				}
			}
		}
		else if( k.key == g_KeyMap.RightKey().keyDown){
			for(KeyQueue::iterator i = m_KeyQue.begin(); i!= m_KeyQue.end(); i++){
				if(i->key == g_KeyMap.LeftKey().keyDown){
					m_KeyQue.erase(i);
					break;
				}
			}
		}
	}
}

void Hero::Recover()
{
	if ( m_MP < 500 )
	{
		m_MP += 1 + 200 / m_HP;

		if ( m_MP > 500 ) { m_MP = 500; }
	}

	if ( m_HP < m_MaxRecoverHP )
	{
		m_HP += 1;

		if ( m_HP > m_MaxRecoverHP ) { m_HP = m_MaxRecoverHP; }
	}

	if ( m_Fall < 70 ) { m_Fall ++; }

	if ( m_Action == 32 ) //HeroAction::DEFEND )
	{
		if ( m_FrontDefence < 100 ) { m_FrontDefence ++; }
	}
	else
	{
		m_FrontDefence = 0;
		m_BackDefence = 0;
	}
}

/**
 * 被敵人攻擊
 * rAtk		:擊中之 Attack
 * rHero	:攻擊者的紀錄資料
 * hitPos	:擊中點(重疊範圍中心，只重視 X 軸精確度)
 * FaceSide	:攻擊者的面向(若為氣功則為氣功波的面向)
 */
void Hero::beAttack( const Attack *rAtk, const Hero *rHero, const Vector3& hitPos, bool rFace )
{
	if ( rAtk->m_Kind == 0 ) 				//普通攻擊形式，套用 effect 擊中特效
	{
		if ( rHero == this ||									//普通形式的攻擊對自己無效
			 (rHero->m_Team != 0 && rHero->m_Team == m_Team) ||	//普通形式的攻擊對同隊無效
			 rHero == m_AtkRest.d )								//重複擊中免疫時間
		{	return;	}

		m_Vel.x += rAtk->m_DVX * ( rFace ? 1.0f : -1.0f );
		m_Vel.y += rAtk->m_DVY;
		m_Vel.z += rAtk->m_DVZ;
		std::wstring nFrame;
		int nFrameID = 0;
		Record_Sptr rHeroRec = rHero->GetRecord();
		int effect = -1;

		if ( ( hitPos.x > m_Position.x && m_FaceSide ) || ( hitPos.x < m_Position.x && !m_FaceSide ) )
		{
			//擊中點在人前方
			if ( m_FrontDefence > 0 ) 		//前方有剛體保護
			{
				m_FrontDefence -= rAtk->m_BreakDefend;
				m_HP -= rAtk->m_Injury / 10;
				m_MaxRecoverHP -= rAtk->m_Injury / 30;
				rHeroRec->Attack += rAtk->m_Injury / 10;
			}
			else
			{
				m_HP -= rAtk->m_Injury;
				m_MaxRecoverHP -= rAtk->m_Injury / 3;
				m_Fall -= rAtk->m_Fall;
				effect = rAtk->m_Effect;
				nFrame = L"injured";
				nFrameID = 0;
				rHeroRec->Attack += rAtk->m_Injury;
			}

			//倒下
			if ( m_HP <= 0 || m_Fall <= 0 )
			{
				nFrame = L"falling_back";
				nFrameID = 0;
				if(m_Vel.y < 10) m_Vel.y += 10;
			}
		}
		else
		{
			//擊中點在人後方
			if ( m_BackDefence > 0 ) 		//後方有剛體保護
			{
				m_FrontDefence -= rAtk->m_BreakDefend;
				m_HP -= rAtk->m_Injury / 10;
				m_MaxRecoverHP -= rAtk->m_Injury / 30;
				rHeroRec->Attack += rAtk->m_Injury / 10;
			}
			else
			{
				m_HP -= rAtk->m_Injury;
				m_MaxRecoverHP -= rAtk->m_Injury / 3;
				m_Fall -= rAtk->m_Fall;
				effect = rAtk->m_Effect;
				nFrame = L"injured";
				nFrameID = 0;
				rHeroRec->Attack += rAtk->m_Injury;
			}

			//倒下
			if ( m_HP <= 0 || m_Fall <= 0 )
			{
				nFrame = L"falling_front";
				nFrameID = 0;
				if(m_Vel.y < 10) m_Vel.y += 10;
			}
		}
		wprintf(L"beAttack MaxHP=%d\tHP=%d\tMP=%d\tFall=%d\tfrontDef=%d\tbackDef=%d\n",m_MaxRecoverHP, m_HP, m_MP, m_Fall, m_FrontDefence, m_BackDefence);
		//effect
		luabind::call_function<int>(m_HeroFunctionLua->GetLuaState(), "AddCondition",this,effect);
		/*if( effect >= 0 ){
			//將 EFFECT 套用，應套用之 EFFECT 即 effect 之值所代表的項目
			//holyk
			//std::cout<<std::endl<<"effect:"<<effect<<std::endl;
			switch ( effect )
			{
				case 0://fire
					luabind::call_function<int>(m_HeroFunctionLua->GetLuaState(), "AddCondition",this,effect);
					break;
				default:
					//nothing to do
					break;
					
			}
			
			//holyk
		}*/
		//設定 reAttackRest
		m_AtkRest.d = rHero;
		m_AtkRest.t = rAtk->m_ReAttackRest;
		//切換 Frame
		if ( !nFrame.empty() )
		{
			SwitchFrame( nFrame, nFrameID );
		}
	}
	else {}
}

void Hero::SetTeam( int team ) { m_Team = team; }

const Vector3& Hero::Position() const { return m_Position; }

int Hero::Team() const { return m_Team; }

//void Hero::SetEffect( EffectType::e effect ) { m_Effect = effect; }

void Hero::CreateEffect()
{
	if( m_Condition->IsEnable()==false )
	{
		m_EffectScale = 1.0f;
	}
	else
	{
		static std::vector<int> presentCondition;
		presentCondition = m_Condition->GetPresentConditionIndex();
		for( unsigned int idx = 0;idx<presentCondition.size();idx++ )
		{
			Vector4 v = Vector4( ( float )m_PicX, ( float )m_PicY, ( float )m_PicH, ( float )m_PicW );
			m_Texture = g_EffectManager->CreateEffect( presentCondition[idx] , m_Texture, &v );
			//holyk test 現在目前只有火焰是屬於"特效"需要放大  例如punch就不用 先標記
			m_PicX = ( int )v.x;
			m_PicY = ( int )v.y;
			m_PicH = ( int )v.z;
			m_PicW = ( int )v.w;
		}
		m_EffectScale = 2.0f;
	}
	
	/*
	if ( m_Effect != EffectType::NONE )
	{
		Vector4 v = Vector4( ( float )m_PicX, ( float )m_PicY, ( float )m_PicH, ( float )m_PicW );
		m_Texture = g_EffectManager->CreateEffect( m_Effect, m_Texture, &v );
		m_PicX = ( int )v.x;
		m_PicY = ( int )v.y;
		m_PicH = ( int )v.z;
		m_PicW = ( int )v.w;
	}
	*/
	
}

PolygonVerteices Hero::GetPolygonVerteices() const
{
	PolygonVerteices pvs;
	PolygonVertex pv;
	Polygon2Ds bodys = GetHeroBodys( *this );
	pv.color.x = 0.0;
	pv.color.y = 0.0;
	pv.color.z = 1.0;
	pv.color.w = 0.5;

	for ( Polygon2Ds::iterator it = bodys.begin(); it != bodys.end(); it++ )
	{
		auto points = it->Points();
		pv.position.z = it->GetZPoint() - it->GetZRange() / 2;

		for ( unsigned int i = 1; i + 1 < points.size(); i++ )
		{
			pv.position.x = points[0].x();
			pv.position.y = points[0].y();
			pvs.push_back( pv );
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pvs.push_back( pv );
			pv.position.x = points[i + 1].x();
			pv.position.y = points[i + 1].y();
			pvs.push_back( pv );
		}
	}

	Polygon2Ds  atks = GetHeroAttacks( *this );
	pv.color.x = 1.0;
	pv.color.y = 0.0;
	pv.color.z = 0.0;
	pv.color.w = 0.5;

	for ( Polygon2Ds::iterator it = atks.begin(); it != atks.end(); it++ )
	{
		auto points = it->Points();
		pv.position.z = it->GetZPoint() - it->GetZRange() / 2;

		for ( unsigned int i = 1; i + 1 < points.size(); i++ )
		{
			pv.position.x = points[0].x();
			pv.position.y = points[0].y();
			pvs.push_back( pv );
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pvs.push_back( pv );
			pv.position.x = points[i + 1].x();
			pv.position.y = points[i + 1].y();
			pvs.push_back( pv );
		}
	}

	Polygon2Ds  catches = GetHeroCatches( *this );
	pv.color.x = 0.0;
	pv.color.y = 1.0;
	pv.color.z = 0.0;
	pv.color.w = 0.5;

	for ( Polygon2Ds::iterator it = catches.begin(); it != catches.end(); it++ )
	{
		auto points = it->Points();
		pv.position.z = it->GetZPoint() - it->GetZRange() / 2;

		for ( unsigned int i = 1; i + 1 < points.size(); i++ )
		{
			pv.position.x = points[0].x();
			pv.position.y = points[0].y();
			pvs.push_back( pv );
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pvs.push_back( pv );
			pv.position.x = points[i + 1].x();
			pv.position.y = points[i + 1].y();
			pvs.push_back( pv );
		}
	}

	return pvs;
}

PolygonVerteices Hero::GetPolygonLineVerteices() const
{
	PolygonVerteices pvs;
	PolygonVertex pv;
	Polygon2Ds bodys = GetHeroBodys( *this );
	pv.color.x = 0.0;
	pv.color.y = 0.0;
	pv.color.z = 1.0;
	pv.color.w = 0.5;

	for ( Polygon2Ds::iterator it = bodys.begin(); it != bodys.end(); it++ )
	{
		auto points = it->Points();

		for ( unsigned int i = 0; i < points.size(); i++ )
		{
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pv.position.z = it->GetZPoint() - it->GetZRange() / 2;
			pvs.push_back( pv );
			pv.position.z = it->GetZPoint() + it->GetZRange() / 2;
			pvs.push_back( pv );
		}

		pv.position.z = it->GetZPoint() + it->GetZRange() / 2;

		for ( unsigned int i = 0; i < points.size(); i++ )
		{
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pvs.push_back( pv );
			pv.position.x = points[( i + 1 ) % points.size()].x();
			pv.position.y = points[( i + 1 ) % points.size()].y();
			pvs.push_back( pv );
		}
	}

	Polygon2Ds atks = GetHeroAttacks( *this );
	pv.color.x = 1.0;
	pv.color.y = 0.0;
	pv.color.z = 0.0;
	pv.color.w = 0.5;

	for ( Polygon2Ds::iterator it = atks.begin(); it != atks.end(); it++ )
	{
		auto points = it->Points();

		for ( unsigned int i = 0; i < points.size(); i++ )
		{
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pv.position.z = it->GetZPoint() - it->GetZRange() / 2;
			pvs.push_back( pv );
			pv.position.z = it->GetZPoint() + it->GetZRange() / 2;
			pvs.push_back( pv );
		}

		pv.position.z = it->GetZPoint() + it->GetZRange() / 2;

		for ( unsigned int i = 0; i < points.size(); i++ )
		{
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pvs.push_back( pv );
			pv.position.x = points[( i + 1 ) % points.size()].x();
			pv.position.y = points[( i + 1 ) % points.size()].y();
			pvs.push_back( pv );
		}
	}

	Polygon2Ds catches = GetHeroCatches( *this );
	pv.color.x = 0.0;
	pv.color.y = 1.0;
	pv.color.z = 0.0;
	pv.color.w = 0.5;

	for ( Polygon2Ds::iterator it = catches.begin(); it != catches.end(); it++ )
	{
		auto points = it->Points();

		for ( unsigned int i = 0; i < points.size(); i++ )
		{
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pv.position.z = it->GetZPoint() - it->GetZRange() / 2;
			pvs.push_back( pv );
			pv.position.z = it->GetZPoint() + it->GetZRange() / 2;
			pvs.push_back( pv );
		}

		pv.position.z = it->GetZPoint() + it->GetZRange() / 2;

		for ( unsigned int i = 0; i < points.size(); i++ )
		{
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pvs.push_back( pv );
			pv.position.x = points[( i + 1 ) % points.size()].x();
			pv.position.y = points[( i + 1 ) % points.size()].y();
			pvs.push_back( pv );
		}
	}

	return pvs;
}

const Vector3& Hero::Velocity() const { return m_Vel; }

Bodys& Hero::GetBodys( ) const
{
	return m_FrameInfo->m_Bodys;
}
Attacks &Hero::GetAttacks( ) const
{
	return m_FrameInfo->m_Attacks;
}
CatchInfos& Hero::GetCatches( ) const
{
	return m_FrameInfo->m_Catchs;
}
Record_Sptr Hero::GetRecord() const
{
	return m_Record;
}
bool Hero::GetFace() const
{
	return m_FaceSide;
}

bool Hero::IsAlive() const
{
	return m_HP > 0;
}

bool Creat( const Vector3& pos, const Creation& obj, bool face, const Record_Sptr owner )
{
	if ( obj.amount <= 0 )
	{
		wprintf( L"you just want to creat nothing!\n" );
		return true;
	}

	std::wstring u = obj.name;
	bool f = face ^ ( obj.facing > 0 );

	if ( g_HeroInfoManager.GetHeroInfo( u ) != HeroInfo_Sptr() )
	{
		for ( int i = 0; i < obj.amount; i++ )
		{
			Hero* s = g_HeroManager.Create( u, pos, owner == Record_Sptr() ? 0 : owner->team );
			s->m_FaceSide = f;
			s->m_Vel = obj.v0;
			s->m_Frame.assign( obj.frame );
			s->m_FrameID = obj.frameID;
			s->m_HP = obj.HP;
			//s->m_MaxRecoverHP = obj.HP;
			//s->owner = owner;
		}

		return true;
	}
	else if ( g_ObjectInfoManager.GetObjectInfo( u ) != ObjectInfo_Sptr() )
	{
		Object** object;

		object = g_ObjectManager.CreateObject( u, pos, obj.v0 , obj.amount, owner == Record_Sptr() ? 0 : owner->team );

		for ( int i = 0; i < obj.amount; i++ )
		{
			object[i]->m_FaceSide = f;
			object[i]->SetVelocity( obj.v0 );
			object[i]->m_Frame = obj.frame;
			object[i]->m_FrameID = obj.frameID;
			object[i]->m_HP = obj.HP;
		}
		return true;
				//(*s)->owner = owner;
	}
	else
	{
		wprintf( L"error: can't find %s\n", u.c_str() );
		return false;
	}
}

bool Hero::isKeyUsed( char r ) const
{
	switch ( r )
	{
		case 'A': return d_key[0];

		case 'B': return d_key[1];

		case 'J': return d_key[2];

		case 'D': return d_key[3];

		default: return false;
	}
}
void Hero::keyUsed( char r )
{
	switch ( r )
	{
		case 'A': d_key[0] = true;

		case 'B': d_key[1] = true;

		case 'J': d_key[2] = true;

		case 'D': d_key[3] = true;
	}
}
void Hero::newKey( char r )
{
	switch ( r )
	{
		case 'A': d_key[0] = false;

		case 'B': d_key[1] = false;

		case 'J': d_key[2] = false;

		case 'D': d_key[3] = false;
	}
}

AABB2D& Hero::GetBodyAABB()
{
	return m_BodyAABB;
}

AABB2D& Hero::GetAttackAABB()
{
	return m_AttackAABB;
}

AABB2D& Hero::GetCatchAABB()
{
	return m_CatchAABB;
}
void Hero::RegisterFunctionToLua( LuaCell_Sptr luadata )
{
	luabind::open(luadata->GetLuaState());
	luabind::module(luadata->GetLuaState())
		[
			luabind::class_<Hero>("Hero")
			.def(luabind::constructor<>())
			//Register Hero member function to luabind
			.def("AddCondition", &Hero::AddCondition)
			.def("ModifyMaxHP", &Hero::ModifyMaxHP)
			.def("ModifyHP", &Hero::ModifyHP)
			.def("ModifyMP", &Hero::ModifyMP)
			.def("ModifyFall", &Hero::ModifyFall)
			.def("ModifyFrontDefence", &Hero::ModifyFrontDefence)
			.def("ModifyBackDefence", &Hero::ModifyBackDefence)
		];
}
inline void Hero::AddCondition( int effectIndex , int time )
{
	m_Condition->Add(effectIndex,time);
}
inline void Hero::ConditionUpdate( float dt )
{
	m_Condition->Update( dt );
}

void Hero::ModifyHP( int delta ){
	m_HP += delta;
	if(delta < 0) m_Record->HPLost += delta;
}

void Hero::ModifyMaxHP( int delta )	{
	m_MaxRecoverHP += delta;
	if( m_HP > m_MaxRecoverHP){
		m_Record->HPLost = m_HP - m_MaxRecoverHP;
		m_HP = m_MaxRecoverHP;
	}
}
void Hero::ModifyMP( int delta )			{	m_MP += delta;			}
void Hero::ModifyFall( int delta )			{
	m_Fall += delta;
	if(m_Fall <= 0 && m_Action != 33 && m_Action != 34){
		SwitchFrame(L"falling_front", 0);
	}
}
void Hero::ModifyFrontDefence( int delta )	{	m_FrontDefence += delta;}
void Hero::ModifyBackDefence( int delta )	{	m_BackDefence += delta;	}
void Hero::ChangeTeam( int newTeam )		{	m_Team = newTeam, m_Record->team = newTeam;}

bool SortHero( Hero_RawPtr a, Hero_RawPtr b )
{
	return a->GetTextureID() < b->GetTextureID();
}
//* 碰撞判定用函示
Polygon2Ds GetHeroBodys( const Hero& r )
{
	Polygon2Ds d;

	for ( Bodys::iterator ib = r.m_FrameInfo->m_Bodys.begin(); ib != r.m_FrameInfo->m_Bodys.end(); ib++ )
	{
		Polygon2D s;

		if ( !ib->m_Area.Points().empty() )
		{
			for ( auto iv = ib->m_Area.Points().begin(); iv != ib->m_Area.Points().end(); iv++ )
			{
				if ( r.m_FaceSide ) 	//面向右邊
				{
					s.AddPoint( r.m_Position.x - ( r.m_CenterX - iv->x() ) * SCALE, r.m_Position.y + ( r.m_CenterY + iv->y() ) * SCALE );
				}
				else 				//面向左邊
				{
					s.AddPoint( r.m_Position.x + ( r.m_CenterX - iv->x() ) * SCALE, r.m_Position.y + ( r.m_CenterY + iv->y() ) * SCALE );
				}
			}
		}

		s.SetZPoint( r.m_Position.z );
		s.SetZRange( ib->m_ZWidth );
		d.push_back( s );
	}

	return d;
}

Polygon2Ds GetHeroAttacks( const Hero& r )
{
	Polygon2Ds d;

	for ( Attacks::iterator ib = r.m_FrameInfo->m_Attacks.begin(); ib != r.m_FrameInfo->m_Attacks.end(); ib++ )
	{
		Polygon2D s;

		for ( auto iv = ib->m_Area.Points().begin(); iv != ib->m_Area.Points().end(); iv++ )
		{
			if ( r.m_FaceSide ) 	//面向右邊
			{
				s.AddPoint( r.m_Position.x - ( r.m_CenterX - iv->x() ) * SCALE, r.m_Position.y + ( r.m_CenterY + iv->y() ) * SCALE );
			}
			else 				//面向左邊
			{
				s.AddPoint( r.m_Position.x + ( r.m_CenterX - iv->x() ) * SCALE, r.m_Position.y + ( r.m_CenterY + iv->y() ) * SCALE );
			}
		}

		s.SetZPoint( r.m_Position.z );
		s.SetZRange( ib->m_ZWidth );
		d.push_back( s );
	}

	return d;
}

Polygon2Ds GetHeroCatches( const Hero& r )
{
	Polygon2Ds d;

	for ( CatchInfos::iterator ib = r.m_FrameInfo->m_Catchs.begin(); ib != r.m_FrameInfo->m_Catchs.end(); ib++ )
	{
		Polygon2D s;

		for ( auto iv = ib->m_Area.Points().begin(); iv != ib->m_Area.Points().end(); iv++ )
		{
			if ( r.m_FaceSide ) 	//面向右邊
			{
				s.AddPoint( r.m_Position.x - ( r.m_CenterX - iv->x() ) * SCALE, r.m_Position.y + ( r.m_CenterY + iv->y() ) * SCALE );
			}
			else 				//面向左邊
			{
				s.AddPoint( r.m_Position.x + ( r.m_CenterX - iv->x() ) * SCALE, r.m_Position.y + ( r.m_CenterY + iv->y() ) * SCALE );
			}
		}

		s.SetZPoint( r.m_Position.z );
		s.SetZRange( ib->m_ZWidth );
		d.push_back( s );
	}

	return d;
}
//*/
