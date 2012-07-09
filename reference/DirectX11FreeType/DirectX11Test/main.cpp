#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <D3Dcompiler.h>
#include <DxErr.h>
#include <xnamath.h>

#include <math.h>
#include <wchar.h>
#include <locale> 
#include <codecvt> 
#include <string> 
#include <fstream> 
#include <cstdlib> 
#include "FTBITMAP.h"

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
bool Initialize(HWND hwnd);
void Render();
bool CompileD3DShader( wchar_t* filePath, char* entry, char* shaderModel, ID3DBlob** buffer );

struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};

ID3D11Device* d3dDevice_;
ID3D11DeviceContext* d3dContext_;
IDXGISwapChain* swapChain_;
ID3D11RenderTargetView* backBufferTarget_;

ID3D11VertexShader* solidColorVS;
ID3D11PixelShader* solidColorPS;
ID3D11InputLayout* inputLayout;
ID3D11Buffer* vertexBuffer;
ID3D11ShaderResourceView* colorMap;
ID3D11SamplerState* colorMapSampler;

float** characterImages;
ID3D11ShaderResourceView** shaderResViews;
std::wstring text;
char text2[256];
UINT count = 0;
UINT current = 3;

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow )
{
	FILE * pFile = fopen ("asd.txt" , "r");

	if (pFile == NULL) perror ("Error opening file");
	else
	{
		while ( ! feof (pFile) )
		{
			fscanf(pFile, "%[^\n]", text2);
		}
		fclose (pFile);
	}

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> ucs2conv;
	text = ucs2conv.from_bytes(text2);
	text.erase(0, 1);

	UNREFERENCED_PARAMETER( prevInstance );
	UNREFERENCED_PARAMETER( cmdLine );
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof( WNDCLASSEX ) ;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
	wndClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = L"DX11BookWindowClass";
	if( !RegisterClassEx( &wndClass ) )
		return -1;
	RECT rc = { 0, 0, 640, 480 };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	HWND hwnd = CreateWindowA( "DX11BookWindowClass", "Blank Win32 Window",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.
		left,
		rc.bottom - rc.top, NULL, NULL, hInstance, NULL );
	if( !hwnd )
		return -1;
	ShowWindow( hwnd, cmdShow );

	Initialize(hwnd);

	MSG msg = { 0 };
	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			Render();
		}

		if(GetAsyncKeyState(VK_LEFT) & 0x1 )
		{

			if(current == 0)
				current = text.length()-1;
			else
				current--;
		}
		if(GetAsyncKeyState(VK_RIGHT) & 0x1 )
		{
			current++;

			if(current == text.length())
				current = 0;
		}
	}

	if( backBufferTarget_ ) backBufferTarget_->Release( );
	if( swapChain_ ) swapChain_->Release( );
	if( d3dContext_ ) d3dContext_->Release( );
	if( d3dDevice_ ) d3dDevice_->Release( );
	d3dDevice_ = 0;
	d3dContext_ = 0;
	swapChain_ = 0;
	backBufferTarget_ = 0;

	return static_cast<int>( msg.wParam );
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

bool Initialize(HWND hwnd)
{
	RECT dimensions;
	GetClientRect( hwnd, &dimensions );
	unsigned int width = dimensions.right - dimensions.left;
	unsigned int height = dimensions.bottom - dimensions.top;

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

	D3D_DRIVER_TYPE driverType_;
	D3D_FEATURE_LEVEL featureLevel_;

	unsigned int creationFlags = 0;
#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	HRESULT result;
	unsigned int driver = 0;
	for( driver = 0; driver < totalDriverTypes; ++driver )
	{
		result = D3D11CreateDeviceAndSwapChain( 0, driverTypes[driver], 0,
			creationFlags, featureLevels, totalFeatureLevels,
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
		DXTRACE_MSG( "Failed to create the Direct3D device!" );
		return false;
	}

	ID3D11Texture2D* backBufferTexture;

	result = swapChain_->GetBuffer( 0, __uuidof( ID3D11Texture2D ),
		( LPVOID* )&backBufferTexture );
	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to get the swap chain back buffer!" );
		return false;
	}
	result = d3dDevice_->CreateRenderTargetView( backBufferTexture, 0,
		&backBufferTarget_ );
	if( backBufferTexture )
		backBufferTexture->Release( );
	if( FAILED( result ) )
	{
		DXTRACE_MSG( "Failed to create the render target view!" );
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

	//------------------------------------------------------------------------------------------------------------------------
	ID3DBlob* vsBuffer = 0;

	bool compileResult = CompileD3DShader( L"TextureMap.fx", "VS_Main", "vs_4_0", &vsBuffer );

	if( compileResult == false )
	{
		MessageBox( 0, L"Error loading vertex shader!", L"Compile Error", MB_OK );
		return false;
	}

	HRESULT d3dResult;

	d3dResult = d3dDevice_->CreateVertexShader( vsBuffer->GetBufferPointer( ),
		vsBuffer->GetBufferSize( ), 0, &solidColorVS );

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( "Failed to create vertex shader!" );
		if( vsBuffer )
			vsBuffer->Release( );

		return false;
	}

	D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	unsigned int totalLayoutElements = ARRAYSIZE( solidColorLayout );

	d3dResult = d3dDevice_->CreateInputLayout( solidColorLayout, totalLayoutElements,
		vsBuffer->GetBufferPointer( ), vsBuffer->GetBufferSize( ), &inputLayout );

	vsBuffer->Release( );

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( "Failed to create input layout!" );
		return false;
	}

	ID3DBlob* psBuffer = 0;

	compileResult = CompileD3DShader( L"TextureMap.fx", "PS_Main", "ps_4_0", &psBuffer );

	if( compileResult == false )
	{
		MessageBox( 0, L"Error loading pixel shader!", L"Compile Error", MB_OK );
		return false;
	}

	d3dResult = d3dDevice_->CreatePixelShader( psBuffer->GetBufferPointer( ),
		psBuffer->GetBufferSize( ), 0, &solidColorPS );

	psBuffer->Release( );

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( "Failed to create pixel shader!" );
		return false;
	}

	/*d3dResult = D3DX11CreateShaderResourceViewFromFile( d3dDevice_,
		"font.dds", 0, 0, &colorMap, 0 );

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( "Failed to load the texture image!" );
		return false;
	}*/

	D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory( &colorMapDesc, sizeof( colorMapDesc ) );
	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	d3dResult = d3dDevice_->CreateSamplerState( &colorMapDesc, &colorMapSampler );

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( "Failed to create color map sampler state!" );
		return false;
	}

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory( &vertexDesc, sizeof( vertexDesc ) );
	vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof( VertexPos ) * 6;

	d3dResult = d3dDevice_->CreateBuffer( &vertexDesc, 0, &vertexBuffer );

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( "Failed to create vertex buffer!" );
		return false;
	}

	//--------------------------------------------------------------------------------------------------------
	int           n, num_chars;

	num_chars     = text.length();
	characterImages = new float*[num_chars];
	shaderResViews = new ID3D11ShaderResourceView*[num_chars];
	count = num_chars;

	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory( &texDesc, sizeof( texDesc ) );
	texDesc.Width = 64;
	texDesc.Height = 64;
	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	D3D11_SHADER_RESOURCE_VIEW_DESC srDesc;
	srDesc.Format = texDesc.Format;
	srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srDesc.Texture2D.MostDetailedMip = 0;
	srDesc.Texture2D.MipLevels = 1;

	D3D11_SUBRESOURCE_DATA sSubData;
	sSubData.pSysMem = 0; 
	sSubData.SysMemPitch = (UINT) (64 * 4); 
	sSubData.SysMemSlicePitch = (UINT) (64 * 64 * 4); 

	for ( n = 0; n < num_chars; n++ )
	{
		Bitmap bitmap;

		if(!rasters(text[n], bitmap)) {
			return false;
		}

		characterImages[n] = new float[bitmap.width * bitmap.height*4];

		texDesc.Width = bitmap.width;
		texDesc.Height = bitmap.height;

		sSubData.SysMemPitch = (UINT)(bitmap.width*4*4);
		sSubData.SysMemSlicePitch = (UINT)(bitmap.width*bitmap.height*4*4);

		sSubData.pSysMem = characterImages[n];

		printf("%d %d\n", bitmap.width, bitmap.height);

		for(int j=0; j<bitmap.height; j++) {
			for(int i=0; i<bitmap.pitch; i++) {
				for(int k=7; k>=0; k--){
					if(7-k+i*8 == bitmap.width)
						break;

					int offset = (j*bitmap.width + i*8 + 7 - k)*4;
					if((bitmap.data[i+j*bitmap.pitch] & 0x1<<k))
					{
						characterImages[n][offset] = 1.0f;
						characterImages[n][offset+1] = 1.0f;
						characterImages[n][offset+2] = 1.0f;
						characterImages[n][offset+3] = 1.0f;
					}
					else
					{
						characterImages[n][offset] = 0.0f;
						characterImages[n][offset+1] = 0.0f;
						characterImages[n][offset+2] = 0.0f;
						characterImages[n][offset+3] = 1.0f;
					}
				}
			}
		}

		/*IplImage* img = 0;
		img = cvLoadImage("test.bmp", 1);
		if(img->origin == 0)
			cvFlip(img);

		characterImages[n] = new float[img->width*img->height*3];

		for(UINT i=0;i<img->height;i++)
		{
			for(UINT j=0;j<img->width;j++)
			{
				int offset1 = (i*img->width + j)*3;
				int offset2 = i*img->widthStep + j*3;
				characterImages[n][offset1] = img->imageData[offset2] / 255.0f;
				characterImages[n][offset1+1] = img->imageData[offset2+1] / 255.0f;
				characterImages[n][offset1+2] = img->imageData[offset2+2] / 255.0f;
			}
		}

		texDesc.Width = img->width;
		texDesc.Height = img->height;

		sSubData.SysMemPitch = (UINT)(img->width*3*4);
		sSubData.SysMemSlicePitch = (UINT)(img->width * img->height*3*4);

		sSubData.pSysMem = characterImages[n];*/

		ID3D11Texture2D* pTexture;
		ID3D11ShaderResourceView* pShaderResView;
		d3dResult = d3dDevice_->CreateTexture2D(&texDesc, &sSubData, &pTexture);

		if(FAILED(d3dResult))
		{
			DXTRACE_MSG( "Failed to create texture2D!" );
			return false;
		}

		d3dResult = d3dDevice_->CreateShaderResourceView(pTexture, &srDesc, &pShaderResView);

		if(FAILED(d3dResult))
		{
			DXTRACE_MSG( "Failed to create ShaderResourceView!" );
			return false;
		}

		delete[] bitmap.data;
		delete[] characterImages[n];
		shaderResViews[n] = pShaderResView;
	}

	delete[] characterImages;

	return true;
}

void Render()
{
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	d3dContext_->ClearRenderTargetView( backBufferTarget_, clearColor );

	unsigned int stride = sizeof( VertexPos );
	unsigned int offset = 0;

	d3dContext_->IASetInputLayout( inputLayout );
	d3dContext_->IASetVertexBuffers( 0, 1, &vertexBuffer, &stride, &offset );
	d3dContext_->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	d3dContext_->VSSetShader( solidColorVS, 0, 0 );
	d3dContext_->PSSetShader( solidColorPS, 0, 0 );
	d3dContext_->PSSetSamplers(0, 1, &colorMapSampler);
	
	UINT i = current;
		d3dContext_->PSSetShaderResources(0, 1, &shaderResViews[i]);
		D3D11_MAPPED_SUBRESOURCE mapResource;
		HRESULT d3dResult = d3dContext_->Map( vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource );

		VertexPos *spritePtr = ( VertexPos* )mapResource.pData;

		spritePtr[0].pos = XMFLOAT3( 1.0f,   1.0f, 1.0f );
		spritePtr[1].pos = XMFLOAT3( 1.0f,   0.0f,   1.0f );
		spritePtr[2].pos = XMFLOAT3( 0.0f, 0.0f,   1.0f );
		spritePtr[3].pos = XMFLOAT3( 0.0f, 0.0f,   1.0f );
		spritePtr[4].pos = XMFLOAT3( 0.0f, 1.0f, 1.0f );
		spritePtr[5].pos = XMFLOAT3( 1.0f,   1.0f, 1.0f );

		spritePtr[0].tex0 = XMFLOAT2( 1.0f, 0.0f );
		spritePtr[1].tex0 = XMFLOAT2( 1.0f, 1.0f );
		spritePtr[2].tex0 = XMFLOAT2( 0.0f, 1.0f );
		spritePtr[3].tex0 = XMFLOAT2( 0.0f, 1.0f );
		spritePtr[4].tex0 = XMFLOAT2( 0.0f, 0.0f );
		spritePtr[5].tex0 = XMFLOAT2( 1.0f, 0.0f );

		d3dContext_->Unmap( vertexBuffer, 0 );
		d3dContext_->Draw( 6, 0 );

	swapChain_->Present( 0, 0 );
}

bool CompileD3DShader( wchar_t* filePath, char* entry, char* shaderModel, ID3DBlob** buffer )
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* errorBuffer = 0;
	HRESULT result;
	
	result = D3DX11CompileFromFile( filePath, 0, 0, entry, shaderModel,
		shaderFlags, 0, 0, buffer, &errorBuffer, 0 );

	if( FAILED( result ) )
	{
		if( errorBuffer != 0 )
		{
			OutputDebugStringA( ( char* )errorBuffer->GetBufferPointer( ) );
			errorBuffer->Release( );
		}

		return false;
	}

	if( errorBuffer != 0 )
		errorBuffer->Release( );

	return true;
}