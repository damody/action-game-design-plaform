#include "StdGame.h"
#include "EffectShaderClass.h"
#include "global.h"
#include <iostream>

EffectShaderClass::EffectShaderClass(): m_device( 0 ), m_deviceContext( 0 ), m_layout( 0 ), m_Buffer( 0 ), m_PTech( 0 ), m_Effect( 0 )
{
}
bool EffectShaderClass::Initialize( ID3D11Device* device, ID3D11DeviceContext* deviceContext, WCHAR* fxFilename, HWND hwnd )
{
	ID3D10Blob* pCode = 0;
	ID3D10Blob* errorMessage = 0;
	HRESULT d3dResult = 0;
	m_device = device;
	m_deviceContext = deviceContext;
	//Compile fx file
	d3dResult = D3DX11CompileFromFile( fxFilename, NULL, NULL, NULL,
	                                   "fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &errorMessage, NULL );

	if ( FAILED( d3dResult ) )
	{
		// If the shader failed to compile it should have writen something to the error message.
		if ( errorMessage )
		{
			OutputShaderErrorMessage( errorMessage, fxFilename, hwnd );
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox( hwnd, L"Missing Shader File", fxFilename, MB_OK );
		}

		return false;
	}

	//Create Effect
	d3dResult = D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, device, &m_Effect );

	if ( FAILED( d3dResult ) )
	{
		MessageBox( hwnd, L"Failed to CreateEffectFromMemory", fxFilename, MB_OK );
		return false;
	}

	//Create input layout
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION",	0, DXGI_FORMAT_R32G32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"PICPOS",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	unsigned int totalLayoutElements = ARRAYSIZE( vertexDesc );
	D3DX11_PASS_DESC PassDesc;
	m_PTech = m_Effect->GetTechniqueByName( "PointTech" );
	m_PTech->GetPassByIndex( 0 )->GetDesc( &PassDesc );
	d3dResult = device->CreateInputLayout(
	                    vertexDesc, totalLayoutElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &m_layout );

	if ( FAILED( d3dResult ) )
	{
		MessageBox( hwnd, L"Failed to CreateInputLayout", fxFilename, MB_OK );
		return false;
	}

	//Set variable by name
	SetEffectVariableByName();
	//Create Texture
	CreateTexture();
	return true;
}

void EffectShaderClass::OutputShaderErrorMessage( ID3D10Blob* errorMessage, WCHAR* shaderFilename, HWND hwnd )
{
	char* compileErrors;
	unsigned long bufferSize, i;
	std::ofstream fout;
	// Get a pointer to the error message text buffer.
	compileErrors = ( char* )( errorMessage->GetBufferPointer() );
	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();
	// Open a file to write the error message to.
	fout.open( "shader-error.txt" );

	// Write out the error message.
	for ( i = 0; i < bufferSize; i++ )
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();
	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;
	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox( hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK );
}



bool EffectShaderClass::CreatVertex( EffectDatas::iterator begin, EffectDatas::iterator end )
{
	if ( begin == end )
	{
		return false;
	}

	m_vertices.clear();
	m_dvg.clear();
	int vertexCount = 0, count = 0;

	for ( EffectDatas::iterator it = begin; it != end; )
	{
		DrawVertexGroup dvg = {};
		dvg.texture = g_TextureManager.GetTexture( it->m_TextureID );
		vertexCount = 0;
		dvg.StartVertexLocation = count;

		do
		{
			Vertex temp = {};
			temp.picpos = it->m_PicPos;
			temp.position = it->m_Pos;
			//save vertex points
			m_vertices.push_back( temp );
			it++;
			++vertexCount;
			++count;
		}
		while ( it != end && dvg.texture == g_TextureManager.GetTexture( it->m_TextureID ) );

		dvg.VertexCount = vertexCount;
		//save dvg
		m_dvg.push_back( dvg );
	}

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.ByteWidth = ( UINT )( sizeof( Vertex ) * m_vertices.size() );
	bufferDesc.StructureByteStride = sizeof( Vertex );
	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory( &resourceData, sizeof( resourceData ) );
	resourceData.pSysMem = &m_vertices[0];
	ReleaseCOM( m_Buffer );
	m_device->CreateBuffer( &bufferDesc, &resourceData, &m_Buffer );
	return true;
}