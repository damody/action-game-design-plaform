#include "homing.h"

int Homing::UpdateBall( Ball* b, float elapsedtime )
{
	try
	{
		Vector3 enemyPos = GetEnemyPos(); // try this line
		Vector3 direction = enemyPos - b->mPosition;
		direction.normalise();
		//if(direction.angleBetween(b->mDirection).valueDegrees() < 45)
		b->mDirection = direction;
	}
	catch (std::exception* e)
	{
		// no enemyPos
	}
	b->mPosition += b->mDirection * mVelocity * elapsedtime;
	b->mPolygon2D.Offset(b->mDirection * mVelocity * elapsedtime);
	return Ball::FLY;
}
