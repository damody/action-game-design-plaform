#pragma once
#include <iostream>
#include "CtrlKey.h"
#include "common\shared_ptr.h"
#include "game\Hero.h"
#include "game\TextString.h"

const float TEAMCOLOR[11][3] =
{
	{1.0f, 1.0f, 1.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 1.0f, 0.0f},
	{1.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.5f, 0.5f, 0.5f},
	{0.5f, 1.0f, 1.0f},
	{1.0f, 0.5f, 1.0f},
	{1.0f, 1.0f, 0.5f}
};

namespace boost {namespace serialization {class access;}}
class Player
{
private:
	std::string	m_HeroName;
	int		m_Team;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& 	m_KeyCode[8];
		ar& 	m_HeroName;
		ar& 	m_Team;
		ar&     m_Record;
	}
public:
	Player();
	Player( int id );
	~Player();

	const int	m_PlayerID;
	TextString	m_UserName;
	Hero_RawPtr     m_Hero;
	Keyboard	m_Keyboard;

	std::string HeroName();

	void SetUserName( const std::wstring& name );
	void SetHero( const std::string& name );
	void SetTeam( int team );


	void UpdateInput();
	void Update();
};
