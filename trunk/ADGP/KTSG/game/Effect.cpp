#include "Effect.h"


Effect::Effect(void)
{
}


Effect::~Effect(void)
{
}

bool Effect::Initialize(HWND hwnd)
{
	bool result;
	//
	m_RenderTexture = new RenderTextureClass();
	if(!m_RenderTexture)
		return false;
	result = m_RenderTexture->Initialize(g_d3dDevice,PIC_W,PIC_H);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture RenderTextureClass object.", L"Error", MB_OK);
		return false;
	}
	//
	m_FireShader = new FireShaderClass();
	result = m_FireShader->Initialize(g_d3dDevice,g_DeviceContext,L"shader\\FireShader.fx",hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the FireShaderClass object.", L"Error", MB_OK);
		return false;
	}
	m_Texture = Texture_Sptr(new Texture(m_RenderTexture->GetShaderResourceView()));
	m_TextureID = g_TextureManager.AddTexture("EffectTexture",m_Texture);
	SetFireParameters();



	return true;
}
void Effect::SetViewport()
{
	D3D11_VIEWPORT vp;
	vp.Width = PIC_W;
	vp.Height = PIC_H;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_DeviceContext->RSSetViewports( 1, &vp );
}
void Effect::SetViewport(float w,float h)
{
	D3D11_VIEWPORT vp;
	vp.Width = w;
	vp.Height = h;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_DeviceContext->RSSetViewports( 1, &vp );
}
void Effect::Updata( float dt )
{
	m_FireShader->UpdateFrameTime(dt);
	m_FireShader->CreatVertex(m_FireEffect.begin(),m_FireEffect.end());
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

bool Effect::CreateEffect( EffectType::e type,EffectData& ed )
{
	if(Overflow())return false;
	if (!Check(type,ed))
	{
		ed.m_Pos.x = 1 + m_SerialNum % (PIC_W/PASTE_W);
		ed.m_Pos.y = 1 + m_SerialNum / (PIC_W/PASTE_W);

		switch(type)
		{
		case	EffectType::FIRE:
			m_FireEffect.push_back(ed);
		}
		m_SerialNum++;
	}
	return true;
}

void Effect::Clear()
{
	m_FireEffect.clear();
	m_SerialNum = 1;
}

bool Effect::Overflow()
{
	return (m_SerialNum > (PIC_H/PASTE_H)*(PIC_W/PASTE_W));
}

bool Effect::Check( EffectType::e type,EffectData& ed )
{

	for (EffectDatas::iterator it = m_FireEffect.begin();it != m_FireEffect.end();it++)
	{
		if(ed == (*it))
		{
			ed.m_Pos = it->m_Pos;
			return true;
		}
	}
	return false;
}

int Effect::GetTextureID()
{
	return m_TextureID;
}

void Effect::Render()
{
	SetViewport();

	m_RenderTexture->SetRenderTarget(g_DeviceContext,0);
	m_RenderTexture->ClearRenderTarget(g_DeviceContext,0,0.0f,1.0f,1.0f,1.0f);

	RenderFire();
}
void Effect::RenderFire()
{
	//Render
	m_FireShader->Render();
}
ID3D11ShaderResourceView* Effect::GetTexture()
{
	return m_Texture->texture;
}


//EffectManager
EffectManager::EffectManager():m_Page(0){
	//初始化 Effect
}
EffectManager::EffectManager(HWND hwnd):m_Page(0){
	//初始化 Effect
	//test
	m_Effect[0].Initialize(hwnd);
}

void EffectManager::CreateEffect( EffectType::e type,int& textureID,Vector4& picpos )
{
	EffectData ed;
	ed.m_TextureID = textureID;
	ed.m_PicPos    = picpos;
	if(!m_Effect[m_Page%3].CreateEffect(type,ed))
	{
		m_Page++;
		m_Effect[m_Page%3].Clear();
		m_Effect[m_Page%3].CreateEffect(type,ed);
	}
	textureID = m_Effect[m_Page%3].GetTextureID();
	//textureID = ed.m_TextureID;
	picpos	  = ed.m_PicPos;
}
