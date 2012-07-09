#pragma once

#include <iostream>


#include "CtrlKey.h"
#include "DX11\InputState.h"
#include "common\shared_ptr.h"
#include "game\Hero.h"


class Player
{
private:
	Hero_RawPtr     m_Hero;
	unsigned char	m_KeyCode[8];
	std::string	m_HeroName;
	int		m_Team;
	Record_Sptr     m_Record;//Set Hero Record 
public:
	Player();
	Player(int id);
	~Player();

	const int	m_PlayerID;
	std::string     m_UserName;

	void SetHero(std::string name);
	void SetTeam(int team);
	void CreatHero();
	void SetCtrlKey(unsigned char index,KeyInfo::CtrlKey key);
	void SetCtrlKey(unsigned char index[8]);
	void UpdateInput();

};