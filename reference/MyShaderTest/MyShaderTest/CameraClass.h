////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_

/////////////
// LINKING //
/////////////
#pragma comment(lib,"d3dx10.lib")
//////////////
// INCLUDES //
//////////////
#include<d3dx10math.h>

////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

	void RenderReflection(float);
	void GetReflectionViewMatrix(D3DXMATRIX& viewMatrix);

private:
	D3DXMATRIX m_viewMatrix;
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_reflectionViewMatrix;
};

#endif