#include "StdGame.h"
#include "Timer.h"
#include <windows.h>
#include <stdio.h>

GameTimer::GameTimer()
	: m_SecondsPerCount( 0.0 ), m_DeltaTime( -1.0 ), m_BaseTime( 0 ),
	  m_PausedTime( 0 ), m_PrevTime( 0 ), m_CurrTime( 0 ), m_Stopped( false )
{
	__int64 countsPerSec;
	QueryPerformanceFrequency( ( LARGE_INTEGER* )&countsPerSec );
	m_SecondsPerCount = 1.0 / ( double )countsPerSec;
}

// Returns the total time elapsed since reset() was called, NOT counting any
// time when the clock is stopped.
float GameTimer::getGameTime()const
{
	// If we are stopped, do not count the time that has passed since we stopped.
	//
	// ----*---------------*------------------------------*------> time
	//  mBaseTime       mStopTime                      mCurrTime
	if ( m_Stopped )
	{
		return ( float )( ( m_StopTime - m_BaseTime ) * m_SecondsPerCount );
	}
	// The distance mCurrTime - mBaseTime includes paused time,
	// which we do not want to count.  To correct this, we can subtract
	// the paused time from mCurrTime:
	//
	//  (mCurrTime - mPausedTime) - mBaseTime
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mCurrTime
	else
	{
		return ( float )( ( ( m_CurrTime - m_PausedTime ) - m_BaseTime ) * m_SecondsPerCount );
	}
}

float GameTimer::getDeltaTime()const
{
	return ( float )m_DeltaTime;
}

void GameTimer::reset()
{
	__int64 currTime;
	QueryPerformanceCounter( ( LARGE_INTEGER* )&currTime );
	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = 0;
	m_Stopped  = false;
}

void GameTimer::start()
{
	__int64 startTime;
	QueryPerformanceCounter( ( LARGE_INTEGER* )&startTime );

	// Accumulate the time elapsed between stop and start pairs.
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  mBaseTime       mStopTime        startTime

	if ( m_Stopped )
	{
		m_PausedTime += ( startTime - m_StopTime );
		m_PrevTime = startTime;
		m_StopTime = 0;
		m_Stopped  = false;
	}
}

void GameTimer::stop()
{
	if ( !m_Stopped )
	{
		__int64 currTime;
		QueryPerformanceCounter( ( LARGE_INTEGER* )&currTime );
		m_StopTime = currTime;
		m_Stopped  = true;
	}
}

void GameTimer::tick()
{
	if ( m_Stopped )
	{
		m_DeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter( ( LARGE_INTEGER* )&currTime );
	m_CurrTime = currTime;
	// Time difference between this frame and the previous.
	m_DeltaTime = ( m_CurrTime - m_PrevTime ) * m_SecondsPerCount;
	//printf("dtime: %f\n", mDeltaTime);
	// Prepare for next frame.
	m_PrevTime = m_CurrTime;

	// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the
	// processor goes into a power save mode or we get shuffled to another
	// processor, then mDeltaTime can be negative.
	if ( m_DeltaTime < 0.0 )
	{
		m_DeltaTime = 0.0;
	}
}