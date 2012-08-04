////////////////////////////////////////////////////////////////////////////////
// Filename: textureshaderclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TextureShaderClass.h"
#include <iostream>
struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};
TextureShaderClass::TextureShaderClass()
{
	m_pos = XMFLOAT2(0.0f,0.0f);
	m_w = 2.0f;m_h = 2.0f;
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_vertexBuffer = 0;
	m_sampleState = 0;
}
TextureShaderClass::TextureShaderClass(XMFLOAT2 p)
{
	m_pos = p;
	m_w = 2.0f;m_h = 2.0f;
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_vertexBuffer = 0;
	m_sampleState = 0;
}
TextureShaderClass::TextureShaderClass(XMFLOAT2 p,float w,float h)
{
	m_pos = p;
	m_w = w;m_h = h;
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_vertexBuffer = 0;
	m_sampleState = 0;
}


TextureShaderClass::TextureShaderClass(const TextureShaderClass& other)
{
}


TextureShaderClass::~TextureShaderClass()
{
}


bool TextureShaderClass::Initialize(ID3D11Device* device, WCHAR* fxFilename,HWND hwnd)
{
	bool result;


	// Initialize the vertex and pixel shaders.
	result = InitializeShader(device, fxFilename ,hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"InitializeShader Failed", fxFilename, MB_OK);
		//DXTRACE_MSG( "InitializeShader Failed" );
		return false;
	}
	result = CreatVertex(device);
	if(!result)
	{
		MessageBox(hwnd, L"CreatVertex Failed", fxFilename, MB_OK);
		//DXTRACE_MSG( "CreatVertex Failed" );
		return false;
	}

	return true;
}


void TextureShaderClass::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader();

	return;
}


bool TextureShaderClass::InitializeShader(ID3D11Device* device, WCHAR* fxFilename,HWND hwnd)
{
	ID3DBlob* vsBuffer = 0;
	ID3DBlob* psBuffer = 0;
	ID3D10Blob* errorMessage;
	HRESULT d3dResult;

	//Complie VS
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
			MessageBox(hwnd, L"Missing Shader File", L"Error", MB_OK);
		}

		return false;
	}
	//Creat VS buffer
	d3dResult = device->CreateVertexShader( vsBuffer->GetBufferPointer( ),
		vsBuffer->GetBufferSize( ), 0, &m_vertexShader );

	if( FAILED( d3dResult ) )
	{
		MessageBox(hwnd, L"Error creating the vertex shader!", L"Error", MB_OK);
		//DXTRACE_MSG( "Error creating the vertex shader!" );
		if( vsBuffer )
			vsBuffer->Release( );

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

	vsBuffer->Release( );

	if( FAILED( d3dResult ) )
	{
		MessageBox(hwnd, L"Error creating the input layout!", L"Error", MB_OK);
		//DXTRACE_MSG( "Error creating the input layout!" );
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
			MessageBox(hwnd, L"Missing Shader File", L"Error", MB_OK);
			//DXTRACE_MSG( "Missing Shader File" );
		}

		return false;
	}
	//Creat PS buffer
	d3dResult = device->CreatePixelShader( psBuffer->GetBufferPointer( ),
		psBuffer->GetBufferSize( ), 0, &m_pixelShader );

	psBuffer->Release( );

	if( FAILED( d3dResult ) )
	{
		MessageBox(hwnd, L"Error creating pixel shader!" , L"Error", MB_OK);
		//DXTRACE_MSG( "Error creating pixel shader!" );
		return false;
	}
	//Set SAMPLER_DESC
	D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory( &colorMapDesc, sizeof( colorMapDesc ) );
	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;
	//Creat SampleState
	d3dResult = device->CreateSamplerState( &colorMapDesc, &m_sampleState );

	if( FAILED( d3dResult ) )
	{
		MessageBox(hwnd, L"Failed to create color map sampler state!" , L"Error", MB_OK);
		//DXTRACE_MSG( "Failed to create color map sampler state!" );
		return false;
	}


	return true;
}


void TextureShaderClass::ShutdownShader()
{
	// Release the sampler state.
	if(m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	// Release the constant buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
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
bool TextureShaderClass::CreatVertex(ID3D11Device* device)
{
	HRESULT d3dResult;
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
void TextureShaderClass::Render(ID3D11DeviceContext* deviceContext, int indexCount, ID3D11ShaderResourceView* texture)
{
	// Set texture
	deviceContext->PSSetShaderResources( 0, 1, &texture );
	RenderShader(deviceContext, indexCount);
}
void TextureShaderClass::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	unsigned int stride = sizeof( VertexPos );
	unsigned int offset = 0;
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(m_layout);
	deviceContext->IASetVertexBuffers( 0, 1, &m_vertexBuffer, &stride, &offset );
	deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	// Set the sampler state in the pixel shader.
	deviceContext->PSSetSamplers(0, 1, &m_sampleState);

	

	// Render the triangle.
	deviceContext->Draw(indexCount, 0);

	return;
}

void TextureShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, WCHAR* shaderFilename,HWND hwnd)
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
	//DXTRACE_MSG("Error compiling shader.  Check shader-error.txt for message.");

	return;
}