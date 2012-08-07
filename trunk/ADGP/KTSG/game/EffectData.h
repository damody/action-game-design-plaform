#pragma once
#include <vector>
#include "math\Vector2.h"
#include "math\Vector4.h"

struct EffectType
{
	enum e
	{
		NONE,
		FIRE,
		FREEZE,
		POISON
	};
};

struct EffectData
{
	int	m_TextureID;
	D3DXVECTOR4	m_PicPos;
	Vector2 m_Pos;

	bool operator == (const EffectData& index)
	{
		return (m_TextureID==index.m_TextureID && m_PicPos.x==index.m_PicPos.x && m_PicPos.y==index.m_PicPos.y);
	}
};
typedef std::vector<EffectData> EffectDatas;
