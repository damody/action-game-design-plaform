#pragma once
#include <iostream>
#include <vector>
#include "game/CtrlKey.h"
//#include "global.h"

namespace boost {namespace serialization {class access;}}

class Replay
{
private:
	std::vector< KeyInfo > repalyKeyQueue;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar&		repalyKeyQueue;
	}
public:
	Replay() { repalyKeyQueue.clear(); }
	~Replay() {}
	void PushKeyInfo( KeyInfo ki );
	bool WriteToFile( std::wstring path );
};