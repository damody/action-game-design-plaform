#include "game/Replay.h"
#include "ConvStr.h"
#include <fstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

#define INT_MAX       2147483647

Replay::Replay()
{
	ReplayKeyQueue.clear(); 
	RecordState = 0;
	PlayState = 0;
	StartOffsetTime = 0;
	RKQIt = ReplayKeyQueue.begin();
}

Replay::~Replay()
{
	//RepalyKeyQueue[ReplayArg::RKQIT_LAST] = 0xFFFF;
}

void Replay::PushKeyInfo( int key, int _g_time, int state )
{
	ReplayKeyInfo _tmpRKI;
	_tmpRKI.keyTime = _g_time - StartOffsetTime;
	_tmpRKI.keyIndex = key;
	_tmpRKI.keyState = state;
	ReplayKeyQueue.push_back( _tmpRKI );
}

void Replay::PushKeyInfo( int key, int _g_time, char state )
{
	ReplayKeyInfo _tmpRKI;
	_tmpRKI.keyTime = _g_time - StartOffsetTime;
	_tmpRKI.keyIndex = key;
	_tmpRKI.keyState = ( state == 'd' )? 1: 0;
	ReplayKeyQueue.push_back( _tmpRKI );
}

void Replay::ResetRKQIt()
{
	RKQIt = ReplayKeyQueue.begin();
}

void Replay::RKQItAdd()
{
	RKQIt++;
}

int Replay::GetRKQItKeyTime()
{
	return RKQIt->keyTime;
}

int Replay::GetRKQItKeyIndex()
{
	return RKQIt->keyIndex;
}

int Replay::GetRKQItKeyState()
{
	return RKQIt->keyState;
}

bool Replay::IsRKQItEnd()
{
	return ( RKQIt == ReplayKeyQueue.end() );
}

void Replay::StartRecord()
{
	StartOffsetTime = g_Time;
	if ( !PlayState ) { RecordState = 1; }
}

void Replay::StopRecord()
{
	RecordState = 0;
}

bool Replay::IsRecord()
{
	return ( RecordState? TRUE: FALSE );
}

void Replay::StartPlay()
{
	StartOffsetTime = g_Time;
	if ( !RecordState && !ReplayKeyQueue.empty() ) { PlayState = 1; }
}

void Replay::StopPlay()
{
	PlayState = 0;
}

bool Replay::IsPlay()
{
	return ( PlayState && !ReplayKeyQueue.empty() ? TRUE: FALSE );
}

int Replay::GetStartOffsetTime()
{
	return StartOffsetTime;
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
