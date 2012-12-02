#include "Disaster.h"
#include "global.h"

Disaster::Disaster(void)
{
}


Disaster::~Disaster(void)
{
}


void Disaster::Update()
{
	m_Earthqauck.Update(1/60.0f);
	m_Wave.Update(1/60.0f);
	m_Wind.Update(1/60.0f);
}

void Disaster::MakeEarthqauck( float Intensity, float Frequency, float LifeTime )
{
	m_Earthqauck.Create(Intensity,Frequency,LifeTime);
}

void Disaster::MakeWave( float Intensity, float Frequency, float LifeTime )
{
	m_Wave.Create(Intensity,Frequency,LifeTime);
}

void Disaster::MakeWind( Vector3 Direction, float Intensity, float LifeTime )
{
	m_Wind.Create(Direction,Intensity,LifeTime);
}
