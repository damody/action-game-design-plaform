#pragma once

#include <game/Slide.h>

class Wind : public Slide
{
public:
	Wind(void);
	~Wind(void);
public:
	void Update(float dt);
	void Create(Vector3 direction, float Intensity, float LifeTime);
};

