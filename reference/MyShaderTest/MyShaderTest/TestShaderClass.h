////////////////////////////////////////////////////////////////////////////////
// Filename: TestShaderClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TESTSHADERCLASS_H_
#define _TESTSHADERCLASS_H_
//////////////
// INCLUDES //
//////////////
#include<d3d11.h>
#include<d3dx11.h>
#include<DxErr.h>
#include<D3Dcompiler.h>
#include<fstream>
#include<xnamath.h>
#include<d3dx11effect.h>
#include <d3dx9.h>
////////////////////////////////////////////////////////////////////////////////
// Class name: TestShaderClass
////////////////////////////////////////////////////////////////////////////////

class TestShaderClass
{
private:
	struct ClipVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 size;
		float angle;
		D3DXVECTOR4 picpos; // x, y, w, h
	};
public:
	TestShaderClass();
	~TestShaderClass();

	bool Initialize(ID3D11Device*, WCHAR*,HWND);
	void Shutdown();
	void Render(ID3D11DeviceContext*, int, ID3D11ShaderResourceView*);

private:
	bool InitializeShader(ID3D11Device*, WCHAR*,HWND);
	void OutputShaderErrorMessage(ID3D10Blob*, WCHAR*,HWND);

private:
	ID3D11InputLayout* m_layout;

	ID3DX11EffectTechnique* m_PTech_Heroes;
	ID3DX11EffectVariable *m_Heroes_cLootAt;
	ID3DX11EffectVariable *m_Heroes_cPos;
	ID3DX11EffectScalarVariable* m_Heroes_Width;
	ID3DX11EffectScalarVariable* m_Heroes_Height;
	ID3DX11EffectShaderResourceVariable*  m_PMap_Heroes;

	ID3DX11Effect* m_Effect_Heroes;

	ID3D11Buffer* m_Buffer_Heroes;

	ClipVertex m_HeroVertex;


};

#endif