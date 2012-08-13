#pragma once

#include <iostream>
#include "DX11/TextureManager.h"

class TextString{
private:
	std::wstring	m_Str;
	Textures	m_Textures;
	int		m_Width,m_Height;
	Vector3		m_Position;
	float		m_Angle;

public:
	TextString();
	~TextString();

	TextVerteices		m_TexVerteices;
	DrawVertexGroups	m_DrawVertexGroups;

	void Create(int w,int h,const Vector4& rgba);
	void buildPoint();

	void SetPosition(const Vector3& pos);
	void SetAngle(float angle);
};