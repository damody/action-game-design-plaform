#include "Wave.h"
#include "global.h"

Wave::Wave(void)
{
}


Wave::~Wave(void)
{
}

int Wave::Add( int Group, Vector3 Direction, float Frequency, double Intensity, float LifeTime, bool EnableDiminuendo /*= false*/, bool EnableCrescendo /*= false*/, bool Loop /*= true*/, bool EnableSmooth /*= true*/, bool AutoDestory /*= true */ )
{
	OffsetControl OC;
	OC.Group = Group;

	OC.Direction = Direction.normalisedCopy();
	OC.Frequency = Frequency;
	OC.LifeTime = LifeTime;

	
	float QuarterTime = LifeTime*0.25;

	if (EnableDiminuendo)//º¥±j
	{
		OC.Intensity.AddPoint(0,Vector3(0,0,0));
	}else{
		OC.Intensity.AddPoint(0,Vector3(Intensity,0,0));
	}
	OC.Intensity.AddPoint(QuarterTime,Vector3(Intensity,0,0));
	OC.Intensity.AddPoint(QuarterTime*3,Vector3(Intensity,0,0));
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

void Wave::Update( float dt )
{
	Shake::Update(dt);
	if (g_Camera != NULL)
	{
		g_Camera->MoveY(GetOffset().y);
	}
}

void Wave::Create( float Intensity, float Frequency, float LifeTime )
{
	Add(0,Vector3(0,1,0),Frequency,Intensity,LifeTime,true,true,false,true);
}
