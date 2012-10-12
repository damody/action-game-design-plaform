#include "StdGame.h"
#include "game/CtrlKey.h"
#include "DX11/InputState.h"
#include "global.h"

KeyQueue Keyboard::Update()
{
	KeyQueue keyQue;

	//InputState::GetInput();
	if ( InputStateS::instance().isKeyDown( KEY_UP ) )
	{
		std::cout << "test \n";
	}
	if ( InputStateS::instance().isKeyDown( KEY_O ) )
	{
		g_Replay.ResetRkqIt();
		g_Replay.StartPlay();
		if ( g_Replay.IsPlay() ) { std::cout << "test: play start\n"; }
		else { std::cout << "test: play error\n"; }
	}
	else if ( InputStateS::instance().isKeyDown( KEY_P ) )
	{
		g_Replay.StopPlay();
		std::cout << "test: play stop\n";
	}
	else if ( InputStateS::instance().isKeyDown( KEY_LBRACKET ) )
	{
		g_Replay = Replay();
		g_Replay.StartRecord();
		if ( g_Replay.IsRecord() ) { std::cout << "test: record start\n"; }
		else { std::cout << "test: record error\n"; }
	}
	else if ( InputStateS::instance().isKeyDown( KEY_RBRACKET ) )
	{
		g_Replay.StopRecord();
		std::cout << "test: record stop\n";
	}

	for ( CtrlKeyMap::iterator it_map = m_CtrlKeyMap.begin() ; it_map != m_CtrlKeyMap.end() ; it_map++ )
	{
		if ( g_Replay.IsPlay() )
		{
			//while ( g_Replay.rkqIt->first < g_Time ) { g_Replay.rkqIt++; }

			if ( g_Replay.GetRkqItTime() + g_Replay.GetStartTime() == g_Time && g_Replay.GetRkqItKeyIndex() == it_map->first )
			{
				KeyInfo info = {};
				info.key = g_Replay.GetRkqItKeyState() ? it_map->second.keyDown: it_map->second.keyUp;
				info.time = g_Time;
				keyQue.push_back( info );
				g_Replay.RkqItAdd();
				if ( g_Replay.IsRkqitEnd() ) { g_Replay.StopPlay(); }
				break;
			}
		}
		else
		{
			if ( InputStateS::instance().isKeyDown( it_map->first ) )
			{
				KeyInfo info = {};
				info.key = it_map->second.keyDown;
				info.time = g_Time;
				keyQue.push_back( info );
				if ( g_Replay.IsRecord() ) { g_Replay.PushKeyInfo( it_map->first, g_Time, 'd' ); }
			}
			if ( InputStateS::instance().isKeyUp( it_map->first ) )
			{
				KeyInfo info = {};
				info.key = it_map->second.keyUp;
				info.time = g_Time;
				keyQue.push_back( info );
				if ( g_Replay.IsRecord() ) { g_Replay.PushKeyInfo( it_map->first, g_Time, 'u' ); }
			}
		}
	}

	return keyQue;
}

void Keyboard::SetCtrlKey( int index, const KeyMap::_KeyMap& key )
{
	m_CtrlKeyMap[index] = key;
}
