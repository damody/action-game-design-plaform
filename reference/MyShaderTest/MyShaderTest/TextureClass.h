////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTURECLASS_H_
#define _TEXTURECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx11tex.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: TextureClass
////////////////////////////////////////////////////////////////////////////////
class TextureClass
{
public:
	TextureClass();
	TextureClass(ID3D11ShaderResourceView* texture);
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device*, WCHAR*);
	bool Initialize(ID3D11ShaderResourceView*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

	void GetTexture2DDesc(D3D11_TEXTURE2D_DESC&);
	unsigned int GetWidth();
	unsigned int GetHeight();

private:
	ID3D11ShaderResourceView* m_texture;
};

#endif