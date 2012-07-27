#pragma once
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include "DX11/Vertex.h"
#include "DX11/TextureManager.h"
#include "math/AxisAlignedBox.h"
#include "math/Vector3.h"
#include "Lua/LuaCell.h"
#include "common\shared_ptr.h"
#include "game/ColorRect.h"
namespace boost{namespace serialization{class access;}}
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

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar &	m_PicturePath;
		ar &	m_PicID;
		ar &	m_Position;
		ar &	m_Width;
		ar &	m_Height;
		ar &	m_LoopDistance;
		ar &	m_TimeLine;
		ar &	m_TimeStart;
		ar &	m_TimeEnd;
		ar &	m_IsGround;
	}
};
typedef std::vector<BGLayer> BGLayers;



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
	float		m_Width;
	// can move bounding
	AxisAlignedBoxs	m_SpaceBounding;
	// can't move bounding
	AxisAlignedBoxs	m_BanBounding;
	BGLayers	m_BGLayers;
	ColorRects	m_ColorRects;
	ParallelLights	m_ParallelLights;

	
public:
	BackGround(){}
	~BackGround(){}

	std::string	 m_Name;
	BGVerteices	 m_BGVerteices;
	CRVerteices	 m_CRVerteices;
	DrawVertexGroups m_DrawVertexGroups;

	void Update(float dt);
	void BuildPoint();

	bool	CheckDataVaild(LuaCell_Sptr luadata);
	void	LoadData(LuaCell_Sptr luadata);

	float   Width();

	bool    InSpace(Vector3 pIn);//判斷vIn是否在地圖的可行範圍
	Vector3	AlignmentSpace(Vector3 pIn);//判斷vIn是否在地圖的可行範圍，並校正

	bool    InBan(Vector3 pIn);//判斷vIn是否在地圖的禁足範圍
	Vector3	AlignmentBan(Vector3 pIn );//判斷vIn是否在地圖的禁足範圍，並校正
};
SHARE_PTR(BackGround);

typedef std::map<std::string,BackGround_RawPtr> BGMaps;
