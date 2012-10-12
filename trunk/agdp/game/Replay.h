#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "game/CtrlKey.h"
//#include "global.h"
extern int	g_Time;

namespace boost {namespace serialization {class access;}}

class Replay
{
private:
	std::map< int, int > RepalyKeyQueue;
	std::map< int, int >::iterator RkqIt;
	//int	ReplayMode; //record 1, play 0
	int RecordState; //record 1, stop 0
	int PlayState; //play 1, stop 0
	int StartTime;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar&		repalyKeyQueue;
	}
public:
	Replay();
	~Replay();

	//state: down 1, up 0
	void		PushKeyInfo( int key, int _g_time, int state);
	void		PushKeyInfo( int key, int _g_time, char state);
	void		ResetRkqIt();
	void		RkqItAdd();
	int		GetRkqItTime();
	int		GetStartTime();
	int		GetRkqItKeyIndex();
	//down 1, up 0
	int		GetRkqItKeyState();
	//record 1, play 0
	//inline int		GetReplayMode();
	bool		IsRkqitEnd();

	void		StartRecord();
	void		StopRecord();
	bool		IsRecord();
	void		StartPlay();
	void		StopPlay();
	bool		IsPlay();

	//bool WriteToFile( std::wstring path );
};