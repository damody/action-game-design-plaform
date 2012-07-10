#pragma once
#include "StraightWay.h"
#include "ball/split.h"

void StraightWay::Modifyed()
{
	mBall_PreComptue.clear();
	mBall_PreComptue.reserve(mNumTrajectory);
	float step_angle = 0;
	float start = -mRadiationAngle*0.5f;
	if (mNumTrajectory > 1)
		step_angle = mRadiationAngle/(mNumTrajectory-1);
	else
		start = 0;
	for (int i = 0;i < mNumTrajectory;i++, start += step_angle)
	{
		Ball ball(mPosition, mDirection, mBehavior);

		mAngle = start / mRadiationAngle*200;
		mVelocity = 500;
		mMaxAngle = mRadiationAngle*0.5f;
		mOAngle = 0;

		mBall_PreComptue.push_back(ball);
	}
	mNeedUpdate = false;
}
