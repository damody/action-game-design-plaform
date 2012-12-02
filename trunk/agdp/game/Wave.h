#pragma once
#include <game/Shake.h>
class Wave : public Shake
{
public:
	Wave(void);
	~Wave(void);
	int Add(int Group, Vector3 Direction, float Frequency, double Intensity, float LifeTime, bool EnableDiminuendo = false, bool EnableCrescendo = false, bool Loop = true, bool EnableSmooth = true, bool AutoDestory = true );
public:
	void Update(float dt);
	void Create(float Intensity, float Frequency, float LifeTime);
};	

