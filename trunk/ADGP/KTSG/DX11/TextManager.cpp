#include "TextManager.h"
#include "global.h"

TextManager::TextManager(void)
{
}


TextManager::~TextManager(void)
{
}

void TextManager::Initialize()
{

}

TextLetters TextManager::GetLetters( const std::wstring& str )
{
	g_TextGenarator.SetForeColor(0,0,0);
	g_TextGenarator.SetForeAlpha(255);
	g_TextGenarator.SetBackColor(0,0,0);
	g_TextGenarator.SetBackAlpha(0);

	TextLetters tls;
	for (unsigned int i=0; i< str.length(); i++)
	{
		if(m_TextLetterMap.count(str.at(i)))
		{
			tls.push_back(m_TextLetterMap[str.at(i)]);
		}else{
			g_TextGenarator.WriteBegin();
			g_TextGenarator.Write(std::wstring(&str.at(i)));
			TextLetters temp = g_TextGenarator.WriteEnd();

			tls.push_back(temp.front());
			m_TextLetterMap[str.at(i)] = temp.front();
		}
	}
	return tls;
}
