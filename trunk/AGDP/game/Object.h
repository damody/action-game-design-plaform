#pragma once
#include <string>
#include "DX11\Vertex.h"
#include "DX11\TextureManager.h"
#include "math\Vector3.h"
#include "common\shared_ptr.h"
#include "game\ObjectInfo.h"
#include "game\Record.h"

class Object
{
private:
	int				m_TimeTik;		//Count down TimeTik from Frame Wait
	ClipVertex		m_Pic;
	ObjectInfo_Sptr m_ObjectInfo;
	int				m_Action;//���U�ʧ@���A
	std::wstring    m_Frame;//Current Frame
	int				m_FrameID;//Current Frame ID

	int				m_Texture;//Current Texture ID
	int             m_PicID;
	int				m_PicW;//W�I������
	int				m_PicH;//H�I������
	int				m_PicX;
	int				m_PicY;

	Vector3			m_Position;
	float			m_CenterX, m_CenterY;
	Vector3			m_Vel;
	Bodys			m_Bodys;
	float			m_Angle;
	bool			m_FaceSide;//true �k, false ��

	int				m_Team;//0������
	int				m_HP;

protected:
	void Init();
	void NextFrame();
public:
	const std::wstring m_ObjectName;

public:
	Object(void);
	Object(std::wstring obj);
	~Object(void);

	void Update( float dt );
	void UpdateDataToDraw();//Data To m_Pic

	ObjectType::e ObjectType();

	int Team(){return m_Team;}
	void SetTeam( int index );

	void SetPosition( Vector3 p );
	void Translation( Vector3 t );
	void SetVelocity( Vector3 v );

	int GetTextureID();
	Texture_Sptr GetTexture();
	ClipVertex GetPic();
	Vector3 Position();
	friend bool Creat( const Vector3& pos, const Creation& obj, bool face, const Record_Sptr owner );
};
SHARE_PTR( Object );
typedef std::vector <Object_RawPtr> Objects;

bool SortObject( Object_RawPtr a, Object_RawPtr b );

