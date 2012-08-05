////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

/////////////
// GLOBALS //
/////////////


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "D3DClass.h"
#include "TextureShaderClass.h"
#include "TextureClass.h"
#include "RenderTextureClass.h"
#include "CameraClass.h"
#include "TestShaderClass.h"
#include "TFireShaderClass.h"
#include "Camera.h"
#include "Effect.h"
////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(WCHAR*,WCHAR*,HWND);
	void Shutdown();
	void Frame();
	void Render();


private:
	bool RenderToTexture();
	bool RenderScene();



private:
	D3DClass* m_D3D;
	TextureClass* m_Texture;
	TestShaderClass* m_TestShader;
	Effect* m_Effect;

};

#endif