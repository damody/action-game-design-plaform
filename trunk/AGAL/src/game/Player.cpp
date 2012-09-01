#include "StdAGAL.h"
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

void Player::UpdateInput()
{
	KeyQueue keyQue = m_Keyboard.Update();
	for (KeyQueue::iterator it=keyQue.begin(); it != keyQue.end(); it++)
	{
		m_Hero->PushKey((*it));
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
	m_UserName.SetOnGround(true);
	m_UserName.SetForeColor(TEAMCOLOR[m_Team][0],TEAMCOLOR[m_Team][1],TEAMCOLOR[m_Team][2]);
}

void Player::Update()
{
	Vector3 v=m_Hero->Position();
	v.y=1.0f;
	m_UserName.SetPosition(v);
}




