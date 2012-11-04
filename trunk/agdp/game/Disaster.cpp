#include "Disaster.h"
#include "global.h"

Disaster::Disaster(void)
{
}


Disaster::~Disaster(void)
{
}

void Disaster::Earthqauck( Vector3 Direction, float Frequency, float LifeCycle)
{
	m_Earthqauck.Add(0,Direction,Frequency,false,true,true,LifeCycle,true);
}

void Disaster::Update()
{
	m_Earthqauck.Update(1/60.0f);
	g_Camera->MoveX(m_Earthqauck.GetOffset().x);
	g_Camera->MoveY(m_Earthqauck.GetOffset().y);
}
