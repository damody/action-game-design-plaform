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
	TextureClass* m_Texture; //材質
	D3DXVECTOR4 m_Picpos;//圖片原先的位置picpos
	D3DXVECTOR2 m_Pos;   //圖片擺放的row and colunm
};
typedef std::vector<EffectData> EffectDatas;
