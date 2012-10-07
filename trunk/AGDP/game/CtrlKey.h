#pragma once
#include <deque>
#include <vector>
#include<map>
#include "game/LuaMap.h"

namespace boost {namespace serialization {class access;}}

typedef std::vector<char> CtrlKeys;
typedef std::map<int, KeyMap::_KeyMap>	CtrlKeyMap;

struct KeyInfo
{
	char key;
	int time;
	int timeUp;

	//KeyInfo():key(0),time(0),timeUp(0) {}

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& key;
		ar& time;
		ar& timeUp;
	}
};
typedef std::deque<KeyInfo> KeyQueue;

class Keyboard
{
private:
	CtrlKeyMap m_CtrlKeyMap;
public:
	Keyboard()
	{
	};
	~Keyboard() {};

	KeyQueue Update();
	void SetCtrlKey( int index, const KeyMap::_KeyMap& key );
};


