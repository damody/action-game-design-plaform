#pragma once
#include <d3dCompiler.h>
#include <d3dx11effect.h>
#include <algorithm>
#include "d3dApp.h"
#include "global.h"

#include "Vertex.h"
#include "Lua/LuaCell.h"
#include "game/Hero.h"
#include "game/Weapon.h"
#include "game/Chee.h"
#include "game/Player.h"
#include "game/BackGround.h"
#include "Camera.h"

class InitDirect3DApp : public D3DApp
{
//HolyK
private:
	EffectManager* m_Effect_Manager;
//HolyK
public:
	InitDirect3DApp();
	~InitDirect3DApp();
	static InitDirect3DApp* dxAppInstance;
	void initApp();
private:
	void InitTexture();
	void LoadResource();
	void LoadBlend();
	void LoadHero();
	void buildPointFX();
	void buildPoint();
	void OnResize();

	void DrawScene();
	void UpdateScene(float dt);
	void UpdateCamera();
	int  UpdateInput();
	void BackgroundDataUpdate();
	int  UpdateUI();
	void PrintInfo();

	//UI處理
	void DealMainMenu();
	void DealOptionPage();
	void DealTowerSettingPage();
	void DealGamePlayPage();
	void ChangeUI(int i);
	void GoBackUI();
	void ReflashTowerState();
private:
	ID3D11ShaderResourceView* SRVView1;
	ID3D11RenderTargetView* RTVView1;

	ID3D11ShaderResourceView* SRVView2;
	ID3D11RenderTargetView* RTVView2;
	ID3D11ShaderResourceView* SRVViewRes;
	ID3D11RenderTargetView* RTVViewRes;

	ID3D11BlendState*	m_pBlendState_ADD;
	ID3D11BlendState*	m_pBlendState_BLEND;
	ID3D11DepthStencilState *m_pDepthStencil_ZWriteON;
	ID3D11DepthStencilState *m_pDepthStencil_ZWriteOFF;

	D3D11_BUFFER_DESC	m_vbd;

	LuaCell			m_Lua;
	Player			m_Player;
	Camera_Sptr		m_Camera;

	ClipVertexs			m_EntityVertex;
	DrawVertexGroups		m_DrawVertexGroups;
	

	ID3D11Buffer* m_Buffer_Entity;
	ID3DX11Effect* m_Effect_Entity;
	ID3DX11EffectTechnique* m_PTech_Entity;
	ID3D11InputLayout* m_PLayout_Entity;
	ID3DX11EffectVariable *m_Entity_cLootAt;
	ID3DX11EffectVariable *m_Entity_cPos;
	ID3DX11EffectScalarVariable* m_Entity_Width;
	ID3DX11EffectScalarVariable* m_Entity_Height;
	ID3DX11EffectShaderResourceVariable*  m_PMap_Entity;

	Chees				m_Chees;
	ClipVertexs			m_CheeVertex;
	DrawVertexGroups		m_CheeDrawVertexGroups;

	ID3D11Buffer* m_Buffer_Chee;
	ID3DX11Effect* m_Effect_Chee;
	ID3DX11EffectTechnique* m_PTech_Chee;
	ID3D11InputLayout* m_PLayout_Chee;
	ID3DX11EffectVariable *m_Chee_cLootAt;
	ID3DX11EffectVariable *m_Chee_cPos;
	ID3DX11EffectScalarVariable* m_Chee_Width;
	ID3DX11EffectScalarVariable* m_Chee_Height;
	ID3DX11EffectShaderResourceVariable*  m_PMap_Chee;

	ID3D11Buffer* m_Buffer_Background;
	ID3DX11Effect* m_Effect_Background;
	ID3DX11EffectTechnique* m_PTech_Background;
	ID3D11InputLayout* m_PLayout_Background;
	ID3DX11EffectVariable *m_Background_cLootAt;
	ID3DX11EffectVariable *m_Background_cPos;
	ID3DX11EffectScalarVariable* m_Background_Width;
	ID3DX11EffectScalarVariable* m_Background_Height;
	ID3DX11EffectShaderResourceVariable*  m_PMap_Background;

	CRVerteices m_CRVerteices;

	ID3D11Buffer* m_Buffer_ColorRect;
	ID3DX11Effect* m_Effect_ColorRect;
	ID3DX11EffectTechnique* m_PTech_ColorRect;
	ID3D11InputLayout* m_PLayout_ColorRect;
	ID3DX11EffectVariable *m_ColorRect_cLootAt;
	ID3DX11EffectVariable *m_ColorRect_cPos;
	ID3DX11EffectScalarVariable* m_ColorRect_Width;
	ID3DX11EffectScalarVariable* m_ColorRect_Height;

	ID3DX11Effect* m_Effect_Shadow;
	ID3DX11EffectTechnique* m_PTech_Shadow;
	ID3D11InputLayout* m_PLayout_Shadow;
	ID3DX11EffectVariable *m_Shadow_cLootAt;
	ID3DX11EffectVariable *m_Shadow_cPos;
	ID3DX11EffectVariable *m_Shadow_lightDir;
	ID3DX11EffectScalarVariable* m_Shadow_lightStr;
	ID3DX11EffectScalarVariable* m_Shadow_Width;
	ID3DX11EffectScalarVariable* m_Shadow_Height;
	ID3DX11EffectShaderResourceVariable*  m_PMap_Shadow;

	int			m_SettingKeyID;		//目前要設定的按鍵的id
	int			m_SettingKeyTextID;	//目前要設定的按鍵的text物件的id
	int			m_GameProcess;		//遊戲流程,表示目前執行的畫面
	int			m_LastGameProcess;	//前一個遊戲流程
	int			m_Last2GameProcess;	//前前一個遊戲流程

	void TestWavPlayer();
	void TestCamera();
	void TestChee();
};

struct CD3D11_BLEND_DESCX : public D3D11_BLEND_DESC
{
	CD3D11_BLEND_DESCX(){}
	explicit CD3D11_BLEND_DESCX(const D3D11_BLEND_DESC& o) : D3D11_BLEND_DESC( o ){}
	explicit CD3D11_BLEND_DESCX(
		BOOL AlphaToCoverageEnable,
		BOOL IndependentBlendEnable,
		BOOL BlendEnable0,
		D3D11_BLEND SrcBlend0,
		D3D11_BLEND DestBlend0,
		D3D11_BLEND_OP BlendOp0,
		D3D11_BLEND SrcBlendAlpha0,
		D3D11_BLEND DestBlendAlpha0,
		D3D11_BLEND_OP BlendOpAlpha0,
		UINT8 RenderTargetWriteMask0 )
	{
		this->AlphaToCoverageEnable = AlphaToCoverageEnable;
		this->IndependentBlendEnable = IndependentBlendEnable;
		this->RenderTarget[0].BlendEnable = BlendEnable0;
		this->RenderTarget[0].SrcBlend = SrcBlend0;
		this->RenderTarget[0].DestBlend = DestBlend0;
		this->RenderTarget[0].BlendOp = BlendOp0;
		this->RenderTarget[0].SrcBlendAlpha = SrcBlendAlpha0;
		this->RenderTarget[0].DestBlendAlpha = DestBlendAlpha0;
		this->RenderTarget[0].BlendOpAlpha = BlendOpAlpha0;
		this->RenderTarget[0].RenderTargetWriteMask = RenderTargetWriteMask0; 
	}
	~CD3D11_BLEND_DESCX(){}
	operator const D3D11_BLEND_DESC&() const { return *this; }
};

