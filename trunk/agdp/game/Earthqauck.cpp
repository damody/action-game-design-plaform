#include "Earthqauck.h"
#include "global.h"

Earthqauck::Earthqauck(void)
{
}


Earthqauck::~Earthqauck(void)
{
}

void Earthqauck::Create(float Intensity, float Frequency, float LifeTime )
{
	Add(0,Vector3(1,0,0),Frequency,Intensity,LifeTime,true,true,false,true);
}

void Earthqauck::Update( float dt )
{
	Shake::Update(dt);
	if (g_Camera != NULL)
	{
		g_Camera->MoveX(GetOffset().x);
	}
}
