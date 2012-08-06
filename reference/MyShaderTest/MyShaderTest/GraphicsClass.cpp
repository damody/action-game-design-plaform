#include "GraphicsClass.h"
#include <xnamath.h>
#include <iostream>
GraphicsClass::GraphicsClass():m_D3D(0),m_Texture(0),m_TestShader(0)
{

}
bool GraphicsClass::Initialize(WCHAR* textureName,WCHAR* shaderName, HWND hwnd )
{
	bool result;

	// Create the Direct3D object.
	m_D3D = new D3DClass();
	if(!m_D3D)
	{
		return false;
	}
	// Initialize the Direct3D object.
	result = m_D3D->Initialize(hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the texture object.
	m_Texture = new TextureClass();
	if(!m_Texture)
	{
		return false;
	}
	// Initialize the texture object.
	textureName = L"davis_0_.png";
	
	result = m_Texture->Initialize(m_D3D->GetDevice(),textureName);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture object.", L"Error", MB_OK);
		return false;
	}

	
	//test
	m_TestShader = new TestShaderClass();
	if(!m_TestShader)
	{
		return false;
	}
	// Initialize the texture shaderGray object.
	result = m_TestShader->Initialize(m_D3D->GetDevice(),L"GStest2.fx",hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the TestShader object.", L"Error", MB_OK);
		return false;
	}


	m_Effect = 0;
	m_Effect = new Effect();
	result = m_Effect->Initialize(m_D3D->GetDevice(),m_D3D->GetDeviceContext(),hwnd);
	

	m_Effect->CreateEffect(EffectType::Fire,m_Texture,D3DXVECTOR4(1.0f,1.0f,10.0f,7.0f));
	m_Effect->CreateEffect(EffectType::Fire,m_Texture,D3DXVECTOR4(1.0f,3.0f,10.0f,7.0f));

	return true;
}

void GraphicsClass::Render()
{


	static float dt = 0.0f;
	dt += 0.001f;
	if(dt > 1000.0f)
	{
		dt = 0.0f;
	}
	
	
	m_Effect->Update(dt);
	m_Effect->Render();
	//m_D3D->TEST(WINDOW_WIDTH,WINDOW_HEIGHT,m_D3D->GetBackBufferTarget());
	m_D3D->SetRenderToBackBuffer();
	m_TestShader->Render(m_D3D->GetDeviceContext(),1,m_Effect->GetTexture());
	
}
void GraphicsClass::Frame()
{
	m_D3D->BeginScene(0.0f, 1.0f, 0.0f, 1.0f);
	Render();
	m_D3D->EndScene();
}