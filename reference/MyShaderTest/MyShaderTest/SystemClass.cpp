////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"
#include <iostream>
SystemClass::SystemClass()
{
	m_Graphics = 0;
}
SystemClass::SystemClass(const SystemClass& other)
{
}
SystemClass::~SystemClass()
{
}
bool SystemClass::Initialize()
{
	int w=640,h=640;
	bool result;

	this->InitializeWindows(w,h);

	
	// Create the Graphics object.
	m_Graphics = new GraphicsClass();
	if(!m_Graphics)
	{
		MessageBox(m_hwnd, L"Failed to create Graphics", L"Error", MB_OK);
		return false;
	}
	//Graphics
	result = m_Graphics->Initialize( L"Start.bmp",L"TextureMap.fx",m_hwnd );
	if(!result)
	{
		MessageBox(m_hwnd, L"Failed to initial Graphics", L"Error", MB_OK);
		return false;
	}
	//
	
	return true;
}


void SystemClass::Shutdown()
{
	//m_Demo.Shutdown();
	this->ShutdownWindows();
}


void SystemClass::Run()
{
	MSG msg;
	bool done, result;
	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	// Loop until there is a quit message from the window or the user.
	done = false;
	while(!done)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.  If frame processing fails then exit.
			//result = true;
			result = Frame();
			if(!result)
			{
				done = true;
			}
		}
	}
	return;
}


bool SystemClass::Frame()
{
	m_Graphics->Frame();
	return true;
}


LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}


void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	m_applicationName = L"ShaderTest";

	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof( WNDCLASSEX ) ;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = m_hinstance;
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
	wndClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = m_applicationName;

	if( !RegisterClassEx( &wndClass ) )
		return ;

	RECT rc = { 0, 0, screenWidth, screenHeight };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );

	m_hwnd = CreateWindow( m_applicationName, L"2D Texture Mapping", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, m_hinstance, NULL );

	if( !m_hwnd )
		return ;

	ShowWindow( m_hwnd, SW_SHOW );
}


void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
// 	if(FULL_SCREEN)
// 	{
// 		ChangeDisplaySettings(NULL, 0);
// 	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch( message )
	{
	case WM_PAINT:
		hDC = BeginPaint( hwnd, &paintStruct );
		EndPaint( hwnd, &paintStruct );
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	default:
		return DefWindowProc( hwnd, message, wParam, lParam );
	}

	return 0;
}