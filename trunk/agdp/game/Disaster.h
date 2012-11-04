#pragma once

#include <game/Shake.h>

class Disaster
{
private:
	Shake m_Earthqauck;
public:
	Disaster(void);
	~Disaster(void);

	void Update();

	void Earthqauck(Vector3 Direction, float Frequency, float LifeCycle = 0.0f);
};

