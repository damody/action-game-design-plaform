#pragma once
#include <game/Shake.h>
class Earthqauck :public Shake
{
public:
	Earthqauck(void);
	~Earthqauck(void);
public:
	void Update(float dt);
	void Create(float Intensity, float Frequency, float LifeTime);
};

