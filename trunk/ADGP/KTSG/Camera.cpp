#include "Camera.h"

Camera::Camera():m_LookAT(Vector3(0,0,0)),m_Radius(0),m_Thita(0),m_Alpha(0)
{

}

Camera::Camera( float xlook,float ylook,float zlook,float r,float thita,float alpha )
:m_LookAT(Vector3(xlook,ylook,zlook)),m_Radius(r),m_Thita(thita),m_Alpha(alpha)
{

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
	if((m_Radius+index)<0)return;
	else m_Radius += index;
}

void Camera::SurroundX( float index )
{
	m_Alpha += index* (float)PI / 180.0f;
}

void Camera::SurroundY( float index )
{
	m_Thita += index* (float)PI / 180.0f;
}

float* Camera::GetLookAt()
{
	return &m_LookAT[0];
}

float* Camera::GetCPos()
{
	return m_Pos;
}

