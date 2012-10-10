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

	for ( CtrlKeyMap::iterator it_map = m_CtrlKeyMap.begin() ; it_map != m_CtrlKeyMap.end() ; it_map++ )
	{
		if ( !g_Replay.replayMode )
		{
			//while ( g_Replay.rkqIt->first < g_Time ) { g_Replay.rkqIt++; }

			if ( g_Replay.rkqIt->first == g_Time && ( g_Replay.rkqIt->second & 0x00FF ) == it_map->first )
			{
				KeyInfo info = {};
				info.key = ( g_Replay.rkqIt->second & 0xF000 ) ? it_map->second.keyDown: it_map->second.keyUp;
				info.time = g_Time;
				keyQue.push_back( info );
				g_Replay.rkqIt++;
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
				if( g_Replay.replayMode ) { g_Replay.PushKeyInfo( it_map->first, g_Time, 'd' ); }
			}
			if ( InputStateS::instance().isKeyUp( it_map->first ) )
			{
				KeyInfo info = {};
				info.key = it_map->second.keyUp;
				info.time = g_Time;
				keyQue.push_back( info );
				if( g_Replay.replayMode ) { g_Replay.PushKeyInfo( it_map->first, g_Time, 'u' ); }
			}
		}
	}

	return keyQue;
}

void Keyboard::SetCtrlKey( int index, const KeyMap::_KeyMap& key )
{
	m_CtrlKeyMap[index] = key;
}
