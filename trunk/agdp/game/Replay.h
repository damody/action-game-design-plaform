#pragma once
#include <iostream>
#include "game/CtrlKey.h"

namespace boost {namespace serialization {class access;}}

class Replay
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar&		repalyKeyQueue;
	}
public:
	Replay();
	~Replay();
	std::vector< KeyInfo > repalyKeyQueue;
};