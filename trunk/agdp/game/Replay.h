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
	std::map< int, int > RepalyKeyQueue;
	std::map< int, int >::iterator RkqIt;
	int	replayMode; //record 1, play 0
	int nextKeyTime;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar&		repalyKeyQueue;
	}
public:
	Replay( int arge );
	~Replay();

	//state: down 1, up 0
	inline void		PushKeyInfo( int key, int _g_time, int state) { RepalyKeyQueue[ _g_time ] = state? 0x1000 | key: key; }
	inline void		PushKeyInfo( int key, int _g_time, char state) { RepalyKeyQueue[ _g_time ] = state=='d'? 0x1000 | key: key; }
	inline void		ResetRkqIt() { RkqIt = RepalyKeyQueue.begin(); }
	inline void		RkqItAdd() { RkqIt++; }
	inline int		GetRkqItTime() { return RkqIt->first; }
	inline int		GetRkqItKeyIndex() { return ( RkqIt->second & 0x00FF ); }
	//down 1, up 0
	inline int		GetRkqItKeyState() { return ( RkqIt->second & 0xF000 ); }
	//record 1, play 0
	inline int		GetReplayMode() { return replayMode; }
	inline bool		IsRkqitEnd() { return ( RkqIt->first == ReplayArg::RKQIT_LAST ); }

	enum ReplayArg
	{
		REPLAY_TEST = -1,
		REPLAY_PLAY = 0,
		REPLAY_RECORD = 1,

		RKQIT_LAST = 2147483647
	};

	//bool WriteToFile( std::wstring path );
};