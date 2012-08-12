#include "stdafx.h"
#include "d3dApp.h"
#include "dxut/DXUT.h"

D3DApp::D3DApp()
{
	m_d3dDevice = NULL;
	m_SwapChain = NULL;
	m_DepthStencilBuffer = NULL;
	m_DepthStencilView2 = NULL;
	m_RenderTargetView = NULL;
	m_DepthStencilView = NULL;
	m_DeviceContext = NULL;

// 	m_Effect_Pics = NULL;
// 	m_PTech_Pics = NULL;
// 	m_PLayout_Pics = NULL;
// 	m_Pics_Width = NULL;
// 	m_Pics_Height = NULL;
// 	m_Pics_Texture = NULL;
// 	m_Buffer_Pics = NULL;

	m_hAppInst   = GetModuleHandle(NULL);

	m_AppPaused  = false;
	m_Minimized  = false;
	m_Maximized  = false;
	m_Resizing   = false;

	m_FrameStats = L"";

	m_DXUT_UI = NULL;
	//mFont               = 0;

	m_MainWndCaption = L"D3D11 Application";
	m_d3dDriverType  = D3D_DRIVER_TYPE_HARDWARE;
	//md3dDriverType  = D3D_DRIVER_TYPE_REFERENCE;
	m_ClearColor     = D3DXCOLOR(0.3f, 0.2f, 0.1f, 1.0f);
	mClientWidth    = 1440;
	mClientHeight   = 900;
}

D3DApp::~D3DApp()
{
	ReleaseCOM(m_d3dDevice);
	ReleaseCOM(m_SwapChain);
	ReleaseCOM(m_DepthStencilBuffer);
	ReleaseCOM(m_DepthStencilView2);
	ReleaseCOM(m_RenderTargetView);
	ReleaseCOM(m_DepthStencilView);
	ReleaseCOM(m_DeviceContext);

// 	ReleaseCOM(m_Effect_Pics);
// 	ReleaseCOM(m_PLayout_Pics);
	if (m_DXUT_UI)
		delete m_DXUT_UI;
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

void D3DApp::initApp(HWND hWnd, int w, int h)
{
	m_hMainWnd = hWnd;
	mClientWidth = w;
	mClientHeight = h;
	initDirect3D();
	LoadBlend();
}

void D3DApp::initDirect3D()
{
	m_DXUT_UI = new DXUTUI;
	m_DXUT_UI->InitDXUT();
	m_DXUT_UI->SetWindow(m_hMainWnd);
	m_DXUT_UI->CreateDevice(mClientWidth, mClientHeight);
	m_d3dDevice = m_DXUT_UI->GetDevice();
	m_DeviceContext = m_DXUT_UI->GetDeviceContext();
	m_SwapChain = m_DXUT_UI->GetSwapChaine();
	//OnResize(mClientWidth, mClientHeight);

	m_vbd.Usage = D3D11_USAGE_IMMUTABLE;
	m_vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_vbd.CPUAccessFlags = 0;
	m_vbd.MiscFlags = 0;
}


void D3DApp::OnResize(int w, int h)
{
	if (!m_d3dDevice) return;
	mClientWidth = w;
	mClientHeight = h;
	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.
	ReleaseCOM(m_RenderTargetView);
	ReleaseCOM(m_DepthStencilView);
	ReleaseCOM(m_DepthStencilBuffer);
	DXUTResizeDXGIBuffers(mClientWidth, mClientHeight, 0);
	// Resize the swap chain and recreate the render target view.
	//HR(mSwapChain->ResizeBuffers(2, mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, 0));
	ID3D11Texture2D* backBuffer;
	HR(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(m_d3dDevice->CreateRenderTargetView(backBuffer, 0, &m_RenderTargetView));
	ReleaseCOM(backBuffer);
	// Create the depth/stencil buffer and view.
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width     = mClientWidth;
	depthStencilDesc.Height    = mClientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count   = 1; // multisampling must match
	depthStencilDesc.SampleDesc.Quality = 0; // swap chain values.
	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;
	HR(m_d3dDevice->CreateTexture2D(&depthStencilDesc, 0, &m_DepthStencilBuffer));
	HR(m_d3dDevice->CreateDepthStencilView(m_DepthStencilBuffer, 0, &m_DepthStencilView));
	// Bind the render target view and depth/stencil view to the pipeline.
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
	// Set the viewport transform.
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width    = (float)mClientWidth;
	vp.Height   = (float)mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_DeviceContext->RSSetViewports(1, &vp);
}

void D3DApp::DrawScene()
{
	m_DXUT_UI->UpdataUI(0.1f);
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, m_ClearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);	
	//Draw Picture
// 	if (m_PictureVertices.size()>0)
// 	{
// 		UINT offset = 0;
// 		UINT stride2 = sizeof(PictureVertex);
// 		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
// 		m_DeviceContext->IASetInputLayout(m_PLayout_Pics);
// 		m_DeviceContext->IASetVertexBuffers(0, 1, &m_Buffer_Pics, &stride2, &offset);
// 		m_PTech_Pics->GetPassByIndex(0)->Apply(0, m_DeviceContext);
// 		m_DeviceContext->Draw((UINT)m_PictureVertices.size(),0);
// 	}
	m_DeviceContext->OMSetDepthStencilState(m_pDepthStencil_ZWriteOFF, 0);
	m_SwapChain->Present(0, 0);
}

void D3DApp::buildShaderFX()
{
	ID3D10Blob* pCode;
	ID3D10Blob* pError;

	//Picture
	HRESULT hr = 0;
// 	hr=D3DX11CompileFromFile(_T("shader\\picture.fx"), NULL, NULL, NULL, 
// 		"fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );
// 	if(FAILED(hr))
// 	{
// 		if( pError )
// 		{
// 			MessageBoxA(0, (char*)pError->GetBufferPointer(), 0, 0);
// 			ReleaseCOM(pError);
// 		}
// 		DXTrace(__FILE__, __LINE__, hr, _T("D3DX11CreateEffectFromFile"), TRUE);
// 	} 
// 	HR(D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Pics));
// 	m_PTech_Pics = m_Effect_Pics->GetTechniqueByName("PointTech");
// 	m_Pics_Width = m_Effect_Pics->GetVariableByName("width")->AsScalar();
// 	m_Pics_Height= m_Effect_Pics->GetVariableByName("height")->AsScalar();
// 	m_PMap_Pics  = m_Effect_Pics->GetVariableByName("gMap")->AsShaderResource();
// 	
// 	D3DX11_PASS_DESC PassDesc;
// 	m_PTech_Pics->GetPassByIndex(0)->GetDesc(&PassDesc);
// 	HR(m_d3dDevice->CreateInputLayout(VertexDesc_PICVertex, 2, PassDesc.pIAInputSignature,PassDesc.IAInputSignatureSize, &m_PLayout_Pics));

}

void D3DApp::buildPoint()
{
//	ReleaseCOM(m_Buffer_Pics);
//	m_PictureVertices.clear();
// 	if (!m_PictureVertices.empty())
// 	{
// 		m_vbd.ByteWidth = (UINT)(sizeof(PictureVertex) * m_PictureVertices.size());
// 		m_vbd.StructureByteStride=sizeof(PictureVertex);
// 		D3D11_SUBRESOURCE_DATA vinitData;
// 		vinitData.pSysMem = &m_PictureVertices[0];
// 		HR(m_d3dDevice->CreateBuffer(&m_vbd, &vinitData, &m_Buffer_Pics));
// 	}
	m_DeviceContext->OMSetDepthStencilState(m_pDepthStencil_ZWriteON, 0);
}

void D3DApp::LoadBlend()
{
	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
	depth_stencil_desc.DepthEnable = TRUE;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;

	depth_stencil_desc.StencilEnable = FALSE;
	depth_stencil_desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depth_stencil_desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	// 開啟zbuffer write
	if ( D3D_OK != m_d3dDevice->CreateDepthStencilState(&depth_stencil_desc, &m_pDepthStencil_ZWriteON) )
		return ;

	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	// 關閉zbuffer write
	if ( D3D_OK != m_d3dDevice->CreateDepthStencilState(&depth_stencil_desc, &m_pDepthStencil_ZWriteOFF) )
		return ;
	m_DeviceContext->OMSetDepthStencilState(m_pDepthStencil_ZWriteON, 0);
	CD3D11_BLEND_DESCX blend_state_desc(
		FALSE,
		FALSE,
		TRUE,
		D3D11_BLEND_ONE,
		D3D11_BLEND_ONE,
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_ONE,
		D3D11_BLEND_ONE,
		D3D11_BLEND_OP_ADD,
		D3D11_COLOR_WRITE_ENABLE_ALL);
	// ADD混色模式
	if ( D3D_OK != m_d3dDevice->CreateBlendState(&blend_state_desc, &m_pBlendState_ADD) )
		return;
	blend_state_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA ;
	blend_state_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	blend_state_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blend_state_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;

	// Alpha Blend混色模式
	if ( D3D_OK != m_d3dDevice->CreateBlendState(&blend_state_desc, &m_pBlendState_BLEND) )
		return ;
}


