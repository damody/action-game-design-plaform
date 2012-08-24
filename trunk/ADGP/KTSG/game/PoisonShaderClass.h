#pragma once

#include "DX11/TextureManager.h"
#include "EffectShaderClass.h"

class PoisonShaderClass : public EffectShaderClass
{
public:
	PoisonShaderClass();
	void Render();
	void Update(float dt);
	void SetShaderParameters();
private:
	void GetVariableByName();
	void CreateTexture();
};