#include "stdafx.h"
#include "d3dApp_Picture.h"
#include "dxut/DXUT.h"
#include "global.h"
#include <d3d11.h>

D3DApp_Picture::D3DApp_Picture()
{
	m_d3dDevice = NULL;
	m_SwapChain = NULL;
	m_DepthStencilBuffer = NULL;
	m_DepthStencilView2 = NULL;
	m_RenderTargetView = NULL;
	m_DepthStencilView = NULL;
	m_DeviceContext = NULL;

	m_Buffer_Points = NULL;
	m_Effect_Points = NULL;
	m_PTech_Points = NULL;
	m_PLayout_Points = NULL;
	m_Points_Width = NULL;
	m_Points_Height = NULL;

	m_Buffer_Lines = NULL;
	m_Effect_Lines = NULL;
	m_PTech_Lines = NULL;
	m_PLayout_Lines = NULL;
	m_Lines_Width = NULL;
	m_Lines_Height = NULL;

	m_Pic = NULL;
	m_picX = 1;
	m_picY = 1;
	m_Effect_Pics = NULL;
	m_PTech_Pics = NULL;
	m_PLayout_Pics = NULL;
	m_Pics_Width = NULL;
	m_Pics_Height = NULL;
	m_Buffer_Pics = NULL;

	m_CenterX=0;
	m_CenterY=0;
	m_Center.Add(m_CenterX + 3,m_CenterY +3);
	m_Center.Add(m_CenterX - 3,m_CenterY -3);
	m_Center.Add(m_CenterX ,m_CenterY);
	m_Center.Add(m_CenterX - 3,m_CenterY +3);
	m_Center.Add(m_CenterX + 3,m_CenterY -3);

	m_hAppInst   = GetModuleHandle(NULL);

	m_AppPaused  = false;
	m_Minimized  = false;
	m_Maximized  = false;
	m_Resizing   = false;

	m_FrameStats = L"";

	//mFont               = 0;

	m_MainWndCaption = L"D3D11 Application";
	m_d3dDriverType  = D3D_DRIVER_TYPE_HARDWARE;
	//md3dDriverType  = D3D_DRIVER_TYPE_REFERENCE;
	m_ClearColor     = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
	mClientWidth    = 1440;
	mClientHeight   = 900;
}

D3DApp_Picture::~D3DApp_Picture()
{
	ReleaseCOM(m_d3dDevice);
	ReleaseCOM(m_SwapChain);
	ReleaseCOM(m_DepthStencilBuffer);
	ReleaseCOM(m_DepthStencilView2);
	ReleaseCOM(m_RenderTargetView);
	ReleaseCOM(m_DepthStencilView);
	ReleaseCOM(m_DeviceContext);
}

HINSTANCE D3DApp_Picture::getAppInst()
{
	return m_hAppInst;
}

HWND D3DApp_Picture::getMainWnd()
{
	return m_hMainWnd;
}

void D3DApp_Picture::initApp(HWND hWnd, int w, int h)
{
	m_hMainWnd = hWnd;
	mClientWidth = w;
	mClientHeight = h;
	initDirect3D();
	LoadBlend();

	float BlendFactor[4] = {0,0,0,0};
	m_DeviceContext->OMSetBlendState(m_pBlendState_BLEND, BlendFactor, 0xffffffff);
}

void D3DApp_Picture::initDirect3D()
{
	// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width  = mClientWidth;
	sd.BufferDesc.Height = mClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// No multisampling.
	sd.SampleDesc.Count   = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount  = 1;
	sd.OutputWindow = m_hMainWnd;
	sd.Windowed     = true;
	sd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags        = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH ;

	// Create the device.
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL  FeatureLevelsRequested = D3D_FEATURE_LEVEL_11_0;
	UINT               numLevelsRequested = 1;
	HR( D3D11CreateDeviceAndSwapChain(
		0,                 //default adapter
		m_d3dDriverType,
		0,                 // no software device
		createDeviceFlags,
		&FeatureLevelsRequested, 
		numLevelsRequested,
		D3D11_SDK_VERSION,
		&sd,
		&m_SwapChain,
		&m_d3dDevice,
		&m_FeatureLevelsSupported,
		&m_DeviceContext) );

	m_TextureManager = new TextureManager(m_d3dDevice);
	OnResize(mClientWidth, mClientHeight);

	m_vbd.Usage = D3D11_USAGE_IMMUTABLE;
	m_vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_vbd.CPUAccessFlags = 0;
	m_vbd.MiscFlags = 0;
	int t = m_TextureManager->AddTexture("media\\Tamplete.png");
	m_Templete = m_TextureManager->GetTexture(t).get();
}


void D3DApp_Picture::OnResize(int w, int h)
{
	if (!m_d3dDevice) return;
	mClientWidth = w;
	mClientHeight = h;
	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.
	ReleaseCOM(m_RenderTargetView);
	ReleaseCOM(m_DepthStencilView);
	ReleaseCOM(m_DepthStencilBuffer);
	// Resize the swap chain and recreate the render target view.
	HR(m_SwapChain->ResizeBuffers(1, mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, 0));
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

	if (m_Points_Width!=NULL && m_Points_Height!=NULL)
	{
		m_Points_Width->SetFloat((float)mClientWidth);
		m_Points_Height->SetFloat((float)mClientHeight);
	}

	if (m_Lines_Width!=NULL && m_Lines_Height!=NULL)
	{
		m_Lines_Width->SetFloat((float)mClientWidth);
		m_Lines_Height->SetFloat((float)mClientHeight);
	}

	if (m_Pics_Width!=NULL && m_Pics_Height!=NULL)
	{
		m_Pics_Width->SetFloat((float)mClientWidth);
		m_Pics_Height->SetFloat((float)mClientHeight);
	}
}

void D3DApp_Picture::DrawScene()
{
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, m_ClearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);	
	m_DeviceContext->OMSetDepthStencilState(m_pDepthStencil_ZWriteOFF, 0);

	if(m_Pic!=NULL){
		UINT offset = 0;
		UINT stride2 = sizeof(PictureVertex);
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		m_DeviceContext->IASetInputLayout(m_PLayout_Pics);
		m_DeviceContext->IASetVertexBuffers(0, 1, &m_Buffer_Pics, &stride2, &offset);
		m_PMap_Pics->SetResource(GetTextureManager().GetTexture(m_Pic->m_TextureID)->texture);
		m_BMap_Pics->SetResource(m_Templete->texture);
		m_PTech_Pics->GetPassByIndex(0)->Apply(0, m_DeviceContext);
		m_DeviceContext->Draw(1,0);
	}

	if (m_LineVertices.size()>0)
	{
		UINT offset = 0;
		UINT stride2 = sizeof(LineVertex);
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		m_DeviceContext->IASetInputLayout(m_PLayout_Lines);
		m_DeviceContext->IASetVertexBuffers(0, 1, &m_Buffer_Lines, &stride2, &offset);
		m_PTech_Lines->GetPassByIndex(0)->Apply(0, m_DeviceContext);
		m_DeviceContext->Draw((UINT)m_LineVertices.size(),0);
	}

	if (m_PointVertices.size()>0)
	{
		UINT offset = 0;
		UINT stride2 = sizeof(PointVertex);
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		m_DeviceContext->IASetInputLayout(m_PLayout_Points);
		m_DeviceContext->IASetVertexBuffers(0, 1, &m_Buffer_Points, &stride2, &offset);
		m_PTech_Points->GetPassByIndex(0)->Apply(0, m_DeviceContext);
		m_DeviceContext->Draw((UINT)m_PointVertices.size(),0);
	}

	m_SwapChain->Present(0, 0);
}

void D3DApp_Picture::buildShaderFX()
{
	ID3D10Blob* pCode;
	ID3D10Blob* pError;

	HRESULT hr = 0;
	hr=D3DX11CompileFromFile(_T("shader\\Point.fx"), NULL, NULL, NULL, 
		"fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );
	if(FAILED(hr))
	{
		if( pError )
		{
			MessageBoxA(0, (char*)pError->GetBufferPointer(), 0, 0);
			ReleaseCOM(pError);
		}
		DXTrace(__FILE__, __LINE__, hr, _T("D3DX11CreateEffectFromFile"), TRUE);
	} 
	HR(D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Points));
	m_PTech_Points = m_Effect_Points->GetTechniqueByName("PointTech");
	m_Points_Width = m_Effect_Points->GetVariableByName("sceneW")->AsScalar();
	m_Points_Height= m_Effect_Points->GetVariableByName("sceneH")->AsScalar();

	D3DX11_PASS_DESC PassDesc;
	m_PTech_Points->GetPassByIndex(0)->GetDesc(&PassDesc);
	HR(m_d3dDevice->CreateInputLayout(VertexDesc_PointVertex, 3, PassDesc.pIAInputSignature,PassDesc.IAInputSignatureSize, &m_PLayout_Points));

	hr = 0;
	hr=D3DX11CompileFromFile(_T("shader\\Line.fx"), NULL, NULL, NULL, 
		"fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );
	if(FAILED(hr))
	{
		if( pError )
		{
			MessageBoxA(0, (char*)pError->GetBufferPointer(), 0, 0);
			ReleaseCOM(pError);
		}
		DXTrace(__FILE__, __LINE__, hr, _T("D3DX11CreateEffectFromFile"), TRUE);
	} 
	HR(D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Lines));
	m_PTech_Lines = m_Effect_Lines->GetTechniqueByName("PointTech");
	m_Lines_Width = m_Effect_Lines->GetVariableByName("sceneW")->AsScalar();
	m_Lines_Height= m_Effect_Lines->GetVariableByName("sceneH")->AsScalar();

	D3DX11_PASS_DESC PassDesc_Line;
	m_PTech_Lines->GetPassByIndex(0)->GetDesc(&PassDesc_Line);
	HR(m_d3dDevice->CreateInputLayout(VertexDesc_LineVertex, 2, PassDesc_Line.pIAInputSignature,PassDesc_Line.IAInputSignatureSize, &m_PLayout_Lines));

	hr = 0;
	hr=D3DX11CompileFromFile(_T("shader\\picture.fx"), NULL, NULL, NULL, 
		"fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );
	if(FAILED(hr))
	{
		if( pError )
		{
			MessageBoxA(0, (char*)pError->GetBufferPointer(), 0, 0);
			ReleaseCOM(pError);
		}
		DXTrace(__FILE__, __LINE__, hr, _T("D3DX11CreateEffectFromFile"), TRUE);
	} 
	HR(D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Pics));
	m_PTech_Pics = m_Effect_Pics->GetTechniqueByName("PointTech");
	m_Pics_Width = m_Effect_Pics->GetVariableByName("sceneW")->AsScalar();
	m_Pics_Height= m_Effect_Pics->GetVariableByName("sceneH")->AsScalar();
	m_PMap_Pics =m_Effect_Pics->GetVariableByName("gMap")->AsShaderResource();
	m_BMap_Pics =m_Effect_Pics->GetVariableByName("bMap")->AsShaderResource();

	D3DX11_PASS_DESC PassDesc_Pic;
	m_PTech_Pics->GetPassByIndex(0)->GetDesc(&PassDesc_Pic);
	HR(m_d3dDevice->CreateInputLayout(VertexDesc_PICVertex, 3, PassDesc_Pic.pIAInputSignature,PassDesc_Pic.IAInputSignatureSize, &m_PLayout_Pics));

	m_vbd.Usage = D3D11_USAGE_IMMUTABLE;
	m_vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_vbd.CPUAccessFlags = 0;
	m_vbd.MiscFlags = 0;
}

void D3DApp_Picture::buildPoint()
{
	//Point
	ReleaseCOM(m_Buffer_Points);
	m_PointVertices.clear();
	for(Bounds::iterator it=m_Body.begin(); it!=m_Body.end();++it){
		PointVertices pvs=it->BuildPoint();
		m_PointVertices.insert(m_PointVertices.end(),pvs.begin(),pvs.end());
	}
	for(Bounds::iterator it=m_Attack.begin(); it!=m_Attack.end();++it){
		PointVertices pvs=it->BuildPoint();
		m_PointVertices.insert(m_PointVertices.end(),pvs.begin(),pvs.end());
	}
	if (!m_PointVertices.empty())
	{
		m_vbd.ByteWidth = (UINT)(sizeof(PointVertex) * m_PointVertices.size());
		m_vbd.StructureByteStride=sizeof(PointVertex);
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &m_PointVertices[0];
		HR(m_d3dDevice->CreateBuffer(&m_vbd, &vinitData, &m_Buffer_Points));
	}

	//Line
	ReleaseCOM(m_Buffer_Lines);
	m_LineVertices.clear();
	for(Bounds::iterator it=m_Body.begin(); it!=m_Body.end();++it){
		LineVertices lvs=it->BuildLine();
		m_LineVertices.insert(m_LineVertices.end(),lvs.begin(),lvs.end());
	}
	for(Bounds::iterator it=m_Attack.begin(); it!=m_Attack.end();++it){
		LineVertices lvs=it->BuildLine();
		m_LineVertices.insert(m_LineVertices.end(),lvs.begin(),lvs.end());
	}
	LineVertices lvs=m_Center.BuildLine(false);
	m_LineVertices.insert(m_LineVertices.end(),lvs.begin(),lvs.end());
	if (!m_LineVertices.empty())
	{
		m_vbd.ByteWidth = (UINT)(sizeof(LineVertex) * m_LineVertices.size());
		m_vbd.StructureByteStride=sizeof(LineVertex);
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &m_LineVertices[0];
		HR(m_d3dDevice->CreateBuffer(&m_vbd, &vinitData, &m_Buffer_Lines));
	}

	if (m_Pic != NULL)
	{
		PictureVertex pv;
		pv.position.x = g_Picture_OffsetX;
		pv.position.y = -g_Picture_OffsetY;
		pv.size.x = m_Pic->m_Width * g_Picture_Scale;
		pv.size.y = m_Pic->m_Height * g_Picture_Scale;
		pv.picpos.x = 1;
		pv.picpos.y = 1;
		pv.picpos.z = 1;
		pv.picpos.w = 1;

		m_vbd.ByteWidth = (UINT)(sizeof(PictureVertex));
		m_vbd.StructureByteStride=sizeof(PictureVertex);
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &pv;
		HR(m_d3dDevice->CreateBuffer(&m_vbd, &vinitData, &m_Buffer_Pics));
	}

	m_DeviceContext->OMSetDepthStencilState(m_pDepthStencil_ZWriteON, 0);
}

void D3DApp_Picture::LoadBlend()
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

void D3DApp_Picture::SetPic( PictureData *pic,float x,float y )
{
	m_Pic = pic;
	m_picX = x;
	m_picY = y;
}

void D3DApp_Picture::SetCenter( float x,float y )
{
	m_Center.Transale(x-m_CenterX,y-m_CenterY);
	m_CenterX = x;
	m_CenterY = y;
}
