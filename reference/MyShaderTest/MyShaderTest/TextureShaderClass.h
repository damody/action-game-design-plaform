////////////////////////////////////////////////////////////////////////////////
// Filename: textureshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTURESHADERCLASS_H_
#define _TEXTURESHADERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include<d3d11.h>
#include<d3dx11.h>
#include<DxErr.h>
#include<D3Dcompiler.h>
#include<fstream>
#include<xnamath.h>
////////////////////////////////////////////////////////////////////////////////
// Class name: TextureShaderClass
////////////////////////////////////////////////////////////////////////////////
class TextureShaderClass
{
public:
	TextureShaderClass();
	TextureShaderClass(XMFLOAT2);
	TextureShaderClass(XMFLOAT2,float,float);
	TextureShaderClass(const TextureShaderClass&);
	~TextureShaderClass();

	bool Initialize(ID3D11Device*, WCHAR*,HWND);
	void Shutdown();
	void Render(ID3D11DeviceContext*, int, ID3D11ShaderResourceView*);
	
	//bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);

private:
	bool InitializeShader(ID3D11Device*, WCHAR*,HWND);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, WCHAR*,HWND);
	void RenderShader(ID3D11DeviceContext*, int);
	//my func
	bool CreatVertex(ID3D11Device*);
	//

	//bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);
	

public:
	XMFLOAT2 m_pos;//position
	float m_w,m_h;//width height
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_vertexBuffer;
};

#endif