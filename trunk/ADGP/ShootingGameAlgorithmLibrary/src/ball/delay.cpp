#include "delay.h"

int Delay::UpdateBall( Ball* b, float elapsedtime )
{
	if(mElapsedTime >= mLaunchTime)
		b->mPosition += b->mDirection * mVelocity * elapsedtime;
	else
		mElapsedTime += elapsedtime;
	return Ball::FLY;
}
