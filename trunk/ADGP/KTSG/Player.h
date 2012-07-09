#pragma once


#include "DX11\InputState.h"

struct Record
{
	int Kill;    
	int Attack;
	int HPLost;
	int MPUsage;
	int Picking;
	bool Status; //true: win false: lose
};

class Player
{
private:
	unsigned char m_KeyCode[8];
	
};