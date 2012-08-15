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
	std::wstring	m_Str;
	TextLetters     m_TextLetters;
	float		m_Lenght;

	Composition::e  m_Composition;

	Vector3		m_Position;
	float		m_Size; 
	float		m_Angle;
	

public:
	TextString();
	~TextString();

	std::wstring w_str();

	void buildPoint();
	TextVerteices		m_TexVerteices;
	DrawVertexGroups	m_DrawVertexGroups;
	
	void SetSize(float size);
	void SetPosition(const Vector3& pos);
	void SetAngle(float angle);

	void clear();
	void operator = (const std::wstring& str);
	void operator +=(const std::wstring& str);
};