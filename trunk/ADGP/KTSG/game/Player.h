#pragma once

#include <iostream>


#include "CtrlKey.h"
#include "DX11\InputState.h"
#include "common\shared_ptr.h"
#include "game\Hero.h"
#include "global.h"

namespace boost{namespace serialization{class access;}}
class Player
{
private:
	
	int		m_KeyCode[8];
	std::string	m_HeroName;
	int		m_Team;
	Record_Sptr     m_Record;//Set Hero Record 


	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar &	m_KeyCode[8];
		ar &	m_HeroName;
		ar &	m_Team;
		ar &    m_Record;
	}
public:
	Player();
	Player(int id);
	~Player();
	Hero_RawPtr     m_Hero;
	const int	m_PlayerID;
	std::string     m_UserName;

	void SetHero(std::string name);
	void SetTeam(int team);
	Hero_RawPtr CreateHero(Vector3 pos);
	void SetCtrlKey(int index,CtrlKey::v key);
	void SetCtrlKey(int index[8]);
	void UpdateInput();

};