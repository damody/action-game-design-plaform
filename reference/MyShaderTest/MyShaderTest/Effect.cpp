#include "Effect.h"

Effect::Effect():m_Row(1),m_Col(1),m_device(0),m_deviceContext(0),m_Texture(0),m_FireShader(0)
{
}
bool Effect::Initialize(ID3D11Device* device,ID3D11DeviceContext* deviceContext,HWND hwnd)
{
	m_device = device;
	m_deviceContext = deviceContext;
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
	m_FireShader = new TFireShaderClass();
	result = m_FireShader->Initialize(device,m_deviceContext,L"effectTest.fx",hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the TFireShaderClass object.", L"Error", MB_OK);
		return false;
	}

	
	SetFireParameters();



	return true;
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
void Effect::Render()
{
	SetViewport();

	m_Texture->SetRenderTarget(m_deviceContext,0);
	m_Texture->ClearRenderTarget(m_deviceContext,0,0.0f,1.0f,1.0f,1.0f);

	RenderFire();
}
void Effect::RenderFire()
{
	//Render
	m_FireShader->Render();
}
void Effect::CreateEffect(EffectType::e type,TextureClass* texture,D3DXVECTOR4 picpos)
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
	scrollSpeeds = D3DXVECTOR3(1.0f, 2.0f, 5.0f);
	scales = D3DXVECTOR3(20.0f, 30.0f, 40.0f);
	distortion1 = D3DXVECTOR2(0.03f, 0.07f);
	distortion2 = D3DXVECTOR2(0.02f, 0.05f);
	distortion3 = D3DXVECTOR2(0.01f, 0.1f);
	distortionScale = 1.2f;
	distortionBias = 1.2f;

	m_FireShader->SetShaderParameters(scrollSpeeds,scales,distortion1,distortion2,distortion3,distortionScale,distortionBias);

}
void Effect::Update(float dt)
{
	m_FireShader->UpdateFrameTime(dt);
	m_FireShader->CreatVertex(m_FireEffect.begin(),m_FireEffect.end());
}
ID3D11ShaderResourceView* Effect::GetTexture()
{
	return m_Texture->GetShaderResourceView();
}