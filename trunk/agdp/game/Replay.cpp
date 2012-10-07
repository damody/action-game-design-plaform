#include "game/Replay.h"
#include "ConvStr.h"
#include <fstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

void Replay::PushKeyInfo( KeyInfo ki )
{
	repalyKeyQueue.push_back( ki );
}

bool Replay::WriteToFile( std::wstring path )
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
}
