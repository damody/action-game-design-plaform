#include "Player.h"
#include "global.h"

Player::Player():m_PlayerID(0)
{

}

Player::Player( int id ):m_PlayerID(id)
{
}

Player::~Player()
{

}

void Player::SetCtrlKey(int index,CtrlKey::v key )
{
	switch(key)
	{
	case CtrlKey::UP :
			m_KeyCode[0]=index;
			break;
	case CtrlKey::DOWN :
			m_KeyCode[1]=index;
			break;
	case CtrlKey::RIGHT :
			m_KeyCode[2]=index;
			break;
	case CtrlKey::LEFT :
			m_KeyCode[3]=index;
			break;
	case CtrlKey::DEF :
			m_KeyCode[4]=index;
			break;
	case CtrlKey::JUMP :
			m_KeyCode[5]=index;
			break;
	case CtrlKey::ATK1 :
			m_KeyCode[6]=index;
			break;
	case CtrlKey::ATK2 :
			m_KeyCode[7]=index;
			break;
	}
}

void Player::SetCtrlKey(int index[8])
{
	for(int k=0; k<8; k++)
	{
		m_KeyCode[k] = index[k];
	}
}

void Player::UpdateInput()
{
	/*
	std::string test[8] ={
		"up","down","right","left","def","jump","atk1","atk2"
	};
	//*/

	if (m_Hero != NULL)
	{
		InputStateS::instance().GetInput();

		for (int k=0 ; k < 8 ;k++)
		{
			KeyInfo keyInfo = {};
			if (InputStateS::instance().isKeyDown(m_KeyCode[k]))
			{
				keyInfo.key = (CtrlKey::v)k;
				keyInfo.time= g_Time;
				//std::cout<<"Ctrl Key:"<< test[k] <<std::endl;
				m_Hero->PushKey(keyInfo);
			}

			if (InputStateS::instance().isKeyUp(m_KeyCode[k]))
			{
				keyInfo.key = (CtrlKey::v)(k+KEYUP);
				keyInfo.time= g_Time;
				m_Hero->PushKey(keyInfo);
			}
		}
	}
		
	
	

}

void Player::SetHero(const std::string& name )
{
	m_HeroName = name;
}

void Player::SetTeam( int team )
{
	m_Team = team;
	m_UserName.SetForeColor(TEAMCOLOR[m_Team][0],TEAMCOLOR[m_Team][1],TEAMCOLOR[m_Team][2]);
}

std::string Player::HeroName()
{
	return m_HeroName;
}

void Player::SetUserName( const std::wstring& name )
{
	m_UserName = name;
	m_UserName.SetComposition(Composition::CENTER);
	m_UserName.SetForeColor(TEAMCOLOR[m_Team][0],TEAMCOLOR[m_Team][1],TEAMCOLOR[m_Team][2]);
	m_UserName.SetBackColor(0.0f, 0.0, 0.0f, 0.0f);
}

void Player::Update()
{
	Vector3 v=m_Hero->Position();
	v.y=0.0f;
	m_UserName.SetPosition(v);
}




