#include "gravity.h"

int Gravity::UpdateBall( Ball* b, float elapsedtime )
{
	mForce -= mGravity * elapsedtime;
	b->mPosition += b->mDirection * mVelocity * elapsedtime;
	b->mPosition += mForce;
	return Ball::FLY;
}
