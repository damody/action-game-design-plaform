#include "GraphicsClass.h"
#include <xnamath.h>
#include <iostream>
GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Texture = 0;
	m_TextureShader = 0;
	m_Camera = 0;
	m_FireShader = 0;
	m_RenderTexture = 0;

	m_TestShader = 0;
	m_TestTS = 0;
	m_tf = 0;
}
GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}
GraphicsClass::~GraphicsClass()
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

	//creat new camera
	m_Camera = new Camera(0,0,0,0,0,0);


	/*
	// Create the Camera object.
	m_Camera = new CameraClass();
	if(!m_Camera)
	{
		return false;
	}
	// Set camera position
	m_Camera->SetPosition(0.0f, 0.0f, -2.0f);
	*/

	// Create the texture object.
	m_Texture = new TextureClass();
	if(!m_Texture)
	{
		return false;
	}
	// Initialize the texture object.
	textureName = L"davis_0.png";
	result = m_Texture->Initialize(m_D3D->GetDevice(),textureName);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass( XMFLOAT2( 0.0f, 0.0f ),1.0,1.0 );
	if(!m_TextureShader)
	{
		return false;
	}
	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(),shaderName,hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}
	// Create the FireShader object.
	m_FireShader = new FireShaderClass();
	if(!m_FireShader)
	{
		return false;
	}
	// Initialize the FireTestShader object.
	result = m_FireShader->Initialize(m_D3D->GetDevice(),L"FireTestShader.fx",hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture FireShader object.", L"Error", MB_OK);
		return false;
	}
	//
	m_RenderTexture = new RenderTextureClass();
	result = m_RenderTexture->Initialize(m_D3D->GetDevice(),256,256);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture RenderTextureClass object.", L"Error", MB_OK);
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
	//test tfire
	m_tf = new TFireShaderClass();
	if(!m_tf)
	{
		return false;
	}
	result = m_tf->Initialize(m_D3D->GetDevice(),L"effectTest.fx",hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the tf shader object.", L"Error", MB_OK);
		return false;
	}


	m_Effect = 0;
	m_Effect = new Effect();
	result = m_Effect->Initialize(m_D3D->GetDevice(),hwnd);
	
	m_Effect->SetD3DContext(m_D3D->GetDeviceContext());

	m_Effect->CreateEffect(EffectType::Fire,m_Texture,D3DXVECTOR4(1.0f,1.0f,10.0f,7.0f));
	m_Effect->CreateEffect(EffectType::Fire,m_Texture,D3DXVECTOR4(1.0f,1.0f,10.0f,7.0f));

	return true;
}

void GraphicsClass::Render()
{
	//m_Effect->test();
	static float dt = 0.0f;
	dt += 0.0001f;
	if(dt > 1000.0f)
	{
		dt = 0.0f;
	}

	
	m_D3D->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);
	m_Effect->Update(dt);
	m_Effect->test();

	m_D3D->TEST(640,480,m_D3D->GetBackBufferTarget());

	m_D3D->BeginScene(0.0f, 1.0f, 0.0f, 1.0f);
	m_D3D->SetRenderToBackBuffer();
	m_TestShader->Render(m_D3D->GetDeviceContext(),1,m_Effect->m_Texture->GetShaderResourceView());
	//m_TestShader->Render(m_D3D->GetDeviceContext(),1,m_Texture->GetTexture());
	m_D3D->EndScene();
	
	/*
	m_D3D->TEST(256,256,m_RenderTexture->GetRenderTargetView());
	m_D3D->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);
	m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext(),0);
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(),0,0.0f,1.0f,1.0f,1.0f);
	
	TEST_RenderFire();
	//m_TextureShader->Render(m_D3D->GetDeviceContext(),4,m_alphaTexture->GetTexture());
	//m_TestShader->Render(m_D3D->GetDeviceContext(),1,m_alphaTexture->GetTexture());

	m_D3D->TEST(640,480,m_D3D->GetBackBufferTarget());
	m_D3D->BeginScene(0.0f, 1.0f, 0.0f, 1.0f);
	m_D3D->SetRenderToBackBuffer();
	//m_TextureShader->Render(m_D3D->GetDeviceContext(),4,m_RenderTexture->GetShaderResourceView());
	m_TestShader->Render(m_D3D->GetDeviceContext(),1,m_RenderTexture->GetShaderResourceView());
	m_D3D->EndScene();
	*/
	/*
	m_D3D->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);
	m_tf->Render(m_D3D->GetDeviceContext(),1,m_Texture->GetTexture());
	m_TestShader->Render(m_D3D->GetDeviceContext(),1,m_Texture->GetTexture());
	m_D3D->EndScene();
	*/
	/*
	m_D3D->TEST(256,256,m_RenderTexture->GetRenderTargetView());
	m_D3D->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);
	m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext(),0);
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(),0,0.0f,0.0f,1.0f,1.0f);

	//m_TestTS->Render(m_D3D->GetDeviceContext(),4,m_Texture->GetTexture());
	TEST_RenderFire();
	//m_D3D->EndScene();
	
	m_D3D->TEST(640,480,m_D3D->GetBackBufferTarget());
	m_D3D->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);
	m_D3D->SetRenderToBackBuffer();
	m_TextureShader->Render(m_D3D->GetDeviceContext(),4,m_RenderTexture->GetShaderResourceView());
	m_D3D->EndScene();
	*/
}
void GraphicsClass::Frame()
{
	Render();
}

// void GraphicsClass::TEST_RenderFire()
// {
// 	
// 	D3DXVECTOR3 scrollSpeeds, scales;
// 	D3DXVECTOR2 distortion1, distortion2, distortion3;
// 	float distortionScale, distortionBias;
// 	static float frameTime = 0.0f;
// 	float width,height;
// 	float* cLookAt;
// 	float* cPolarCoord;
// 
// 	scrollSpeeds = D3DXVECTOR3(1.3f, 2.1f, 2.3f);
// 	scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);
// 	distortion1 = D3DXVECTOR2(0.1f, 0.2f);
// 	distortion2 = D3DXVECTOR2(0.1f, 0.3f);
// 	distortion3 = D3DXVECTOR2(0.1f, 0.1f);
// 	distortionScale = 0.8f;
// 	distortionBias = 0.5f;
// 
// 	frameTime += 0.0001f;
// 	if(frameTime > 1000.0f)
// 	{
// 		frameTime = 0.0f;
// 	}
// 
// 	// Clear the buffers to begin the scene.
// 	m_D3D->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);
// 	//set
// 	width = 256;
// 	height = 256;
// 	cLookAt = m_Camera->GetLookAt();
// 	cPolarCoord = m_Camera->GetCPos();
// 
// 
// 	bool result;
// 	result = m_tf->Render(m_D3D->GetDeviceContext(), 1, width, height, cLookAt,cPolarCoord, 
// 		m_fireTexture->GetTexture(), m_noiseTexture->GetTexture(), m_alphaTexture->GetTexture(), frameTime, scrollSpeeds, 
// 		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
// 
// 	if(!result)
// 	{
// 		std::cout<<"Graphics Render fail"<<std::endl;
// 	}
// 	// Present the rendered scene to the screen.
// 	//m_D3D->EndScene();
// 	
// 
// 
// 	/*
// 	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
// 	D3DXVECTOR3 scrollSpeeds, scales;
// 	D3DXVECTOR2 distortion1, distortion2, distortion3;
// 	float distortionScale, distortionBias;
// 	static float frameTime = 0.0f;
// 
// 	scrollSpeeds = D3DXVECTOR3(1.3f, 2.1f, 2.3f);
// 	scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);
// 	distortion1 = D3DXVECTOR2(0.1f, 0.2f);
// 	distortion2 = D3DXVECTOR2(0.1f, 0.3f);
// 	distortion3 = D3DXVECTOR2(0.1f, 0.1f);
// 	distortionScale = 0.8f;
// 	distortionBias = 0.5f;
// 
// 	frameTime += 0.0001f;
// 	if(frameTime > 1000.0f)
// 	{
// 		frameTime = 0.0f;
// 	}
// 
// 	// Clear the buffers to begin the scene.
// 	m_D3D->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);
// 
// 
// 	// Generate the view matrix based on the camera's position.
// 	//m_Camera->Render();
// 	// Get the world, view, and projection matrices from the camera and d3d objects.
// 	m_D3D->GetWorldMatrix(worldMatrix);
// 	//m_Camera->GetViewMatrix(viewMatrix);
// 	m_D3D->GetProjectionMatrix(projectionMatrix);
// 
// 
// 	bool result;
// 	result = m_FireShader->Render(m_D3D->GetDeviceContext(), 4, worldMatrix, viewMatrix, projectionMatrix, 
// 		0, 0, 0, frameTime, scrollSpeeds, 
// 		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
// 	result = m_tf->Render(m_D3D->GetDeviceContext(), 1, worldMatrix, viewMatrix, projectionMatrix, 
// 		m_fireTexture->GetTexture(), m_noiseTexture->GetTexture(), m_alphaTexture->GetTexture(), frameTime, scrollSpeeds, 
// 		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
// 
// 	if(!result)
// 	{
// 		std::cout<<"Graphics Render fail"<<std::endl;
// 	}
// 	// Present the rendered scene to the screen.
// 	//m_D3D->EndScene();
// 	*/
// }
