#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include "DX11/TextureManager.h"
#include "game/EffectData.h"
#include "EffectShaderClass.h"
#include "game/FireShaderClass.h"
#include "game/PoisonShaderClass.h"
#include "game/RenderTextureClass.h"

const int PIC_H = 2048;
const int PIC_W = 2048;
const int PASTE_H = 256;
const int PASTE_W = 256;

//const int EFFECT_SHADER_SIZE = 3;//n�خĪG

//ShaderClass���ΨC�iEFFECT���� �i�H������beffectMG�� ����A��. ���M���Kshader�|���Ƴ�4�� by holyk
class Effect
{
private:
	Texture_Sptr m_Texture;
	int	     m_TextureID;
	int	     m_SerialNum;
	RenderTextureClass* m_RenderTexture;

	typedef std::vector<EffectDatas> VEffectDatas;//��m�Ҧ����A��EffectData��vector
	VEffectDatas m_vEffect;
	
	typedef std::vector<EffectShaderClass*> EffectShaders;
	EffectShaders m_EffectShaders;

	//shader pointer
	FireShaderClass* m_FireShader;
	PoisonShaderClass* m_PoisonShader;
public:
	Effect(void);
	~Effect(void);
	bool Initialize(HWND hwnd);
	void Render();
	void Updata(float dt);
	void SetFireParameters();

	bool CreateEffect(EffectType::e type,EffectData* ed);//������ed�^��
	void Clear();//�M�� EffectDatas
	bool Check(EffectType::e type,EffectData* ed);//�P�_�O�_�����ƪ���
	bool Overflow();//�K�Ϸ���

	int  GetTextureID();

	ID3D11ShaderResourceView* GetTexture();
private:
	void RenderShader();
};

class EffectManager
{
public:
	Effect**  m_Effect;
	int	m_Size;
	int	m_Page;

	int	m_ScreanW,m_ScreanH;
public:
	EffectManager(void);
	EffectManager(HWND hwnd);
	~EffectManager(void);

	int CreateEffect(EffectType::e type,int textureID,D3DXVECTOR4 *picpos);//������texture & picpos�^��

	void Update(ID3D11RenderTargetView* originRTV);
	void OnResize(int W,int H);

	float	EffectScale(EffectType::e type);

	ID3D11ShaderResourceView* Test_GetNowTexture();
};
