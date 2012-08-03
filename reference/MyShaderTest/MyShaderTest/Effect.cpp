#include "Effect.h"


Effect::Effect():m_RenderTexture(0)
{
}
bool Effect::Initialize(ID3D11Device* device,HWND hwnd)
{
	bool result;
	//
	m_RenderTexture = new RenderTextureClass();
	if(!m_RenderTexture)
		return false;
	result = m_RenderTexture->Initialize(device,256,256);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture RenderTextureClass object.", L"Error", MB_OK);
		return false;
	}
}