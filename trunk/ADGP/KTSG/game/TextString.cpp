#include "game/TextString.h"
#include "global.h"

TextString::TextString()
{

}

TextString::~TextString()
{

}

void TextString::clear()
{
	m_Str.clear();
	m_TextLetters.clear();
}

void TextString::SetSize( float size )
{
	m_Size = size;
}

void TextString::SetPosition( const Vector3& pos )
{
	m_Position = pos;
}

void TextString::SetAngle( float angle )
{
	m_Angle = angle;
}

void TextString::operator=( const std::wstring& str )
{
	this->clear();
	m_Str.append(str);
	m_TextLetters = g_TextMG.GetLetters(m_Str);
}

void TextString::operator+=( const std::wstring& str )
{
	m_Str.assign(str.begin(),str.end());
	TextLetters temp = g_TextMG.GetLetters(str);
	m_TextLetters.assign(temp.begin(),temp.end());
}

std::wstring TextString::w_str()
{
	return m_Str;
}


