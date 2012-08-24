#include "StdGame.h"
#include "Camera.h"

Camera::Camera():m_LookAT(Vector3(0,0,0)),m_Radius(0),m_Thita(0),m_Alpha(0),m_ScreenW(0),m_ScreenH(0)
{
	m_Thita_R = (float)cos(-m_Thita *3.14159/180.0f);
}

Camera::Camera( float xlook,float ylook,float zlook,float r,float thita,float alpha )
:m_LookAT(Vector3(xlook,ylook,zlook)),m_Radius(r),m_Thita(thita),m_Alpha(alpha)
{
	m_Thita_R = (float)cos(-m_Thita *3.14159/180.0f);
}

Camera::~Camera()
{

}


void Camera::SetLookAt( float xlook,float ylook,float zlook )
{
	m_LookAT = Vector3(xlook,ylook,zlook);
}

void Camera::MoveX( float index )
{
	m_LookAT.x += index;
}

void Camera::MoveY( float index )
{
	m_LookAT.y += index;
}

void Camera::Rotate( float inX,float inY )
{
	inX = inX * (float)PI / 180.0f;
	inY = inY * (float)PI / 180.0f; 
	m_LookAT.x = m_Radius * cos(inY) * sin(inX);
	m_LookAT.y = m_Radius * sin(inY);
	m_LookAT.z = m_Radius * cos(inY) * cos(inX);
}

void Camera::Zoom( float index )
{
	if((m_Radius+index)<-2200)return;
	else m_Radius += index;
	std::cout<<"Zoom:"<<m_Radius<<std::endl;
}

void Camera::SurroundX( float index )
{
	m_Alpha += index;
}

void Camera::SurroundY( float index )
{
	m_Thita += index;
	m_Thita_R = (float)cos(-m_Thita *3.14159/180.0f);
}

float* Camera::GetLookAt()
{
	return &m_LookAT[0];
}

float* Camera::GetCPos()
{
	return m_Pos;
}

Vector3 Camera::LookAt()
{
	return m_LookAT;
}

bool Camera::Visable( const Vector3& pos )
{
	float target = (pos.x - LookAt().x) * m_Thita_R;
	return target > -2*m_ScreenW && target < 2*m_ScreenW;
}

bool Camera::Visable( const D3DXVECTOR3& pos )
{
	float target = (pos.x - LookAt().x) * m_Thita_R;
	return target > -2*m_ScreenW && target < 2*m_ScreenW;
}

void Camera::onResize( float w,float h )
{
	m_ScreenW = w;
	m_ScreenH = h;
}

int Camera::Offside( const D3DXVECTOR3& pos )
{
	float target = (pos.x - LookAt().x) * m_Thita_R;
	if (target > 2*m_ScreenW)
	{
		return 1;
	}else if (target < -2*m_ScreenW)
	{
		return -1;
	}else   return 0;
}

float Camera::Offsidelength()
{
	return 4*m_ScreenW;
}



