#include "TextRendererDX11.h"

bool TextRendererDX11::CompileD3DShader( char* filePath, char* entry, char* shaderModel, ID3DBlob** buffer )
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* errorBuffer = 0;
	HRESULT result;

	result = D3DX11CompileFromFile( filePath, 0, 0, entry, shaderModel,
		shaderFlags, 0, 0, buffer, &errorBuffer, 0 );

	if( FAILED( result ) )
	{
		if( errorBuffer != 0 )
		{
			OutputDebugStringA( ( char* )errorBuffer->GetBufferPointer( ) );
			errorBuffer->Release( );
		}

		return false;
	}

	if( errorBuffer != 0 )
		errorBuffer->Release( );

	return true;
}

TextRendererDX11::TextRendererDX11(ID3D11Device* device, ID3D11DeviceContext* context, std::string& font)
{
	m_Initialized = false;

	m_D3DDevice = device;
	m_D3DContext = context;

	m_Font = font;
	m_FontWidth = 12;
	m_FontWidth = 12;

	m_TotalHeight = 0;
	m_CurrentHeightTop = 0;
	m_CurrentHeightBottom = 100;
	m_TotalMessages = 0;
	m_LastLineIndex = 0;
	m_LastLines = 0;
	m_StartX = 0;
	m_StartY = 0;
	m_Gap = 2;
	m_Width = 100;
	m_Height = 100;
	m_MaxWidthPerLine = 100;

	m_TextGernerator = new TextGeneratorDX11(device, font);

	ID3DBlob* vsBuffer = 0;

	bool compileResult = CompileD3DShader( "TextureMap.fx", "VS_Main", "vs_4_0", &vsBuffer );

	if( compileResult == false )
	{
		MessageBox( 0, L"Error loading vertex shader!", "Compile Error", MB_OK );
		return;
	}

	HRESULT d3dResult;

	d3dResult = m_D3DDevice->CreateVertexShader( vsBuffer->GetBufferPointer( ),
		vsBuffer->GetBufferSize( ), 0, &m_VertexShader );

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( "Failed to create vertex shader!" );
		if( vsBuffer )
			vsBuffer->Release( );

		return;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	unsigned int totalLayoutElements = ARRAYSIZE( layout );

	d3dResult = m_D3DDevice->CreateInputLayout( layout, totalLayoutElements,
		vsBuffer->GetBufferPointer( ), vsBuffer->GetBufferSize( ), &m_InputLayout );

	vsBuffer->Release( );

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( "Failed to create input layout!" );
		return;
	}

	ID3DBlob* psBuffer = 0;

	compileResult = CompileD3DShader( "TextureMap.fx", "PS_Main", "ps_4_0", &psBuffer );

	if( compileResult == false )
	{
		MessageBox( 0, L"Error loading pixel shader!", "Compile Error", MB_OK );
		return;
	}

	d3dResult = m_D3DDevice->CreatePixelShader( psBuffer->GetBufferPointer( ),
		psBuffer->GetBufferSize( ), 0, &m_PixelShader );

	psBuffer->Release( );

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( "Failed to create pixel shader!" );
		return;
	}

	D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory( &colorMapDesc, sizeof( colorMapDesc ) );
	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	d3dResult = m_D3DDevice->CreateSamplerState( &colorMapDesc, &m_Sampler );

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( "Failed to create color map sampler state!" );
		return;
	}

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory( &vertexDesc, sizeof( vertexDesc ) );
	vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//vertexDesc.ByteWidth = sizeof( VertexPos ) * (m_MaxWidthPerLine / (MIN_FONT_SIZE + m_Gap) + 1) * 6;
	vertexDesc.ByteWidth = sizeof(VertexPos) * 6;

	d3dResult = m_D3DDevice->CreateBuffer( &vertexDesc, 0, &m_VertexBuffer );

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( "Failed to create vertex buffer!" );
		return;
	}

	m_Initialized = true;
}


TextRendererDX11::~TextRendererDX11(void)
{
	for(unsigned int i=0;i<m_TextLineShow.size();i++)
	{
		for(unsigned int j=0;j<m_TextLineShow.at(i).m_Length;j++)
		{
			m_TextLineShow.at(i).m_Characters[i].m_ShaderResView->Release();
		}
		delete[] m_TextLineShow.at(i).m_Characters;
	}

/*
	for(unsigned int i=0;i<m_TextLineHide.size();i++)
	{
		for(unsigned int j=0;j<m_TextLineHide.at(i).m_Length;j++)
		{
			m_TextLineHide.at(i).m_Characters[i].m_ShaderResView->Release();
		}
		delete[] m_TextLineHide.at(i).m_Characters;
	}*/

	m_VertexBuffer->Release();
	m_Sampler->Release();
	m_PixelShader->Release();
	m_InputLayout->Release();
	m_VertexShader->Release();
}

void TextRendererDX11::Append( std::wstring& str )
{
	if(str.length() > 0)
	{
		std::wstring temp = str;
		std::wstring text;
		int maxLength = m_MaxWidthPerLine / (m_FontWidth);
		int currentLength;

		while(temp.length() > 0)
		{
			currentLength = 0;
			text.clear();
			while(currentLength < maxLength && temp.length() > 0)
			{
				text.append(temp, 0, 1);
				temp.erase(temp.front());
				currentLength++;
			}

			m_TextGernerator->WriteBegin();
			m_TextGernerator->Write(text);

			ID3D11ShaderResourceView** shaderResView;
			int size;
			shaderResView = m_TextGernerator->WriteEnd(&size);

			if(shaderResView != 0 && size == currentLength)
			{
				TextLineUnit line;
				line.m_MessageIndex = m_TotalMessages;
				line.m_Length = size;
				line.m_MaxHeight = m_FontHeight;
				line.m_Characters = new CharacterUnit[size];
				line.m_StartY = m_TotalHeight;
				m_TotalHeight += line.m_MaxHeight;
				for(unsigned int i=0;i<size;i++)
				{
					line.m_Characters[i].m_Height = m_FontHeight;
					line.m_Characters[i].m_Width = m_FontWidth;
					line.m_Characters[i].m_ShaderResView = shaderResView[i];
				}

				m_TextLineShow.push_back(line);

				m_CurrentHeightBottom = line.m_StartY + line.m_MaxHeight;
				if(m_CurrentHeightBottom < m_Height)
					m_CurrentHeightBottom = m_Height;
				m_CurrentHeightTop = m_CurrentHeightBottom - m_Height;
			}
		}
	}

	m_TotalMessages++;
}


void TextRendererDX11::Draw()
{
	unsigned int stride = sizeof( VertexPos );
	unsigned int offset = 0;

	m_D3DContext->IASetInputLayout( m_InputLayout );
	m_D3DContext->IASetVertexBuffers( 0, 1, &m_VertexBuffer, &stride, &offset );
	m_D3DContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	m_D3DContext->VSSetShader( m_VertexShader, 0, 0 );
	m_D3DContext->PSSetShader( m_PixelShader, 0, 0 );
	m_D3DContext->PSSetSamplers(0, 1, &m_Sampler);

	if(m_LastLines > 0)
	{
		for(unsigned int i=0;i<m_LastLines;i++)
		{
			TextLineUnit& line = m_TextLineShow[m_LastLineIndex + i];

			for(unsigned int j=0;j<line.m_Length;j++)
			{
				m_D3DContext->PSSetShaderResources(0, 1, &line.m_Characters[j].m_ShaderResView);
				D3D11_MAPPED_SUBRESOURCE mapResource;
				HRESULT d3dResult = m_D3DContext->Map( m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource );

				VertexPos *spritePtr = ( VertexPos* )mapResource.pData;

				spritePtr[0].pos = XMFLOAT3( 1.0f,   1.0f, 1.0f );
				spritePtr[1].pos = XMFLOAT3( 1.0f,   0.0f,   1.0f );
				spritePtr[2].pos = XMFLOAT3( 0.0f, 0.0f,   1.0f );
				spritePtr[3].pos = XMFLOAT3( 0.0f, 0.0f,   1.0f );
				spritePtr[4].pos = XMFLOAT3( 0.0f, 1.0f, 1.0f );
				spritePtr[5].pos = XMFLOAT3( 1.0f,   1.0f, 1.0f );

				spritePtr[0].tex0 = XMFLOAT2( 1.0f, 0.0f );
				spritePtr[1].tex0 = XMFLOAT2( 1.0f, 1.0f );
				spritePtr[2].tex0 = XMFLOAT2( 0.0f, 1.0f );
				spritePtr[3].tex0 = XMFLOAT2( 0.0f, 1.0f );
				spritePtr[4].tex0 = XMFLOAT2( 0.0f, 0.0f );
				spritePtr[5].tex0 = XMFLOAT2( 1.0f, 0.0f );

				m_D3DContext->Unmap( m_VertexBuffer, 0 );
				m_D3DContext->Draw( 6, 0 );
			}
		}
	}
	else
	{
		unsigned int currentHeight = 0;
		for(unsigned int i=0;i<m_TextLineShow.size();i++)
		{
			currentHeight = m_TextLineShow[i].m_StartY + m_TextLineShow[i].m_MaxHeight;
			if(currentHeight > m_CurrentHeightTop)
			{
				m_LastLineIndex = i;
			}
		}
		for(unsigned int i=m_LastLineIndex;i<m_TextLineShow.size();i++)
		{
			currentHeight = m_TextLineShow[i].m_StartY;
			if(currentHeight < m_CurrentHeightTop)
			{
				m_LastLines++;
			}
			else
			{
				break;
			}
		}

		for(unsigned int i=0;i<m_LastLines;i++)
		{
			TextLineUnit& line = m_TextLineShow[m_LastLineIndex + i];

			for(unsigned int j=0;j<line.m_Length;j++)
			{
				m_D3DContext->PSSetShaderResources(0, 1, &line.m_Characters[j].m_ShaderResView);
				D3D11_MAPPED_SUBRESOURCE mapResource;
				HRESULT d3dResult = m_D3DContext->Map( m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource );

				VertexPos *spritePtr = ( VertexPos* )mapResource.pData;

				spritePtr[0].pos = XMFLOAT3( 1.0f,   1.0f, 1.0f );
				spritePtr[1].pos = XMFLOAT3( 1.0f,   0.0f,   1.0f );
				spritePtr[2].pos = XMFLOAT3( 0.0f, 0.0f,   1.0f );
				spritePtr[3].pos = XMFLOAT3( 0.0f, 0.0f,   1.0f );
				spritePtr[4].pos = XMFLOAT3( 0.0f, 1.0f, 1.0f );
				spritePtr[5].pos = XMFLOAT3( 1.0f,   1.0f, 1.0f );

				spritePtr[0].tex0 = XMFLOAT2( 1.0f, 0.0f );
				spritePtr[1].tex0 = XMFLOAT2( 1.0f, 1.0f );
				spritePtr[2].tex0 = XMFLOAT2( 0.0f, 1.0f );
				spritePtr[3].tex0 = XMFLOAT2( 0.0f, 1.0f );
				spritePtr[4].tex0 = XMFLOAT2( 0.0f, 0.0f );
				spritePtr[5].tex0 = XMFLOAT2( 1.0f, 0.0f );

				m_D3DContext->Unmap( m_VertexBuffer, 0 );
				m_D3DContext->Draw( 6, 0 );
			}
		}
	}
}

bool TextRendererDX11::SetFont( std::string& font )
{
	if(m_TextGernerator->SetFont(font))
	{
		m_Font = font;
		return true;
	}
	
	return false;
}

bool TextRendererDX11::SetFontSize( unsigned int width, unsigned int height )
{
	if(width+m_Gap > MAX_FONT_SIZE || width+m_Gap < MIN_FONT_SIZE || height+m_Gap > MAX_FONT_SIZE || height+m_Gap < MIN_FONT_SIZE)
		return false;

	m_FontWidth = width+m_Gap;
	m_FontHeight = height+m_Gap;
	return true;
}

void TextRendererDX11::AdjustCurrentHeight( int offset )
{
	long long temp = m_CurrentHeightTop + offset;
	if(temp < 0)
	{
		m_CurrentHeightTop = 0;
		m_CurrentHeightBottom = m_Height;
	}
	else
	{
		m_CurrentHeightTop += offset;
		m_CurrentHeightBottom += offset;
	}

	m_LastLineIndex = 0;
	m_LastLines = 0;
}

void TextRendererDX11::SetRectangle( int x, int y, unsigned short int width, unsigned short int height )
{
	this->m_StartX = x;
	this->m_StartY = y;
	this->m_Width = width;
	this->m_Height = height;
}