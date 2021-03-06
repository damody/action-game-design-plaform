#pragma once

#include <cmath>
#include <d3d9.h>
#include <d3dx9.h>
#include "math\Vector3.h"
#include "common\shared_ptr.h"
#include "Game\Hero.h"
#define PI 3.14159

class Camera
{
private:
	Vector3 m_LookAt;
	union
	{
		//極座標 p(半徑,z軸-x軸 角度, y軸-xz平面 角度)
		float m_Pos[3];
		struct
		{
			float m_Radius;
			float m_Thita;
			float m_Alpha;
		};
	};


	float m_Thita_R;
	float m_ScreenW, m_ScreenH;
	bool  m_Trackable;
public:
	Camera();
	Camera( float xlook, float ylook, float zlook, float r, float thita, float alpha );
	~Camera();

	//徵對Look At
	Vector3 LookAt();
	void SetLookAt( float xlook, float ylook, float zlook );
	void MoveX( float index );
	void MoveY( float index );
	void Rotate( float inX, float inY ); //角度
	void TrackHero( Hero& hero, float left, float right ,float width );

	//徵對Camera Position
	void Zoom( float index );
	void SurroundX( float index ); //角度
	void SurroundY( float index ); //角度

	bool Visable( const Vector3& pos );
	bool Visable( const D3DXVECTOR3& pos );
	int Offside( const D3DXVECTOR3& pos );
	float Offsidelength();

	void onResize( float w, float h );

	float* GetLookAt();
	float* GetCPos();
};
SHARE_PTR( Camera );

