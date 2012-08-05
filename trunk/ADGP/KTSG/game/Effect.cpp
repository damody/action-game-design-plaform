#include "Effect.h"
#include "global.h"

Effect::Effect(void)
{
}


Effect::~Effect(void)
{
}

bool Effect::Initialize()
{
	/*g_d3dDevice*/
	return true;
}

void Effect::Updata( float dt )
{

}

void Effect::SetFireParameters()
{

}

bool Effect::CreateEffect( EffectType::e type,EffectData& ed )
{
	if(Overflow())return false;
	if (!Check(type,ed))
	{
		ed.m_Pos.x = 1 + m_SerialNum % (PIC_W/PASTE_W);
		ed.m_Pos.y = 1 + m_SerialNum / (PIC_W/PASTE_W);

		switch(type)
		{
		   case	EffectType::FIRE:
				m_FireEffect.push_back(ed);
		}

	}

	return true;
}

void Effect::Clear()
{
	m_FireEffect.clear();
	m_SerialNum = 1;
}

bool Effect::Overflow()
{
	return (m_SerialNum > (PIC_H/PASTE_H)*(PIC_W/PASTE_W));
}

bool Effect::Check( EffectType::e type,EffectData& ed )
{

	for (EffectDatas::iterator it = m_FireEffect.begin();it != m_FireEffect.end();it++)
	{
		if(ed == (*it))
		{
			ed.m_Pos = it->m_Pos;
			return true;
		}
	}
	return false;
}

int Effect::Texture()
{
	return m_TextureID;
}

void EffectManager::CreateEffect( EffectType::e type,int& textureID,Vector4& picpos )
{
	EffectData ed;
	ed.m_TextureID = textureID;
	ed.m_PicPos    = picpos;
	if(!m_Effect[m_Page%3].CreateEffect(type,ed))
	{
		m_Page++;
		m_Effect[m_Page%3].Clear();
		m_Effect[m_Page%3].CreateEffect(type,ed);
	}
	textureID = ed.m_TextureID;
	picpos	  = ed.m_PicPos;	
}
