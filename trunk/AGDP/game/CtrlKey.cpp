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
		g_Replay.ResetRKQIt();
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
			if ( g_Replay.IsRKQItEnd() ) 
			{ 
				g_Replay.StopPlay(); 
				break;
			}
			else
			{
				while ( g_Replay.GetRKQItKeyTime() + g_Replay.GetStartOffsetTime() < g_Time ) 
				{ 
					g_Replay.RKQItAdd(); 
					if ( g_Replay.IsRKQItEnd() ) 
					{ 
						g_Replay.StopPlay(); 
						break;
					}
				}
				while ( g_Replay.GetRKQItKeyTime() + g_Replay.GetStartOffsetTime() == g_Time && g_Replay.GetRKQItKeyIndex() == it_map->first )
				{
					KeyInfo info = {};
					info.key = g_Replay.GetRKQItKeyState() ? it_map->second.keyDown: it_map->second.keyUp;
					info.time = g_Time;
					keyQue.push_back( info );
					g_Replay.RKQItAdd();
					if ( g_Replay.IsRKQItEnd() ) 
					{ 
						g_Replay.StopPlay(); 
						break;
					}
				}
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
