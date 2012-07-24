#pragma once
#include <string>
#include <vector>
#include "math/AxisAlignedBox.h"
#include "math/Vector3.h"
#include "Lua/LuaCell.h"

struct BGLayer
{
	std::string	m_PicturePath;
	Vector3		m_Position;
	float		m_Width;
	float		m_Height;
	float		m_LoopDistance;
	int		m_TimeLine;
	int		m_TimeStart;
	int		m_TimeEnd;
	bool		m_IsGround;
};
typedef std::vector<BGLayer> BGLayers;

struct ColorRect
{
	// min:0.0 ~ max:1.0, RGBA
	Vector4		m_Color;
	Vector3		m_Position;
	float		m_Width;
	float		m_Height;
	bool		m_IsGround;
};
typedef std::vector<ColorRect> ColorRects;

struct ParallelLight
{
	Vector3		m_Direction;
	float		m_LightStrength;
	int		m_TimeLine;
	int		m_TimeStart;
	int		m_TimeEnd;
};
typedef std::vector<ParallelLight> ParallelLights;

class BackGround
{
public:
	std::string	m_Name;
	// can move bounding
	AxisAlignedBoxs	m_SpaceBounding;
	// can't move bounding
	AxisAlignedBoxs	m_BanBounding;
	BGLayers	m_BGLayers;
	ColorRects	m_ColorRects;
	ParallelLights	m_ParallelLights;
	LuaCell_Sptr	m_LuaCell;
	bool	CheckDataVaild(LuaCell_Sptr luadata);
	void	LoadData(LuaCell_Sptr luadata);
};

