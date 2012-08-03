#ifndef _EFFECT_H
#define _EFFECT_H

#define POSTSIZE 256
#define VIEWPORT_WIDTH 1024
#define VIEWPORT_HEIGHT 1024

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include <vector>
#include "D3DClass.h"
#include "RenderTextureClass.h"
#include "TFireShaderClass.h"
#include "EffectData.h"
#include "TextureClass.h"




class Effect
{
public:
	Effect();
	bool Initialize(ID3D11Device* device,HWND hwnd);
	void GetEffect(EffectType);
	void Effect::SetViewport();
	void test();
	void CreatVertices();
	void RenderFire();

	int m_Row,m_Col;

	void SetFireParameters();

	void SetD3DContext(ID3D11DeviceContext* deviceContext);

	void Update(float dt);
public:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	EffectDatas m_FireEffect;
	void CreateEffect(EffectType::e type,TextureClass* texture,D3DXVECTOR4 picpos);
	RenderTextureClass* m_Texture;

	TFireShaderClass* m_FireShader;

	TextureClass* m_fireTexture;
	TextureClass* m_noiseTexture;
	TextureClass* m_alphaTexture;
};

#endif