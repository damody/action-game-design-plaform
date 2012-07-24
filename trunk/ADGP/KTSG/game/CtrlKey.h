#pragma once
#include <deque>

#define KEYUP 7

enum CtrlKey{
	UP,DOWN,RIGHT,LEFT,DEF,JUMP,ATK1,ATK2,
	UP_KEYUP,DOWN_KEYUP,RIGHT_KEYUP,LEFT_KEYUP,DEF_KEYUP,JUMP_KEYUP,ATK1_KEYUP,ATK2_KEYUP //Key Up
	}typedef CtrlKey;

struct KeyInfo{
	CtrlKey key;
	int time;
}typedef KeyInfo;

typedef std::deque<KeyInfo> KeyQue; 