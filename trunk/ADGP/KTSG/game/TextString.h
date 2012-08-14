#pragma once

#include <iostream>
#include <string>
#include "DX11/Vertex.h"
#include "DX11/TextureManager.h"
#include "math/Vector3.h"
#include "math/Vector4.h"

 

class TextString{
private:
	std::wstring	m_Str;
	Textures	m_Textures;
	int		m_Width,m_Height;
	Vector4		m_ForeColor;
	Vector4		m_BackColor;
	Vector3		m_Position;
	float		m_Angle;

public:
	TextString();
	~TextString();

	TextVerteices		m_TexVerteices;
	DrawVertexGroups	m_DrawVertexGroups;

	void Texting(const std::wstring& text);
	void Clear();
	void Create();

	void buildPoint();

	void SetPosition(const Vector3& pos);
	void SetAngle(float angle);
	void SetForeColor(const Vector4& color);
	void SetBackColor(const Vector4& color);
};