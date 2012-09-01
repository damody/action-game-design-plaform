#pragma once
#include <string>
#include "DX11\Vertex.h"
#include "DX11\TextureManager.h"
#include "math\Vector3.h"
#include "HeroAction.h"
#include "common\shared_ptr.h"
#include "game\ObjectInfo.h"
#include "Record.h"

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
	float		m_CenterX,m_CenterY;
	Vector3		m_Vel;
	Bodys		m_Bodys;
	float		m_Angle;
	bool		m_FaceSide;//true 右, false 左

	int		m_Team;//0為不分
	int		m_HP;

protected:
	void Init();
	void NextFrame();
public:
	const std::string weapon;

	Weapon(void);
	Weapon(std::string w);
	~Weapon(void);

	void Update(float dt);
	void UpdateDataToDraw();//Data To m_Pic

	void SetTeam(int index);

	void SetPosition(Vector3 p);
	void Translation(Vector3 t);
	void SetVelocity(Vector3 v);

	int GetTextureID();
	Texture_Sptr GetTexture();
	ClipVertex GetPic();
	Vector3 Position();
	friend bool Creat(const Vector3 &pos, const Creation &obj, bool face, const Record_Sptr owner);
};
SHARE_PTR(Weapon)
typedef std::vector <Weapon_RawPtr> Weapons;

bool SortWeapon( Weapon_RawPtr a,Weapon_RawPtr b);
