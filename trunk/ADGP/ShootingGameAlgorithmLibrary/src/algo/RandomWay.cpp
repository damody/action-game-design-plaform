#pragma once
#include "algo/RandomWay.h"
#include "math/Quaternion.h"
#include "ball/straight.h"

void RandomWay::Modifyed()
{
	mBall_PreComptue.clear();
	mBall_PreComptue.reserve(mNumTrajectory);
	boost::uniform_real<float> rng(-mRadiationAngle*0.5f, mRadiationAngle*0.5f);
	for (int i = 0;i < mNumTrajectory;i++)
	{
		Ball ball(mPosition, Quaternion::GetRotation(mDirection, rng(mRandom)), mBehavior);
		ball.Update(mInitializeTime);
		mBall_PreComptue.push_back(ball);
	}
	mNeedUpdate = false;
}
