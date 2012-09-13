#pragma once
#include "Trajectory.h"
#include <iostream>
#include <algorithm>

class SwirlWay : public Trajectory
{
public:
	float mSecPerCircle;
	int   mCircles;
	float mElapsedTime;
	float mLaunchTime;
	float mVelocity;
	SwirlWay( int _mNumPerCircle = 1, int _mCircles = 1, float _mSecPerCircle = 1, Vector3 _mPosition = Vector3::ZERO )
		: Trajectory( _mNumPerCircle, _mPosition, Vector3( 0, 0, 0 ) ), mSecPerCircle( _mSecPerCircle ), mCircles( _mCircles )
	{}
	virtual ~SwirlWay()
	{}

protected:
	virtual void Modifyed();
};
