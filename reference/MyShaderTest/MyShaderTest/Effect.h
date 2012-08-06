#ifndef _EFFECT_H
#define _EFFECT_H

#define POSTSIZE 256
#define VIEWPORT_WIDTH 1024
#define VIEWPORT_HEIGHT 1024

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include <vector>
#include "RenderTextureClass.h"
#include "FireShaderClass.h"
#include "TextureClass.h"
#include "EffectData.h"

class Effect
{
public:
	Effect();
	bool Initialize(ID3D11Device* device,ID3D11DeviceContext* deviceContext,HWND hwnd);
	void GetEffect(EffectType);//not yet
	void SetViewport();
	void Render();
	void CreatVertices();//not yet
	void SetFireParameters();
	void Update(float dt);
	void CreateEffect(EffectType::e type,TextureClass* texture,D3DXVECTOR4 picpos);

	ID3D11ShaderResourceView* GetTexture();

private:
	void RenderFire();
private:
	int m_Row,m_Col;//init 1,1
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	EffectDatas m_FireEffect;
	RenderTextureClass* m_Texture;
	FireShaderClass* m_FireShader;
};

#endif