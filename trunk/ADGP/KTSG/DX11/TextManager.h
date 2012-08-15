#pragma once
#include "TextLetter.h"

const std::wstring Type_1 = std::wstring(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%&?");
const std::wstring Type_2 = std::wstring(L"acemnorsuvwxz+-");
const std::wstring Type_3 = std::wstring(L"bdfhiklt");
const std::wstring Type_4 = std::wstring(L"gpqy");
const std::wstring Type_5 = std::wstring(L"j");
const std::wstring Type_6 = std::wstring(L".");
const std::wstring Type_7 = std::wstring(L".");

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

