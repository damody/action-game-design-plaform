#pragma once
#include <iostream>
#include <boost/random.hpp>
#include "Trajectory.h"

class RandomWay : public Trajectory
{
public:
	boost::mt19937  mRandom; 
	float		mRadiationAngle;
	RandomWay(int _mNumTrajectory=1, Vector3 _mPosition = Vector3::ZERO, Vector3 _mDirection = Vector3::ZERO, float _angle = 90.0f)
		:Trajectory(_mNumTrajectory, _mPosition, _mDirection), mRadiationAngle(_angle)
	{}
	virtual ~RandomWay()
	{}
	virtual void SetRadiationAngle(float angle)
	{
		mRadiationAngle = angle;
		this->Modifyed();
	}
protected:
	virtual void Modifyed();
};
