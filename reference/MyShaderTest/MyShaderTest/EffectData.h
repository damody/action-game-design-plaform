#pragma once
#include "TextureClass.h"
#include <d3dx10math.h>
#include <vector>


struct EffectType
{
	enum e{Fire,Ice};
};
struct EffectData
{
	TextureClass* m_Texture; //����
	D3DXVECTOR4 m_Picpos;//�Ϥ��������mpicpos
	D3DXVECTOR2 m_Pos;   //�Ϥ��\��row and colunm
};
typedef std::vector<EffectData> EffectDatas;
