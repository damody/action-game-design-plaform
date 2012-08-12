#pragma once
#include <string>
#include "DX11\Vertex.h"
#include "DX11\TextureManager.h"
#include "math\Vector3.h"
#include "HeroAction.h"
#include "game\FlyingPath.h"
#include "common\shared_ptr.h"
#include "game\ObjectInfo.h"

class Chee
{
private:
	int m_TimeTik;		//Count down TimeTik from Frame Wait
	int m_TimeCount;	//�o�X��֭p�ɶ�
	ClipVertex	m_Pic;
	ObjectInfo_Sptr m_ObjectInfo;
	HeroAction::e	m_Action;//��U�ʧ@���A
	std::string     m_Frame;//Current Frame
	int		m_FrameID;//Current Frame ID

	int		m_Texture;//Current Texture ID
	int             m_PicID;
	int		m_PicW;//W�I������
	int		m_PicH;//H�I������
	int		m_PicX;
	int		m_PicY;

	Vector3		m_Position;
	float		m_OffsetX,m_OffsetY; //�����I����
	Vector3		m_Vel;
	Bodys		m_Bodys;
	float		m_Angle;
	bool		m_FaceSide;//true �k, false ��

	int		m_Team;//0������
	int		m_HP;

protected:
	void Init();
	void NextFrame();
public:
	std::string chee;
	Chee(void);
	Chee(std::string c);
	~Chee(void);

	void Update(float dt);
	void UpdateDataToDraw();//Data To m_Pic

	void SetTeam(int index);

	void SetPosition(Vector3 p);
	void Translation(Vector3 t);
	void SetVelocity(Vector3 v);

	int GetTextureID();
	Texture_Sptr GetTexture();
	ClipVertex GetPic();
	int Team();
	Vector3 Position();
	Vector3 BackPosition(float back);
};
SHARE_PTR(Chee)
typedef std::vector <Chee_RawPtr> Chees;

bool SortChee(Chee_RawPtr a,Chee_RawPtr b);