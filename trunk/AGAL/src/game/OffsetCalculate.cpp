#include "game/OffsetCalculate.h"

OffsetCalculate::OffsetCalculate(void):m_Offset(Vector3::ZERO),m_Enable(true)
{
	this->m_OffsetControls.clear();
}


OffsetCalculate::~OffsetCalculate(void)
{
}

void OffsetCalculate::Update( float deltaTime )
{
	m_Offset*=0.0f;
	if(!m_Enable || m_OffsetControls.empty()) return;

	for(OffsetControls::iterator it = m_OffsetControls.begin();it != m_OffsetControls.end();)
	{
		if(it->AutoDestory && it->StartTime > it->LifeTime)
			it = m_OffsetControls.erase(it);
		else{
			Calculate(*it, deltaTime);
			it->StartTime+=deltaTime;
			if(it->StartTime>it->LifeTime){
				if (it->Loop)
				{
					it->Init();
				}else{
					it->Enable = false;
				}
			}
			it++;
		}
			
	}
}

int OffsetCalculate::Add( int Group, Vector3 Direction, float Frequency, double Intensity, float LifeTime, bool EnableDiminuendo /*= false*/, bool EnableCrescendo /*= false*/, bool Loop /*= true*/, bool EnableSmooth /*= true*/, bool AutoDestory /*= true */ )
{
	OffsetControl OC;
	OC.Group = Group;

	OC.Direction = Direction.normalisedCopy();
	OC.Frequency = Frequency;
	OC.LifeTime = LifeTime;

	float midTime = LifeTime*0.5;
	if (EnableDiminuendo)//º¥±j
	{
		OC.Intensity.AddPoint(0,Vector3(0,0,0));
	}else{
		OC.Intensity.AddPoint(0,Vector3(Intensity,0,0));
	}
	OC.Intensity.AddPoint(midTime,Vector3(Intensity,0,0));
	if (EnableDiminuendo)//º¥®z
	{
		OC.Intensity.AddPoint(LifeTime,Vector3(0,0,0));
	}else{
		OC.Intensity.AddPoint(LifeTime,Vector3(Intensity,0,0));
	}

	OC.Loop = Loop;
	OC.EnableSmooth = EnableSmooth;
	OC.AutoDestory = AutoDestory;
	m_OffsetControls.push_back(OC);
	return m_OffsetControls.size();
}

void OffsetCalculate::Remove( int ID )
{
	for(OffsetControls::iterator it = m_OffsetControls.begin();
		it != m_OffsetControls.end();)
	{
		if(it->Group == ID)
			it = m_OffsetControls.erase(it);
		else
			++it;
	}
}

void OffsetCalculate::Pause( int ID )
{
	for(OffsetControls::iterator it = m_OffsetControls.begin();
		it != m_OffsetControls.end(); ++it)
	{
		if(it->Group == ID)
			it->Enable = false;
	}
}

void OffsetCalculate::Resume( int ID )
{
	for(OffsetControls::iterator it = m_OffsetControls.begin();
		it != m_OffsetControls.end(); ++it)
	{
		if(it->Group == ID)
			it->Enable = true;
	}
}

void OffsetCalculate::Stop( int ID )
{
	for(OffsetControls::iterator it = m_OffsetControls.begin();
		it != m_OffsetControls.end(); ++it)
	{
		if(it->Group == ID)
		{
			it->Enable = false;
			it->StartTime = 0.0f;
		}

	}
}