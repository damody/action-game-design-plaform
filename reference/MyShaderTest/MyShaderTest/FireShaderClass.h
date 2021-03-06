#ifndef _FIRESHADERCLASS_H_
#define _FIRESHADERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include <d3dx11effect.h>
#include <vector>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////

#include "TextureClass.h"
#include "EffectData.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: TFireShaderClass
////////////////////////////////////////////////////////////////////////////////

struct ClipVertex
{
	D3DXVECTOR2 position;
	D3DXVECTOR4 picpos; // x, y, w, h
};
typedef std::vector<ClipVertex> ClipVertices;
struct DrawVertexGroup
{
	TextureClass*	 texture;	// ����
	int	VertexCount, StartVertexLocation;
};
typedef std::vector<DrawVertexGroup> DrawVertexGroups;

class FireShaderClass
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct NoiseBufferType
	{
		float frameTime;
		D3DXVECTOR3 scrollSpeeds;
		D3DXVECTOR3 scales;
		float padding;
	};

	struct DistortionBufferType
	{
		D3DXVECTOR2 distortion1;
		D3DXVECTOR2 distortion2;
		D3DXVECTOR2 distortion3;
		float distortionScale;
		float distortionBias;
	};

public:
	FireShaderClass();

	bool Initialize(ID3D11Device*,ID3D11DeviceContext* , WCHAR*, HWND);
	void Shutdown();//not yet
	void Render();
	bool CreatVertex(EffectDatas::iterator begin,EffectDatas::iterator end);
	void UpdateFrameTime(float frameTime);
	bool InitializeShader(ID3D11Device*, WCHAR*, HWND);
	void ShutdownShader();//not yet
	void OutputShaderErrorMessage(ID3D10Blob*, WCHAR*, HWND);
	void SetShaderParameters(D3DXVECTOR3 scrollSpeeds, D3DXVECTOR3 scales, D3DXVECTOR2 distortion1, 
		D3DXVECTOR2 distortion2, D3DXVECTOR2 distortion3, float distortionScale, 
		float distortionBias);
private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_Buffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11SamplerState* m_sampleState2;

	ClipVertices m_cvs;
	DrawVertexGroups m_dvg;

	TextureClass* m_fire;
	TextureClass* m_noise;

	
	//Effect variable
	ID3DX11Effect* m_Effect;
	ID3DX11EffectTechnique* m_PTech;
	ID3DX11EffectScalarVariable* m_frameTime;
	ID3DX11EffectVariable* m_scrollSpeeds;
	ID3DX11EffectVariable* m_scales;
	ID3DX11EffectVariable* m_distortion1;
	ID3DX11EffectVariable* m_distortion2;
	ID3DX11EffectVariable* m_distortion3;
	ID3DX11EffectScalarVariable* m_distortionScale;
	ID3DX11EffectScalarVariable* m_distortionBias;
	ID3DX11EffectShaderResourceVariable*  m_fireTexture;
	ID3DX11EffectShaderResourceVariable*  m_noiseTexture;
	ID3DX11EffectShaderResourceVariable*  m_alphaTexture;
	ID3DX11EffectSamplerVariable* m_Sampler;
	ID3DX11EffectSamplerVariable* m_Sampler2;
};

#endif