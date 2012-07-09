#include "TextGeneratorDX11.h"


TextGeneratorDX11::TextGeneratorDX11(ID3D11Device* device, std::string& font)
{
	m_Initialized = false;
	m_Device = device;

	if (FT_Init_FreeType(&m_Library))
	{
		std::runtime_error("Freetype2: Init library error.");
	}

	if(FT_New_Face(m_Library, font.c_str(), 0, &m_Face))
	{
		FT_Done_FreeType(m_Library);
		std::runtime_error("Freetype2: New face error.");
	}

	int m_Width = 1024;
	int m_Height = 1024;
	if(FT_Set_Pixel_Sizes(m_Face, m_Width, m_Height)) {
		FT_Done_Face(m_Face);
		FT_Done_FreeType(m_Library);
		std::runtime_error("Freetype2: Set pixel size error.");
	}

	FT_Select_Charmap(m_Face, FT_ENCODING_UNICODE);

	m_Font = std::string(font);
	m_WString = L"";
	m_RenderFlag = END;

	m_ForeColor[0] = 0.0f;
	m_ForeColor[1] = 0.0f;
	m_ForeColor[2] = 0.0f;
	m_ForeAlpha = 1.0f;

	m_BackColor[0] = 1.0f;
	m_BackColor[1] = 1.0f;
	m_BackColor[2] = 1.0f;
	m_BackAlpha = 0.0f;

	m_Initialized = true;
}


TextGeneratorDX11::~TextGeneratorDX11(void)
{
	FT_Done_Face(m_Face);
	FT_Done_FreeType(m_Library);
}

bool TextGeneratorDX11::SetFont( std::string& font )
{
	std::string preFont = m_Font;

	FT_Done_Face(m_Face);
	if(FT_New_Face(m_Library, font.c_str(), 0, &m_Face))
	{
		FT_New_Face(m_Library, preFont.c_str(), 0, &m_Face);
		FT_Set_Pixel_Sizes(m_Face, m_Width, m_Height);
		FT_Select_Charmap(m_Face, FT_ENCODING_UNICODE);
		std::runtime_error("Freetype2: New face error.");
		return false;
	}

	FT_Set_Pixel_Sizes(m_Face, m_Width, m_Height);
	FT_Select_Charmap(m_Face, FT_ENCODING_UNICODE);
	m_Font = std::string(font);
	return true;
}

bool TextGeneratorDX11::SetFontSize( int& width, int& height )
{
	if(FT_Set_Pixel_Sizes(m_Face, width, height))
	{
		std::runtime_error("Freetype2: Set pixel size error.");
		return false;
	}

	this->m_Width = width;
	this->m_Height = height;
	return true;
}

bool TextGeneratorDX11::SetForeColor( BYTE r, BYTE g, BYTE b )
{
	m_ForeColor[0] = r / 255.0f;
	m_ForeColor[1] = g / 255.0f;
	m_ForeColor[2] = b / 255.0f;
}

bool TextGeneratorDX11::SetBackColor( BYTE r, BYTE g, BYTE b )
{
	m_BackColor[0] = r / 255.0f;
	m_BackColor[1] = g / 255.0f;
	m_BackColor[2] = b / 255.0f;
}

bool TextGeneratorDX11::SetForeAlpha(BYTE alpha)
{
	m_ForeAlpha = alpha / 255.0f;
}

bool TextGeneratorDX11::SetBackAlpha(BYTE alpha)
{
	m_BackAlpha = alpha / 255.0f;
}

void TextGeneratorDX11::WriteBegin()
{
	if(m_RenderFlag == END)
		m_RenderFlag = BEGIN;
}

ID3D11ShaderResourceView** TextGeneratorDX11::WriteEnd(int* size)
{
	if(m_RenderFlag != BEGIN)
	{
		*size = 0;
		return 0;
	}

	if(m_WString.length() == 0)
	{
		m_RenderFlag = END;
		*size = 0;
		return 0;
	}

	float* characterImages = new float[m_WString.length()];
	ID3D11ShaderResourceView** shaderResViews = new ID3D11ShaderResourceView*[m_WString.length()];
	CharBitmap bitmap;
	D3D11_TEXTURE2D_DESC texDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC srDesc;
	D3D11_SUBRESOURCE_DATA sSubData;

	ZeroMemory( &texDesc, sizeof( texDesc ) );
	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	srDesc.Format = texDesc.Format;
	srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srDesc.Texture2D.MostDetailedMip = 0;
	srDesc.Texture2D.MipLevels = 1;
	
	for(int n=0;n<m_WString.length();n++)
	{
		rasters(m_WString[n], bitmap);

		characterImages = new float[bitmap.width * bitmap.height*4];

		texDesc.Width = bitmap.width;
		texDesc.Height = bitmap.height;

		sSubData.SysMemPitch = (UINT)(bitmap.width*4*4);
		sSubData.SysMemSlicePitch = (UINT)(bitmap.width*bitmap.height*4*4);

		sSubData.pSysMem = characterImages;

		for(int j=0; j<bitmap.height; j++) {
			for(int i=0; i<bitmap.pitch; i++) {
				for(int k=7; k>=0; k--){
					if(7-k+i*8 == bitmap.width)
						break;

					int offset = (j*bitmap.width + i*8 + 7 - k)*4;
					if((bitmap.data[i+j*bitmap.pitch] & 0x1<<k))
					{
						characterImages[offset] = m_ForeColor[0];
						characterImages[offset+1] = m_ForeColor[1];
						characterImages[offset+2] = m_ForeColor[2];
						characterImages[offset+3] = m_ForeAlpha;
					}
					else
					{
						characterImages[offset] = m_BackColor[0];
						characterImages[offset+1] = m_BackColor[1];
						characterImages[offset+2] = m_BackColor[2];
						characterImages[offset+3] = m_BackAlpha;
					}
				}
			}
		}

		ID3D11Texture2D* pTexture;
		ID3D11ShaderResourceView* pShaderResView;
		HRESULT d3dResult = m_Device->CreateTexture2D(&texDesc, &sSubData, &pTexture);

		if(FAILED(d3dResult))
		{
			DXTRACE_MSG( "Freetype2: Failed to create texture2D!" );
			return 0;
		}

		d3dResult = m_Device->CreateShaderResourceView(pTexture, &srDesc, &pShaderResView);

		if(FAILED(d3dResult))
		{
			DXTRACE_MSG( "Freetype2: Failed to create ShaderResourceView!" );
			return 0;
		}

		delete[] characterImages;
		delete[] bitmap.data;
		shaderResViews[n] = pShaderResView;
	}

	*size = m_WString.length();
	m_WString.clear();
	m_RenderFlag = END;
	return shaderResViews;
}

void TextGeneratorDX11::Write( std::wstring& str )
{
	m_WString.append(str);
}

bool TextGeneratorDX11::rasters( const wchar_t texts, CharBitmap& bitmap )
{
	unsigned int ucode = texts;
	FT_UInt glyph_index = FT_Get_Char_Index(m_Face, ucode);
	if(!glyph_index) {
		return false;
	}

	if (FT_Load_Glyph(m_Face, glyph_index, FT_LOAD_DEFAULT)) {
		return false;
	}
	if (m_Face->glyph->format != FT_GLYPH_FORMAT_BITMAP) {
		if (FT_Render_Glyph(m_Face->glyph, FT_RENDER_MODE_MONO)) {
			return false;
		}
	}

	CharBitmap font = {    m_Face->glyph->bitmap_left,
		m_Face->glyph->bitmap_top - m_Face->glyph->bitmap.rows,
		m_Face->glyph->bitmap.width,
		m_Face->glyph->bitmap.rows,
		m_Face->glyph->bitmap.pitch,
		m_Face->glyph->bitmap.buffer
	};

	unsigned char *buffer;

	if((m_Face->glyph->bitmap.width + 0.0f) / m_Face->glyph->bitmap.pitch > 1.0f)
	{
		buffer = static_cast<unsigned char*>(calloc((m_Face->glyph->bitmap.pitch+1)*m_Face->glyph->bitmap.rows, sizeof(unsigned char)));
		memcpy(buffer, m_Face->glyph->bitmap.buffer, (m_Face->glyph->bitmap.pitch+1)*m_Face->glyph->bitmap.rows*sizeof(unsigned char));
	}
	else
	{
		buffer = static_cast<unsigned char*>(calloc(m_Face->glyph->bitmap.pitch*m_Face->glyph->bitmap.rows, sizeof(unsigned char)));
		memcpy(buffer, m_Face->glyph->bitmap.buffer, m_Face->glyph->bitmap.pitch*m_Face->glyph->bitmap.rows*sizeof(unsigned char));
	}

	font.data = buffer;
	bitmap = font;

	return true;
}
