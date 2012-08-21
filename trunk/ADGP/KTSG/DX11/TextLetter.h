#pragma once
#include "StdGame.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "common/shared_ptr.h"
#include "TextureManager.h"

struct TextLetter
{
	wchar_t letter;
	Texture_Sptr texture;
	float m_ScaleW,m_ScaleH;
	float m_OffsetX_Fore,m_OffsetX_Back,m_OffsetY;

	TextLetter():m_ScaleW(1.0),m_ScaleH(1.0),m_OffsetX_Fore(0.0),m_OffsetX_Back(0.0),m_OffsetY(0.0){}
};
SHARE_PTR(TextLetter)

typedef std::vector<TextLetter_Sptr>   TextLetters;
typedef std::map<wchar_t,TextLetter_Sptr> TextLetterMap;