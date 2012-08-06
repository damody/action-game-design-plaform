#pragma once
#include<d3d11.h>
#include<d3dx11.h>
#include<DxErr.h>
#include "global.h"
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

	bool CreateEffect(EffectType::e type,EffectData& ed);//������ed�^��
	void Clear();//�M�� EffectDatas
	bool Check(EffectType::e type,EffectData& ed);//�P�_�O�_�����ƪ���
	bool Overflow();//�K�Ϸ���

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
	std::vector<Effect> m_Effect;
	//Effect m_Effect[4];
	int	m_Page;
public:
	EffectManager(void);
	EffectManager(HWND hwnd);
	~EffectManager(void);

	void CreateEffect(EffectType::e type,int textureID,Vector4& picpos);//������texture & picpos�^��

	void Render();
};
