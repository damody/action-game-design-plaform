#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <d3dx11effect.h>
#include <vector>
#include <map>
#include <string>
#include "Lua/LuaCell.h"
#include "common\shared_ptr.h"
#include "DX11/TextureManager.h"
#include "game/EffectData.h"



class EffectShaderClass
{
public:
	EffectShaderClass();
	bool Initialize( WCHAR* luaFileName, ID3D11Device*, ID3D11DeviceContext*, HWND ); //參數HWND方便錯誤訊息在視窗顯現
	void Shutdown();//not yet
	void ShutdownShader();//not yet
	bool CreatVertex( EffectDatas::iterator begin, EffectDatas::iterator end );
	void Render();
	void Update( float dt );
private:
	struct EffectVariable
	{
		std::string variableType;
		ID3DX11EffectVariable* m_EffectVariable;
	};
	struct Vertex
	{
		Vector2 position;
		D3DXVECTOR4 picpos; // x, y, w, h
	}; typedef std::vector<Vertex> Vertices;
private:
	void OutputShaderErrorMessage( ID3D10Blob*, const wchar_t*, HWND );
	bool SetShaderParameters();
	bool InitShader( const wchar_t*, HWND );//參數HWND方便錯誤訊息在視窗顯現
	bool SetEffectVariableByName();
	bool CreateTexture();
private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_Buffer;

	Vertices m_vertices;
	DrawVertexGroups m_dvg;

	ID3DX11EffectTechnique* m_PTech;
	ID3DX11Effect* m_Effect;

	//Lua variable
	LuaCell_Sptr m_LuaCell;
	std::string m_ShaderPath;
	strings m_LuaTextureNames;
	strings m_LuaShaderParameterNames;

	//Texture
	typedef std::vector<Texture_Sptr> Textures;
	Textures m_Textures;

	//Effect variable
	ID3DX11EffectScalarVariable* m_frameTime;
	ID3DX11EffectShaderResourceVariable*  m_alphaTexture;//人物圖
	std::map<std::string, ID3DX11EffectShaderResourceVariable*> m_EffectShaderResource; //string map to EffectShaderResource.
	std::map<std::string, EffectVariable> m_EffectVariable; //string map to EffectVariable.
};