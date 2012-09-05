#pragma once
#include "Trajectory.h"
#include <iostream>
#include <algorithm>

class NWay : public Trajectory
{
public:
	float	mRadiationAngle;
	NWay( int _mNumTrajectory = 1, Vector3 _mPosition = Vector3::ZERO, Vector3 _mDirection = Vector3::ZERO, float _angle = 90.0f )
		: Trajectory( _mNumTrajectory, _mPosition, _mDirection ), mRadiationAngle( _angle )
	{}
	virtual ~NWay()
	{}
	virtual void SetRadiationAngle( float angle )
	{
		mRadiationAngle = angle;
		this->Modifyed();
	}

protected:
	virtual void Modifyed();
};
