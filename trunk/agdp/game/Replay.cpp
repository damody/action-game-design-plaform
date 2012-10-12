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
	RepalyKeyQueue.clear(); 
	
	//RepalyKeyQueue[50] = 0x10C8;
	//RepalyKeyQueue[70] = 0x00C8;
	//RepalyKeyQueue[100] = 0x10CB; 
	//RepalyKeyQueue[102] = 0x00CB; 
	//RepalyKeyQueue[104] = 0x10CB; 
	//RepalyKeyQueue[106] = 0x00CB; 
	//RepalyKeyQueue[ReplayArg::RKQIT_LAST] = 0xFFFF;

	RecordState = 0;
	PlayState = 0;
	StartTime = 0;
	RkqIt = RepalyKeyQueue.begin();
}

Replay::~Replay()
{
	//RepalyKeyQueue[ReplayArg::RKQIT_LAST] = 0xFFFF;
}

void Replay::PushKeyInfo( int key, int _g_time, int state )
{
	RepalyKeyQueue[ _g_time - StartTime ] = state? 0x1000 | key: key;
}

void Replay::PushKeyInfo( int key, int _g_time, char state )
{
	RepalyKeyQueue[ _g_time - StartTime ] = state=='d'? 0x1000 | key: key;
}

void Replay::ResetRkqIt()
{
	RkqIt = RepalyKeyQueue.begin();
}

void Replay::RkqItAdd()
{
	RkqIt++;
}

int Replay::GetRkqItTime()
{
	return RkqIt->first;
}

int Replay::GetRkqItKeyIndex()
{
	return ( RkqIt->second & 0x00FF );
}

int Replay::GetRkqItKeyState()
{
	return ( RkqIt->second & 0xF000 );
}

bool Replay::IsRkqitEnd()
{
	return ( RkqIt == RepalyKeyQueue.end() );
}

void Replay::StartRecord()
{
	StartTime = g_Time;
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
	StartTime = g_Time;
	if ( !RecordState ) { PlayState = 1; }
}

void Replay::StopPlay()
{
	PlayState = 0;
}

bool Replay::IsPlay()
{
	return ( PlayState? TRUE: FALSE );
}

int Replay::GetStartTime()
{
	return StartTime;
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
