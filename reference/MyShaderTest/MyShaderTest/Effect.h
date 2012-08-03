#ifndef _EFFECT_H
#define _EFFECT_H


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "RenderTextureClass.h"
#include "TFireShaderClass.h"

struct EffectType
{
	enum e{Fire,Ice};
};

class Effect
{
public:
	Effect();
	bool Initialize(ID3D11Device* device,HWND hwnd);

	void GetEffect(EffectType);

private:
	RenderTextureClass* m_RenderTexture;
	

	TFireShaderClass* m_FireShader;

};

#endif