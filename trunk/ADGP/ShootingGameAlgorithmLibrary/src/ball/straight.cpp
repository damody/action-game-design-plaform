#include "straight.h"

int Straight::UpdateBall( Ball* b, float elapsedtime )
{
	Vector3 tmp(b->mDirection * mVelocity * elapsedtime);
	b->mPosition += tmp;
	b->mPolygon2D.Offset(tmp);
	return Ball::FLY;
}

