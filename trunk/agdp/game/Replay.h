#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "game/CtrlKey.h"
extern int	g_Time;

namespace boost {namespace serialization {class access;}}

class Replay
{
public:
	struct ReplayKeyInfo{
		int keyTime;
		int keyIndex;
		int keyState;
	};
	typedef std::vector< ReplayKeyInfo > RKIVector;
private:
	RKIVector ReplayKeyQueue;
	RKIVector::iterator RKQIt;
	//int	ReplayMode; //record 1, play 0
	int RecordState; //record 1, stop 0
	int PlayState; //play 1, stop 0
	int StartOffsetTime;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar&		RepalyKeyQueue;
	}
public:
	Replay();
	~Replay();

	//state: down 1, up 0
	void		PushKeyInfo( int key, int _g_time, int state);
	void		PushKeyInfo( int key, int _g_time, char state);
	void		ResetRKQIt();
	void		RKQItAdd();
	int			GetStartOffsetTime();
	int			GetRKQItKeyTime();
	int			GetRKQItKeyIndex();
	//down 1, up 0
	int			GetRKQItKeyState();
	//record 1, play 0
	//inline int		GetReplayMode();
	bool		IsRKQItEnd();

	void		StartRecord();
	void		StopRecord();
	bool		IsRecord();
	void		StartPlay();
	void		StopPlay();
	bool		IsPlay();

	//bool WriteToFile( std::wstring path );
};