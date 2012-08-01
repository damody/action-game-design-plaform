#pragma once
#include <string>
#include "DX11\Vertex.h"
#include "DX11\TextureManager.h"
#include "math\Vector3.h"
#include "global.h"
#include "HeroAction.h"

class Weapon
{
private:
	int m_TimeTik;		//Count down TimeTik from Frame Wait
	ClipVertex	m_Pic;
	ObjectInfo_Sptr m_ObjectInfo;
	HeroAction::e	m_Action;//當下動作狀態
	std::string     m_Frame;//Current Frame
	int		m_FrameID;//Current Frame ID

	int		m_Texture;//Current Texture ID
	int             m_PicID;
	int		m_PicW;//W截切次數
	int		m_PicH;//H截切次數
	int		m_PicX;
	int		m_PicY;

	Vector3		m_Position;
	Vector3		m_Vel;
	Bodys		m_Bodys;
	float		m_Angle;
	bool		m_FaceSide;//true 右, false 左

	int		m_Team;//0為不分
	int		m_Hp;

public:
	const std::string weapon;

	Weapon(void);
	~Weapon(void);

	void Update(float dt);

};

