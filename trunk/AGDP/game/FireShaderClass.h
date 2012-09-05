#pragma once

#include "DX11/TextureManager.h"
#include "EffectShaderClass.h"

class FireShaderClass : public EffectShaderClass
{
public:
	FireShaderClass();
	void Render();
	void Update( float dt );
	void SetShaderParameters( int i, ... );
	/*void SetShaderParameters(D3DXVECTOR3 scrollSpeeds, D3DXVECTOR3 scales, D3DXVECTOR2 distortion1,
		D3DXVECTOR2 distortion2, D3DXVECTOR2 distortion3, float distortionScale,
		float distortionBias);*/
private:
	void SetEffectVariableByName();
	void CreateTexture();
private:
	Texture_Sptr m_fire;
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
	ID3DX11EffectShaderResourceVariable*  m_fireTexture;
	ID3DX11EffectShaderResourceVariable*  m_noiseTexture;
	ID3DX11EffectShaderResourceVariable*  m_alphaTexture;
};