#include "StdAGAL.h"
#include "Effect.h"
#include "global.h"
#include <iostream>

Effect::Effect( void ): m_SerialNum( 1 )
{
}


Effect::~Effect( void )
{
}

bool Effect::Initialize( HWND hwnd )
{
	bool result;
	//
	m_RenderTexture = new RenderTextureClass();

	if ( !m_RenderTexture )
	{
		return false;
	}

	result = m_RenderTexture->Initialize( g_d3dDevice, PIC_W, PIC_H );

	if ( !result )
	{
		MessageBox( hwnd, L"Could not initialize the texture RenderTextureClass object.", L"Error", MB_OK );
		return false;
	}

	//
	m_FireShader = new FireShaderClass();
	result = m_FireShader->Initialize( g_d3dDevice, g_DeviceContext, L"shader\\FireShaderScale.fx", hwnd );

	if ( !result )
	{
		MessageBox( hwnd, L"Could not initialize the FireShaderClass object.", L"Error", MB_OK );
		return false;
	}

	m_Texture = Texture_Sptr( new Texture( m_RenderTexture->GetShaderResourceView() ) );
	m_TextureID = g_TextureManager.AddTexture( "EffectTexture", m_Texture );
	//
	m_EffectShaders.push_back( m_FireShader ); //push Fire
	//push Poison
	//push Freeze
	//push else...
	//
	m_vEffect.resize( m_EffectShaders.size() );
	//
	SetFireParameters();
	return true;
}
void Effect::Updata( float dt )
{
	for ( int i = 0; i < m_vEffect.size(); i++ )
	{
		if ( !m_vEffect[i].empty() )
		{
			if ( i < m_EffectShaders.size() )
			{
				m_EffectShaders[i]->Update( dt );
				m_EffectShaders[i]->CreatVertex( m_vEffect[i].begin(), m_vEffect[i].end() );
			}
		}
	}
}

void Effect::SetFireParameters()
{
	D3DXVECTOR3 scrollSpeeds, scales;
	D3DXVECTOR2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	scrollSpeeds = D3DXVECTOR3( 1.0f, 2.0f, 5.0f );
	scales = D3DXVECTOR3( 20.0f, 30.0f, 40.0f );
	distortion1 = D3DXVECTOR2( 0.03f, 0.07f );
	distortion2 = D3DXVECTOR2( 0.02f, 0.05f );
	distortion3 = D3DXVECTOR2( 0.01f, 0.1f );
	distortionScale = 1.2f;
	distortionBias = 1.2f;
	m_EffectShaders[EffectType::FIRE]->SetShaderParameters( 7, scrollSpeeds, scales, distortion1, distortion2, distortion3, distortionScale, distortionBias );
}

bool Effect::CreateEffect( EffectType::e type, EffectData* ed )
{
	if ( Overflow() ) { return false; }

	ed->m_Pos.x = ( float ) 1 + ( m_SerialNum - 1 ) % ( PIC_W / PASTE_W );
	ed->m_Pos.y = ( float ) 1 + ( m_SerialNum - 1 ) / ( PIC_W / PASTE_W );

	switch ( type )
	{
	case	EffectType::FIRE:
		m_vEffect[EffectType::FIRE].push_back( *ed );
		break;

	case	EffectType::POISON:
		break;
	}

	m_SerialNum++;
	return true;
}

void Effect::Clear()
{
	for ( int i = 0; i < m_vEffect.size(); i++ )
	{
		m_vEffect[i].clear();
	}

	//m_FireEffect.clear();
	m_SerialNum = 0;
}

bool Effect::Overflow()
{
	return ( m_SerialNum >= ( PIC_H / PASTE_H ) * ( PIC_W / PASTE_W ) );
}

bool Effect::Check( EffectType::e type, EffectData* ed )
{
	for ( int i = 0; i < m_vEffect.size(); i++ )
	{
		for ( EffectDatas::iterator it = m_vEffect[i].begin(); it != m_vEffect[i].end(); it++ )
		{
			if ( ( *ed ) == ( *it ) )
			{
				ed->m_Pos = it->m_Pos;
				return true;
			}
		}
	}

	/*
	for (EffectDatas::iterator it = m_FireEffect.begin();it != m_FireEffect.end();it++)
	{
		if((*ed) == (*it))
		{
			ed->m_Pos = it->m_Pos;
			return true;
		}
	}*/
	return false;
}

int Effect::GetTextureID()
{
	return m_TextureID;
}

void Effect::Render()
{
	if ( g_DeviceContext != NULL && g_DeviceContext != NULL )
	{
		m_RenderTexture->SetRenderTarget( g_DeviceContext, 0 );
		m_RenderTexture->ClearRenderTarget( g_DeviceContext, NULL, 0.0f, 0.0f, 0.0f, 0.0f );
		RenderShader();
	}
}
void Effect::RenderShader()
{
	//Render
	for ( int i = 0; i < m_EffectShaders.size(); i++ )
	{
		m_EffectShaders[i]->Render();
	}
}
ID3D11ShaderResourceView* Effect::GetTexture()
{
	return m_Texture->texture;
}


//EffectManager
EffectManager::EffectManager(): m_Page( 0 ), m_Size( 4 )
{
	//��l�� Effect
}
EffectManager::EffectManager( HWND hwnd ): m_Page( 0 ), m_Size( 4 )
{
	//��l�� Effect
	//test
	m_Effect = new Effect*[m_Size];

	for ( int i = 0; i < m_Size; i++ )
	{
		m_Effect[i] = new Effect();
		m_Effect[i]->Initialize( hwnd );
	}
}

int EffectManager::CreateEffect( EffectType::e type, int textureID, D3DXVECTOR4* picpos )
{
	EffectData ed;
	ed.m_TextureID = textureID;
	ed.m_PicPos    = *picpos;

	for ( int i = 0; i < m_Size; i++ )
	{
		if ( i == ( m_Page + 1 ) % m_Size ) { continue; } //�U�@����Buffer�����j��

		if ( m_Effect[i]->Check( type, &ed ) )
		{
			*picpos = D3DXVECTOR4( ed.m_Pos.x, ed.m_Pos.y, ( PIC_W / PASTE_W ), ( PIC_H / PASTE_H ) );
			return m_Effect[i]->GetTextureID();
		}
	}

	if ( !m_Effect[m_Page % m_Size]->CreateEffect( type, &ed ) )
	{
		m_Page++;
		m_Effect[m_Page % m_Size]->Clear();
		m_Effect[m_Page % m_Size]->CreateEffect( type, &ed );
	}

	*picpos = D3DXVECTOR4( ed.m_Pos.x, ed.m_Pos.y, ( PIC_W / PASTE_W ), ( PIC_H / PASTE_H ) );
	return m_Effect[m_Page % m_Size]->GetTextureID();
}

void EffectManager::OnResize( int W, int H )
{
	m_ScreanH = H;
	m_ScreanW = W;
}

void EffectManager::Update( ID3D11RenderTargetView* originRTV )
{
	//set viewport because every Effect's vp.w & vp.h are all the same
	D3D11_VIEWPORT vp;
	vp.Width = PIC_W;
	vp.Height = PIC_H;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_DeviceContext->RSSetViewports( 1, &vp );

	for ( int i = 0; i < m_Size; i++ )
	{
		m_Effect[i]->Updata( g_Time * 0.01f );
		m_Effect[i]->Render();
	}

	//set viewport to screan's width & height
	vp.Width = ( float ) m_ScreanW;
	vp.Height = ( float ) m_ScreanH;
	g_DeviceContext->RSSetViewports( 1, &vp );
	g_DeviceContext->OMSetRenderTargets( 1, &originRTV, 0 );
}
//HolyK Test
ID3D11ShaderResourceView* EffectManager::Test_GetNowTexture()
{
	return NULL;
}

float EffectManager::EffectScale( EffectType::e type )
{
	switch ( type )
	{
	case EffectType::FIRE:
		return 2.0f;

	default:
		return 1.0f;
	}
}

//HolyK Test