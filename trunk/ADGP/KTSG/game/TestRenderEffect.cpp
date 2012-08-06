#include "TestRenderEffect.h"


TestRenderEffect::TestRenderEffect(void)
{
	m_layout = 0;
	m_PTech_Heroes = 0;
	m_Heroes_cLootAt = 0;
	m_Heroes_cPos = 0;
	m_Heroes_Width = 0;
	m_Heroes_Height = 0;
	m_PMap_Heroes = 0;
	m_Effect_Heroes = 0;

	
}
TestRenderEffect::~TestRenderEffect()
{
}
bool TestRenderEffect::Initialize(ID3D11Device* device,ID3D11DeviceContext* deviceContext, WCHAR* fxFilename,HWND hwnd)
{
	m_Device = device;
	m_DeviceContext = deviceContext;
	bool result;
	result = InitializeShader(device,fxFilename,hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"InitializeShader failed", fxFilename, MB_OK);
		return false;
	}
	return true;
}
bool TestRenderEffect::InitializeShader(ID3D11Device* device, WCHAR* fxFilename,HWND hwnd)
{
	ID3D10Blob* pCode = 0;
	ID3D10Blob* errorMessage = 0;
	HRESULT d3dResult = 0;

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
	d3dResult = D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, device, &m_Effect_Heroes);
	if(FAILED(d3dResult))
	{
		MessageBox(hwnd, L"Failed to CreateEffectFromMemory", fxFilename, MB_OK);
	}
	m_PTech_Heroes = m_Effect_Heroes->GetTechniqueByName("PointTech");
	//m_Heroes_Width = m_Effect_Heroes->GetVariableByName("width")->AsScalar();
	//m_Heroes_Height =m_Effect_Heroes->GetVariableByName("height")->AsScalar();
	m_Heroes_cLootAt = m_Effect_Heroes->GetVariableByName("cLookAt");
	m_Heroes_cPos = m_Effect_Heroes->GetVariableByName("cPolarCoord");
	m_PMap_Heroes =m_Effect_Heroes->GetVariableByName("gMap")->AsShaderResource();
	D3D11_INPUT_ELEMENT_DESC VertexDesc_HeroVertex[] =
	{
		{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"SIZE",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"PI",		0, DXGI_FORMAT_R32_FLOAT,		0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"PICPOS",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	D3DX11_PASS_DESC PassDesc;
	m_PTech_Heroes->GetPassByIndex(0)->GetDesc(&PassDesc);
	d3dResult = device->CreateInputLayout(
		VertexDesc_HeroVertex, 4, PassDesc.pIAInputSignature,PassDesc.IAInputSignatureSize, &m_layout);
	if(FAILED(d3dResult))
	{
		MessageBox(hwnd, L"Failed to CreateInputLayout", fxFilename, MB_OK);
	}
	//
	D3D11_BUFFER_DESC bufferDesc;
	TestVertex heroVertex = { D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f),0.0f,D3DXVECTOR4(1.0f,1.0f,10.0f,7.0f) };
	ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.ByteWidth = (UINT)(sizeof(TestVertex) * 1);
	bufferDesc.StructureByteStride=sizeof(TestVertex);
	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory( &resourceData, sizeof( resourceData ) );
	resourceData.pSysMem = &heroVertex;
	d3dResult = device->CreateBuffer( &bufferDesc, &resourceData, &m_Buffer_Heroes );

	if( FAILED( d3dResult ) )
	{
		MessageBox(hwnd, L"Creat buffer fail", fxFilename, MB_OK);
		return false;
	}
	//
	//m_Heroes_Width->SetFloat((float)1.0f);
	//m_Heroes_Height->SetFloat((float)1.0f);
	float a[] = {0.0f,0.0f,0.0f};
	float b[] = {0.0f,0.0f,0.0f};

	m_Heroes_cLootAt->SetRawValue(a, 0, sizeof(float)*3);
	m_Heroes_cPos->SetRawValue(b, 0, sizeof(float)*3);

	return true;
}

void TestRenderEffect::Render(int indexCount, ID3D11ShaderResourceView* texture)
{

	UINT offset = 0;
	UINT stride2 = sizeof(TestVertex);
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_DeviceContext->IASetInputLayout(m_layout);
	m_DeviceContext->IASetVertexBuffers(0, 1, &m_Buffer_Heroes, &stride2, &offset);

	m_PMap_Heroes->SetResource(texture);

	m_PTech_Heroes->GetPassByIndex(0)->Apply(0, m_DeviceContext);
	m_DeviceContext->Draw(indexCount, 0);
}

void TestRenderEffect::OutputShaderErrorMessage(ID3D10Blob* errorMessage, WCHAR* shaderFilename,HWND hwnd)
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
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message." , L"Error", MB_OK);
}