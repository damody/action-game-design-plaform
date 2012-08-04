////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"

TextureClass::TextureClass()
{
	m_texture = 0;
}
TextureClass::TextureClass(ID3D11ShaderResourceView* texture)
{
	m_texture = texture;
}

TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11ShaderResourceView* texture)
{
	m_texture = texture;
	return true;
}
bool TextureClass::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;


	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}


void TextureClass::Shutdown()
{
	// Release the texture resource.
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}


ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}

void TextureClass::GetTexture2DDesc(D3D11_TEXTURE2D_DESC& desc)
{
	ID3D11Resource* resource;
	ID3D11Texture2D* pTextureInterface;
	m_texture->GetResource(&resource);
	resource->QueryInterface<ID3D11Texture2D>(&pTextureInterface);
	pTextureInterface->GetDesc(&desc);
}
unsigned int TextureClass::GetWidth()
{
	D3D11_TEXTURE2D_DESC desc;
	this->GetTexture2DDesc(desc);
	return desc.Width;
}
unsigned int TextureClass::GetHeight()
{
	D3D11_TEXTURE2D_DESC desc;
	this->GetTexture2DDesc(desc);
	return desc.Height;
}