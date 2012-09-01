#pragma once
#include <deque>
#include <vector>
#include<map>

#define KEYUP 8
namespace boost{namespace serialization{class access;}}
struct CtrlKey
{
	enum v{
	UP,DOWN,RIGHT,LEFT,DEF,JUMP,ATK1,ATK2,
	UP_KEYUP,DOWN_KEYUP,RIGHT_KEYUP,LEFT_KEYUP,DEF_KEYUP,JUMP_KEYUP,ATK1_KEYUP,ATK2_KEYUP //Key Up
	};
};
typedef std::vector<CtrlKey::v> CtrlKeys;
typedef std::map<int,CtrlKeys>	CtrlKeyMap;

struct KeyInfo{
	CtrlKey::v key;
	int time;
	int timeUp;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & key;
		ar & time;
		ar & timeUp;
	}
};
typedef std::deque<KeyInfo> KeyQueue;

class Keyboard{
private:
	CtrlKeyMap m_CtrlKeyMap;
public:
	Keyboard(){
	};
	~Keyboard(){};

	KeyQueue Update();
	void SetCtrlKey(int index,CtrlKeys keys);
};


