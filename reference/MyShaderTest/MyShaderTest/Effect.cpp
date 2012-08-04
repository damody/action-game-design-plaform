#include "Effect.h"
#include <iostream>

Effect::Effect():m_Texture(0),m_Row(1),m_Col(1)
{
}
bool Effect::Initialize(ID3D11Device* device,HWND hwnd)
{
	m_device = device;
	bool result;
	//
	m_Texture = new RenderTextureClass();
	if(!m_Texture)
		return false;
	result = m_Texture->Initialize(device,VIEWPORT_WIDTH,VIEWPORT_HEIGHT);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture RenderTextureClass object.", L"Error", MB_OK);
		return false;
	}
	//
	m_FireShader = 0;
	m_FireShader = new TFireShaderClass();
	result = m_FireShader->Initialize(device,L"effectTest.fx",hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the TFireShaderClass object.", L"Error", MB_OK);
		return false;
	}
	//
	WCHAR* fireTextureName = L"fire01.dds";
	WCHAR* noiseTextureName = L"noise01.dds";

	m_fireTexture = 0;
	m_fireTexture = new TextureClass();
	result = m_fireTexture->Initialize(device,fireTextureName);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the TFireShaderClass object.", L"Error", MB_OK);
		return false;
	}
	m_noiseTexture = 0;
	m_noiseTexture = new TextureClass();
	result = m_noiseTexture->Initialize(device,noiseTextureName);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the TFireShaderClass object.", L"Error", MB_OK);
		return false;
	}

	




	return true;
}
void Effect::SetD3DContext(ID3D11DeviceContext* deviceContext)
{
	m_deviceContext = deviceContext;
}

void Effect::SetViewport()
{
	D3D11_VIEWPORT vp;
	vp.Width = VIEWPORT_WIDTH;
	vp.Height = VIEWPORT_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_deviceContext->RSSetViewports( 1, &vp );
}

void Effect::test()
{
	SetViewport();

	m_Texture->SetRenderTarget(m_deviceContext,0);
	m_Texture->ClearRenderTarget(m_deviceContext,0,0.0f,1.0f,1.0f,1.0f);

	//Render



	m_FireShader->Render(m_deviceContext);





}


void Effect::CreateEffect( EffectType::e type,TextureClass* texture,D3DXVECTOR4 picpos )
{
	EffectData ed;
	ed.m_Texture = texture;
	ed.m_Picpos = picpos;
	ed.m_Pos = D3DXVECTOR2(m_Row,m_Col);

	m_Row++;
	if(m_Row > VIEWPORT_WIDTH/POSTSIZE)
	{
		m_Row = 1;
		m_Col++;
		if(m_Col > VIEWPORT_HEIGHT/POSTSIZE)
		{
			m_Col = 1;
			//ªì©l¤Æ
		}
	}
	switch (type)
	{
		case EffectType::Fire:
			m_FireEffect.push_back(ed);
			break;
	}
	

}

void Effect::SetFireParameters()
{
	D3DXVECTOR3 scrollSpeeds, scales;
	D3DXVECTOR2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float frameTime = 0.0f;
	float width,height;
	float* cLookAt;
	float* cPolarCoord;

	scrollSpeeds = D3DXVECTOR3(1.3f, 2.1f, 2.3f);
	scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);
	distortion1 = D3DXVECTOR2(0.1f, 0.2f);
	distortion2 = D3DXVECTOR2(0.1f, 0.3f);
	distortion3 = D3DXVECTOR2(0.1f, 0.1f);
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	frameTime += 0.0001f;
	if(frameTime > 1000.0f)
	{
		frameTime = 0.0f;
	}
	//set
	width = 256;
	height = 256;

	m_FireShader->SetShaderParameters(width,height,0,0,m_fireTexture->GetTexture(),m_noiseTexture->GetTexture(),0
		,frameTime,scrollSpeeds,scales,distortion1,distortion2,distortion3,distortionScale,distortionBias);
}

void Effect::Update(float dt)
{
	m_FireShader->SetFrameTime(dt);
	m_FireShader->CreatVertex(m_FireEffect.begin(),m_FireEffect.end());
}
