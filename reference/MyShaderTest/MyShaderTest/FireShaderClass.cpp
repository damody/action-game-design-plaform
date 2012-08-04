////////////////////////////////////////////////////////////////////////////////
// Filename: fireshaderclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "fireshaderclass.h"
#include <xnamath.h>
#include <fstream>
struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};
FireShaderClass::FireShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
	m_noiseBuffer = 0;
	m_sampleState = 0;
	m_sampleState2 = 0;
	m_distortionBuffer = 0;

	//
	m_fireT = 0;
	m_noiseT = 0;
	m_alphaT = 0;
	//
	m_vertexBuffer = 0;
	m_fireTexture = 0;
	m_noiseTexture = 0;
	m_alphaTexture = 0;
}


FireShaderClass::FireShaderClass(const FireShaderClass& other)
{
}


FireShaderClass::~FireShaderClass()
{
}


bool FireShaderClass::Initialize(ID3D11Device* device, WCHAR* fxFilename, HWND hwnd)
{
	bool result;
	WCHAR* fireTextureName = L"fire01.dds";
	WCHAR* noiseTextureName = L"noise01.dds";
	WCHAR* alphaTextureName = L"davis_0.png";

	// Create the texture object.
	m_fireTexture = new TextureClass();
	m_noiseTexture = new TextureClass();
	m_alphaTexture = new TextureClass();
	if(!m_fireTexture || !m_noiseTexture || !m_alphaTexture)
	{
		return false;
	}
	// Initialize the texture object.
	result = m_fireTexture->Initialize(device,fireTextureName);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the fireTexture object in FireShader.", L"Error", MB_OK);
		return false;
	}
	result = m_noiseTexture->Initialize(device,noiseTextureName);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the noiseTexture object in FireShader.", L"Error", MB_OK);
		return false;
	}
	result = m_alphaTexture->Initialize(device,alphaTextureName);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the alphatTxture object in FireShader.", L"Error", MB_OK);
		return false;
	}


	// Initialize the vertex and pixel shaders.
	result = InitializeShader(device, fxFilename, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Failed to initialize shader.", fxFilename, MB_OK);
		return false;
	}
	//Creat the VertexBuffer
	result = CreatVertex(device);
	if(!result)
	{
		MessageBox(hwnd, L"Failed to creat vertexBuffer.", fxFilename, MB_OK);
		return false;
	}

	return true;
}

void FireShaderClass::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader();

	return;
}


bool FireShaderClass::InitializeShader(ID3D11Device* device, WCHAR* fxFilename, HWND hwnd)
{
	ID3DBlob* vsBuffer;
	ID3DBlob* psBuffer;
	ID3D10Blob* errorMessage;
	HRESULT d3dResult;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC noiseBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_SAMPLER_DESC samplerDesc2;
	D3D11_BUFFER_DESC distortionBufferDesc;
	//Initialize the pointers this function will use to null.
	vsBuffer = 0;
	psBuffer = 0;
	errorMessage = 0;
	//Complie vs
	d3dResult = D3DX11CompileFromFile(fxFilename, NULL, NULL, "VS_Main", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
		&vsBuffer, &errorMessage, NULL);
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
	//Complie PS
	d3dResult = D3DX11CompileFromFile(fxFilename, NULL, NULL, "PS_Main", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
		&psBuffer, &errorMessage, NULL);
	if(FAILED(d3dResult))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, fxFilename,hwnd);
		}
		// If there was  nothing in the error message then it simply could not find the file itself.
		else
		{
			MessageBox(hwnd, L"Missing Shader File", fxFilename, MB_OK);
			//DXTRACE_MSG( "Missing Shader File" );
		}

		return false;
	}
	//Creat VS shader
	d3dResult = device->CreateVertexShader( vsBuffer->GetBufferPointer( ),
		vsBuffer->GetBufferSize( ), 0, &m_vertexShader );

	if( FAILED( d3dResult ) )
	{
		MessageBox(hwnd, L"Error creating the vertex shader!", fxFilename, MB_OK);
		if( vsBuffer )
			vsBuffer->Release( );

		return false;
	}
	//Creat PS shader
	d3dResult = device->CreatePixelShader( psBuffer->GetBufferPointer( ),
		psBuffer->GetBufferSize( ), 0, &m_pixelShader );

	if( FAILED( d3dResult ) )
	{
		MessageBox(hwnd, L"Error creating pixel shader!" , fxFilename, MB_OK);
		//DXTRACE_MSG( "Error creating pixel shader!" );
		return false;
	}

	//Creat InputLayout
	D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	unsigned int totalLayoutElements = ARRAYSIZE( solidColorLayout );

	d3dResult = device->CreateInputLayout( solidColorLayout, totalLayoutElements,
		vsBuffer->GetBufferPointer( ), vsBuffer->GetBufferSize( ), &m_layout );

	if( FAILED( d3dResult ) )
	{
		MessageBox(hwnd, L"Error creating the input layout!", fxFilename, MB_OK);
		return false;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	if(vsBuffer)vsBuffer->Release();
	vsBuffer = 0;

	if(psBuffer)psBuffer->Release();
	psBuffer = 0;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	// Create the matrix buffer pointer so we can access the vertex shader constant buffer from within this class.
	d3dResult = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if(FAILED(d3dResult))
	{
		MessageBox(hwnd, L"Error CreateBuffer", fxFilename, MB_OK);
		return false;
	}
	// Setup the description of the dynamic noise constant buffer that is in the vertex shader.
	noiseBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	noiseBufferDesc.ByteWidth = sizeof(NoiseBufferType);
	noiseBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	noiseBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	noiseBufferDesc.MiscFlags = 0;
	noiseBufferDesc.StructureByteStride = 0;

	// Create the noise buffer pointer so we can access the vertex shader constant buffer from within this class.
	d3dResult = device->CreateBuffer(&noiseBufferDesc, NULL, &m_noiseBuffer);
	if(FAILED(d3dResult))
	{
		MessageBox(hwnd, L"Error CreateBuffer", fxFilename, MB_OK);
		return false;
	}
	// Create a texture sampler state description.
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

	// Setup the description of the dynamic distortion constant buffer that is in the pixel shader.
	distortionBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	distortionBufferDesc.ByteWidth = sizeof(DistortionBufferType);
	distortionBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	distortionBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	distortionBufferDesc.MiscFlags = 0;
	distortionBufferDesc.StructureByteStride = 0;

	// Create the distortion buffer pointer so we can access the pixel shader constant buffer from within this class.
	d3dResult = device->CreateBuffer(&distortionBufferDesc, NULL, &m_distortionBuffer);
	if(FAILED(d3dResult))
	{
		MessageBox(hwnd, L"Error CreateBuffer", fxFilename, MB_OK);
		return false;
	}

	return true;
}


void FireShaderClass::ShutdownShader()
{
	// Release the distortion constant buffer.
	if(m_distortionBuffer)
	{
		m_distortionBuffer->Release();
		m_distortionBuffer = 0;
	}

	// Release the second sampler state.
	if(m_sampleState2)
	{
		m_sampleState2->Release();
		m_sampleState2 = 0;
	}

	// Release the sampler state.
	if(m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	// Release the noise constant buffer.
	if(m_noiseBuffer)
	{
		m_noiseBuffer->Release();
		m_noiseBuffer = 0;
	}

	// Release the matrix constant buffer.
	if(m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	// Release the layout.
	if(m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	// Release the pixel shader.
	if(m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	// Release the vertex shader.
	if(m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

	return;
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

	return;
}


bool FireShaderClass::SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,
	D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* fireTexture, 
	ID3D11ShaderResourceView* noiseTexture, ID3D11ShaderResourceView* alphaTexture, 
	float frameTime, D3DXVECTOR3 scrollSpeeds, D3DXVECTOR3 scales, D3DXVECTOR2 distortion1, 
	D3DXVECTOR2 distortion2, D3DXVECTOR2 distortion3, float distortionScale, 
	float distortionBias)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	NoiseBufferType* dataPtr2;
	DistortionBufferType* dataPtr3;
	unsigned int bufferNumber;


	// Transpose the matrices to prepare them for the shader.
	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

	// Lock the matrix constant buffer so it can be written to.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the matrix constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the matrix constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the matrix constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the matrix constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the matrix constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	// Lock the noise constant buffer so it can be written to.
	result = deviceContext->Map(m_noiseBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the noise constant buffer.
	dataPtr2 = (NoiseBufferType*)mappedResource.pData;

	// Copy the data into the noise constant buffer.
	dataPtr2->frameTime = frameTime;
	dataPtr2->scrollSpeeds = scrollSpeeds;
	dataPtr2->scales = scales;
	dataPtr2->padding = 0.0f;

	// Unlock the noise constant buffer.
	deviceContext->Unmap(m_noiseBuffer, 0);

	// Set the position of the noise constant buffer in the vertex shader.
	bufferNumber = 1;

	// Now set the noise constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_noiseBuffer);

	// Set the three shader texture resources in the pixel shader.
	deviceContext->PSSetShaderResources(0, 1, &fireTexture);
	deviceContext->PSSetShaderResources(1, 1, &noiseTexture);
	deviceContext->PSSetShaderResources(2, 1, &alphaTexture);

	// Lock the distortion constant buffer so it can be written to.
	result = deviceContext->Map(m_distortionBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the distortion constant buffer.
	dataPtr3 = (DistortionBufferType*)mappedResource.pData;

	// Copy the data into the distortion constant buffer.
	dataPtr3->distortion1 = distortion1;
	dataPtr3->distortion2 = distortion2;
	dataPtr3->distortion3 = distortion3;
	dataPtr3->distortionScale = distortionScale;
	dataPtr3->distortionBias = distortionBias;

	// Unlock the distortion constant buffer.
	deviceContext->Unmap(m_distortionBuffer, 0);

	// Set the position of the distortion constant buffer in the pixel shader.
	bufferNumber = 0;

	// Now set the distortion constant buffer in the pixel shader with the updated values.
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_distortionBuffer);

	return true;
}


bool FireShaderClass::Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
	D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* fireTexture, 
	ID3D11ShaderResourceView* noiseTexture, ID3D11ShaderResourceView* alphaTexture, float frameTime,
	D3DXVECTOR3 scrollSpeeds, D3DXVECTOR3 scales, D3DXVECTOR2 distortion1, D3DXVECTOR2 distortion2,
	D3DXVECTOR2 distortion3, float distortionScale, float distortionBias)
{
	//test
	fireTexture = m_fireTexture->GetTexture();
	noiseTexture = m_noiseTexture->GetTexture();
	alphaTexture = m_alphaTexture->GetTexture();

	bool result;

	deviceContext->PSSetShaderResources( 0, 1, &fireTexture );

	// Set the shader parameters that it will use for rendering.
	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, fireTexture, noiseTexture, alphaTexture, 
		frameTime, scrollSpeeds, scales, distortion1, distortion2, distortion3, distortionScale, 
		distortionBias);
	if(!result)
	{
		return false;
	}
	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, indexCount);



	return true;
}
void FireShaderClass::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	//
	unsigned int stride = sizeof( VertexPos );
	unsigned int offset = 0;

	// Set the vertex input layout.
	deviceContext->IASetInputLayout(m_layout);

	//test
	deviceContext->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );
	deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	// Set the sampler states in the pixel shader.
	deviceContext->PSSetSamplers(0, 1, &m_sampleState);
	deviceContext->PSSetSamplers(1, 1, &m_sampleState2);

	// Render the triangle.
	deviceContext->Draw(indexCount, 0);
	//deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}
bool FireShaderClass::CreatVertex(ID3D11Device* device)
{
	HRESULT d3dResult;
	XMFLOAT2 m_pos = XMFLOAT2( 0.0f, 0.0f );
	float m_w=2.0f;
	float m_h=2.0f;
	VertexPos vertices[] =
	{
		{ XMFLOAT3( m_pos.x-(m_w/2), m_pos.y-(m_h/2), 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
		{ XMFLOAT3( m_pos.x-(m_w/2), m_pos.y+(m_h/2), 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
		{ XMFLOAT3( m_pos.x+(m_w/2), m_pos.y-(m_h/2), 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
		{ XMFLOAT3( m_pos.x+(m_w/2), m_pos.y+(m_h/2), 1.0f ), XMFLOAT2( 1.0f, 0.0f ) }
	};

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory( &vertexDesc, sizeof( vertexDesc ) );
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof( VertexPos ) * 4;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory( &resourceData, sizeof( resourceData ) );
	resourceData.pSysMem = vertices;

	d3dResult = device->CreateBuffer( &vertexDesc, &resourceData, &m_vertexBuffer );

	if( FAILED( d3dResult ) )
	{
		return false;
	}
	return true;
}