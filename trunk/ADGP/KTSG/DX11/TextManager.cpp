#include "StdGame.h"
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
	std::wstring TYPE_1 = std::wstring(L"ABCDEFGHIJKLMNOPQRSTUVWXYZbdfhk1234567890@#$%&?/");
	std::wstring TYPE_2 = std::wstring(L"acemnorsuvwxz+");
	std::wstring TYPE_3 = std::wstring(L"il!|");
	std::wstring TYPE_4 = std::wstring(L"gpqy");
	std::wstring TYPE_5 = std::wstring(L"j");
	std::wstring TYPE_6 = std::wstring(L"t><");
	std::wstring TYPE_7 = std::wstring(L".");
	std::wstring TYPE_8 = std::wstring(L",");
	std::wstring TYPE_9 = std::wstring(L"*");
	std::wstring TYPE_10 = std::wstring(L"()");
	std::wstring TYPE_11 = std::wstring(L"¤@");
	std::wstring TYPE_12 = std::wstring(L"-");

	g_TextGenarator.SetForeColor(255,255,255);
	g_TextGenarator.SetForeAlpha(255);
	g_TextGenarator.SetBackColor(0,0,0);
	g_TextGenarator.SetBackAlpha(0);

	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(TYPE_1);
	TextLetters temp = g_TextGenarator.WriteEnd();
	int i=0;
	for (TextLetters::iterator it = temp.begin(); it != temp.end();it++)
	{
		(*it)->m_OffsetY = 0.2f;
		(*it)->m_ScaleH = 0.7f;
		
		(*it)->m_ScaleW = 0.5f;
		m_TextLetterMap[TYPE_1.at(i)]=(*it);
		i++;
	}

	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(TYPE_2);
	temp = g_TextGenarator.WriteEnd();
	i=0;
	for (TextLetters::iterator it = temp.begin(); it != temp.end();it++)
	{
		(*it)->m_OffsetY = 0.4f;
		(*it)->m_ScaleH = 0.5f;
		
		(*it)->m_ScaleW = 0.5f;
		m_TextLetterMap[TYPE_2.at(i)]=(*it);
		i++;
	}
	
	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(TYPE_3);
	temp = g_TextGenarator.WriteEnd();
	i=0;
	for (TextLetters::iterator it = temp.begin(); it != temp.end();it++)
	{
		(*it)->m_OffsetY = 0.2f;
		(*it)->m_ScaleH = 0.7f;

		(*it)->m_OffsetX_Fore = 0.1f;
		(*it)->m_ScaleW = 0.3f;
		(*it)->m_OffsetX_Back = 0.1f;
		m_TextLetterMap[TYPE_3.at(i)]=(*it);
		i++;
	}

	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(TYPE_4);
	temp = g_TextGenarator.WriteEnd();
	i=0;
	for (TextLetters::iterator it = temp.begin(); it != temp.end();it++)
	{
		(*it)->m_OffsetY = 0.4f;
		(*it)->m_ScaleH = 0.7f;

		(*it)->m_ScaleW = 0.5f;
		m_TextLetterMap[TYPE_4.at(i)]=(*it);
		i++;
	}

	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(TYPE_5);
	temp = g_TextGenarator.WriteEnd();
	i=0;
	for (TextLetters::iterator it = temp.begin(); it != temp.end();it++)
	{
		(*it)->m_OffsetY = 0.2f;
		(*it)->m_ScaleH = 0.9f;

		(*it)->m_ScaleW = 0.3f;
		(*it)->m_OffsetX_Back = 0.1f;
		m_TextLetterMap[TYPE_5.at(i)]=(*it);
		i++;
	}
	
	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(TYPE_6);
	temp = g_TextGenarator.WriteEnd();
	i=0;
	for (TextLetters::iterator it = temp.begin(); it != temp.end();it++)
	{
		(*it)->m_OffsetY = 0.3f;
		(*it)->m_ScaleH = 0.6f;

		(*it)->m_ScaleW = 0.5f;
		m_TextLetterMap[TYPE_6.at(i)]=(*it);
		i++;
	}
	
	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(TYPE_7);
	temp = g_TextGenarator.WriteEnd();
	i=0;
	for (TextLetters::iterator it = temp.begin(); it != temp.end();it++)
	{
		(*it)->m_OffsetY = 0.7f;
		(*it)->m_ScaleH = 0.1f;

		(*it)->m_OffsetX_Fore = 0.2f;
		(*it)->m_ScaleW = 0.1f;
		(*it)->m_OffsetX_Back = 0.2f;
		m_TextLetterMap[TYPE_7.at(i)]=(*it);
		i++;
	}
	
	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(TYPE_8);
	temp = g_TextGenarator.WriteEnd();
	i=0;
	for (TextLetters::iterator it = temp.begin(); it != temp.end();it++)
	{
		(*it)->m_OffsetY = 0.6f;
		(*it)->m_ScaleH = 0.2f;

		(*it)->m_OffsetX_Fore = 0.2f;
		(*it)->m_ScaleW = 0.1f;
		(*it)->m_OffsetX_Back = 0.2f;
		m_TextLetterMap[TYPE_8.at(i)]=(*it);
		i++;
	}

	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(TYPE_9);
	temp = g_TextGenarator.WriteEnd();
	i=0;
	for (TextLetters::iterator it = temp.begin(); it != temp.end();it++)
	{
		(*it)->m_ScaleH = 0.4f;

		(*it)->m_ScaleW = 0.5f;
		m_TextLetterMap[TYPE_9.at(i)]=(*it);
		i++;
	}
	
	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(TYPE_10);
	temp = g_TextGenarator.WriteEnd();
	i=0;
	for (TextLetters::iterator it = temp.begin(); it != temp.end();it++)
	{
		(*it)->m_ScaleW = 0.5f;
		m_TextLetterMap[TYPE_10.at(i)]=(*it);
		i++;
	}
	
	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(TYPE_11);
	temp = g_TextGenarator.WriteEnd();
	i=0;
	for (TextLetters::iterator it = temp.begin(); it != temp.end();it++)
	{
		(*it)->m_OffsetY = 0.45f;
		(*it)->m_ScaleH = 0.1f;

		(*it)->m_ScaleW = 1.0f;
		m_TextLetterMap[TYPE_11.at(i)]=(*it);
		i++;
	}

	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(TYPE_12);
	temp = g_TextGenarator.WriteEnd();
	i=0;
	for (TextLetters::iterator it = temp.begin(); it != temp.end();it++)
	{
		(*it)->m_OffsetY = 0.5f;
		(*it)->m_ScaleH = 0.1f;

		(*it)->m_ScaleW = 0.5f;
		m_TextLetterMap[TYPE_12.at(i)]=(*it);
		i++;
	}
}

TextLetters TextManager::GetLetters( const std::wstring& str )
{
	TextLetters tls;
	for (unsigned int i=0; i< str.length(); i++)
	{
		if(m_TextLetterMap.count(str.at(i)))
		{
			tls.push_back(m_TextLetterMap[str.at(i)]);
		}else{
			g_TextGenarator.SetForeColor(255,255,255);
			g_TextGenarator.SetForeAlpha(255);
			g_TextGenarator.SetBackColor(0,0,0);
			g_TextGenarator.SetBackAlpha(0);

			g_TextGenarator.WriteBegin();
			g_TextGenarator.Write(std::wstring(&str.at(i)));
			TextLetters temp = g_TextGenarator.WriteEnd();

			tls.push_back(temp.front());
			m_TextLetterMap[str.at(i)] = temp.front();
		}
	}
	return tls;
}
