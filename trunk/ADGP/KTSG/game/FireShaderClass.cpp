#include "FireShaderClass.h"
#include <fstream>
#include "global.h"
FireShaderClass::FireShaderClass():
m_device(0),m_deviceContext(0),m_layout(0),m_Buffer(0),m_sampleState(0),m_sampleState2(0),
	m_Effect(0),m_PTech(0),m_frameTime(0),m_scrollSpeeds(0),m_scales(0),
	m_distortion1(0),m_distortion2(0),m_distortion3(0),m_distortionScale(0),m_distortionBias(0),
	m_fireTexture(0),m_noiseTexture(0),m_alphaTexture(0),m_Sampler(0),m_Sampler2(0)
{
}
bool FireShaderClass::Initialize(ID3D11Device* device,ID3D11DeviceContext* deviceContext, WCHAR* fxFilename, HWND hwnd)
{
	ID3D10Blob* pCode = 0;
	ID3D10Blob* errorMessage = 0;
	HRESULT d3dResult = 0;
	bool result;
	m_device = device;
	m_deviceContext = deviceContext;

	//Compile fx file
	d3dResult = D3DX11CompileFromFile(fxFilename, NULL, NULL, NULL, 
		"fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &errorMessage, NULL );
	if(FAILED(d3dResult))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, fxFilename,hwnd);
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(hwnd, L"Missing Shader File", fxFilename, MB_OK);
		}
		return false;
	}
	//Create Effect
	d3dResult = D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, device, &m_Effect);
	if(FAILED(d3dResult))
	{
		MessageBox(hwnd, L"Failed to CreateEffectFromMemory", fxFilename, MB_OK);
		return false;
	}
	//Get variable by name
	m_fireTexture = m_Effect->GetVariableByName("fireTexture")->AsShaderResource();
	m_noiseTexture = m_Effect->GetVariableByName("noiseTexture")->AsShaderResource();
	m_alphaTexture = m_Effect->GetVariableByName("alphaTexture")->AsShaderResource();
	m_frameTime = m_Effect->GetVariableByName("frameTime")->AsScalar();
	m_scrollSpeeds = m_Effect->GetVariableByName("scrollSpeeds");
	m_scales = m_Effect->GetVariableByName("scales");
	m_distortion1 = m_Effect->GetVariableByName("distortion1");
	m_distortion2 = m_Effect->GetVariableByName("distortion2");
	m_distortion3 = m_Effect->GetVariableByName("distortion3");
	m_distortionScale = m_Effect->GetVariableByName("distortionScale")->AsScalar();
	m_distortionBias = m_Effect->GetVariableByName("distortionBias")->AsScalar();

	m_Sampler = m_Effect->GetVariableByName("SampleType")->AsSampler();
	m_Sampler2 = m_Effect->GetVariableByName("SampleType2")->AsSampler();


	//Creat input layout
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION",	0, DXGI_FORMAT_R32G32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"PICPOS",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	unsigned int totalLayoutElements = ARRAYSIZE( vertexDesc );
	D3DX11_PASS_DESC PassDesc;
	m_PTech = m_Effect->GetTechniqueByName("PointTech");
	m_PTech->GetPassByIndex(0)->GetDesc(&PassDesc);
	d3dResult = device->CreateInputLayout(
		vertexDesc, totalLayoutElements, PassDesc.pIAInputSignature,PassDesc.IAInputSignatureSize, &m_layout);
	if(FAILED(d3dResult))
	{
		MessageBox(hwnd, L"Failed to CreateInputLayout", fxFilename, MB_OK);
		return false;
	}
	//Creat 
	D3D11_BUFFER_DESC bufferDesc;
	FireVertex heroVertex = { Vector2(1.0f,1.0f),D3DXVECTOR4(1.0f,1.0f,10.0f,7.0f) };

	ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.ByteWidth = (UINT)(sizeof(FireVertex) * 1);
	bufferDesc.StructureByteStride=sizeof(FireVertex);
	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory( &resourceData, sizeof( resourceData ) );
	resourceData.pSysMem = &heroVertex;
	d3dResult = device->CreateBuffer( &bufferDesc, &resourceData, &m_Buffer );
	if( FAILED( d3dResult ) )
	{
		MessageBox(hwnd, L"Creat buffer fail", fxFilename, MB_OK);
		return false;
	}

	// Create a texture sampler state description.
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_SAMPLER_DESC samplerDesc2;

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	// Create the texture sampler state.
	d3dResult = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if(FAILED(d3dResult))
	{
		MessageBox(hwnd, L"Error CreateSamplerState", fxFilename, MB_OK);
		return false;
	}
	// Create a second texture sampler state description for a Clamp sampler.
	samplerDesc2.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc2.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc2.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc2.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc2.MipLODBias = 0.0f;
	samplerDesc2.MaxAnisotropy = 1;
	samplerDesc2.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc2.BorderColor[0] = 0;
	samplerDesc2.BorderColor[1] = 0;
	samplerDesc2.BorderColor[2] = 0;
	samplerDesc2.BorderColor[3] = 0;
	samplerDesc2.MinLOD = 0;
	samplerDesc2.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	d3dResult = device->CreateSamplerState(&samplerDesc2, &m_sampleState2);
	if(FAILED(d3dResult))
	{
		MessageBox(hwnd, L"Error CreateSamplerState", fxFilename, MB_OK);
		return false;
	}

	//Creat fire and noise Texture
	m_fire = Texture_Sptr(new Texture(L"Media\\fire01.dds"));
	m_noise = Texture_Sptr(new Texture(L"Media\\noise01.dds"));

	m_fireTexture->SetResource(m_fire->texture);
	m_noiseTexture->SetResource(m_noise->texture);


	return true;
}
void FireShaderClass::Render()
{
	UINT offset = 0;
	UINT stride2 = sizeof(FireVertex);
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_deviceContext->IASetInputLayout(m_layout);
	m_deviceContext->IASetVertexBuffers(0, 1, &m_Buffer, &stride2, &offset);
	m_PTech->GetPassByIndex(0)->Apply(0, m_deviceContext);


	for (DrawVertexGroups::iterator it = m_dvg.begin();it != m_dvg.end();++it)
	{
		m_alphaTexture->SetResource(it->texture->texture);
		m_PTech->GetPassByIndex(0)->Apply(0, m_deviceContext);
		m_deviceContext->Draw(it->VertexCount, it->StartVertexLocation);
	}
}
void FireShaderClass::SetShaderParameters(D3DXVECTOR3 scrollSpeeds, D3DXVECTOR3 scales, D3DXVECTOR2 distortion1, 
	D3DXVECTOR2 distortion2, D3DXVECTOR2 distortion3, float distortionScale, 
	float distortionBias)
{
	m_scrollSpeeds->SetRawValue(scrollSpeeds,0,sizeof(float)*3);
	m_scales->SetRawValue(scales,0,sizeof(float)*3);
	m_distortion1->SetRawValue(distortion1,0,sizeof(float)*2);
	m_distortion2->SetRawValue(distortion2,0,sizeof(float)*2);
	m_distortion3->SetRawValue(distortion3,0,sizeof(float)*2);
	m_distortionScale->SetFloat(distortionScale);
	m_distortionBias->SetFloat(distortionBias);

	m_Sampler->SetSampler(0,m_sampleState);
	m_Sampler->SetSampler(1,m_sampleState2);
}
void FireShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, WCHAR* shaderFilename, HWND hwnd)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	std::ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for(i=0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

}
bool FireShaderClass::CreatVertex(EffectDatas::iterator begin,EffectDatas::iterator end)
{
	if(begin == end){
		return false;
	}
	m_cvs.clear();
	m_dvg.clear();
	int vertexCount = 0, count = 0;
	for(EffectDatas::iterator it = begin;it!=end;)
	{
		DrawVertexGroup dvg={};
		dvg.texture = g_TextureManager.GetTexture(it->m_TextureID);
		vertexCount = 0;
		dvg.StartVertexLocation = count;
		do 
		{
			FireVertex temp = {};
			temp.picpos = it->m_PicPos;
			temp.position = it->m_Pos;
			//save vertex points
			m_cvs.push_back(temp);
			it++;
			++vertexCount;
			++count;
		} while (it!=end && dvg.texture == g_TextureManager.GetTexture(it->m_TextureID));
		dvg.VertexCount = vertexCount;
		//save dvg
		m_dvg.push_back(dvg);
	}


	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.ByteWidth = (UINT)(sizeof(FireVertex) * m_cvs.size());
	bufferDesc.StructureByteStride=sizeof(FireVertex);
	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory( &resourceData, sizeof( resourceData ) );
	resourceData.pSysMem = &m_cvs[0];
	m_device->CreateBuffer( &bufferDesc, &resourceData, &m_Buffer );

	return true;
}
void FireShaderClass::UpdateFrameTime(float frameTime)
{
	m_frameTime->SetFloat(frameTime);
}