////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


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
#include "FireShaderClass.h"
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
	Camera* m_Camera;
	//CameraClass* m_Camera;
	TextureClass* m_Texture;
	TextureShaderClass* m_TextureShader;
	RenderTextureClass* m_RenderTexture;

	//
	FireShaderClass* m_FireShader;
	TestShaderClass* m_TestShader;
	//

	//

	//

	//TEST
	TextureShaderClass* m_TestTS;
	TFireShaderClass* m_tf;
	//

	//
	Effect* m_Effect;
	//

	//
	//
};

#endif