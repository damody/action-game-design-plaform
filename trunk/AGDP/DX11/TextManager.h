#pragma once
#include "TextLetter.h"

class TextManager
{
private:
	TextLetterMap m_TextLetterMap;
public:
	TextManager(void);
	~TextManager(void);

	void Initialize();
	TextLetters GetLetters(const std::wstring& str);
};

