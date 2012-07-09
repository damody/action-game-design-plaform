#pragma once

#include <d3d11.h>
#include <D3DX11.h>
#include <D3Dcompiler.h>
#include <DxErr.h>
#include <xnamath.h>
#include <string>
#include <deque>
#include "TextGeneratorDX11.h"

#ifndef MIN_FONT_SIZE
#define MIN_FONT_SIZE 4
#endif

#ifndef MAX_FONT_SIZE
#define MAX_FONT_SIZE 36
#endif

struct CharacterUnit
{
	BYTE m_Width;
	BYTE m_Height;
	ID3D11ShaderResourceView* m_ShaderResView;
};

struct TextLineUnit
{
	BYTE m_Length;
	BYTE m_MaxHeight;
	unsigned int m_StartY;
	unsigned short int m_MessageIndex;
	CharacterUnit* m_Characters;
};

struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};

class TextRendererDX11
{
private:
	bool m_Initialized;

	int m_StartX;
	int m_StartY;
	unsigned int m_Gap;
	unsigned int m_Width;
	unsigned int m_Height;

	unsigned int m_TotalHeight;
	unsigned int m_CurrentHeightTop;
	unsigned int m_CurrentHeightBottom;
	unsigned int m_TotalMessages;
	unsigned int m_LastLineIndex;
	unsigned int m_LastLines;

	std::string m_Font;
	unsigned int m_FontWidth;
	unsigned int m_FontHeight;

	unsigned int m_MaxWidthPerLine;

	std::deque<TextLineUnit> m_TextLineShow;

	ID3D11Device* m_D3DDevice;
	ID3D11DeviceContext* m_D3DContext;
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_InputLayout;
	ID3D11SamplerState* m_Sampler;
	ID3D11Buffer* m_VertexBuffer;

	TextGeneratorDX11* m_TextGernerator;

	static bool CompileD3DShader( char* filePath, char* entry, char* shaderModel, ID3DBlob** buffer );
public:
	TextRendererDX11(ID3D11Device* device, ID3D11DeviceContext* context, std::string& font);
	~TextRendererDX11(void);
	void Append(std::wstring& str);
	void Draw();
	bool SetFont(std::string& font);
	bool SetFontSize(unsigned int width, unsigned int height);
	void AdjustCurrentHeight(int offset);
	void SetRectangle(int x, int y, unsigned short int width, unsigned short int height);
};