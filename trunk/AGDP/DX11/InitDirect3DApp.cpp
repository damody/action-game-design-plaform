#include "StdGame.h"
#include <cstdlib>
#include <ctime>
#include <boost/algorithm/string.hpp>
#include "InitDirect3DApp.h"
#include "InputState.h"

#include "ui/CmdDef.h"
#include "game/CtrlKey.h"
#include "game/HeroInfo.h"
#include "game/ObjectInfo.h"
#include "game/HeroAction.h"

#include "game/LuaResuorce.h"

InitDirect3DApp* InitDirect3DApp::dxAppInstance = NULL;

InitDirect3DApp::InitDirect3DApp()
	: D3DApp(), m_Entity_Width( 0 ), m_Entity_Height( 0 ), m_Buffer_Entity( 0 ),
	  m_Chee_Width( 0 ), m_Chee_Height( 0 ), m_Buffer_Chee( 0 ),
	  m_Background_Width( 0 ), m_Background_Height( 0 ), m_Buffer_Background( 0 ),
	  m_ColorRect_Width( 0 ), m_ColorRect_Height( 0 ), m_Buffer_ColorRect( 0 ),
	  m_Shadow_Width( 0 ), m_Shadow_Height( 0 ),
	  m_Body_Width( 0 ), m_Body_Height( 0 ), m_Buffer_Body( 0 ), m_Buffer_BodyLine( 0 ),
	  m_Text_Width( 0 ), m_Text_Height( 0 ), m_Buffer_Text( 0 ),
	  m_SettingKeyID( -1 ), m_LastGameProcess( 1 ), m_GameProcess( 1 ), m_Last2GameProcess( 1 ),
	  b_Body( false ), b_Pause( false )
{
	dxAppInstance = this;
}

InitDirect3DApp::~InitDirect3DApp()
{
	if ( m_DeviceContext )
	{
		m_DeviceContext->ClearState();
	}
}

void InitDirect3DApp::initApp( int argc, char* argv[] )
{
	D3DApp::initApp();
	InitTexture();
	LoadBlend();
	g_Camera = Camera_Sptr( new Camera( ( float )m_ClientWidth, 0, 1000, 800, 0, 45 ) );
	g_WavPlayer.Initialize( getMainWnd() );
	g_TextGenarator.Initialize();
	g_TextManager.Initialize();
	g_EffectManager = new EffectManager( m_hMainWnd );
	LoadData();
	InitPlayer();
	ParseCommandLine( argc, argv );
	buildPointFX();
	OnResize();
	// Set blend
	float BlendFactor[4] = {0, 0, 0, 0};
	m_DeviceContext->OMSetBlendState( m_pBlendState_BLEND, BlendFactor, 0xffffffff );
	//m_DeviceContext->OMSetDepthStencilState(m_pDepthStencil_ZWriteOFF, 0);
	buildPoint();
	//HolyK
	g_TestViewEffect = false;
	//init m_Effect_Manager
	//init m_TestRenderEffect
	m_TestRenderEffect = 0;
	m_TestRenderEffect = new TestRenderEffect();
	m_TestRenderEffect->Initialize( g_d3dDevice, g_DeviceContext, L"shader\\TestRenderEffect.fx", m_hMainWnd );
	//HolyK
}
//HolyK
void InitDirect3DApp::TestRender()
{
	m_TestRenderEffect->Render( 1, g_EffectManager->m_Effect[0]->GetTexture() );
}
void InitDirect3DApp::TestViewEffect()
{
	if ( InputStateS::instance().isKeyDown( KEY_V ) )
	{
		g_TestViewEffect = true;
	}

	if ( InputStateS::instance().isKeyUp( KEY_V ) )
	{
		g_TestViewEffect = false;
	}
}
//HolyK

void InitDirect3DApp::UpdateScene( float dt )
{
	//HolyK
	if ( g_TestViewEffect )
	{
		if ( g_EffectManager != NULL ) { g_EffectManager->Update( m_RenderTargetView ); }

		PrintInfo();
		D3DApp::DrawScene(); // clear window
		UpdateInput();
		TestRender();
		m_SwapChain->Present( 0, 0 );
		return ;
	}

	//HolyK
	PrintInfo();
	//m_DXUT_UI->UpdataUI(dt);
	//UpdateUI();
	D3DApp::DrawScene(); // clear window
	this->DrawScene();
	m_SwapChain->Present( 0, 0 );
	UpdateInput();

	if ( !b_Pause )
	{
		static float timp_count = 0;
		timp_count += dt;

		if ( timp_count > g_TimeSpeed )
		{
			g_Time++;
			UpdateCamera();

			if ( g_EffectManager != NULL ) { g_EffectManager->Update( m_RenderTargetView ); }

			buildPoint();
			//Hero Update
			g_HeroManager.Update( dt );
			//Chee Update
			g_ObjectManager.Update( dt );
			m_Player.Update();

			//Background Update
			if ( g_BackGroundManager.GetCurrentBackGround() != NULL )
			{
				g_BackGroundManager.GetCurrentBackGround()->Update( dt );
				BackgroundDataUpdate();
			}

			timp_count -= g_TimeSpeed;
		}
	}
}

void InitDirect3DApp::OnResize()
{
	D3DApp::OnResize();

	if ( g_Camera.get() )
	{
		g_Camera->onResize( ( float )m_ClientWidth, ( float )m_ClientHeight );
	}

	if ( g_EffectManager != NULL ) { g_EffectManager->OnResize( m_ClientWidth, m_ClientHeight ); }

	if ( m_Entity_Width != NULL && m_Entity_Height != NULL )
	{
		m_Entity_Width->SetFloat( ( float )m_ClientWidth );
		m_Entity_Height->SetFloat( ( float )m_ClientHeight );
	}

	if ( m_Chee_Width != NULL && m_Chee_Height != NULL )
	{
		m_Chee_Width->SetFloat( ( float )m_ClientWidth );
		m_Chee_Height->SetFloat( ( float )m_ClientHeight );
	}

	if ( m_Background_Width != NULL && m_Background_Height != NULL )
	{
		m_Background_Width->SetFloat( ( float )m_ClientWidth );
		m_Background_Height->SetFloat( ( float )m_ClientHeight );
	}

	if ( m_ColorRect_Width != NULL && m_ColorRect_Height != NULL )
	{
		m_ColorRect_Width->SetFloat( ( float )m_ClientWidth );
		m_ColorRect_Height->SetFloat( ( float )m_ClientHeight );
	}

	if ( m_Shadow_Width != NULL && m_Shadow_Height != NULL )
	{
		m_Shadow_Width->SetFloat( ( float )m_ClientWidth );
		m_Shadow_Height->SetFloat( ( float )m_ClientHeight );
	}

	if ( m_Body_Width != NULL && m_Body_Height != NULL )
	{
		m_Body_Width->SetFloat( ( float )m_ClientWidth );
		m_Body_Height->SetFloat( ( float )m_ClientHeight );
	}

	if ( m_Text_Width != NULL && m_Text_Height != NULL )
	{
		m_Text_Width->SetFloat( ( float )m_ClientWidth );
		m_Text_Height->SetFloat( ( float )m_ClientHeight );
	}
}

void InitDirect3DApp::DrawScene()
{
	// clear color
	m_DeviceContext->ClearRenderTargetView( m_RenderTargetView, m_ClearColor );
	m_DeviceContext->ClearDepthStencilView( m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,  1.0f, 0 );
	m_DeviceContext->ClearRenderTargetView( m_RTVView1, m_ClearColor );
	m_DeviceContext->ClearRenderTargetView( m_RTVView2, m_ClearColor );
	m_DeviceContext->OMSetRenderTargets( 1, &m_RenderTargetView, m_DepthStencilView );
	m_DeviceContext->OMSetDepthStencilState( m_pDepthStencil_ZWriteOFF, 0 );
	//Draw Color Rect
	UINT offset = 0;
	UINT stride2 = sizeof( CRVertex );
	m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );
	m_DeviceContext->IASetInputLayout( m_PLayout_ColorRect );
	m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_ColorRect, &stride2, &offset );
	m_PTech_ColorRect->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
	m_DeviceContext->Draw( ( UINT )m_CRVerteices.size(), 0 );

	//Draw Background
	if ( g_BackGroundManager.GetCurrentBackGround() != NULL )
	{
		UINT offset = 0;
		UINT stride2 = sizeof( BGVertex );
		m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );
		m_DeviceContext->IASetInputLayout( m_PLayout_Background );
		m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_Background, &stride2, &offset );

		for ( DrawVertexGroups::iterator it = g_BackGroundManager.GetCurrentBackGround()->m_DrawVertexGroups.begin(); it != g_BackGroundManager.GetCurrentBackGround()->m_DrawVertexGroups.end(); ++it )
		{
			if ( it->texture.get() )
			{
				m_PMap_Background->SetResource( *( it->texture ) );
				m_PTech_Background->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
				m_DeviceContext->Draw( it->VertexCount, it->StartVertexLocation );
			}
		}
	}

	//Draw Name
	if ( g_Time > 120 )
	{
		offset = 0;
		stride2 = sizeof( TextVertex );
		m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );
		m_DeviceContext->IASetInputLayout( m_PLayout_Text );
		m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_Text, &stride2, &offset );

		for ( DrawVertexGroups::iterator it = m_DrawVertexGroups_Text.begin(); it != m_DrawVertexGroups_Text.end(); ++it )
		{
			if ( it->texture.get() )
			{
				m_PMap_Text->SetResource( *( it->texture ) );
				m_PTech_Text->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
				m_DeviceContext->Draw( it->VertexCount, it->StartVertexLocation );
			}
		}
	}

	//Draw Shadow
	offset = 0;
	stride2 = sizeof( ClipVertex );
	m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );
	m_DeviceContext->IASetInputLayout( m_PLayout_Shadow );
	m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_Entity, &stride2, &offset );

	for ( DrawVertexGroups::iterator it = m_DrawVertexGroups.begin(); it != m_DrawVertexGroups.end(); ++it )
	{
		if ( it->texture.get() )
		{
			m_PMap_Shadow->SetResource( *( it->texture ) );
			m_PTech_Shadow->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
			m_DeviceContext->Draw( it->VertexCount, it->StartVertexLocation );
		}
	}

	//m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL,  1.0f, 0);
	//Draw Hero & Weapon
	offset = 0;
	stride2 = sizeof( ClipVertex );
	m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );
	m_DeviceContext->IASetInputLayout( m_PLayout_Entity );
	m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_Entity, &stride2, &offset );

	for ( DrawVertexGroups::iterator it = m_DrawVertexGroups.begin(); it != m_DrawVertexGroups.end(); ++it )
	{
		if ( it->texture.get() )
		{
			m_PMap_Entity->SetResource( *( it->texture ) );
			m_PTech_Entity->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
			m_DeviceContext->Draw( it->VertexCount, it->StartVertexLocation );
		}
	}

	//Draw Chee
	offset = 0;
	stride2 = sizeof( ClipVertex );
	m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );
	m_DeviceContext->IASetInputLayout( m_PLayout_Chee );
	m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_Chee, &stride2, &offset );

	for ( DrawVertexGroups::iterator it = m_CheeDrawVertexGroups.begin(); it != m_CheeDrawVertexGroups.end(); ++it )
	{
		if ( it->texture.get() )
		{
			m_PMap_Chee->SetResource( *( it->texture ) );
			m_PTech_Chee->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
			m_DeviceContext->Draw( it->VertexCount, it->StartVertexLocation );
		}
	}

	//Draw Body
	if ( b_Body )
	{
		offset = 0;
		stride2 = sizeof( PolygonVertex );
		m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		m_DeviceContext->IASetInputLayout( m_PLayout_Body );
		m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_Body, &stride2, &offset );
		m_PTech_Body->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
		m_DeviceContext->Draw( m_PolygonVerteices.size(), 0 );
		offset = 0;
		stride2 = sizeof( PolygonVertex );
		m_DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINELIST );
		m_DeviceContext->IASetInputLayout( m_PLayout_Body );
		m_DeviceContext->IASetVertexBuffers( 0, 1, &m_Buffer_BodyLine, &stride2, &offset );
		m_PTech_Body->GetPassByIndex( 0 )->Apply( 0, m_DeviceContext );
		m_DeviceContext->Draw( m_PolygonLineVerteices.size(), 0 );
	}

	//m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL,  1.0f, 0);
}

void InitDirect3DApp::buildPointFX()
{
	ID3D10Blob* pCode;
	ID3D10Blob* pError;
	//Hero
	HRESULT hr = 0;
	hr = D3DX11CompileFromFile( _T( "shader\\Hero.fx" ), NULL, NULL, NULL,
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

	HR( D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Entity ) );
	m_PTech_Entity = m_Effect_Entity->GetTechniqueByName( "PointTech" );
	m_Entity_Width = m_Effect_Entity->GetVariableByName( "sceneW" )->AsScalar();
	m_Entity_Height = m_Effect_Entity->GetVariableByName( "sceneH" )->AsScalar();
	m_Entity_cLootAt = m_Effect_Entity->GetVariableByName( "cLookAt" );
	m_Entity_cPos = m_Effect_Entity->GetVariableByName( "cPolarCoord" );
	m_PMap_Entity = m_Effect_Entity->GetVariableByName( "gMap" )->AsShaderResource();
	D3DX11_PASS_DESC PassDesc;
	m_PTech_Entity->GetPassByIndex( 0 )->GetDesc( &PassDesc );
	HR( m_d3dDevice->CreateInputLayout( VertexDesc_ClipVertex, 6, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &m_PLayout_Entity ) );
	//Chee
	hr = 0;
	hr = D3DX11CompileFromFile( _T( "shader\\Chee.fx" ), NULL, NULL, NULL,
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

	HR( D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Chee ) );
	m_PTech_Chee = m_Effect_Chee->GetTechniqueByName( "PointTech" );
	m_Chee_Width = m_Effect_Chee->GetVariableByName( "sceneW" )->AsScalar();
	m_Chee_Height = m_Effect_Chee->GetVariableByName( "sceneH" )->AsScalar();
	m_Chee_cLootAt = m_Effect_Chee->GetVariableByName( "cLookAt" );
	m_Chee_cPos = m_Effect_Chee->GetVariableByName( "cPolarCoord" );
	m_PMap_Chee = m_Effect_Chee->GetVariableByName( "gMap" )->AsShaderResource();
	D3DX11_PASS_DESC PassDescChee;
	m_PTech_Chee->GetPassByIndex( 0 )->GetDesc( &PassDescChee );
	HR( m_d3dDevice->CreateInputLayout( VertexDesc_ClipVertex, 6, PassDescChee.pIAInputSignature, PassDescChee.IAInputSignatureSize, &m_PLayout_Chee ) );
	//Background
	hr = 0;
	hr = D3DX11CompileFromFile( _T( "shader\\Background.fx" ), NULL, NULL, NULL,
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

	HR( D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Background ) );
	m_PTech_Background = m_Effect_Background->GetTechniqueByName( "PointTech" );
	m_Background_Width = m_Effect_Background->GetVariableByName( "sceneW" )->AsScalar();
	m_Background_Height = m_Effect_Background->GetVariableByName( "sceneH" )->AsScalar();
	m_Background_cLootAt = m_Effect_Background->GetVariableByName( "cLookAt" );
	m_Background_cPos = m_Effect_Background->GetVariableByName( "cPolarCoord" );
	m_PMap_Background = m_Effect_Background->GetVariableByName( "gMap" )->AsShaderResource();
	D3DX11_PASS_DESC PassDescBG;
	m_PTech_Background->GetPassByIndex( 0 )->GetDesc( &PassDescBG );
	HR( m_d3dDevice->CreateInputLayout( VertexDesc_BGVertex, 3, PassDescBG.pIAInputSignature, PassDescBG.IAInputSignatureSize, &m_PLayout_Background ) );
	//Color Rect
	hr = 0;
	hr = D3DX11CompileFromFile( _T( "shader\\ColorRect.fx" ), NULL, NULL, NULL,
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

	HR( D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_ColorRect ) );
	m_PTech_ColorRect = m_Effect_ColorRect->GetTechniqueByName( "PointTech" );
	m_ColorRect_Width = m_Effect_ColorRect->GetVariableByName( "sceneW" )->AsScalar();
	m_ColorRect_Height = m_Effect_ColorRect->GetVariableByName( "sceneH" )->AsScalar();
	m_ColorRect_cLootAt = m_Effect_ColorRect->GetVariableByName( "cLookAt" );
	m_ColorRect_cPos = m_Effect_ColorRect->GetVariableByName( "cPolarCoord" );
	D3DX11_PASS_DESC PassDescCR;
	m_PTech_ColorRect->GetPassByIndex( 0 )->GetDesc( &PassDescCR );
	HR( m_d3dDevice->CreateInputLayout( VertexDesc_CRVertex, 4, PassDescCR.pIAInputSignature, PassDescCR.IAInputSignatureSize, &m_PLayout_ColorRect ) );
	//Shadow
	hr = 0;
	hr = D3DX11CompileFromFile( _T( "shader\\Shadow.fx" ), NULL, NULL, NULL,
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

	HR( D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Shadow ) );
	m_PTech_Shadow = m_Effect_Shadow->GetTechniqueByName( "PointTech" );
	m_Shadow_Width = m_Effect_Shadow->GetVariableByName( "sceneW" )->AsScalar();
	m_Shadow_Height = m_Effect_Shadow->GetVariableByName( "sceneH" )->AsScalar();
	m_Shadow_cLootAt = m_Effect_Shadow->GetVariableByName( "cLookAt" );
	m_Shadow_cPos = m_Effect_Shadow->GetVariableByName( "cPolarCoord" );
	m_Shadow_lightStr = m_Effect_Shadow->GetVariableByName( "lightStr" )->AsScalar();
	m_Shadow_lightDir = m_Effect_Shadow->GetVariableByName( "lightDir" );
	m_PMap_Shadow = m_Effect_Shadow->GetVariableByName( "gMap" )->AsShaderResource();
	D3DX11_PASS_DESC PassDescShadow;
	m_PTech_Shadow->GetPassByIndex( 0 )->GetDesc( &PassDescShadow );
	HR( m_d3dDevice->CreateInputLayout( VertexDesc_ClipVertex, 6, PassDescShadow.pIAInputSignature, PassDescShadow.IAInputSignatureSize, &m_PLayout_Shadow ) );
	//Polygon
	hr = 0;
	hr = D3DX11CompileFromFile( _T( "shader\\Body.fx" ), NULL, NULL, NULL,
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

	HR( D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Body ) );
	m_PTech_Body = m_Effect_Body->GetTechniqueByName( "PointTech" );
	m_Body_Width = m_Effect_Body->GetVariableByName( "sceneW" )->AsScalar();
	m_Body_Height = m_Effect_Body->GetVariableByName( "sceneH" )->AsScalar();
	m_Body_cLootAt = m_Effect_Body->GetVariableByName( "cLookAt" );
	m_Body_cPos = m_Effect_Body->GetVariableByName( "cPolarCoord" );
	D3DX11_PASS_DESC PassDescBody;
	m_PTech_Body->GetPassByIndex( 0 )->GetDesc( &PassDescBody );
	HR( m_d3dDevice->CreateInputLayout( VertexDesc_PolygonVertex, 2, PassDescBody.pIAInputSignature, PassDescBody.IAInputSignatureSize, &m_PLayout_Body ) );
	//
	hr = 0;
	hr = D3DX11CompileFromFile( _T( "shader\\TextString.fx" ), NULL, NULL, NULL,
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

	HR( D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Text ) );
	m_PTech_Text = m_Effect_Text->GetTechniqueByName( "PointTech" );
	m_Text_Width = m_Effect_Text->GetVariableByName( "sceneW" )->AsScalar();
	m_Text_Height = m_Effect_Text->GetVariableByName( "sceneH" )->AsScalar();
	m_Text_cLootAt = m_Effect_Text->GetVariableByName( "cLookAt" );
	m_Text_cPos = m_Effect_Text->GetVariableByName( "cPolarCoord" );
	m_PMap_Text = m_Effect_Text->GetVariableByName( "gMap" )->AsShaderResource();
	D3DX11_PASS_DESC PassDescText;
	m_PTech_Text->GetPassByIndex( 0 )->GetDesc( &PassDescText );
	HR( m_d3dDevice->CreateInputLayout( VertexDesc_TextVertex, 4, PassDescText.pIAInputSignature, PassDescText.IAInputSignatureSize, &m_PLayout_Text ) );
	m_vbd.Usage = D3D11_USAGE_IMMUTABLE;
	m_vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_vbd.CPUAccessFlags = 0;
	m_vbd.MiscFlags = 0;
}



void InitDirect3DApp::buildPoint()
{
	ReleaseCOM( m_Buffer_Entity );
	ReleaseCOM( m_Buffer_Chee );
	ReleaseCOM( m_Buffer_Background );
	ReleaseCOM( m_Buffer_ColorRect );
	ReleaseCOM( m_Buffer_Body );
	ReleaseCOM( m_Buffer_BodyLine );
	ReleaseCOM( m_Buffer_Text );

	if ( g_BackGroundManager.GetCurrentBackGround() != NULL )
	{
		g_BackGroundManager.GetCurrentBackGround()->BuildPoint();
	}

	//set color rect
	m_CRVerteices.clear();

	if ( g_BackGroundManager.GetCurrentBackGround() != NULL )
	{
		m_CRVerteices.assign( g_BackGroundManager.GetCurrentBackGround()->m_CRVerteices.begin(), g_BackGroundManager.GetCurrentBackGround()->m_CRVerteices.end() );
	}

	if ( !m_CRVerteices.empty() )
	{
		m_vbd.ByteWidth = ( UINT )( sizeof( CRVertex ) * m_CRVerteices.size() );
		m_vbd.StructureByteStride = sizeof( CRVertex );
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &m_CRVerteices[0];
		HR( m_d3dDevice->CreateBuffer( &m_vbd, &vinitData, &m_Buffer_ColorRect ) );
	}

	// set background
	if ( g_BackGroundManager.GetCurrentBackGround() != NULL )
	{
		m_vbd.ByteWidth = ( UINT )( sizeof( BGVertex ) * g_BackGroundManager.GetCurrentBackGround()->m_BGVerteices.size() );
		m_vbd.StructureByteStride = sizeof( BGVertex );
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &g_BackGroundManager.GetCurrentBackGround()->m_BGVerteices[0];
		HR( m_d3dDevice->CreateBuffer( &m_vbd, &vinitData, &m_Buffer_Background ) );
	}

	// set heroes and weapons
	m_EntityVertex.clear();
	m_DrawVertexGroups.clear();
	g_HeroManager.UpdateDataToDraw();
	g_ObjectManager.UpdateDataToDraw();
	int vertexCount = 0, count = 0;

	if ( !g_HeroManager.Empty() )
	{
		for ( Heroes::iterator it = g_HeroManager.HeroVectorBegin(); it != g_HeroManager.HeroVectorEnd(); )
		{
			DrawVertexGroup dvg = {};
			dvg.texture = ( *it )->GetTexture();
			vertexCount = 0;
			dvg.StartVertexLocation = count;

			do
			{
				if ( !g_Camera->Visable( ( *it )->Position() ) )
				{
					it++;
					continue;
				}

				//save vertex points
				m_EntityVertex.push_back( ( *it )->GetPic() );
				it++;
				++vertexCount;
				++count;
			}
			while ( it != g_HeroManager.HeroVectorEnd() && dvg.texture == ( *it )->GetTexture() );

			dvg.VertexCount = vertexCount;
			//save dvg
			m_DrawVertexGroups.push_back( dvg );
		}
	}

	if ( !g_ObjectManager.WeaponEmpty() )
	{
		for ( Weapons::iterator it = g_ObjectManager.WeaponVectorBegin(); it != g_ObjectManager.WeaponVectorEnd(); )
		{
			DrawVertexGroup dvg = {};
			dvg.texture = ( *it )->GetTexture();
			vertexCount = 0;
			dvg.StartVertexLocation = count;

			do
			{
				if ( !g_Camera->Visable( ( *it )->Position() ) )
				{
					it++;
					continue;
				}

				//save vertex points
				m_EntityVertex.push_back( ( *it )->GetPic() );
				it++;
				++vertexCount;
				++count;
			}
			while ( it != g_ObjectManager.WeaponVectorEnd() && dvg.texture == ( *it )->GetTexture() );

			dvg.VertexCount = vertexCount;

			//save dvg
			if ( dvg.VertexCount != 0 ) { m_DrawVertexGroups.push_back( dvg ); }
		}
	}

	if ( m_EntityVertex.size() > 0 )
	{
		m_vbd.ByteWidth = ( UINT )( sizeof( ClipVertex ) * m_EntityVertex.size() );
		m_vbd.StructureByteStride = sizeof( ClipVertex );
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &m_EntityVertex[0];
		HR( m_d3dDevice->CreateBuffer( &m_vbd, &vinitData, &m_Buffer_Entity ) );
	}

	// Chee
	m_CheeVertex.clear();
	m_CheeDrawVertexGroups.clear();
	vertexCount = 0;
	count = 0;

	if ( !g_ObjectManager.CheeEmpty() )
	{
		for ( Chees::iterator it = g_ObjectManager.CheeVectorBegin(); it != g_ObjectManager.CheeVectorEnd(); )
		{
			DrawVertexGroup dvg = {};
			dvg.texture = ( *it )->GetTexture();
			vertexCount = 0;
			dvg.StartVertexLocation = count;

			do
			{
				if ( !g_Camera->Visable( ( *it )->Position() ) )
				{
					it++;
					continue;
				}

				//save vertex points
				m_CheeVertex.push_back( ( *it )->GetPic() );
				it++;
				++vertexCount;
				++count;
			}
			while ( it != g_ObjectManager.CheeVectorEnd() && dvg.texture == ( *it )->GetTexture() );

			dvg.VertexCount = vertexCount;
			//save dvg
			m_CheeDrawVertexGroups.push_back( dvg );
		}
	}

	if ( m_CheeVertex.size() > 0 )
	{
		m_vbd.ByteWidth = ( UINT )( sizeof( ClipVertex ) * m_CheeVertex.size() );
		m_vbd.StructureByteStride = sizeof( ClipVertex );
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &m_CheeVertex[0];
		HR( m_d3dDevice->CreateBuffer( &m_vbd, &vinitData, &m_Buffer_Chee ) );
	}

	m_PolygonVerteices.clear();
	m_PolygonLineVerteices.clear();
	count = 0;

	if ( !g_HeroManager.Empty() )
	{
		for ( Heroes::iterator it = g_HeroManager.HeroVectorBegin(); it != g_HeroManager.HeroVectorEnd(); it++ )
		{
			PolygonVerteices bvs = ( *it )->GetPolygonVerteices();
			m_PolygonVerteices.insert( m_PolygonVerteices.end(), bvs.begin(), bvs.end() );
		}
	}

	if ( m_PolygonVerteices.size() > 0 )
	{
		m_vbd.ByteWidth = ( UINT )( sizeof( PolygonVertex ) * m_PolygonVerteices.size() );
		m_vbd.StructureByteStride = sizeof( PolygonVertex );
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &m_PolygonVerteices[0];
		HR( m_d3dDevice->CreateBuffer( &m_vbd, &vinitData, &m_Buffer_Body ) );
	}

	if ( !g_HeroManager.Empty() )
	{
		for ( Heroes::iterator it = g_HeroManager.HeroVectorBegin(); it != g_HeroManager.HeroVectorEnd(); it++ )
		{
			PolygonVerteices bvs = ( *it )->GetPolygonLineVerteices();
			m_PolygonLineVerteices.insert( m_PolygonLineVerteices.end(), bvs.begin(), bvs.end() );
		}
	}

	if ( m_PolygonLineVerteices.size() > 0 )
	{
		m_vbd.ByteWidth = ( UINT )( sizeof( PolygonVertex ) * m_PolygonLineVerteices.size() );
		m_vbd.StructureByteStride = sizeof( PolygonVertex );
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &m_PolygonLineVerteices[0];
		HR( m_d3dDevice->CreateBuffer( &m_vbd, &vinitData, &m_Buffer_BodyLine ) );
	}

	//Name
	m_TextVeices.clear();
	m_TextLetters.clear();
	m_DrawVertexGroups_Text.clear();
	m_Player.m_UserName.buildPoint();

	if ( !m_Player.m_UserName.m_TexVerteices.empty() )
	{
		m_TextVeices.assign( m_Player.m_UserName.m_TexVerteices.begin(), m_Player.m_UserName.m_TexVerteices.end() );
		m_TextLetters.assign( m_Player.m_UserName.m_TextLetters.begin(), m_Player.m_UserName.m_TextLetters.end() );
	}

	SortLetters( m_TextVeices, m_TextLetters );
	vertexCount = 0;
	count = 0;

	if ( !m_TextLetters.empty() )
	{
		for ( TextLetters::iterator it = m_TextLetters.begin(); it != m_TextLetters.end(); )
		{
			DrawVertexGroup dvg = {};
			dvg.texture = ( *it )->m_Texture;
			vertexCount = 0;
			dvg.StartVertexLocation = count;

			do
			{
				it++;
				++vertexCount;
				++count;
			}
			while ( it != m_TextLetters.end() && dvg.texture == ( *it )->m_Texture );

			dvg.VertexCount = vertexCount;
			//save dvg
			m_DrawVertexGroups_Text.push_back( dvg );
		}
	}

	if ( vertexCount > 0 )
	{
		m_vbd.ByteWidth = ( UINT )( sizeof( TextVertex ) * m_TextVeices.size() );
		m_vbd.StructureByteStride = sizeof( TextVertex );
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &m_TextVeices[0];
		HR( m_d3dDevice->CreateBuffer( &m_vbd, &vinitData, &m_Buffer_Text ) );
	}
}

void InitDirect3DApp::LoadBlend()
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

void InitDirect3DApp::LoadData()
{
	//AddHeroInfo
	std::vector<HeroInfo_Sptr> heroInfos;
	heroInfos = LuaResource::LoadLua<HeroInfo>( "hero" );

	for ( int idx = 0; idx < heroInfos.size(); idx++ )
	{
		g_HeroInfoManager.AddHeroInfo( heroInfos[idx]->m_Name, heroInfos[idx] );
	}
	//AddBG
	std::vector<BackGround_Sptr> backGrounds;
	backGrounds = LuaResource::LoadLua<BackGround>( "backGround" );

	for ( int idx = 0; idx < backGrounds.size(); idx++ )
	{
		g_BackGroundManager.AddBackGround( backGrounds[idx]->m_Name , backGrounds[idx] );
	}
	
	//AddObjectInfo
	std::vector<ObjectInfo_Sptr> objectInfos;
	objectInfos = LuaResource::LoadLua<ObjectInfo>( "object" );
	for ( int idx = 0; idx < objectInfos.size(); idx++ )
	{
		g_ObjectInfoManager.AddObjectInfo( objectInfos[idx]->m_Name, objectInfos[idx] );
	}
	
	//Add Background Music
	std::vector<std::string> BGMpath = LuaResource::LoadMusic("mp3");
	g_BackGroundManager.Set_BGM_PathList(BGMpath);
	
	//Add Sound
	std::vector<std::string> WAVpath = LuaResource::LoadMusic("wav");
	while (!WAVpath.empty())
	{
		g_WavPlayer.CreatSound(WAVpath.back());
		WAVpath.pop_back();
	}
	

	//*test
		g_BackGroundManager.SetCurrentBackGround( backGrounds.back()->m_Name );//set last element be current background
		g_BackGroundManager.Set_BGM_Play(0);
		g_ObjectManager.CreateWeapon( "Bat", Vector3( 600, 0, 600 ) );
	//*/
}

int InitDirect3DApp::UpdateInput()
{
	InputStateS::instance().GetInput();
	m_Player.UpdateInput();
	//test
	TestCamera();
	TestChee();
	TestWavPlayer();
	TestGameSpeed();
	TestViewEffect();
	TestFire();
	TestBody();

	if ( InputStateS::instance().isKeyDown( KEY_F1 ) )
	{
		b_Pause = !b_Pause;
	}

	if ( InputStateS::instance().isKeyDown( KEY_F2 ) )
	{
		if ( b_Pause )
		{
			D3DApp::DrawScene(); // clear window
			this->DrawScene();
			m_SwapChain->Present( 0, 0 );
			g_Time++;
			UpdateCamera();

			if ( g_EffectManager != NULL ) { g_EffectManager->Update( m_RenderTargetView ); }

			buildPoint();
			//Hero Update
			g_HeroManager.Update( 0 );
			//Chee Update
			g_ObjectManager.Update( 0 );
			m_Player.Update();

			//Background Update
			if ( g_BackGroundManager.GetCurrentBackGround() != NULL )
			{
				g_BackGroundManager.GetCurrentBackGround()->Update( 0 );
				BackgroundDataUpdate();
			}
		}
		else
		{
			b_Pause = true;
		}
	}

	return 0;
}
int InitDirect3DApp::UpdateUI()
{
	switch ( m_GameProcess )
	{
	case UI_PAGE_MAIN_MENU:
		DealMainMenu();
		break;

	case UI_PAGE_OPTION:
		DealOptionPage();
		break;

	case UI_PAGE_TOWER_SETTING:
		DealTowerSettingPage();
		break;

	case UI_PAGE_GAME_PLAY:
		DealGamePlayPage();
		break;
	}

	m_DXUT_UI->ClearCmdState();
	return 0;
}

void InitDirect3DApp::PrintInfo()
{
	// Code computes the average frames per second, and also the
	// average time it takes to render one frame.
	static int frameCnt = 0;
	static float t_base = 0.0f;
	frameCnt++;

	// Compute averages over one second period.
	if ( ( m_Timer.getGameTime() - t_base ) >= 1.0f )
	{
		float fps = ( float )frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;
		std::wcout << L"FPS: " << fps << L" Balls: " << g_ObjectManager.AmountChee()
		           << "\t" << L"\n";
		std::wcout << m_FrameStats;
		// Reset for next average.
		frameCnt = 0;
		t_base  += 1.0f;
	}
}


void InitDirect3DApp::InitTexture()
{
	ID3D11Texture2D* tex1, *tex2, *tesres;
	// Create the depth/stencil buffer and view.
	D3D11_TEXTURE2D_DESC depthStencilDesc0;
	depthStencilDesc0.Width     = m_ClientWidth;
	depthStencilDesc0.Height    = m_ClientHeight;
	depthStencilDesc0.MipLevels = 1;
	depthStencilDesc0.ArraySize = 1;
	depthStencilDesc0.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
	depthStencilDesc0.SampleDesc.Count   = 1; // multisampling must match
	depthStencilDesc0.SampleDesc.Quality = 0; // swap chain values.
	depthStencilDesc0.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc0.BindFlags      = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	depthStencilDesc0.CPUAccessFlags = 0;
	depthStencilDesc0.MiscFlags      = 0;
	HR( m_d3dDevice->CreateTexture2D( &depthStencilDesc0, 0, &tex1 ) );
	HR( m_d3dDevice->CreateShaderResourceView( tex1, 0, &m_SRVView1 ) );
	HR( m_d3dDevice->CreateRenderTargetView( tex1, 0, &m_RTVView1 ) );
	HR( m_d3dDevice->CreateTexture2D( &depthStencilDesc0, 0, &tex2 ) );
	HR( m_d3dDevice->CreateShaderResourceView( tex2, 0, &m_SRVView2 ) );
	HR( m_d3dDevice->CreateRenderTargetView( tex2, 0, &m_RTVView2 ) );
	HR( m_d3dDevice->CreateTexture2D( &depthStencilDesc0, 0, &tesres ) );
	HR( m_d3dDevice->CreateShaderResourceView( tesres, 0, &m_SRVViewRes ) );
	HR( m_d3dDevice->CreateRenderTargetView( tesres, 0, &m_RTVViewRes ) );
	ID3D11Texture2D* tex12;
	D3D11_TEXTURE2D_DESC depthStencilDesc1;
	depthStencilDesc1.Width     = m_ClientWidth;
	depthStencilDesc1.Height    = m_ClientHeight;
	depthStencilDesc1.MipLevels = 1;
	depthStencilDesc1.ArraySize = 1;
	depthStencilDesc1.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc1.SampleDesc.Count   = 1; // multisampling must match
	depthStencilDesc1.SampleDesc.Quality = 0; // swap chain values.
	depthStencilDesc1.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc1.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc1.CPUAccessFlags = 0;
	depthStencilDesc1.MiscFlags      = 0;
	HR( m_d3dDevice->CreateTexture2D( &depthStencilDesc1, 0, &tex12 ) );
	HR( m_d3dDevice->CreateDepthStencilView( tex12, 0, &m_DepthStencilView2 ) );
}

void InitDirect3DApp::DealMainMenu()
{
	std::vector<CmdState> cmdstate = m_DXUT_UI->GetCmdState();

	for ( size_t i = 0; i < cmdstate.size(); i++ )
	{
		switch ( cmdstate[i].id )
		{
		case IDC_MAIN_MENU_STARTGAME:
			ChangeUI( UI_PAGE_GAME_PLAY );
			break;

		case IDC_MAIN_MENU_OPTION:
			ChangeUI( UI_PAGE_OPTION );
			break;

		case IDC_MAIN_MENU_EXIT:
			exit( 0 );
			break;
		}
	}
}

void InitDirect3DApp::DealOptionPage()
{
	int val;
	std::vector<CmdState> cmdstate = m_DXUT_UI->GetCmdState();

// 	if (m_SettingKeyID>=0)
// 		SetCtrlKey();		//設定控制按鍵的處理函數

	for ( size_t i = 0; i < cmdstate.size(); i++ )
	{
		switch ( cmdstate[i].id )
		{
		case IDC_OPTION_MENU_VOLUME:
			val = m_DXUT_UI->GetSliderNum( cmdstate[i].id ) - 7000;
			WavSoundS::instance().SetVolume( val );
			break;

		case IDC_OPTION_MENU_KEY_UP:
			m_SettingKeyID = 0;
			m_SettingKeyTextID = IDC_OPTION_MENU_KEY_UP - 1;
			break;

		case IDC_OPTION_MENU_KEY_DOWN:
			m_SettingKeyID = 1;
			m_SettingKeyTextID = IDC_OPTION_MENU_KEY_DOWN - 1;
			break;

		case IDC_OPTIOT_MENU_KEY_LEFT:
			m_SettingKeyID = 2;
			m_SettingKeyTextID = IDC_OPTIOT_MENU_KEY_LEFT - 1;
			break;

		case IDC_OPTIOT_MENU_KEY_RIGHT:
			m_SettingKeyID = 3;
			m_SettingKeyTextID = IDC_OPTIOT_MENU_KEY_RIGHT - 1;
			break;

		case IDC_OPTIOT_MENU_KEY_SKILL:
			m_SettingKeyID = 4;
			m_SettingKeyTextID = IDC_OPTIOT_MENU_KEY_SKILL - 1;
			break;

		case IDC_OPTIOT_MENU_KEY_TIME:
			m_SettingKeyID = 5;
			m_SettingKeyTextID = IDC_OPTIOT_MENU_KEY_TIME - 1;
			break;

		case IDC_OPTIOT_MENU_KEY_EXIT:
			GoBackUI();
			break;
		}
	}
}

void InitDirect3DApp::DealTowerSettingPage()
{
	int tid;
	std::vector<CmdState> cmdstate = m_DXUT_UI->GetCmdState();

	for ( size_t i = 0; i < cmdstate.size(); i++ )
	{
		switch ( cmdstate[i].id )
		{
		case IDC_TOWER_SETTING_TOWERCOMBO:
			ReflashTowerState();
			break;

		case IDC_TOWER_SETTING_LVUP:
			tid = m_DXUT_UI->GetComboBoxSel( IDC_TOWER_SETTING_TOWERCOMBO );
			ReflashTowerState();
			break;

		case IDC_TOWER_SETTING_SELL:
			tid = m_DXUT_UI->GetComboBoxSel( IDC_TOWER_SETTING_TOWERCOMBO );
			ReflashTowerState();
			break;

		case IDC_TOWER_SETTING_TOWERSEL:
			break;

		case IDC_TOWER_SETTING_BUY:
			tid = m_DXUT_UI->GetComboBoxSel( IDC_TOWER_SETTING_TOWERCOMBO );
			ReflashTowerState();
			break;

		case IDC_TOWER_SETTING_OPTION:
			ChangeUI( UI_PAGE_OPTION );
			break;

		case IDC_TOWER_SETTING_BACK:
			GoBackUI();
			break;

		case IDC_TOWER_SETTING_EXIT:
			exit( 0 );
			break;
		}
	}
}

void InitDirect3DApp::DealGamePlayPage()
{
	std::vector<CmdState> cmdstate = m_DXUT_UI->GetCmdState();

	for ( size_t i = 0; i < cmdstate.size(); i++ )
	{
		switch ( cmdstate[i].id )
		{
		case IDC_PLAY_PAGE_MENU:
			ChangeUI( UI_PAGE_TOWER_SETTING );
			break;
		}
	}
}

void InitDirect3DApp::ChangeUI( int i )
{
	if ( i != m_GameProcess )
	{
		m_Last2GameProcess = m_LastGameProcess;
		m_LastGameProcess = m_GameProcess;
		m_GameProcess = i;
		m_DXUT_UI->CloseAllUI();
		m_DXUT_UI->OpenUI( i );
	}
}

void InitDirect3DApp::GoBackUI()
{
	if ( m_LastGameProcess != m_GameProcess )
	{
		m_GameProcess = m_LastGameProcess;
		m_LastGameProcess = m_Last2GameProcess;
		m_DXUT_UI->CloseAllUI();
		m_DXUT_UI->OpenUI( m_GameProcess );
	}
}

void InitDirect3DApp::ReflashTowerState()
{
}



void InitDirect3DApp::UpdateCamera()
{
	if ( m_Player.m_Hero->Position().x < m_ClientWidth )
	{
		float m = m_ClientWidth - g_Camera->LookAt().x;
		g_Camera->MoveX( m * 0.05f );
	}
	else if ( m_Player.m_Hero->Position().x > g_BackGroundManager.GetCurrentBackGround()->Width() - m_ClientWidth )
	{
		float m = g_BackGroundManager.GetCurrentBackGround()->Width() - m_ClientWidth - g_Camera->LookAt().x;
		g_Camera->MoveX( m * 0.05f );
	}
	else
	{
		float m = m_Player.m_Hero->Position().x - g_Camera->LookAt().x;
		g_Camera->MoveX( m * 0.05f );
	}

	m_Entity_cLootAt->SetRawValue( g_Camera->GetLookAt(), 0, sizeof( float ) * 3 );
	m_Entity_cPos->SetRawValue( ( void* )g_Camera->GetCPos(), 0, sizeof( float ) * 3 );
	m_Chee_cLootAt->SetRawValue( g_Camera->GetLookAt(), 0, sizeof( float ) * 3 );
	m_Chee_cPos->SetRawValue( ( void* )g_Camera->GetCPos(), 0, sizeof( float ) * 3 );
	m_Background_cLootAt->SetRawValue( g_Camera->GetLookAt(), 0, sizeof( float ) * 3 );
	m_Background_cPos->SetRawValue( ( void* )g_Camera->GetCPos(), 0, sizeof( float ) * 3 );
	m_ColorRect_cLootAt->SetRawValue( g_Camera->GetLookAt(), 0, sizeof( float ) * 3 );
	m_ColorRect_cPos->SetRawValue( ( void* )g_Camera->GetCPos(), 0, sizeof( float ) * 3 );
	m_Shadow_cLootAt->SetRawValue( g_Camera->GetLookAt(), 0, sizeof( float ) * 3 );
	m_Shadow_cPos->SetRawValue( ( void* )g_Camera->GetCPos(), 0, sizeof( float ) * 3 );
	m_Body_cLootAt->SetRawValue( g_Camera->GetLookAt(), 0, sizeof( float ) * 3 );
	m_Body_cPos->SetRawValue( ( void* )g_Camera->GetCPos(), 0, sizeof( float ) * 3 );
	m_Text_cLootAt->SetRawValue( g_Camera->GetLookAt(), 0, sizeof( float ) * 3 );
	m_Text_cPos->SetRawValue( ( void* )g_Camera->GetCPos(), 0, sizeof( float ) * 3 );
}

void InitDirect3DApp::BackgroundDataUpdate()
{
	ParallelLight pl = g_BackGroundManager.GetCurrentBackGround()->GetParallelLight();
	m_Shadow_lightDir->SetRawValue( &pl.m_Direction[0], 0, sizeof( float ) * 3 );
	m_Shadow_lightStr->SetFloat( pl.m_LightStrength * 0.1f );
}

void InitDirect3DApp::TestCamera()
{
	if ( InputStateS::instance().isKeyPress( KEY_Z ) )
	{
		g_Camera->Zoom( -3 );
	}

	if ( InputStateS::instance().isKeyPress( KEY_X ) )
	{
		g_Camera->Zoom( 3 );
	}

	if ( InputStateS::instance().isKeyPress( KEY_NUMPAD4 ) )
	{
		g_Camera->MoveX( -3 );
	}

	if ( InputStateS::instance().isKeyPress( KEY_NUMPAD6 ) )
	{
		g_Camera->MoveX( 3 );
	}

	if ( InputStateS::instance().isKeyPress( KEY_NUMPAD2 ) )
	{
		g_Camera->MoveY( -3 );
	}

	if ( InputStateS::instance().isKeyPress( KEY_NUMPAD8 ) )
	{
		g_Camera->MoveY( 3 );
	}

	if ( InputStateS::instance().isKeyPress( KEY_K ) )
	{
		g_Camera->SurroundX( -0.1f );
	}

	if ( InputStateS::instance().isKeyPress( KEY_I ) )
	{
		g_Camera->SurroundX( 0.1f );
	}

	if ( InputStateS::instance().isKeyPress( KEY_J ) )
	{
		g_Camera->SurroundY( -0.1f );
	}

	if ( InputStateS::instance().isKeyPress( KEY_L ) )
	{
		g_Camera->SurroundY( 0.1f );
	}
}

void InitDirect3DApp::TestChee()
{
	if ( InputStateS::instance().isKeyDown( KEY_1 ) )
	{
		g_ObjectManager.CreateChee( "davis_ball", Vector3( 100, 80, 1000 ), Vector3( 0, 0, 0 ) );
	}

	if ( InputStateS::instance().isKeyDown( KEY_2 ) )
	{
		g_ObjectManager.CreateChee( "davis_ball", Vector3( 1000, 80, 1000 ), Vector3( -10, 0, 0 ) );
	}
}

void InitDirect3DApp::TestWavPlayer()
{
	if ( InputStateS::instance().isKeyDown( KEY_P ) )
	{
		g_WavPlayer.StartDevice();
	}

	if ( InputStateS::instance().isKeyDown( KEY_LBRACKET ) )
	{
		g_WavPlayer.PauseDevice();
	}

	if ( InputStateS::instance().isKeyDown( KEY_RBRACKET ) )
	{
		g_WavPlayer.StopDevice();
	}

	int vol = g_WavPlayer.GetVolume();

	if ( InputStateS::instance().isKeyPress( KEY_COMMA ) )
	{
		g_WavPlayer.SetVolume( ++vol );
	}

	if ( InputStateS::instance().isKeyPress( KEY_PERIOD ) )
	{
		g_WavPlayer.SetVolume( --vol );
	}
}

void InitDirect3DApp::TestFire()
{
	if ( InputStateS::instance().isKeyDown( KEY_D ) )
	{
		m_Player.m_Hero->SetEffect( EffectType::NONE );
	}

	if ( InputStateS::instance().isKeyDown( KEY_F ) )
	{
		m_Player.m_Hero->SetEffect( EffectType::FIRE );
		//m_Player.m_Hero->SetEffect(EffectType::POISON);
	}
}

void InitDirect3DApp::TestBody()
{
	if ( InputStateS::instance().isKeyDown( KEY_B ) )
	{
		b_Body = !b_Body;
	}
}

void InitDirect3DApp::ParseCommandLine( int argc, char* argv[] )
{
	int current = 1;
	std::string mainStr;

	while ( current < argc )
	{
		mainStr = argv[current];

		if ( !mainStr.compare( "-hero" ) )
		{
			if ( ++current >= argc )
			{
				break;
			}

			/*std::string heros( argv[current] );
			std::vector<std::string> v;
			boost::split( v, heros, boost::is_any_of( "," ) );
			for( std::size_t i = 0; i < v.size(); i++ )
			{
				LuaCell_Sptr hero = LuaCell_Sptr( new LuaCell );
				hero->InputLuaFile( v[i].c_str() );
				HeroInfo_Sptr temp = HeroInfo_Sptr( new HeroInfo );
				temp->LoadHeroData( hero );
				g_HeroInfoManager.AddHeroInfo( temp->m_Name, temp );
			}*/
			std::string heroStr( argv[current] );
			heroStr.append( ".lua" );
			LuaCell_Sptr hero = LuaCell_Sptr( new LuaCell );
			hero->InputLuaFile( heroStr.c_str() );
			HeroInfo_Sptr temp = HeroInfo_Sptr( new HeroInfo );
			temp->LoadData( hero );
			g_HeroInfoManager.AddHeroInfo( temp->m_Name, temp );
			g_HeroManager.Destory( m_Player.m_Hero, 10 );
			m_Player.SetHero( temp->m_Name );
			m_Player.m_Hero = g_HeroManager.Create( m_Player.HeroName(), Vector3( 1000, 500, 100 ) );
			current++;
		}
	}
}

void InitDirect3DApp::TestGameSpeed()
{
	if ( InputStateS::instance().isKeyDown( KEY_F3 ) && g_TimeSpeed > 1.f / 600.f )
	{
		g_TimeSpeed -= 1.f / 600.f;
		std::cout << "g_TimeSpeed: " << g_TimeSpeed << std::endl;
	}

	if ( InputStateS::instance().isKeyDown( KEY_F4 ) )
	{
		g_TimeSpeed += 1.f / 600.f;
		std::cout << "g_TimeSpeed: " << g_TimeSpeed << std::endl;
	}
}

void InitDirect3DApp::InitPlayer()
{
	//player init
	CtrlKeys key;
	key.push_back( CtrlKey::UP );
	m_Player.m_Keyboard.SetCtrlKey( KEY_UP, key );
	key.clear();
	key.push_back( CtrlKey::DOWN );
	m_Player.m_Keyboard.SetCtrlKey( KEY_DOWN, key );
	key.clear();
	key.push_back( CtrlKey::RIGHT );
	m_Player.m_Keyboard.SetCtrlKey( KEY_RIGHT, key );
	key.clear();
	key.push_back( CtrlKey::LEFT );
	m_Player.m_Keyboard.SetCtrlKey( KEY_LEFT, key );
	key.clear();
	key.push_back( CtrlKey::DEF );
	m_Player.m_Keyboard.SetCtrlKey( KEY_Q, key );
	key.clear();
	key.push_back( CtrlKey::JUMP );
	m_Player.m_Keyboard.SetCtrlKey( KEY_W, key );
	key.clear();
	key.push_back( CtrlKey::ATK1 );
	m_Player.m_Keyboard.SetCtrlKey( KEY_E, key );
	key.clear();
	key.push_back( CtrlKey::ATK2 );
	m_Player.m_Keyboard.SetCtrlKey( KEY_R, key );
	key.clear();
	key.push_back( CtrlKey::DEF );
	key.push_back( CtrlKey::UP );
	key.push_back( CtrlKey::ATK1 );
	m_Player.m_Keyboard.SetCtrlKey( KEY_T, key );
	m_Player.SetHero( "Davis" );
	m_Player.SetTeam( 0 );
	m_Player.m_Hero = g_HeroManager.Create( m_Player.HeroName(), Vector3( 1000, 500, 100 ) );
	m_Player.SetUserName( L"<こんにちは測試人-Testing...>" );
}
