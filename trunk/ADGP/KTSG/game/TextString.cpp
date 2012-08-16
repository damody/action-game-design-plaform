#include "game/TextString.h"
#include "global.h"

TextString::TextString():OFFSET(0.1f),
m_Size(50),m_OnGround(false),m_Composition(Composition::LEFT),
m_Position(Vector3(0,0,0)),m_ForeColor(Vector3(0,0,0))
{

}

TextString::TextString(const std::wstring& str ):OFFSET(0.1f),
m_Str(str),m_Size(50),m_OnGround(false),m_Composition(Composition::LEFT),
m_Position(Vector3(0,0,0)),m_ForeColor(Vector3(0,0,0))
{
	m_TextLetters = g_TextMG.GetLetters(m_Str);
	lenght();
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

void TextString::operator=( const std::wstring& str )
{
	this->clear();
	m_Str.append(str);
	m_TextLetters = g_TextMG.GetLetters(m_Str);
	lenght();
}

void TextString::operator+=( const std::wstring& str )
{
	m_Str.assign(str.begin(),str.end());
	TextLetters temp = g_TextMG.GetLetters(str);
	m_TextLetters.assign(temp.begin(),temp.end());
	lenght();
}

const std::wstring& TextString::w_str()
{
	return m_Str;
}

void TextString::lenght()
{
	m_Lenght = 0;
	for (TextLetters::iterator it=m_TextLetters.begin(); it != m_TextLetters.end();++it)
	{
		m_Lenght += m_Size * (*it)->m_OffsetX_Fore;
		m_Lenght += m_Size * (*it)->m_ScaleW;
		m_Lenght += m_Size * (*it)->m_OffsetX_Back;
	}
}

void TextString::SetForeColor( float r,float g,float b )
{
	m_ForeColor = Vector3(r,g,b);
}

void TextString::buildPoint()
{
	float c;
	switch (m_Composition)
	{
	case Composition::LEFT:
		c = 0.0f;
		break;
	case Composition::CENTER:
		c = m_Lenght * 0.5f;
		break;
	case Composition::RIGHT:
		c = m_Lenght;
		break;
	}

	m_TexVerteices.clear();
	m_DrawVertexGroups.clear();
	float p = 0;
	for (TextLetters::iterator it = m_TextLetters.begin(); it != m_TextLetters.end();++it)
	{
		TextVertex tv;

		p += m_Size * (*it)->m_OffsetX_Fore;
		tv.position.x = m_Position.x + p - c;
		p += m_Size * (*it)->m_ScaleW;
		p += m_Size * (*it)->m_OffsetX_Back + OFFSET;

		tv.position.y = m_Position.y;
		tv.position.z = m_Position.z;

		
		tv.size.x = m_Size * (*it)->m_ScaleW;
		tv.size.y = m_Size * (*it)->m_ScaleH;

		if(m_OnGround){
			tv.position.z -= m_Size * (*it)->m_OffsetY;
			tv.angle = -90;
		}else{
			tv.position.y -= m_Size * (*it)->m_OffsetY;
			tv.angle = 0;
		}
		
		tv.color.x = m_ForeColor.x;
		tv.color.y = m_ForeColor.y;
		tv.color.z = m_ForeColor.z;

		m_TexVerteices.push_back(tv);
	}
}

void TextString::SetComposition( Composition::e c )
{
	m_Composition = c;
}

void TextString::SetOnGround( bool g )
{
	m_OnGround = g;
}



void SortLetters( TextVerteices& tvs, TextLetters& letters )
{
	

}
