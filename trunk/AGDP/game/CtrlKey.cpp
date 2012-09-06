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
		if ( it_map->second.size() == 1 )
		{
			if ( InputStateS::instance().isKeyDown( it_map->first ) )
			{
				KeyInfo info;
				info.key = it_map->second.front();
				info.time = g_Time;
				keyQue.push_back( info );
			}

			if ( InputStateS::instance().isKeyUp( it_map->first ) )
			{
				KeyInfo info;
				info.key = ( CtrlKey::v )( ( int )it_map->second.front() + KEYUP );
				info.time = g_Time;
				keyQue.push_back( info );
			}
		}
		else
		{
			if ( InputStateS::instance().isKeyDown( it_map->first ) )
			{
				for ( CtrlKeys::iterator it = it_map->second.begin(); it != it_map->second.end(); it++ )
				{
					KeyInfo info;
					info.key = ( *it );
					info.time = g_Time;
					keyQue.push_back( info );
					info.key = ( CtrlKey::v )( ( int )( *it ) + KEYUP );
					info.time = g_Time;
					keyQue.push_back( info );
				}
			}
		}
	}

	return keyQue;
}

void Keyboard::SetCtrlKey( int index, CtrlKeys keys )
{
	m_CtrlKeyMap[index] = keys;
}
