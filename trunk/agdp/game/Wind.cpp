#include "Wind.h"
#include "global.h"

Wind::Wind(void)
{
}


Wind::~Wind(void)
{
}

void Wind::Update( float dt )
{
	if(!m_Enable || m_OffsetControls.empty()) return;
	Slide::Update(dt);
	for ( Heroes::iterator it = g_HeroManager.HeroVectorBegin(); it != g_HeroManager.HeroVectorEnd(); ++it)
	{
		(*it)->Translate(GetOffset());
	}
}

void Wind::Create(Vector3 direction, float Intensity, float LifeTime )
{
	Add(0,direction,0,Intensity,LifeTime,true,true,false,true);
}
