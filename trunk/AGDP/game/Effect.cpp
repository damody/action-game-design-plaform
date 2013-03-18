#include "StdGame.h"
#include "Effect.h"
#include "global.h"
#include <iostream>


EffectShaders effectShaders;

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

	//Set this effect texture info
	m_Texture = Texture_Sptr( new Texture( m_RenderTexture->GetShaderResourceView() ) );
	m_TextureID = g_TextureManager.AddTexture( L"EffectTexture", m_Texture );
	//
	m_vEffect.resize( effectShaders.size() );
	return true;
}
void Effect::Updata( float dt )
{
	for ( unsigned int i = 0; i < m_vEffect.size(); i++ )
	{
		if ( !m_vEffect[i].empty() )
		{
			effectShaders[i]->Update( dt );
			effectShaders[i]->CreatVertex( m_vEffect[i].begin(), m_vEffect[i].end() );
		}
	}
}

bool Effect::CreateEffect( EffectType type, EffectData* ed )
{
	if ( Overflow() ) { return false; }

	ed->m_Pos.x = ( float ) 1 + ( m_SerialNum - 1 ) % ( PIC_W / PASTE_W );
	ed->m_Pos.y = ( float ) 1 + ( m_SerialNum - 1 ) / ( PIC_W / PASTE_W );

	switch ( type )
	{
		case	0:
			m_vEffect[type].push_back( *ed );
			break;

		case	1:
			break;
	}

	m_SerialNum++;
	return true;
}

void Effect::Clear()
{
	for ( unsigned int i = 0; i < m_vEffect.size(); i++ )
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

bool Effect::Check( EffectType type, EffectData* ed )
{
	for ( unsigned int i = 0; i < m_vEffect.size(); i++ )
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
	for ( unsigned int i = 0; i < effectShaders.size(); i++ )
	{
		effectShaders[i]->Render();
	}
}
ID3D11ShaderResourceView* Effect::GetTexture()
{
	return m_Texture->texture;
}


//EffectManager
EffectManager::EffectManager(): m_Page( 0 ), m_Size( 4 ), m_Effect(0)
{
	//初始化 Effect
}
EffectManager::EffectManager( HWND hwnd ): m_Page( 0 ), m_Size( 4 )
{
	//初始化 Effect
	//test
	m_Effect = new Effect*[m_Size];
	//Init shader //push Fire ,Poison ,Freeze ...
	effectShaders.resize( 1 ); //目前只有火焰1種 所以size=1

	for ( unsigned int i = 0; i < effectShaders.size(); i++ )
	{
		bool result;
		effectShaders[i] = new EffectShaderClass();
		result = effectShaders[0]->Initialize( L"FireShader.lua", g_d3dDevice, g_DeviceContext, hwnd );

		if ( !result )
		{
			MessageBox( hwnd, L"Could not init EffectShader.", L"FireShader.Lua", MB_OK );
		}
	}

	for ( int i = 0; i < m_Size; i++ )
	{
		m_Effect[i] = new Effect();
		m_Effect[i]->Initialize( hwnd );
	}
}

int EffectManager::CreateEffect( EffectType type, int textureID, Vector4* picpos )
{
	EffectData ed;
	ed.m_TextureID = textureID;
	ed.m_PicPos    = *picpos;

	for ( int i = 0; i < m_Size; i++ )
	{
		if ( i == ( m_Page + 1 ) % m_Size ) { continue; } //下一頁為Buffer不做搜索

		if ( m_Effect[i]->Check( type, &ed ) )
		{
			*picpos = Vector4( ed.m_Pos.x, ed.m_Pos.y, ( PIC_W / PASTE_W ), ( PIC_H / PASTE_H ) );
			return m_Effect[i]->GetTextureID();
		}
	}

	if ( !m_Effect[m_Page % m_Size]->CreateEffect( type, &ed ) )
	{
		m_Page++;
		m_Effect[m_Page % m_Size]->Clear();
		m_Effect[m_Page % m_Size]->CreateEffect( type, &ed );
	}

	*picpos = Vector4( ed.m_Pos.x, ed.m_Pos.y, ( PIC_W / PASTE_W ), ( PIC_H / PASTE_H ) );
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

float EffectManager::EffectScale( EffectType type )
{
	switch ( type )
	{
		case 0://fire
			return 2.0f;

		default:
			return 1.0f;
	}
}

EffectManager::~EffectManager( void )
{
	for ( size_t i = 0; i < effectShaders.size(); i++ )
	{
		delete effectShaders[i];
	}
	if ( m_Effect )
	{
		for ( int i = 0; i < m_Size; i++ )
		{
			delete m_Effect[i];
			m_Effect[i] = NULL;
		}

		delete[] m_Effect;
		m_Effect = NULL;
	}
}

//HolyK Test