#pragma once

#include <string>
#include <d3d11.h>
#include <DxErr.h>
#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct CharBitmap_ {
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
	ID3D11Device* m_Device;
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

	bool rasters(const wchar_t texts, CharBitmap& bitmap);
public:

	TextGeneratorDX11(ID3D11Device* device, std::string& font);
	~TextGeneratorDX11(void);

	bool SetFont(std::string& font);
	bool SetFontSize(int& width, int& height);
	bool SetForeColor(BYTE r, BYTE g, BYTE b);
	bool SetBackColor(BYTE r, BYTE g, BYTE b);
	bool SetForeAlpha(BYTE alpha);
	bool SetBackAlpha(BYTE alpha);
	void WriteBegin();
	ID3D11ShaderResourceView** WriteEnd(int* size);
	void Write(std::wstring& str);
};

