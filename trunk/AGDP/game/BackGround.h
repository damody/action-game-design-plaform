#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include "DX11/Vertex.h"
#include "DX11/TextureManager.h"
#include "math/AxisAlignedBox.h"
#include "math/Vector3.h"
#include "Lua/LuaCell.h"
#include "common/shared_ptr.h"
#include "game/ColorRect.h"
#include "path/HSplineCurve.h"
#include "game/Disaster.h"

namespace boost {namespace serialization {class access;}}
struct BGLayer
{

	std::wstring	m_PicturePath;
	int		m_PicID;
	Vector3		m_Position;
	float		m_Width;
	float		m_Height;
	float		m_LoopDistance;
	int		m_TimeLine;
	int		m_TimeStart;
	int		m_TimeEnd;
	Vector3		m_Rotation;
	bool		m_IsGround;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& 	m_PicturePath;
		ar& 	m_PicID;
		ar& 	m_Position;
		ar& 	m_Width;
		ar& 	m_Height;
		ar& 	m_LoopDistance;
		ar& 	m_TimeLine;
		ar& 	m_TimeStart;
		ar& 	m_TimeEnd;
		ar& 	m_IsGround;
	}
};
typedef std::vector<BGLayer> BGLayers;



struct ParallelLight
{
	Vector3		m_Direction;     //y<0
	float		m_LightStrength; //1-10
	int		m_TimeStart;
};
typedef std::vector<ParallelLight> ParallelLights;

struct LightPath
{
	HsplineCurve m_Direction;
	HsplineCurve m_LightStrength;
};

class Background
{
private:
	LuaCell_Sptr	m_LuaCell;
	//總長
	float		m_Width;
	//時線
	int		m_TimeLine;
	//重力
	float		m_Gravity;
	//摩擦力
	float		m_Friction;
	// can move bounding
	AxisAlignedBoxs	m_SpaceBounding;
	// can't move bounding
	AxisAlignedBoxs	m_BanBounding;

	BGLayers	m_BGLayers;
	ColorRects	m_ColorRects;
	// 光線
	ParallelLights	m_ParallelLights;
	LightPath	m_LightPath;
	ParallelLight	m_CurrentLight;

	Disaster m_Disaster;

//	int _isOnBan(Vector3 &pos);
//	int _isOnSpace(Vector3 &pos);
//	int _isOnGround(Vector3 &pos);

public:
	Background() {
		//testing
		//m_Disaster.MakeEarthqauck(5,10,30);
		//m_Disaster.MakeWave(5,1,30);
		//m_Disaster.MakeWind(Vector3(1,0,0),-1,30);
	}
	~Background() {}

	std::wstring	 m_Name;
	BGVerteices	 m_BGVerteices;
	CRVerteices	 m_CRVerteices;
	DrawVertexGroups m_DrawVertexGroups;

	void Update( float dt );
	void BuildPoint();

	bool	CheckDataVaild( LuaCell_Sptr luadata );
	void	LoadData( LuaCell_Sptr luadata );

	float   Width();
	float   Gravity();
	float	Friction();

	ParallelLight GetParallelLight();

	bool	IsOpenUpDownBounding(); //場地上下是否限制物件飛出
	void	FixUpDownBounding(Vector3& pIn, const Vector3& vel);
	bool    InSpace( const Vector3& pIn ); //判斷vIn是否在地圖的可行範圍
	Vector3	AlignmentSpace( const Vector3& pIn ); //判斷vIn是否在地圖的可行範圍，並校正
	int		AboveSpaceBottom( const Vector3& pIn );


	bool    InBan( const Vector3& pIn ); //判斷vIn是否在地圖的禁足範圍
	AxisAlignedBoxs::iterator InWhichBan( const Vector3& pIn );
	AxisAlignedBoxs::iterator InWhichSpace( const Vector3& pIn );
	Vector3	AlignmentBan( const Vector3& pIn , const Vector3& pIn_past ); //判斷vIn是否在地圖的禁足範圍，並校正
	//-1: under ground, 0:on ground, 1:above ground, 2:not in
	int		AboveBanTop( const Vector3& pIn );
	int		AboveGround( const Vector3& pIn );
	bool 	isOnGround( const Vector3& pIn , const Vector3& dp, Vector3* pOut );
};
SHARE_PTR( Background );

typedef std::map<std::wstring, Background_Sptr> BackgroundMaps;
