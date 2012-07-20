#pragma once
#include <string>
#include <vector>
#include "DX11/Vertex.h"
#include "DX11/TextureManager.h"
#include "math/AxisAlignedBox.h"
#include "math/Vector3.h"
#include "Lua/LuaCell.h"

struct BGLayer
{
	std::string	m_PicturePath;
	int		m_PicID;
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
private:
	LuaCell_Sptr	m_LuaCell;
	std::string	m_Name;
	float		m_Width;
	// can move bounding
	AxisAlignedBoxs	m_SpaceBounding;
	// can't move bounding
	AxisAlignedBoxs	m_BanBounding;
	BGLayers	m_BGLayers;
	ColorRects	m_ColorRects;
	ParallelLights	m_ParallelLights;

	int		m_TimeTik;
	BGVerteices	m_BGVerteices;
	DrawVertexGroups m_DrawVertexGroups;
public:
	BackGround(){}
	~BackGround(){}

	void Update(float dt);
	
	bool	CheckDataVaild(LuaCell_Sptr luadata);
	void	LoadData(LuaCell_Sptr luadata);

protected:	
	void UpdateDataToDraw();
};

