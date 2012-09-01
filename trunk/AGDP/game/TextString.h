#pragma once

#include <iostream>
#include <string>
#include "DX11/Vertex.h"
#include "DX11/TextureManager.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "DX11/TextLetter.h"
 
struct Composition
{
	enum e{
		LEFT,   //¸m¥ª
		CENTER, //¸m¤¤
		RIGHT   //¸m¥k
	};
};

class TextString{
private:
	const float OFFSET;
	std::wstring	m_Str;
	
	float		m_Lenght;

	Composition::e  m_Composition;

	Vector3		m_Position;
	float		m_Size; 
	bool		m_OnGround;
	Vector3		m_ForeColor;
	Vector3		m_BackColor;
	float		m_BackAlpha;
	
	void lenght();
public:
	TextString();
	~TextString();
	TextString(const std::wstring& str);

	TextLetters     m_TextLetters;
	const std::wstring& w_str();

	void buildPoint();
	TextVerteices		m_TexVerteices;
	DrawVertexGroups	m_DrawVertexGroups;
	
	void SetSize(float size);
	void SetPosition(const Vector3& pos);
	void SetOnGround(bool g);
	void SetForeColor(float r,float g,float b);
	void SetComposition(Composition::e c);


	void clear();
	void operator = (const std::wstring& str);
	void operator +=(const std::wstring& str);
};

void SortLetters(TextVerteices& tvs, TextLetters& letters);