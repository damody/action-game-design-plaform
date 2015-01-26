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
	int				m_Action;//當下動作狀態
	FrameInfo*		m_FrameInfo;
	std::wstring    m_Frame;//Current Frame
	int				m_FrameID;//Current Frame ID
	int				m_Texture;//Current Texture ID
	int             m_PicID;
	int				m_PicW;//W截切次數
	int				m_PicH;//H截切次數
	int				m_PicX;
	int				m_PicY;

	Vector3			m_Position;
	float			m_CenterX, m_CenterY;
	Vector3			m_Vel;
	float			m_Angle;
	bool			m_FaceSide;//true 右, false 左

	int				m_Team;//0為不分
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
	void AddVelocity( Vector3 v );

	int GetTextureID();
	Texture_Sptr GetTexture();
	ClipVertex GetPic();
	PolygonVerteices GetPolygonLineVerteices() const;
	PolygonVerteices GetPolygonVerteices() const;

	Vector3 Position();
	friend bool Creat( const Vector3& pos, const Creation& obj, bool face, const Record_Sptr owner );
	friend Polygon2Ds GetObjectBodys(const Object& r);
	friend Polygon2Ds GetObjectAttacks(const Object& r);
	friend Polygon2Ds GetObjectCatches(const Object& r);
};
SHARE_PTR( Object );
typedef std::vector <Object_Sptr> Objects;

bool SortObject( Object_Sptr a, Object_Sptr b );
Polygon2Ds GetObjectBodys(const Object& r);
Polygon2Ds GetObjectAttacks(const Object& r);
Polygon2Ds GetObjectCatches(const Object& r);
