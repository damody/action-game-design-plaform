#pragma once
//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <fstream>
#include <xnamath.h>
#include <d3dx11effect.h>
#include <d3dx9.h>
////////////////////////////////////////////////////////////////////////////////
// Class name: TestShaderClass
////////////////////////////////////////////////////////////////////////////////

class TestRenderEffect
{
private:
	struct TestVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 size;
		float angle;
		D3DXVECTOR4 picpos; // x, y, w, h
	};
public:
	TestRenderEffect();
	~TestRenderEffect();

	bool Initialize(ID3D11Device*,ID3D11DeviceContext*, WCHAR*,HWND);
	void Shutdown();
	void Render(int, ID3D11ShaderResourceView*);

private:
	bool InitializeShader(ID3D11Device*, WCHAR*,HWND);
	void OutputShaderErrorMessage(ID3D10Blob*, WCHAR*,HWND);

private:
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DeviceContext;
	ID3D11InputLayout* m_layout;

	ID3DX11EffectTechnique* m_PTech_Heroes;
	ID3DX11EffectVariable *m_Heroes_cLootAt;
	ID3DX11EffectVariable *m_Heroes_cPos;
	ID3DX11EffectScalarVariable* m_Heroes_Width;
	ID3DX11EffectScalarVariable* m_Heroes_Height;
	ID3DX11EffectShaderResourceVariable*  m_PMap_Heroes;

	ID3DX11Effect* m_Effect_Heroes;

	ID3D11Buffer* m_Buffer_Heroes;

	TestVertex m_HeroVertex;


};