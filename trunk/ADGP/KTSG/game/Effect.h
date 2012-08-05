#pragma once
#include<d3d11.h>
#include<d3dx11.h>
#include<DxErr.h>
#include "DX11/TextureManager.h"
#include "EffectData.h"

const int PIC_H = 2048;
const int PIC_W = 2048;
const int PASTE_H = 256;
const int PASTE_W = 256;

class Effect
{
protected:
	Texture_Sptr m_FireTexture;
	Texture_Sptr m_FireNoise;
private:
	Texture_Sptr m_Texture;
	int	     m_TextureID;
	int	     m_SerialNum;

	EffectDatas m_FireEffect;
public:
	Effect(void);
	~Effect(void);
	bool Initialize();
	void Render();
	void Updata(float dt);
	void SetFireParameters();

	bool CreateEffect(EffectType::e type,EffectData& ed);//������ed�^��
	void Clear();//�M�� EffectDatas
	bool Check(EffectType::e type,EffectData& ed);//�P�_�O�_�����ƪ���
	bool Overflow();//�K�Ϸ���

	int  Texture();
};

class EffectManager
{
protected:
	Texture_Sptr m_FireTexture;
	Texture_Sptr m_FireNoise;
private:
	Effect	m_Effect[3];
	int	m_Page;
public:
	EffectManager(void):m_Page(0){
		//��l�� Effect
	}
	~EffectManager(void);

	void CreateEffect(EffectType::e type,int& textureID,Vector4& picpos);//������texture & picpos�^��
};
