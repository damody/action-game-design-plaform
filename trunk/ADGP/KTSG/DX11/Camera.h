#pragma once

#include <cmath>
#include "math\Vector3.h"
#include "common\shared_ptr.h"

#define PI 3.14159

class Camera
{
	private:
		Vector3 m_LookAT;//註: Shader 採用Othogonal 所以 z 不影響
		union {
			float m_Pos[3];//極座標 p(半徑,z軸-x軸 角度, y軸-xz平面 角度)
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

		//徵對Look At
		void SetLookAt(float xlook,float ylook,float zlook);
		void MoveX(float index);
		void MoveY(float index);
		void Rotate(float inX,float inY);//角度

		//徵對Camera Position
		void Zoom(float index);
		void SurroundX(float index);//角度
		void SurroundY(float index);//角度

		float* GetLookAt();
		float* GetCPos();
		
};
SHARE_PTR(Camera)



