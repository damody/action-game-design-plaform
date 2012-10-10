#include "game/Replay.h"
#include "ConvStr.h"
#include <fstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

void Replay::PushKeyInfo( int key, int _g_time, int state )
{
	repalyKeyQueue[ _g_time ] = state? 0x1000 | key: key;
}

void Replay::PushKeyInfo( int key, int _g_time, char state )
{
	repalyKeyQueue[ _g_time ] = state=='d'? 0x1000 | key: key;
}

Replay::Replay()
{
	repalyKeyQueue.clear(); 
	replayMode = 1; 
	repalyKeyQueue[0] = 0x10CB; 
	repalyKeyQueue[2] = 0x00CB; 
	repalyKeyQueue[4] = 0x10CB; 
	repalyKeyQueue[6] = 0x00CB; 
	rkqIt = repalyKeyQueue.begin();
}

/*bool Replay::WriteToFile( std::wstring path )
{
	std::string _spath = ConvStr::GetStr( path );

	std::ofstream ofs( _spath, std::ios::binary );

	if ( !ofs.is_open() ) { return 0; }
	{
		//boost::archive::text_oarchive oa(ofs);
		boost::archive::binary_oarchive oa( ofs );
		oa << this->repalyKeyQueue;
	}
	ofs.close();
	return 1;
}*/
