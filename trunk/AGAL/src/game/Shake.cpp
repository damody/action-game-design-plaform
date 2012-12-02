#include "game\Shake.h"


Shake::Shake(void):OffsetCalculate()
{
}

Shake::~Shake(void)
{
}

void Shake::Calculate( OffsetControl& OC, float deltaTime )
{
	if(!OC.Enable) return;
	Vector3 tOffset;
	float tFloat;
	float Cycle = OC.StartTime*OC.Frequency*2.0f;
	
	if( int(Cycle)%2 )
		tOffset = -OC.Direction*OC.Intensity.GetValue(OC.StartTime).x;
	else
		tOffset = OC.Direction*OC.Intensity.GetValue(OC.StartTime).x;
	
	if(OC.EnableSmooth)
	{
		
		float CycleRate = modff(Cycle, &tFloat)*2.0f-1.0f;
		tOffset *= CycleRate;
	}
	
	m_Offset += tOffset;
}

