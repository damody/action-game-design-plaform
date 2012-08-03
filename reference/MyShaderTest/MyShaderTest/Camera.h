#pragma once

#include <cmath>
#include "Vector3.h"

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

		float* GetLookAt();
		float* GetCPos();
		
};


