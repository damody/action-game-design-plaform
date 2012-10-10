#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "game/CtrlKey.h"
//#include "global.h"

namespace boost {namespace serialization {class access;}}

class Replay
{
private:
	int nextKeyTime;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar&		repalyKeyQueue;
	}
public:
	Replay();
	~Replay() {}
	//state: down 1, up 0
	void PushKeyInfo( int key, int _g_time, int state);
	void PushKeyInfo( int key, int _g_time, char state);

	int	replayMode; //record 1, play 0
	std::map< int, int > repalyKeyQueue;
	std::map< int, int >::iterator rkqIt;
	//bool WriteToFile( std::wstring path );
};