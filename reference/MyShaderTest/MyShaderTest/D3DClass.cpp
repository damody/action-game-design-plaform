#include"D3DClass.h"
#include<D3Dcompiler.h>
#include <iostream>
#include <stdio.h>

D3DClass::D3DClass( ) : driverType_( D3D_DRIVER_TYPE_NULL ), featureLevel_( D3D_FEATURE_LEVEL_11_0 ),
                                d3dDevice_( 0 ), d3dContext_( 0 ), swapChain_( 0 ), backBufferTarget_( 0 )
{

}


D3DClass::~D3DClass( )
{
    Shutdown( );
}


bool D3DClass::Initialize( HWND hwnd )
{
    hwnd_ = hwnd;

    RECT dimensions;
    GetClientRect( hwnd, &dimensions );

    unsigned int width = dimensions.right - dimensions.left;
    unsigned int height = dimensions.bottom - dimensions.top;
	m_width = width;
	m_height = height;
	//Set projection world ortho matrix
	SetMatrix(width,height,1000.0f,0.1f);

	D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
    };

    unsigned int totalDriverTypes = ARRAYSIZE( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    unsigned int totalFeatureLevels = ARRAYSIZE( featureLevels );

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory( &swapChainDesc, sizeof( swapChainDesc ) );
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hwnd;
    swapChainDesc.Windowed = true;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    unsigned int creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    HRESULT result;
    unsigned int driver = 0;

    for( driver = 0; driver < totalDriverTypes; ++driver )
    {
        result = D3D11CreateDeviceAndSwapChain( 0, driverTypes[driver], 0, creationFlags,
                                                featureLevels, totalFeatureLevels,
                                                D3D11_SDK_VERSION, &swapChainDesc, &swapChain_,
                                                &d3dDevice_, &featureLevel_, &d3dContext_ );

        if( SUCCEEDED( result ) )
        {
            driverType_ = driverTypes[driver];
            break;
        }
    }

    if( FAILED( result ) )
    {
		MessageBox(hwnd, L"Failed to create the Direct3D device!", L"Error", MB_OK);
        //DXTRACE_MSG( "Failed to create the Direct3D device!" );
        return false;
    }

    ID3D11Texture2D* backBufferTexture;

    result = swapChain_->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&backBufferTexture );

    if( FAILED( result ) )
    {
		MessageBox(hwnd, L"Failed to get the swap chain back buffer!", L"Error", MB_OK);
        //DXTRACE_MSG( "Failed to get the swap chain back buffer!" );
        return false;
    }

    result = d3dDevice_->CreateRenderTargetView( backBufferTexture, 0, &backBufferTarget_ );

    if( backBufferTexture )
        backBufferTexture->Release( );

    if( FAILED( result ) )
    {
		MessageBox(hwnd, L"Failed to create the render target view!", L"Error", MB_OK);
        //DXTRACE_MSG( "Failed to create the render target view!" );
        return false;
    }

	
    d3dContext_->OMSetRenderTargets( 1, &backBufferTarget_, 0 );
    D3D11_VIEWPORT viewport;
    viewport.Width = static_cast<float>(width);
    viewport.Height = static_cast<float>(height);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;

    d3dContext_->RSSetViewports( 1, &viewport );

    return true;
}

void D3DClass::TEST(int w,int h,ID3D11RenderTargetView* rtv)
{
	/*
	HRESULT result;
	int Width = w,Height = h;
	result = swapChain_->ResizeBuffers(2,
		Width,
		Height,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		0 );
	if(FAILED(result))
	{
		printf("%x\n",result);
		std::cout<<"failed"<<std::endl;
	}*/
	
	if (swapChain_)
	{
		/*
		d3dContext_->OMSetRenderTargets(0, 0, 0);

		// Release all outstanding references to the swap chain's buffers.
		//g_pRenderTargetView->Release();

		HRESULT hr;
		// Preserve the existing buffer count and format.
		// Automatically choose the width and height to match the client rect for HWNDs.
		hr = swapChain_->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
		
		// Perform error handling here!

		// Get buffer and create a render-target-view.
		ID3D11Texture2D* pBuffer=0;
		
		// Perform error handling here!
		hr = swapChain_->GetBuffer(0, __uuidof( ID3D11Texture2D),
			(void**) &pBuffer );
		hr = d3dDevice_->CreateRenderTargetView(pBuffer, NULL,
			&renderTargetView);
		pBuffer->Release();
		
		// Perform error handling here!
		

		d3dContext_->OMSetRenderTargets(1, &renderTargetView, NULL );
		*/
		// Set up the viewport.
		
		D3D11_VIEWPORT vp;
		vp.Width = w;
		vp.Height = h;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		d3dContext_->RSSetViewports( 1, &vp );
		
	}
}
void D3DClass::SetMatrix(int screenWidth, int screenHeight,
					   float screenDepth, float screenNear)
{
	float fieldOfView, screenAspect;
	// Setup the projection matrix.
	fieldOfView = (float)D3DX_PI / 4.0f;
	screenAspect = (float)screenWidth / (float)screenHeight;

	// Create the projection matrix for 3D rendering.
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

	// Initialize the world matrix to the identity matrix.
	D3DXMatrixIdentity(&m_worldMatrix);

	// Create an orthographic projection matrix for 2D rendering.
	D3DXMatrixOrthoLH(&m_orthoMatrix, (float)screenWidth, (float)screenHeight, screenNear, screenDepth);
}

void D3DClass::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];


	// Setup the color to clear the buffer to.
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	// Clear the back buffer.
	d3dContext_->ClearRenderTargetView(backBufferTarget_, color);

	// Clear the depth buffer.
	d3dContext_->ClearDepthStencilView(0, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//Set Render to backbuffer
	//d3dContext_->OMSetRenderTargets( 1, &backBufferTarget_, 0 );

	return;
}


void D3DClass::EndScene()
{
	swapChain_->Present(0, 0);
}


void D3DClass::Shutdown( )
{
    if( backBufferTarget_ ) backBufferTarget_->Release( );
    if( swapChain_ ) swapChain_->Release( );
    if( d3dContext_ ) d3dContext_->Release( );
    if( d3dDevice_ ) d3dDevice_->Release( );    

    backBufferTarget_ = 0;
    swapChain_ = 0;
    d3dContext_ = 0;
    d3dDevice_ = 0;
}
void D3DClass::SetRenderToBackBuffer()
{
	D3D11_VIEWPORT vp;
	vp.Width = m_width;
	vp.Height = m_height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	d3dContext_->RSSetViewports( 1, &vp );
	d3dContext_->OMSetRenderTargets( 1, &backBufferTarget_, 0 );
}
ID3D11Device* D3DClass::GetDevice()
{
	return d3dDevice_;
}
ID3D11DeviceContext* D3DClass::GetDeviceContext()
{
	return d3dContext_;
}
IDXGISwapChain* D3DClass::GetSwapChain()
{
	return swapChain_;
}
ID3D11RenderTargetView* D3DClass::GetBackBufferTarget()
{
	return backBufferTarget_;
}
void D3DClass::GetProjectionMatrix(D3DXMATRIX& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;
}
void D3DClass::GetWorldMatrix(D3DXMATRIX& worldMatrix)
{
	worldMatrix = m_worldMatrix;
}
void D3DClass::GetOrthoMatrix(D3DXMATRIX& orthoMatrix)
{
	orthoMatrix = m_orthoMatrix;
}
