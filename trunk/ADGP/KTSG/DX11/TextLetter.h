#pragma once
#include "stdafx.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "common/shared_ptr.h"

struct TextLetter
{
	ID3D11ShaderResourceView* texture;
	float m_ScaleW,m_ScaleH;
	float m_OffsetX,m_OffsetY;

	TextLetter():m_ScaleW(1.0),m_ScaleH(1.0),m_OffsetX(0.0),m_OffsetY(0.0),texture(0){}
};
SHARE_PTR(TextLetter)

typedef std::vector<TextLetter_Sptr>   TextLetters;
typedef std::map<wchar_t,TextLetter_Sptr> TextLetterMap;