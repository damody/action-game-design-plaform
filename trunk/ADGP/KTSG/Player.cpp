#include "Player.h"


Player::Player():m_PlayerID(0),m_UserName("Player")
{

}

Player::Player( int id ):m_PlayerID(id),m_UserName("Player")
{
	m_UserName+=id;
}

Player::~Player()
{

}

void Player::SetCtrlKey(int index,KeyInfo::CtrlKey key )
{
	switch(key)
	{
	case KeyInfo::CtrlKey::UP :
			m_KeyCode[0]=index;
			break;
	case KeyInfo::CtrlKey::DOWN :
			m_KeyCode[1]=index;
			break;
	case KeyInfo::CtrlKey::RIGHT :
			m_KeyCode[2]=index;
			break;
	case KeyInfo::CtrlKey::LEFT :
			m_KeyCode[3]=index;
			break;
	case KeyInfo::CtrlKey::DEF :
			m_KeyCode[4]=index;
			break;
	case KeyInfo::CtrlKey::JUMP :
			m_KeyCode[5]=index;
			break;
	case KeyInfo::CtrlKey::ATK1 :
			m_KeyCode[6]=index;
			break;
	case KeyInfo::CtrlKey::ATK2 :
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
	///*
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
				keyInfo.key = (KeyInfo::CtrlKey)k;
				std::cout<<"Ctrl Key:"<< test[k] <<std::endl;
				m_Hero->PushKey(keyInfo);
			}

			if (InputStateS::instance().isKeyUp(m_KeyCode[k]))
			{
				keyInfo.key = (KeyInfo::CtrlKey)(k+KEYUP);
				m_Hero->PushKey(keyInfo);
			}
		}
	}
		
	
	

}

Hero_RawPtr Player::CreateHero(Vector3 pos)
{
	m_Hero = Hero_RawPtr(new Hero(m_HeroName));
	m_Hero->SetTeam(m_Team);
	m_Hero->SetRecord(m_Record);
	m_Hero->Position(pos);
	return m_Hero;
}

void Player::SetHero( std::string name )
{
	m_HeroName = name;
}

void Player::SetTeam( int team )
{
	m_Team = team;
}
