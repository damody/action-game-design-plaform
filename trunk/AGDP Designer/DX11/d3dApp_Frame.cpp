#include "stdafx.h"
#include "d3dApp_Frame.h"
#include "global.h"
#include <d3d11.h>

D3DApp_Frame::D3DApp_Frame()
{
	m_PlayingFrame = NULL;
	m_IsPlaying = false;
	m_TextureManager = NULL;
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
	m_Effect_Pics = NULL;
	m_PTech_Pics = NULL;
	m_PLayout_Pics = NULL;
	m_Pics_Width = NULL;
	m_Pics_Height = NULL;
	m_Buffer_GPics = NULL;
	m_Effect_GPics = NULL;
	m_PTech_GPics = NULL;
	m_PLayout_GPics = NULL;
	m_GPics_Width = NULL;
	m_GPics_Height = NULL;
	m_Buffer_Pics = NULL;
	m_hAppInst   = GetModuleHandle( NULL );
	m_AppPaused  = false;
	m_Minimized  = false;
	m_Maximized  = false;
	m_Resizing   = false;
	m_FrameStats = L"";
	//mFont               = 0;
	m_MainWndCaption = L"D3D11 Application";
	m_d3dDriverType  = D3D_DRIVER_TYPE_HARDWARE;
	//md3dDriverType  = D3D_DRIVER_TYPE_REFERENCE;
	m_ClearColor     = D3DXCOLOR( 0.75f, 0.75f, 0.75f, 1.0f );
	mClientWidth    = 1440;
	mClientHeight   = 900;
	Init();

	
}

D3DApp_Frame::~D3DApp_Frame()
{
	ReleaseCOM( m_d3dDevice );
	ReleaseCOM( m_SwapChain );
	ReleaseCOM( m_DepthStencilBuffer );
	ReleaseCOM( m_DepthStencilView2 );
	ReleaseCOM( m_RenderTargetView );
	ReleaseCOM( m_DepthStencilView );
	ReleaseCOM( m_DeviceContext );

	if ( m_TextureManager ) { delete m_TextureManager; }
}

HINSTANCE D3DApp_Frame::getAppInst()
{
	return m_hAppInst;
}

HWND D3DApp_Frame::getMainWnd()
{
	return m_hMainWnd;
}

void D3DApp_Frame::initApp( HWND hWnd, int w, int h )
{
	m_hMainWnd = hWnd;
	mClientWidth = w;
	mClientHeight = h;
	initDirect3D();
	LoadBlend();
	float BlendFactor[4] = {0, 0, 0, 0};
	m_DeviceContext->OMSetBlendState( m_pBlendState_BLEND, BlendFactor, 0xffffffff );
}

void D3DApp_Frame::initDirect3D()
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
	            &m_DeviceContext ) );
	m_TextureManager = new TextureManager( m_d3dDevice );
	g_TextureManagerFrame = m_TextureManager;
	OnResize( mClientWidth, mClientHeight );
	m_vbd.Usage = D3D11_USAGE_IMMUTABLE;
	m_vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_vbd.CPUAccessFlags = 0;
	m_vbd.MiscFlags = 0;
	int t = m_TextureManager->AddTexture( L"media\\Tamplete.png" );
	m_Templete = m_TextureManager->GetTexture( t ).get();
}

void D3DApp_Frame::OnResize( int w, int h )
{
	if ( !m_d3dDevice ) { return; }

	mClientWidth = w;
	mClientHeight = h;
	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.
	ReleaseCOM( m_RenderTargetView );
	ReleaseCOM( m_DepthStencilView );
	ReleaseCOM( m_DepthStencilBuffer );
	// Resize the swap chain and recreate the render target view.
	HR( m_SwapChain->ResizeBuffers( 1, mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, 0 ) );
	ID3D11Texture2D* backBuffer;
	HR( m_SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), reinterpret_cast<void**>( &backBuffer ) ) );
	HR( m_d3dDevice->CreateRenderTargetView( backBuffer, 0, &m_RenderTargetView ) );
	ReleaseCOM( backBuffer );
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
	HR( m_d3dDevice->CreateTexture2D( &depthStencilDesc, 0, &m_DepthStencilBuffer ) );
	HR( m_d3dDevice->CreateDepthStencilView( m_DepthStencilBuffer, 0, &m_DepthStencilView ) );
	// Bind the render target view and depth/stencil view to the pipeline.
	m_DeviceContext->OMSetRenderTargets( 1, &m_RenderTargetView, m_DepthStencilView );
	// Set the viewport transform.
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width    = ( float )mClientWidth;
	vp.Height   = ( float )mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_DeviceContext->RSSetViewports( 1, &vp );

	if ( m_Points_Width != NULL && m_Points_Height != NULL )
	{
		m_Points_Width->SetFloat( ( float )mClientWidth );
		m_Points_Height->SetFloat( ( float )mClientHeight );
	}

	if ( m_Lines_Width != NULL && m_Lines_Height != NULL )
	{
		m_Lines_Width->SetFloat( ( float )mClientWidth );
		m_Lines_Height->SetFloat( ( float )mClientHeight );
	}

	if ( m_Pics_Width != NULL && m_Pics_Height != NULL )
	{
		m_Pics_Width->SetFloat( ( float )mClientWidth );
		m_Pics_Height->SetFloat( ( float )mClientHeight );
	}

	if ( m_GPics_Width != NULL && m_GPics_Height != NULL )
	{
		m_GPics_Width->SetFloat( ( float )mClientWidth );
		m_GPics_Height->SetFloat( ( float )mClientHeight );
	}
}

void D3DApp_Frame::DrawScene()
{
	m_DeviceContext->ClearRenderTargetView( m_RenderTargetView, m_ClearColor );
	m_DeviceContext->ClearDepthStencilView( m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );
	m_DeviceContext->OMSetDepthStencilState( m_pDepthStencil_ZWriteOFF, 0 );

	if( !m_IsPlaying){
		if ( m_Pic != NULL )
		{
			UINT offset = 0;
			UINT stride2 = sizeof( PictureVertex );
			m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );
			m_DeviceContext->IASetInputLayout( m_PLayout_Pics );
			m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_Pics, &stride2, &offset );
			m_PMap_Pics->SetResource( GetTextureManager().GetTexture( m_Pic->m_TextureID )->texture );
			m_BMap_Pics->SetResource( m_Templete->texture );
			m_PTech_Pics->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
			m_DeviceContext->Draw( 1, 0 );
		}

		//Creations
		if ( m_CreationsVertics.size() > 0 )
		{
			UINT offset = 0;
			UINT stride2 = sizeof( GamePictureVertex );
			m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );
			m_DeviceContext->IASetInputLayout( m_PLayout_GPics );
			m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_GPics, &stride2, &offset );
			for ( DrawVertexGroups::iterator it = m_DrawVertexGroups.begin(); it != m_DrawVertexGroups.end(); ++it )
			{
				if ( it->texture.get() )
				{
					m_PMap_GPics->SetResource( *( it->texture ) );
					m_PTech_GPics->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
					m_DeviceContext->Draw( it->VertexCount, it->StartVertexLocation );
				}
			}
		}

		if ( m_LineVertices.size() > 0 )
		{
			UINT offset = 0;
			UINT stride2 = sizeof( LineVertex );
			m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINELIST );
			m_DeviceContext->IASetInputLayout( m_PLayout_Lines );
			m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_Lines, &stride2, &offset );
			m_PTech_Lines->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
			m_DeviceContext->Draw( ( UINT )m_LineVertices.size(), 0 );
		}

		if ( m_PointVertices.size() > 0 )
		{
			UINT offset = 0;
			UINT stride2 = sizeof( PointVertex );
			m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );
			m_DeviceContext->IASetInputLayout( m_PLayout_Points );
			m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_Points, &stride2, &offset );
			m_PTech_Points->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
			m_DeviceContext->Draw( ( UINT )m_PointVertices.size(), 0 );
		}
	}else
	{
		if(m_PlayingFrame!=NULL)
		{
			UINT offset = 0;
			UINT stride2 = sizeof( GamePictureVertex );
			m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );
			m_DeviceContext->IASetInputLayout( m_PLayout_GPics );
			m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_GPics, &stride2, &offset );
			m_PMap_GPics->SetResource( g_TextureManagerFrame->GetTexture(g_HeroInfo->m_PictureDatas[m_PlayingFrame->m_PictureID].m_TextureID)->texture );
			m_PTech_GPics->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
			m_DeviceContext->Draw( 1, 0 );
		}
	}
	m_SwapChain->Present( 0, 0 );
}

void D3DApp_Frame::buildShaderFX()
{
	ID3D10Blob* pCode;
	ID3D10Blob* pError;
	HRESULT hr = 0;
	hr = D3DX11CompileFromFile( _T( "shader\\Point.fx" ), NULL, NULL, NULL,
	                            "fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );

	if ( FAILED( hr ) )
	{
		if ( pError )
		{
			MessageBoxA( 0, ( char* )pError->GetBufferPointer(), 0, 0 );
			ReleaseCOM( pError );
		}

		DXTrace( __FILE__, __LINE__, hr, _T( "D3DX11CreateEffectFromFile" ), TRUE );
	}

	HR( D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Points ) );
	m_PTech_Points = m_Effect_Points->GetTechniqueByName( "PointTech" );
	m_Points_Width = m_Effect_Points->GetVariableByName( "sceneW" )->AsScalar();
	m_Points_Height = m_Effect_Points->GetVariableByName( "sceneH" )->AsScalar();
	D3DX11_PASS_DESC PassDesc;
	m_PTech_Points->GetPassByIndex( 0 )->GetDesc( &PassDesc );
	HR( m_d3dDevice->CreateInputLayout( VertexDesc_PointVertex, 3, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &m_PLayout_Points ) );

	hr = 0;
	hr = D3DX11CompileFromFile( _T( "shader\\Line.fx" ), NULL, NULL, NULL,
	                            "fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );

	if ( FAILED( hr ) )
	{
		if ( pError )
		{
			MessageBoxA( 0, ( char* )pError->GetBufferPointer(), 0, 0 );
			ReleaseCOM( pError );
		}

		DXTrace( __FILE__, __LINE__, hr, _T( "D3DX11CreateEffectFromFile" ), TRUE );
	}

	HR( D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Lines ) );
	m_PTech_Lines = m_Effect_Lines->GetTechniqueByName( "PointTech" );
	m_Lines_Width = m_Effect_Lines->GetVariableByName( "sceneW" )->AsScalar();
	m_Lines_Height = m_Effect_Lines->GetVariableByName( "sceneH" )->AsScalar();
	D3DX11_PASS_DESC PassDesc_Line;
	m_PTech_Lines->GetPassByIndex( 0 )->GetDesc( &PassDesc_Line );
	HR( m_d3dDevice->CreateInputLayout( VertexDesc_LineVertex, 2, PassDesc_Line.pIAInputSignature, PassDesc_Line.IAInputSignatureSize, &m_PLayout_Lines ) );

	//Main Picture
	hr = 0;
	hr = D3DX11CompileFromFile( _T( "shader\\picture.fx" ), NULL, NULL, NULL,
	                            "fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );

	if ( FAILED( hr ) )
	{
		if ( pError )
		{
			MessageBoxA( 0, ( char* )pError->GetBufferPointer(), 0, 0 );
			ReleaseCOM( pError );
		}

		DXTrace( __FILE__, __LINE__, hr, _T( "D3DX11CreateEffectFromFile" ), TRUE );
	}

	HR( D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Pics ) );
	m_PTech_Pics = m_Effect_Pics->GetTechniqueByName( "PointTech" );
	m_Pics_Width = m_Effect_Pics->GetVariableByName( "sceneW" )->AsScalar();
	m_Pics_Height = m_Effect_Pics->GetVariableByName( "sceneH" )->AsScalar();
	m_PMap_Pics = m_Effect_Pics->GetVariableByName( "gMap" )->AsShaderResource();
	m_BMap_Pics = m_Effect_Pics->GetVariableByName( "bMap" )->AsShaderResource();
	D3DX11_PASS_DESC PassDesc_Pic;
	m_PTech_Pics->GetPassByIndex( 0 )->GetDesc( &PassDesc_Pic );
	HR( m_d3dDevice->CreateInputLayout( VertexDesc_PICVertex, 3, PassDesc_Pic.pIAInputSignature, PassDesc_Pic.IAInputSignatureSize, &m_PLayout_Pics ) );

	//Creation
	hr = 0;
	hr = D3DX11CompileFromFile( _T( "shader\\GamePicture.fx" ), NULL, NULL, NULL,
		"fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );

	if ( FAILED( hr ) )
	{
		if ( pError )
		{
			MessageBoxA( 0, ( char* )pError->GetBufferPointer(), 0, 0 );
			ReleaseCOM( pError );
		}

		DXTrace( __FILE__, __LINE__, hr, _T( "D3DX11CreateEffectFromFile" ), TRUE );
	}

	HR( D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_GPics ) );
	m_PTech_GPics = m_Effect_GPics->GetTechniqueByName( "PointTech" );
	m_GPics_Width = m_Effect_GPics->GetVariableByName( "sceneW" )->AsScalar();
	m_GPics_Height = m_Effect_GPics->GetVariableByName( "sceneH" )->AsScalar();
	m_PMap_GPics = m_Effect_GPics->GetVariableByName( "gMap" )->AsShaderResource();
	D3DX11_PASS_DESC PassDesc_GPic;
	m_PTech_GPics->GetPassByIndex( 0 )->GetDesc( &PassDesc_GPic );
	HR( m_d3dDevice->CreateInputLayout( VertexDesc_GPICVertex, 5, PassDesc_GPic.pIAInputSignature, PassDesc_GPic.IAInputSignatureSize, &m_PLayout_GPics ) );

	m_vbd.Usage = D3D11_USAGE_IMMUTABLE;
	m_vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_vbd.CPUAccessFlags = 0;
	m_vbd.MiscFlags = 0;
}

void D3DApp_Frame::buildPoint()
{
	if(!m_IsPlaying)
	{
		//Point
		ReleaseCOM( m_Buffer_Points );
		m_PointVertices.clear();

		for ( Area::iterator it = m_Body.begin(); it != m_Body.end(); ++it )
		{
			PointVertices pvs = it->BuildPoint( g_Frame_Scale, g_Frame_OffsetX, g_Frame_OffsetY );
			m_PointVertices.insert( m_PointVertices.end(), pvs.begin(), pvs.end() );
		}

		for ( Area::iterator it = m_Attack.begin(); it != m_Attack.end(); ++it )
		{
			PointVertices pvs = it->BuildPoint( g_Frame_Scale, g_Frame_OffsetX, g_Frame_OffsetY );
			m_PointVertices.insert( m_PointVertices.end(), pvs.begin(), pvs.end() );
		}

		for ( Area::iterator it = m_Catch.begin(); it != m_Catch.end(); ++it )
		{
			PointVertices pvs = it->BuildPoint( g_Frame_Scale, g_Frame_OffsetX, g_Frame_OffsetY );
			m_PointVertices.insert( m_PointVertices.end(), pvs.begin(), pvs.end() );
		}

		if ( !m_PointVertices.empty() )
		{
			m_vbd.ByteWidth = ( UINT )( sizeof( PointVertex ) * m_PointVertices.size() );
			m_vbd.StructureByteStride = sizeof( PointVertex );
			D3D11_SUBRESOURCE_DATA vinitData;
			vinitData.pSysMem = &m_PointVertices[0];
			HR( m_d3dDevice->CreateBuffer( &m_vbd, &vinitData, &m_Buffer_Points ) );
		}

		//Line
		ReleaseCOM( m_Buffer_Lines );
		m_LineVertices.clear();

		for ( Area::iterator it = m_Body.begin(); it != m_Body.end(); ++it )
		{
			LineVertices lvs = it->BuildLine( g_Frame_Scale, g_Frame_OffsetX, g_Frame_OffsetY );
			m_LineVertices.insert( m_LineVertices.end(), lvs.begin(), lvs.end() );
		}

		for ( Area::iterator it = m_Attack.begin(); it != m_Attack.end(); ++it )
		{
			LineVertices lvs = it->BuildLine( g_Frame_Scale, g_Frame_OffsetX, g_Frame_OffsetY );
			m_LineVertices.insert( m_LineVertices.end(), lvs.begin(), lvs.end() );
		}

		for ( Area::iterator it = m_Catch.begin(); it != m_Catch.end(); ++it )
		{
			LineVertices lvs = it->BuildLine( g_Frame_Scale, g_Frame_OffsetX, g_Frame_OffsetY );
			m_LineVertices.insert( m_LineVertices.end(), lvs.begin(), lvs.end() );
		}

		for(Crosses::iterator it = m_CreationPos.begin(); it != m_CreationPos.end(); ++it)
		{
			LineVertices lvs = it->BuildLine( g_Frame_Scale, g_Frame_OffsetX, g_Frame_OffsetY );
			m_LineVertices.insert( m_LineVertices.end(), lvs.begin(), lvs.end() );
		}

		if (m_ShowCross)
		{
			LineVertices lvs = m_Center.BuildLine( g_Frame_Scale, g_Frame_OffsetX, g_Frame_OffsetY, false);
			m_LineVertices.insert( m_LineVertices.end(), lvs.begin(), lvs.end() );
		}

		if ( !m_LineVertices.empty() )
		{
			m_vbd.ByteWidth = ( UINT )( sizeof( LineVertex ) * m_LineVertices.size() );
			m_vbd.StructureByteStride = sizeof( LineVertex );
			D3D11_SUBRESOURCE_DATA vinitData;
			vinitData.pSysMem = &m_LineVertices[0];
			HR( m_d3dDevice->CreateBuffer( &m_vbd, &vinitData, &m_Buffer_Lines ) );
		}

		//Main Picture
		ReleaseCOM( m_Buffer_Pics );
		if ( m_Pic != NULL )
		{
			PictureVertex pv;
			pv.position.x = g_Frame_OffsetX;
			pv.position.y = -g_Frame_OffsetY;
			pv.size.x = m_Pic->m_Width * g_Frame_Scale;
			pv.size.y = m_Pic->m_Height * g_Frame_Scale;
			pv.picpos.x = m_picX;
			pv.picpos.y = m_picY;
			pv.picpos.z = m_Pic->m_Row;
			pv.picpos.w = m_Pic->m_Column;
			m_vbd.ByteWidth = ( UINT )( sizeof( PictureVertex ) );
			m_vbd.StructureByteStride = sizeof( PictureVertex );
			D3D11_SUBRESOURCE_DATA vinitData;
			vinitData.pSysMem = &pv;
			HR( m_d3dDevice->CreateBuffer( &m_vbd, &vinitData, &m_Buffer_Pics ) );
		}

		//Creation
		ReleaseCOM( m_Buffer_GPics );
		m_CreationsVertics.clear();
		m_DrawVertexGroups.clear();
		for (Creations::iterator it = m_Creation.begin(); it != m_Creation.end(); ++it)
		{
			GamePictureVertex gpv;
			gpv.position.x = it->x * g_Frame_Scale + g_Frame_OffsetX ;
			gpv.position.y = it->y * g_Frame_Scale - g_Frame_OffsetY ;
			gpv.faceside = (it->facing? -1:1);

			ObjectInfoMap::iterator it_Object = g_ObjectInfoMap.find(it->name);

			int count = 0;
			if (it_Object!=g_ObjectInfoMap.end())
			{
				FramesMap::iterator it_Frame = it_Object->second->m_FramesMap.find(it->frame);
				if (it_Frame != it_Object->second->m_FramesMap.end())
				{
					if (it->frameID > -1 && it->frameID < it_Frame->second.size())
					{
						FrameInfo frameInfo = it_Frame->second[it->frameID];
						gpv.center.x = frameInfo.m_CenterX * g_Frame_Scale;
						gpv.center.y = -frameInfo.m_CenterY * g_Frame_Scale;

						PictureData *pic = &it_Object->second->m_PictureDatas[frameInfo.m_PictureID];
						gpv.size.x = pic->m_Width * g_Frame_Scale;
						gpv.size.y = pic->m_Height * g_Frame_Scale;
						gpv.picpos.x = frameInfo.m_PictureX;
						gpv.picpos.y = frameInfo.m_PictureY;
						gpv.picpos.z = pic->m_Row;
						gpv.picpos.w = pic->m_Column;
						m_CreationsVertics.push_back(gpv);
						int textureID = g_TextureManagerFrame->AddTexture(pic->m_Path);

						if(!m_DrawVertexGroups.empty() && m_DrawVertexGroups.back().texture == g_TextureManagerFrame->GetTexture(textureID))
						{
							m_DrawVertexGroups.back().VertexCount++;
						}else
						{
							DrawVertexGroup dvg;
							dvg.StartVertexLocation = count;
							dvg.VertexCount = 1;
							dvg.texture = g_TextureManagerFrame->GetTexture(textureID);
							m_DrawVertexGroups.push_back(dvg);
						}
						count++;
					}
				}
			}

			HeroInfoMap::iterator it_Hero = g_HeroInfoMap.find(it->name);
			if (it_Hero!=g_HeroInfoMap.end())
			{
				FramesMap::iterator it_Frame = it_Hero->second->m_FramesMap.find(it->frame);
				if (it_Frame != it_Hero->second->m_FramesMap.end())
				{
					if (it->frameID > -1 && it->frameID < it_Frame->second.size())
					{
						FrameInfo frameInfo = it_Frame->second[it->frameID];
						gpv.center.x = frameInfo.m_CenterX * g_Frame_Scale;
						gpv.center.y = -frameInfo.m_CenterY * g_Frame_Scale;

						PictureData *pic = &it_Hero->second->m_PictureDatas[frameInfo.m_PictureID];
						gpv.size.x = pic->m_Width * g_Frame_Scale;
						gpv.size.y = pic->m_Height * g_Frame_Scale;
						gpv.picpos.x = frameInfo.m_PictureX;
						gpv.picpos.y = frameInfo.m_PictureY;
						gpv.picpos.z = pic->m_Row;
						gpv.picpos.w = pic->m_Column;
						m_CreationsVertics.push_back(gpv);
						int textureID = g_TextureManagerFrame->AddTexture(pic->m_Path);

						if(!m_DrawVertexGroups.empty() && m_DrawVertexGroups.back().texture == g_TextureManagerFrame->GetTexture(textureID))
						{
							m_DrawVertexGroups.back().VertexCount++;
						}else
						{
							DrawVertexGroup dvg;
							dvg.StartVertexLocation = count;
							dvg.VertexCount = 1;
							dvg.texture = g_TextureManagerFrame->GetTexture(textureID);
							m_DrawVertexGroups.push_back(dvg);
						}
						count++;
					}
				}
			}
		}
		if(!m_CreationsVertics.empty())
		{
			m_vbd.ByteWidth = ( UINT )( sizeof( GamePictureVertex ) * m_CreationsVertics.size());
			m_vbd.StructureByteStride = sizeof( GamePictureVertex );
			D3D11_SUBRESOURCE_DATA vinitData;
			vinitData.pSysMem = &m_CreationsVertics[0];
			HR( m_d3dDevice->CreateBuffer( &m_vbd, &vinitData, &m_Buffer_GPics ) );
		}
	}else
	{
		if (m_PlayingFrame != NULL)
		{
			ReleaseCOM( m_Buffer_GPics );
			if ( m_Pic != NULL )
			{
				GamePictureVertex gpv;
				gpv.position.x =   100 + g_Frame_OffsetX;
				gpv.position.y =  -200 - g_Frame_OffsetY;
				gpv.faceside = 1;
				gpv.size.x = g_HeroInfo->m_PictureDatas[m_PlayingFrame->m_PictureID].m_Width * g_Frame_Scale;
				gpv.size.y = g_HeroInfo->m_PictureDatas[m_PlayingFrame->m_PictureID].m_Height * g_Frame_Scale;
				gpv.picpos.x = m_PlayingFrame->m_PictureX;
				gpv.picpos.y = m_PlayingFrame->m_PictureY;
				gpv.picpos.z = g_HeroInfo->m_PictureDatas[m_PlayingFrame->m_PictureID].m_Row;
				gpv.picpos.w = g_HeroInfo->m_PictureDatas[m_PlayingFrame->m_PictureID].m_Column;
				gpv.center.x = m_PlayingFrame->m_CenterX * g_Frame_Scale;
				gpv.center.y = -m_PlayingFrame->m_CenterY * g_Frame_Scale;
				m_vbd.ByteWidth = ( UINT )( sizeof( GamePictureVertex ));
				m_vbd.StructureByteStride = sizeof( GamePictureVertex );
				D3D11_SUBRESOURCE_DATA vinitData;
				vinitData.pSysMem = &gpv;
				HR( m_d3dDevice->CreateBuffer( &m_vbd, &vinitData, &m_Buffer_GPics ) );
			}
		}
	}
	m_DeviceContext->OMSetDepthStencilState( m_pDepthStencil_ZWriteON, 0 );
}

void D3DApp_Frame::LoadBlend()
{
	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	ZeroMemory( &depth_stencil_desc, sizeof( depth_stencil_desc ) );
	depth_stencil_desc.DepthEnable = TRUE;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	depth_stencil_desc.StencilEnable = FALSE;
	depth_stencil_desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depth_stencil_desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	// 開啟zbuffer write
	if ( D3D_OK != m_d3dDevice->CreateDepthStencilState( &depth_stencil_desc, &m_pDepthStencil_ZWriteON ) )
	{
		return ;
	}

	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	// 關閉zbuffer write
	if ( D3D_OK != m_d3dDevice->CreateDepthStencilState( &depth_stencil_desc, &m_pDepthStencil_ZWriteOFF ) )
	{
		return ;
	}

	m_DeviceContext->OMSetDepthStencilState( m_pDepthStencil_ZWriteON, 0 );
	CD3D11_BLEND_DESCX2 blend_state_desc(
	        FALSE,
	        FALSE,
	        TRUE,
	        D3D11_BLEND_ONE,
	        D3D11_BLEND_ONE,
	        D3D11_BLEND_OP_ADD,
	        D3D11_BLEND_ONE,
	        D3D11_BLEND_ONE,
	        D3D11_BLEND_OP_ADD,
	        D3D11_COLOR_WRITE_ENABLE_ALL );

	// ADD混色模式
	if ( D3D_OK != m_d3dDevice->CreateBlendState( &blend_state_desc, &m_pBlendState_ADD ) )
	{
		return;
	}

	blend_state_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA ;
	blend_state_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blend_state_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blend_state_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;

	// Alpha Blend混色模式
	if ( D3D_OK != m_d3dDevice->CreateBlendState( &blend_state_desc, &m_pBlendState_BLEND ) )
	{
		return ;
	}
}

void D3DApp_Frame::SetPic( PictureData* pic, float x, float y )
{
	m_Pic = pic;
	m_picX = x;
	m_picY = y;
}

void D3DApp_Frame::Init()
{
	m_Body.clear();
	m_Attack.clear();
	m_Catch.clear();
	m_Center.Clear();
	m_CreationPos.clear();
	m_Creation.clear();
	m_DrawVertexGroups.clear();
	m_Pic = NULL;
	m_picX = 1;
	m_picY = 1;
	m_ShowCross = false;
	SwitchShowCrossOff();
	m_PlayingFrame = NULL;
	m_IsPlaying = false;
	m_Center.Add(-20,0);
	m_Center.Add(20,0);
	m_Center.Add(0,0);
	m_Center.Add(0,-10);
	m_Center.Add(0,10);
	m_Center.SetLineColor(0,0,1);
	m_CenterPos = Vector2(0,0);
}

void D3DApp_Frame::SwitchShowCrossOff()
{
	m_ShowCross = false;
}

void D3DApp_Frame::SwitchShowCrossOn()
{
	m_ShowCross = true;
}

void D3DApp_Frame::SetCreation( Creations& creation )
{
	m_Creation.assign(creation.begin(),creation.end());
}

void D3DApp_Frame::PlayFrame( FrameInfo &frame )
{
	m_IsPlaying = true;
	m_PlayingFrame = &frame;
	buildPoint();
	DrawScene();
}

void D3DApp_Frame::StopPlayFrame()
{
	m_IsPlaying = false;
	m_PlayingFrame = NULL;
}

void D3DApp_Frame::SetCenterPos( float x ,float y )
{
	m_Center.Transale(x-m_CenterPos.x,y-m_CenterPos.y);
	m_CenterPos = Vector2(x,y);
}
