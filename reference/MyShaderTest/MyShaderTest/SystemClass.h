#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

//#define WIN32_LEAN_AND_MEAN


//////////////
// INCLUDES //
//////////////
#include <windows.h>
#include <memory>
///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "GraphicsClass.h"
////////////////////////////////////////////////////////////////////////////////
// Class name: SystemClass
////////////////////////////////////////////////////////////////////////////////
class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;//Unicode
	//LPCTSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	GraphicsClass* m_Graphics;
};


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/////////////
// GLOBALS //
/////////////
static SystemClass* ApplicationHandle = 0;


#endif