#include "StdGame.h"
#include "d3dApp.h"
#include "ui/dxut/DXUT.h"
#include "InputState.h"
#include "global.h"
#include <auto_link_effect11.hpp>

LRESULT CALLBACK MainWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	static D3DApp* app = 0;

	switch ( message )
	{
	case WM_CREATE:
	{
		// Get the 'this' pointer we passed to CreateWindow via the lpParam parameter.
		CREATESTRUCT* cs = ( CREATESTRUCT* )lParam;
		app = ( D3DApp* )cs->lpCreateParams;
		return 0;
	}
	}

	// Don't start processing messages until after WM_CREATE.
	if ( app )
	{
		return app->msgProc( message, wParam, lParam );
	}
	else
	{
		return DefWindowProc( hWnd, message, wParam, lParam );
	}
}

D3DApp::D3DApp()
{
	m_hAppInst   = GetModuleHandle( NULL );
	m_AppPaused  = false;
	m_Minimized  = false;
	m_Maximized  = false;
	m_Resizing   = false;
	m_FrameStats = L"";
	m_d3dDevice          = 0;
	m_SwapChain          = 0;
	m_DepthStencilBuffer = 0;
	m_RenderTargetView   = 0;
	m_DepthStencilView   = 0;
	m_DXUT_UI = NULL;
	//mFont               = 0;
	m_MainWndCaption = L"D3D11 Application";
	m_d3dDriverType  = D3D_DRIVER_TYPE_HARDWARE;
	//md3dDriverType  = D3D_DRIVER_TYPE_REFERENCE;
	m_ClearColor     = D3DXCOLOR( 0.3f, 0.2f, 0.1f, 1.0f );
	m_ClientWidth    = 1440;
	m_ClientHeight   = 900;
}

D3DApp::~D3DApp()
{
	ReleaseCOM( m_RenderTargetView );
	ReleaseCOM( m_DepthStencilView );
	ReleaseCOM( m_SwapChain );
	ReleaseCOM( m_DepthStencilBuffer );
	ReleaseCOM( m_d3dDevice );

	if ( m_DXUT_UI )
	{
		delete m_DXUT_UI;
	}

	//	ReleaseCOM(mFont);
}
HINSTANCE D3DApp::getAppInst()
{
	return m_hAppInst;
}

HWND D3DApp::getMainWnd()
{
	return m_hMainWnd;
}

void D3DApp::initApp()
{
	initMainWindow();
	initDirect3D();
	InputStateS::instance().InputInit( m_hMainWnd, m_hAppInst );
}

void D3DApp::initDirect3D()
{
	m_DXUT_UI = new DXUTUI;
	m_DXUT_UI->InitDXUT();
	m_DXUT_UI->SetWindow( m_hMainWnd );
	m_DXUT_UI->CreateDevice( m_ClientWidth, m_ClientHeight );
	m_d3dDevice = m_DXUT_UI->GetDevice();
	g_d3dDevice = m_DXUT_UI->GetDevice();
	m_DeviceContext = m_DXUT_UI->GetDeviceContext();
	g_DeviceContext = m_DXUT_UI->GetDeviceContext();
	m_SwapChain = m_DXUT_UI->GetSwapChaine();
	OnResize();
}


void D3DApp::OnResize()
{
	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.
	ReleaseCOM( m_RenderTargetView );
	ReleaseCOM( m_DepthStencilView );
	ReleaseCOM( m_DepthStencilBuffer );
	DXUTResizeDXGIBuffers( m_ClientWidth, m_ClientHeight, 0 );
	// Resize the swap chain and recreate the render target view.
	//HR(mSwapChain->ResizeBuffers(2, mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, 0));
	ID3D11Texture2D* backBuffer;
	HR( m_SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), reinterpret_cast<void**>( &backBuffer ) ) );
	HR( m_d3dDevice->CreateRenderTargetView( backBuffer, 0, &m_RenderTargetView ) );
	ReleaseCOM( backBuffer );
	// Create the depth/stencil buffer and view.
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width     = m_ClientWidth;
	depthStencilDesc.Height    = m_ClientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count   = 1; // multisampling must match
	depthStencilDesc.SampleDesc.Quality = 0; // swap chain values.
	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags      = 0;
	HR( m_d3dDevice->CreateTexture2D( &depthStencilDesc, 0, &m_DepthStencilBuffer ) );
	HR( m_d3dDevice->CreateDepthStencilView( m_DepthStencilBuffer, 0, &m_DepthStencilView ) );
	// Bind the render target view and depth/stencil view to the pipeline.
	m_DeviceContext->OMSetRenderTargets( 1, &m_RenderTargetView, m_DepthStencilView );
	// Set the viewport transform.
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width    = ( float )m_ClientWidth;
	vp.Height   = ( float )m_ClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_DeviceContext->RSSetViewports( 1, &vp );
}
void D3DApp::DrawScene()
{
	m_DeviceContext->ClearRenderTargetView( m_RenderTargetView, m_ClearColor );
	m_DeviceContext->ClearDepthStencilView( m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );
}

LRESULT D3DApp::msgProc( UINT msg, WPARAM wParam, LPARAM lParam )
{
	if ( m_DXUT_UI )
	{
		m_DXUT_UI->MsgProc( m_hMainWnd, msg, wParam, lParam );
	}

	switch ( msg )
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated.
		// We pause the game when the window is deactivated and unpause it
		// when it becomes active.
	case WM_ACTIVATE:
		if ( LOWORD( wParam ) == WA_INACTIVE )
		{
			m_AppPaused = true;
			m_Timer.stop();
		}
		else
		{
			m_AppPaused = false;
			m_Timer.start();
		}

		return 0;

		// WM_SIZE is sent when the user resizes the window.
	case WM_SIZE:
		// Save the new client area dimensions.
		m_ClientWidth  = LOWORD( lParam );
		m_ClientHeight = HIWORD( lParam );

		if ( m_d3dDevice )
		{
			if ( wParam == SIZE_MINIMIZED )
			{
				m_AppPaused = true;
				m_Minimized = true;
				m_Maximized = false;
			}
			else if ( wParam == SIZE_MAXIMIZED )
			{
				m_AppPaused = false;
				m_Minimized = false;
				m_Maximized = true;
				OnResize();
			}
			else if ( wParam == SIZE_RESTORED )
			{
				// Restoring from minimized state?
				if ( m_Minimized )
				{
					m_AppPaused = false;
					m_Minimized = false;
					OnResize();
				}
				// Restoring from maximized state?
				else if ( m_Maximized )
				{
					m_AppPaused = false;
					m_Maximized = false;
					OnResize();
				}
				else if ( m_Resizing )
				{
					// If user is dragging the resize bars, we do not resize
					// the buffers here because as the user continuously
					// drags the resize bars, a stream of WM_SIZE messages are
					// sent to the window, and it would be pointless (and slow)
					// to resize for each WM_SIZE message received from dragging
					// the resize bars.  So instead, we reset after the user is
					// done resizing the window and releases the resize bars, which
					// sends a WM_EXITSIZEMOVE message.
				}
				else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
				{
					OnResize();
				}
			}
		}

		return 0;

		// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		m_AppPaused = true;
		m_Resizing  = true;
		m_Timer.stop();
		return 0;

		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		m_AppPaused = false;
		m_Resizing  = false;
		m_Timer.start();
		OnResize();
		return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses
		// a key that does not correspond to any mnemonic or accelerator key.
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT( 0, MNC_CLOSE );

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		( ( MINMAXINFO* )lParam )->ptMinTrackSize.x = 200;
		( ( MINMAXINFO* )lParam )->ptMinTrackSize.y = 200;
		return 0;
	}

	return DefWindowProc( m_hMainWnd, msg, wParam, lParam );
}


int D3DApp::run()
{
	MSG msg = {0};
	m_Timer.reset();

	while ( msg.message != WM_QUIT )
	{
		// If there are Window messages then process them.
		if ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		// Otherwise, do animation/game stuff.
		else
		{
			//Sleep(1);//不想打爆CPU的時候就用吧
			m_Timer.tick();

			if ( !m_AppPaused )
			{
				UpdateScene( m_Timer.getDeltaTime() );
			}
			else
			{
				Sleep( 1 );
			}

			//DrawScene();
		}
	}

	return ( int )msg.wParam;
}

void D3DApp::initMainWindow()
{
	WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = MainWndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hAppInst;
	wc.hIcon         = LoadIcon( 0, IDI_APPLICATION );
	wc.hCursor       = LoadCursor( 0, IDC_ARROW );
	wc.hbrBackground = ( HBRUSH )GetStockObject( NULL_BRUSH );
	wc.lpszMenuName  = 0;
	wc.lpszClassName = _T( "D3DWndClassName" );

	if ( !RegisterClass( &wc ) )
	{
		MessageBox( 0, _T( "RegisterClass FAILED" ), 0, 0 );
		PostQuitMessage( 0 );
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, m_ClientWidth, m_ClientHeight };
	AdjustWindowRect( &R, WS_OVERLAPPEDWINDOW, false );
	int width  = R.right - R.left;
	int height = R.bottom - R.top;
	m_hMainWnd = CreateWindow( _T( "D3DWndClassName" ), _T( "Demo" ),
	                           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, m_hAppInst, this );

	if ( !m_hMainWnd )
	{
		MessageBox( 0, _T( "CreateWindow FAILED" ), 0, 0 );
		PostQuitMessage( 0 );
	}

	ShowWindow( m_hMainWnd, SW_SHOW );
	UpdateWindow( m_hMainWnd );
	//Input di(DISCL_FOREGROUND | DISCL_EXCLUSIVE,DISCL_NONEXCLUSIVE|DISCL_FOREGROUND,mhAppInst,mhMainWnd);
	//DirectInput=&di;
}
