#include "game/TextString.h"
#include "global.h"

TextString::TextString():m_Angle(0),m_Width(50),m_Height(50),m_ForeColor(Vector4(0,0,0,1)),m_BackColor(Vector4(0,0,0,0)),m_Position(Vector3(0,0,0))
{
	m_Str.clear();
}

TextString::~TextString()
{

}

void TextString::buildPoint()
{
	int i=0;
	TextVertex tv;
	tv.size.x=(float)m_Width;
	tv.size.y=(float)m_Height;
	tv.position.x = m_Position.x;
	tv.position.y = m_Position.z;
	tv.position.z = m_Position.y;
	tv.angle    = m_Angle;
	for (Textures::iterator it = m_Textures.begin(); it != m_Textures.end() ; ++it)
	{
		
		tv.position.x +=(float) i*m_Width;
		m_TexVerteices.push_back(tv);

		DrawVertexGroup dvg;
		dvg.texture = (*it);
		dvg.StartVertexLocation=i;
		dvg.VertexCount = 1;
		m_DrawVertexGroups.push_back(dvg);
	}
}

void TextString::SetPosition( const Vector3& pos )
{
	m_Position = pos;
}

void TextString::SetAngle( float angle )
{
	m_Angle = angle;
}

void TextString::Texting( const std::wstring& text )
{
	m_Str.append(text);
}

void TextString::Create()
{
	g_TextGenarator.WriteBegin();
	g_TextGenarator.Write(m_Str);
	g_TextGenarator.SetFontSize(125,125);
	g_TextGenarator.SetForeColor((BYTE)m_ForeColor.x,(BYTE)m_ForeColor.y,(BYTE)m_ForeColor.z);
	g_TextGenarator.SetForeAlpha((BYTE)m_ForeColor.w);
	g_TextGenarator.SetBackColor((BYTE)m_BackColor.x,(BYTE)m_BackColor.y,(BYTE)m_BackColor.z);
	g_TextGenarator.SetBackAlpha((BYTE)m_BackColor.w);
	m_Textures = g_TextGenarator.WriteEnd();
}

void TextString::SetForeColor( const Vector4& color )
{
	m_ForeColor = color;
}

void TextString::SetBackColor( const Vector4& color )
{
	m_BackColor = color;
}

void TextString::Clear()
{
	m_Str.clear();
}


