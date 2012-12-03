#include "game/Slide.h"


Slide::Slide(void)
{
}


Slide::~Slide(void)
{
}

void Slide::Calculate( OffsetControl& OC, float deltaTime )
{
	if(!OC.Enable) return;
	Vector3 tOffset;
	float tFloat;
	
	tOffset = OC.Direction*OC.Intensity.GetValue(OC.StartTime).x;

	m_Offset += tOffset;
}
