#pragma once

#include "Earthqauck.h"
#include "Wave.h"
#include "Wind.h"

class Disaster
{
public:
	enum e{
		EARTHQAUCK,
		WAVE,
		WIND,
		RAIN,
		SNOW,
		FROG
	};
private:
	Earthqauck m_Earthqauck;
	Wave	   m_Wave;
	Wind	   m_Wind;
public:
	Disaster(void);
	~Disaster(void);

	void Update();

	void MakeEarthqauck(float Intensity, float Frequency, float LifeTime);
	void MakeWave(float Intensity, float Frequency, float LifeTime);
	void MakeWind(Vector3 Direction, float Intensity, float LifeTime);
};

