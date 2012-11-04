#include "game\Shake.h"


Shake::Shake(void)
{
	this->m_Offset = Vector3::ZERO;
	this->m_ShakeControls.clear();
	this->m_EnableShake = true;
}

Shake::~Shake(void)
{
}

void Shake::Update( float deltaTime )
{
	m_Offset*=0.0f;
	if(!m_EnableShake || m_ShakeControls.empty()) return;

	for(ShakeControls::iterator it = m_ShakeControls.begin();
		it != m_ShakeControls.end();)
	{
		if(it->AutoDestory != 0.0f && it->StartTime > it->AutoDestory)
			it = m_ShakeControls.erase(it);
		else 
			MakeShake(*(it++), deltaTime);
	}
}

int Shake::Add( int ID, Vector3 Direction, float Frequency, bool Loop /*= true*/, bool EnableDiminuendo /*= false*/, bool EnableCrescendo /*= false*/, float LifeCycle /*= 0.0f*/, bool EnableSmooth /*= true*/, float AutoDestory /*= 0.0 */ )
{
	ShakeControl SC;
	SC.Group = ID;
	SC.StartTime = 0.0f;
	SC.Enable = true;
	SC.Loop = Loop;
	SC.Direction = Direction;
	SC.Frequency = Frequency;
	SC.LifeCycle = LifeCycle;
	SC.EnableSmooth = EnableSmooth;
	SC.EnableDiminuendo = EnableDiminuendo;
	SC.EnableCrescendo = EnableCrescendo;
	SC.AutoDestory = AutoDestory;
	m_ShakeControls.push_back(SC);
	return m_ShakeControls.size();
}

void Shake::MakeShake( ShakeControl& SC, float deltaTime )
{
	if(!SC.Enable) return;
	Vector3 tOffset;
	float tFloat;
	float Cycle = SC.StartTime*SC.Frequency*2.0f;
	
	if( int(Cycle)%2 )
		tOffset = -SC.Direction;
	else
		tOffset = SC.Direction;

	if(SC.LifeCycle!=0.0f)
	{
		float LifeRate = modff(SC.StartTime/SC.LifeCycle, &tFloat);
		if(SC.EnableDiminuendo)
			tOffset *= 1.0f - LifeRate;
		if(SC.EnableCrescendo)
			tOffset *= LifeRate;
	}
	
	if(SC.EnableSmooth)
	{
		
		float CycleRate = modff(Cycle, &tFloat)*2.0f-1.0f;
		tOffset *= CycleRate;
	}
	
	m_Offset += tOffset;
	SC.StartTime+=deltaTime;
	if(!SC.Loop && SC.StartTime>SC.LifeCycle) SC.Enable = false;
}

void Shake::Remove( int ID )
{
	for(ShakeControls::iterator it = m_ShakeControls.begin();
		it != m_ShakeControls.end();)
	{
		if(it->Group == ID)
			it = m_ShakeControls.erase(it);
		else
			++it;
	}
}

void Shake::Pause( int ID )
{
	for(ShakeControls::iterator it = m_ShakeControls.begin();
		it != m_ShakeControls.end(); ++it)
	{
		if(it->Group == ID)
			it->Enable = false;
	}
}

void Shake::Resume( int ID )
{
	for(ShakeControls::iterator it = m_ShakeControls.begin();
		it != m_ShakeControls.end(); ++it)
	{
		if(it->Group == ID)
			it->Enable = true;
	}
}

void Shake::Stop( int ID )
{
	for(ShakeControls::iterator it = m_ShakeControls.begin();
		it != m_ShakeControls.end(); ++it)
	{
		if(it->Group == ID)
		{
			it->Enable = false;
			it->StartTime = 0.0f;
		}
			
	}
}
