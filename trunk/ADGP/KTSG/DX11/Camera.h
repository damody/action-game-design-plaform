#pragma once

#include <cmath>
#include <d3d9.h>
#include <d3dx9.h>
#include "math\Vector3.h"
#include "common\shared_ptr.h"

#define PI 3.14159

class Camera
{
	private:
		Vector3 m_LookAT;
		union {
			float m_Pos[3];//���y�� p(�b�|,z�b-x�b ����, y�b-xz���� ����)
			struct
			{
				float m_Radius;
				float m_Thita;
				float m_Alpha;
			};
		};


		float m_Thita_R;
		float m_ScreenW,m_ScreenH;
	public:
		Camera();
		Camera(float xlook,float ylook,float zlook,float r,float thita,float alpha);
		~Camera();

		//�x��Look At
		Vector3 LookAt();
		void SetLookAt(float xlook,float ylook,float zlook);
		void MoveX(float index);
		void MoveY(float index);
		void Rotate(float inX,float inY);//����

		//�x��Camera Position
		void Zoom(float index);
		void SurroundX(float index);//����
		void SurroundY(float index);//����

		bool Visable(const Vector3& pos);
		bool Visable(const D3DXVECTOR3& pos);
		int Offside(const D3DXVECTOR3& pos);
		float Offsidelength();

		void onResize(float w,float h);

		float* GetLookAt();
		float* GetCPos();
		
};
SHARE_PTR(Camera)



