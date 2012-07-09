#pragma once
#include "algo/nway.h"
#include "math/Quaternion.h"
#include "ball/straight.h"

void NWay::Modifyed()
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
		Ball ball(mPosition, Quaternion::GetRotation(mDirection, start), mBehavior);
		ball.mPolygon2D = mPolygon;
		ball.mPolygon2D.Rotation(mAngle+start);
		//ball.mPolygon2D.Offset(mPosition); // because plane will add offset
		ball.Update(mInitializeTime);
		mBall_PreComptue.push_back(ball);
	}
	mNeedUpdate = false;
}
