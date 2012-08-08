#pragma once
#include<d3d11.h>
#include<d3dx11.h>
#include<DxErr.h>
#include "DX11/TextureManager.h"
#include "game/EffectData.h"
#include "game/FireShaderClass.h"
#include "game/RenderTextureClass.h"

const int PIC_H = 2048;
const int PIC_W = 2048;
const int PASTE_H = 256;
const int PASTE_W = 256;

class Effect
{
private:
	Texture_Sptr m_Texture;
	int	     m_TextureID;
	int	     m_SerialNum;

	EffectDatas m_FireEffect;
	RenderTextureClass* m_RenderTexture;
	FireShaderClass* m_FireShader;
public:
	Effect(void);
	~Effect(void);
	bool Initialize(HWND hwnd);
	void Render();
	void Updata(float dt);
	void SetFireParameters();

	bool CreateEffect(EffectType::e type,EffectData* ed);//直接改ed回傳
	void Clear();//清除 EffectDatas
	bool Check(EffectType::e type,EffectData* ed);//判斷是否有重複的圖
	bool Overflow();//貼圖溢位

	int  GetTextureID();
	void SetViewport();
	void SetViewport(float w,float h);

	ID3D11ShaderResourceView* GetTexture();
private:
	void RenderFire();
};

class EffectManager
{
public:
	Effect**  m_Effect;
	int	m_Size;
	int	m_Page;

	int	m_ScreamW,m_ScreamH;
public:
	EffectManager(void);
	EffectManager(HWND hwnd);
	~EffectManager(void);

	int CreateEffect(EffectType::e type,int textureID,D3DXVECTOR4 *picpos);//直接改texture & picpos回傳

	void Update(ID3D11RenderTargetView* originRTV);
	void OnResize(int W,int H);

	ID3D11ShaderResourceView* Test_GetNowTexture();
};
