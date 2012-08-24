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
#include "common/shared_ptr.h"
#include "game/ColorRect.h"
#include "path/HSplineCurve.h"

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
	Vector3		m_Direction;     //y<0
	float		m_LightStrength; //1-10
	int		m_TimeStart;
};
typedef std::vector<ParallelLight> ParallelLights;

struct LightPath
{
	HsplineCurve m_Direction;
	HsplineCurve m_LightStrength;
}typedef LightPath;

class BackGround
{
private:
	LuaCell_Sptr	m_LuaCell;
	//�`��
	float		m_Width;
	//�ɽu
	int		m_TimeLine;
	//���O
	float		m_Gravity;
	//�����O
	float		m_Friction;
	// can move bounding
	AxisAlignedBoxs	m_SpaceBounding;
	// can't move bounding
	AxisAlignedBoxs	m_BanBounding;
	BGLayers	m_BGLayers;
	ColorRects	m_ColorRects;
	ParallelLights	m_ParallelLights;
	LightPath	m_LightPath;
	ParallelLight	m_CurrentLight;
	
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
	float   Gravity();

	ParallelLight GetParallelLight();

	bool    InSpace(const Vector3& pIn);//�P�_vIn�O�_�b�a�Ϫ��i��d��
	Vector3	AlignmentSpace(const Vector3& pIn);//�P�_vIn�O�_�b�a�Ϫ��i��d��A�îե�
	bool    AboveSpaceBottom(const Vector3& pIn);


	bool    InBan(const Vector3& pIn);//�P�_vIn�O�_�b�a�Ϫ��T���d��
	AxisAlignedBoxs::iterator InWinchBan(const Vector3& pIn);
	Vector3	AlignmentBan(const Vector3& pIn ,const Vector3& pIn_past);//�P�_vIn�O�_�b�a�Ϫ��T���d��A�îե�
	bool    AboveBanTop(const Vector3& pIn);

	bool	AboveGround(const Vector3& pIn);
};
SHARE_PTR(BackGround);

typedef std::map<std::string,BackGround_RawPtr> BGMaps;
