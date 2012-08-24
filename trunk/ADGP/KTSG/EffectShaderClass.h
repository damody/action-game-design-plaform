#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <d3dx11effect.h>
#include <vector>
#include "DX11/TextureManager.h"
#include "game/EffectData.h"

class EffectShaderClass
{
public:
	struct Vertex
	{
		Vector2 position;
		D3DXVECTOR4 picpos; // x, y, w, h
	};typedef std::vector<Vertex> Vertices;
public:
	EffectShaderClass();
	bool Initialize(ID3D11Device*,ID3D11DeviceContext* , WCHAR*, HWND);
	void Shutdown();//not yet
	void ShutdownShader();//not yet
	bool CreatVertex(EffectDatas::iterator begin,EffectDatas::iterator end);
	void OutputShaderErrorMessage(ID3D10Blob*, WCHAR*, HWND);


	virtual void Render() = 0;
	virtual void Update(float dt) = 0;
protected:
	virtual void GetVariableByName() = 0;
	virtual void CreateTexture() = 0;
protected:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_Buffer;

	Vertices m_vertices;
	DrawVertexGroups m_dvg;

	ID3DX11EffectTechnique* m_PTech;
	ID3DX11Effect* m_Effect;
};