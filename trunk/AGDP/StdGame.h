#pragma once
#pragma warning(disable:4819)
#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <fstream>
#include <xnamath.h>
#include <d3dx11effect.h>
#include <d3dx9.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <d3dx11effect.h>
#include <vector>
#include <sstream>
#include <tchar.h>

#include <common/shared_ptr.h>
#include <math/AABB2D.h>
#include <math/AxisAlignedBox.h>
#include <math/BasicMath.h>
#include <math/Centroid.h>
#include <math/Matrix3.h>
#include <math/Matrix4.h>
#include <math/Polygon2D.h>
#include <math/Quaternion.h>
#include <math/Ray.h>
#include <math/Sphere.h>
#include <math/Vector2.h>
#include <math/Vector3.h>
#include <math/Vector4.h>
#include <algo/nway.h>
#include <ball/homing.h>


//¥þ°ì¥¨¶°
#define ReleaseCOM(x) { if(x){ x->Release();x = 0; }}

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                      \
	{                                                  \
	HRESULT hr = x;                                \
	if(FAILED(hr))                                 \
		{                                              \
		DXTrace(__FILE__, __LINE__, hr, _T(#x), TRUE); \
		}                                              \
	}
#endif
#else
#ifndef HR
#define HR(x) x;
#endif
#endif 

#define CTRL_KEY_MAX 6
#define DEFAULT_CTRL_KEY_UP 0xC8
#define DEFAULT_CTRL_KEY_LEFT 0xCB
#define DEFAULT_CTRL_KEY_RIGHT 0xCD
#define DEFAULT_CTRL_KEY_DOWN 0xD0
#define DEFAULT_CTRL_KEY_SKILL 0x39
#define DEFAULT_CTRL_KEY_TIMECHENGE 0x1D
