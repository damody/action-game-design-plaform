#pragma once


struct KeyInfo{
	enum CtrlKey{
	UP,DOWN,RIGHT,LEFT,DEF,JUMP,ATK1,ATK2,
	UP_KEYUP,DOWN_KEYUP,RIGHT_KEYUP,LEFT_KEYUP,DEF_KEYUP,JUMP_KEYUP,ATK1_KEYUP,ATK2_KEYUP //Key Up
	};

	CtrlKey key;
	int time;
}typedef KeyInfo;

typedef std::deque<KeyInfo> KeyQue; 