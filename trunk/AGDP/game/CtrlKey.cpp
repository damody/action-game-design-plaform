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
		/*if ( InputStateS::instance().isKeyDown( it_map->first ) && it_map->second.keyDown == )
		{
			
			continue;
		}*/
		if ( InputStateS::instance().isKeyDown( it_map->first ) )
		{
			KeyInfo info = {};
			info.key = it_map->second.keyDown;
			info.time = g_Time;
			keyQue.push_back( info );
			//g_Replay.PushKeyInfo( info );
		}
		if ( InputStateS::instance().isKeyUp( it_map->first ) )
		{
			KeyInfo info = {};
			info.key = it_map->second.keyUp;
			info.time = g_Time;
			keyQue.push_back( info );
			//g_Replay.PushKeyInfo( info );
		}
	}

	return keyQue;
}

void Keyboard::SetCtrlKey( int index, const KeyMap::_KeyMap& key )
{
	m_CtrlKeyMap[index] = key;
}
