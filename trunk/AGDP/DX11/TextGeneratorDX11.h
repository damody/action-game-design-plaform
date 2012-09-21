#pragma once

#include <string>
#include <d3d11.h>
#include <DxErr.h>
#include <auto_link_freetype.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>
#include "DX11/TextureManager.h"
#include "TextLetter.h"

const std::string DEFAULT_FONT = "Media\\unifont.ttf";

typedef struct CharBitmap_
{
	int             x;
	int             y;
	unsigned int    width;
	unsigned int    height;
	unsigned int    pitch;
	unsigned char*  data;
} CharBitmap;

enum RenderFlag
{
        BEGIN,
        END
};

class TextGeneratorDX11
{
private:
	bool m_Initialized;
	FT_Face m_Face;
	FT_Library m_Library;
	std::string m_Font;
	std::wstring m_WString;
	int m_Width;
	int m_Height;
	float m_ForeColor[3];
	float m_BackColor[3];
	float m_ForeAlpha;
	float m_BackAlpha;
	RenderFlag m_RenderFlag;

	bool rasters( const wchar_t texts, CharBitmap& bitmap );
public:

	TextGeneratorDX11();
	~TextGeneratorDX11( void );

	void Initialize();

	bool SetFont( std::string& font );
	bool SetFontSize( int width, int height );
	void SetForeColor( BYTE r, BYTE g, BYTE b );
	void SetBackColor( BYTE r, BYTE g, BYTE b );
	void SetForeAlpha( BYTE alpha );
	void SetBackAlpha( BYTE alpha );
	void WriteBegin();
	TextLetters WriteEnd();
	void Write( std::wstring& str );
};

