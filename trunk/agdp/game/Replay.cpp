#include "game/Replay.h"
#include "ConvStr.h"
#include <fstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

#define INT_MAX       2147483647

Replay::Replay( int arge )
{
	RepalyKeyQueue.clear(); 
	if ( arge == ReplayArg::REPLAY_TEST )
	{ 
		replayMode = ReplayArg::REPLAY_PLAY;
		RepalyKeyQueue[50] = 0x10C8;
		RepalyKeyQueue[70] = 0x00C8;
		RepalyKeyQueue[100] = 0x10CB; 
		RepalyKeyQueue[102] = 0x00CB; 
		RepalyKeyQueue[104] = 0x10CB; 
		RepalyKeyQueue[106] = 0x00CB; 
		RepalyKeyQueue[ReplayArg::RKQIT_LAST] = 0xFFFF;
	}
	else
	{
		replayMode = arge;
	}
	RkqIt = RepalyKeyQueue.begin();
}

Replay::~Replay()
{
	RepalyKeyQueue[ReplayArg::RKQIT_LAST] = 0xFFFF;
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
