#pragma once

#include "DX11/TextureManager.h"
#include "EffectShaderClass.h"

class PoisonShaderClass : public EffectShaderClass
{
public:
	PoisonShaderClass();
	void Render();
	void Update(float dt);
	void SetShaderParameters(D3DXVECTOR3 scrollSpeeds, D3DXVECTOR3 scales, D3DXVECTOR2 distortion1, 
		D3DXVECTOR2 distortion2, D3DXVECTOR2 distortion3, float distortionScale, 
		float distortionBias);
private:
	void SetEffectVariableByName();
	void CreateTexture();
private:
	Texture_Sptr m_poison;
	Texture_Sptr m_noise;
	//Effect variable
	ID3DX11EffectScalarVariable* m_frameTime;
	ID3DX11EffectVariable* m_scrollSpeeds;
	ID3DX11EffectVariable* m_scales;
	ID3DX11EffectVariable* m_distortion1;
	ID3DX11EffectVariable* m_distortion2;
	ID3DX11EffectVariable* m_distortion3;
	ID3DX11EffectScalarVariable* m_distortionScale;
	ID3DX11EffectScalarVariable* m_distortionBias;
	ID3DX11EffectShaderResourceVariable*  m_poisonTexture;
	ID3DX11EffectShaderResourceVariable*  m_noiseTexture;
	ID3DX11EffectShaderResourceVariable*  m_alphaTexture;
};