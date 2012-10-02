#include "StdGame.h"
#include "EffectShaderClass.h"
#include "global.h"
#include "ConvStr.h"
#include <iostream>

EffectShaderClass::EffectShaderClass(): m_device( 0 ), m_deviceContext( 0 ), m_layout( 0 ), m_Buffer( 0 ),
	m_PTech( 0 ), m_Effect( 0 ),
	m_frameTime( 0 ), m_alphaTexture( 0 )
{
}

bool EffectShaderClass::Initialize( WCHAR* luaFileName, ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd )
{
	bool result;
	//Get D3DDevice pointer
	m_device = device;
	m_deviceContext = deviceContext;
	//Get LuaCell
	m_LuaCell = LuaCell_Sptr( new LuaCell );
	result = m_LuaCell->InputLuaFile( luaFileName );

	if ( !result )
	{
		MessageBox( hwnd, L"Missing Lua File", luaFileName, MB_OK );
		return false;
	}

	//Get shader file name
	result = m_LuaCell->HasValue( "ShaderPath" );

	if ( !result )
	{
		MessageBox( hwnd, L"This Lua file's content didn't have ShaderPath", luaFileName, MB_OK );
		return false;
	}

	m_ShaderPath = m_LuaCell->GetLua<const char*>( "ShaderPath" );
	//Get texture all names
	result = m_LuaCell->HasValue( "TexturePath" );

	if ( !result )
	{
		MessageBox( hwnd, L"This Lua file's content didn't have TexturePath", luaFileName, MB_OK );
		return false;
	}

	m_LuaTextureNames = m_LuaCell->GetLuaTableKeys( "TexturePath" );
	//Get shader parameter all names
	result = m_LuaCell->HasValue( "ShaderParameters" );

	if ( !result )
	{
		MessageBox( hwnd, L"This Lua file's content didn't have ShaderParameters", luaFileName, MB_OK );
		return false;
	}

	m_LuaShaderParameterNames = m_LuaCell->GetLuaTableKeys( "ShaderParameters" );
	//Initialize shader
	result = InitShader( ConvStr::GetWstr( m_ShaderPath.c_str() ).c_str() , hwnd );

	if ( !result )
	{
		MessageBox( hwnd, L"Init shader fail .Please check your shader file content", luaFileName, MB_OK );
		return false;
	}

	//Set variable by name
	result = SetEffectVariableByName();

	if ( !result )
	{
		MessageBox( hwnd, L"SetEffectVariableByName failed .Please check your lua file content", luaFileName, MB_OK );
		return false;
	}

	//Create Texture
	result = CreateTexture();

	if ( !result )
	{
		MessageBox( hwnd, L"Create texture failed .Please check your lua file content.\nMay lua file's texturePath was wrong?", luaFileName, MB_OK );
		return false;
	}

	//Set shader parameters
	SetShaderParameters();
	return true;
}

bool EffectShaderClass::InitShader( const wchar_t* fxFilename, HWND hwnd )
{
	ID3D10Blob* pCode = 0;
	ID3D10Blob* errorMessage = 0;
	HRESULT d3dResult = 0;
	//Compile shader file
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
	d3dResult = D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_device, &m_Effect );

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
	d3dResult = m_device->CreateInputLayout(
	                    vertexDesc, totalLayoutElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &m_layout );

	if ( FAILED( d3dResult ) )
	{
		MessageBox( hwnd, L"Failed to CreateInputLayout", fxFilename, MB_OK );
		return false;
	}

	return true;
}

void EffectShaderClass::OutputShaderErrorMessage( ID3D10Blob* errorMessage, const wchar_t* shaderFilename, HWND hwnd )
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

bool EffectShaderClass::SetEffectVariableByName()
{
	bool result;
	EffectVariable temp;
	m_alphaTexture = m_Effect->GetVariableByName( "alphaTexture" )->AsShaderResource();
	m_frameTime = m_Effect->GetVariableByName( "frameTime" )->AsScalar();

	for (unsigned int i = 0; i < m_LuaTextureNames.size(); i++ )
	{
		m_EffectShaderResource[ m_LuaTextureNames[i] ] =
		        m_Effect->GetVariableByName( m_LuaTextureNames[i].c_str() )->AsShaderResource();
	}

	for (unsigned int i = 0; i < m_LuaShaderParameterNames.size(); i++ )
	{
		std::string variableType;
		//Check value
		result = m_LuaCell->HasValue( "ShaderParameters/%s/type" , m_LuaShaderParameterNames[i].c_str() );

		if ( !result )
		{
			return false;
		}

		//Get value
		variableType = m_LuaCell->GetLua<const char*>( "ShaderParameters/%s/type" , m_LuaShaderParameterNames[i].c_str() );
		temp.variableType = variableType;
		temp.m_EffectVariable = m_Effect->GetVariableByName( m_LuaShaderParameterNames[i].c_str() );
		m_EffectVariable[ m_LuaShaderParameterNames[i] ] = temp;
	}

	return true;
}

bool EffectShaderClass::SetShaderParameters()
{
	for ( std::map<std::string, EffectVariable>::iterator iter = m_EffectVariable.begin(); iter != m_EffectVariable.end(); ++iter )
	{
		bool result;

		if ( iter->second.variableType == "float" )
		{
			float temp;
			//Check value
			result = m_LuaCell->HasValue( "ShaderParameters/%s/x" , iter->first.c_str() );

			if ( !result )
			{
				return false;
			}

			//Get value
			temp = ( float ) m_LuaCell->GetLua<double>( "ShaderParameters/%s/x" , iter->first.c_str() );
			iter->second.m_EffectVariable->SetRawValue( &temp, 0, sizeof( float ) * 1 );
		}
		else if ( iter->second.variableType == "float2" )
		{
			D3DXVECTOR2 temp;
			//Check value
			result = m_LuaCell->HasValue( "ShaderParameters/%s/x" , iter->first.c_str() );
			result &= m_LuaCell->HasValue( "ShaderParameters/%s/y" , iter->first.c_str() );

			if ( !result )
			{
				return false;
			}

			//Get value
			temp[0] = ( float ) m_LuaCell->GetLua<double>( "ShaderParameters/%s/x" , iter->first.c_str() );
			temp[1] = ( float ) m_LuaCell->GetLua<double>( "ShaderParameters/%s/y" , iter->first.c_str() );
			iter->second.m_EffectVariable->SetRawValue( temp, 0, sizeof( float ) * 2 );
		}
		else if ( iter->second.variableType == "float3" )
		{
			D3DXVECTOR3 temp;
			//Check value
			result = m_LuaCell->HasValue( "ShaderParameters/%s/x" , iter->first.c_str() );
			result &= m_LuaCell->HasValue( "ShaderParameters/%s/y" , iter->first.c_str() );
			result &= m_LuaCell->HasValue( "ShaderParameters/%s/z" , iter->first.c_str() );

			if ( !result )
			{
				return false;
			}

			//Get value
			temp[0] = ( float ) m_LuaCell->GetLua<double>( "ShaderParameters/%s/x" , iter->first.c_str() );
			temp[1] = ( float ) m_LuaCell->GetLua<double>( "ShaderParameters/%s/y" , iter->first.c_str() );
			temp[2] = ( float ) m_LuaCell->GetLua<double>( "ShaderParameters/%s/z" , iter->first.c_str() );
			iter->second.m_EffectVariable->SetRawValue( temp, 0, sizeof( float ) * 3 );
		}
	}
}
void EffectShaderClass::Update( float dt )
{
	m_frameTime->SetFloat( dt );
}
void EffectShaderClass::Render()
{
	UINT offset = 0;
	UINT stride2 = sizeof( Vertex );
	m_deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );
	m_deviceContext->IASetInputLayout( m_layout );
	m_deviceContext->IASetVertexBuffers( 0, 1, &m_Buffer, &stride2, &offset );
	m_PTech->GetPassByIndex( 0 )->Apply( 0, m_deviceContext );

	for ( DrawVertexGroups::iterator it = m_dvg.begin(); it != m_dvg.end(); ++it )
	{
		m_alphaTexture->SetResource( it->texture->texture );
		m_PTech->GetPassByIndex( 0 )->Apply( 0, m_deviceContext );
		m_deviceContext->Draw( it->VertexCount, it->StartVertexLocation );
	}
}
bool EffectShaderClass::CreateTexture()
{
	for ( std::map<std::string, ID3DX11EffectShaderResourceVariable*>::iterator iter = m_EffectShaderResource.begin();
	                iter != m_EffectShaderResource.end();
	                ++iter )
	{
		bool result;
		std::string texturePath;

		if ( m_EffectShaderResource[ iter->first ] == NULL )
		{
			//error
			return false;
		}

		result = m_LuaCell->HasValue( "TexturePath/%s" , iter->first.c_str() );

		if ( !result )
		{
			//error
			return false;
		}

		texturePath = m_LuaCell->GetLua<const char*>( "TexturePath/%s" , iter->first.c_str() );
		m_Textures.push_back( Texture_Sptr( new Texture( texturePath ) ) );
		m_EffectShaderResource[ iter->first ]->SetResource( m_Textures[ m_Textures.size() - 1 ]->texture );
	}

	return true;
}