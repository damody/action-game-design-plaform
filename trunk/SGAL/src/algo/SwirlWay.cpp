#pragma once
#include "algo/SwirlWay.h"
#include "math/Quaternion.h"
#include "ball/delay.h"

void SwirlWay::Modifyed()
{
	mBall_PreComptue.clear();
	mBall_PreComptue.reserve(mNumTrajectory);
	float step_angle = 0;
	float step_sec = 0;
	float start_angle = 0;
	float start_sec =0;
	if (mNumTrajectory > 1)
	{
		step_angle = 360.0f / mNumTrajectory;
		step_sec = mSecPerCircle / mNumTrajectory;
	}

	for(int j=0; j<mCircles; j++)
	{
		for (int i = 0;i < mNumTrajectory;i++, start_angle += step_angle, start_sec += step_sec)
		{
			Ball ball(mPosition, Quaternion::GetRotation(mDirection, start_angle), mBehavior);

			mVelocity = 50;
			mLaunchTime = start_sec;

			ball.Update(mInitializeTime);
			mBall_PreComptue.push_back(ball);
		}
		start_angle = 0;
	}
	
	mNeedUpdate = false;
}
