#include "StdGame.h"
#include "TextureManager.h"
#include "d3dApp.h"
#include "global.h"
TextureManager::TextureManager( void ): m_index( -1 )
{
}

TextureManager::~TextureManager( void )
{
}

int TextureManager::AddTexture( std::wstring path )
{
	int index = Find( path );

	if ( index != -1 )
	{
		return index;
	}

	m_Textures.push_back( Texture_Sptr( new Texture( path ) ) );
	m_List.push_back( path );
	m_index++;
	return m_index;
}

int TextureManager::AddTexture( std::wstring name , Texture_Sptr texture )
{
	m_Textures.push_back( texture );
	m_List.push_back( name );
	m_index++;
	return m_index;
}


Texture_Sptr TextureManager::GetTexture( unsigned int index )
{
	if ( index < m_Textures.size() )
	{
		return m_Textures[index];
	}
	else { return Texture_Sptr(); }
}

int TextureManager::Find( std::wstring path )
{
	int index = -1;

	for ( std::vector<std::wstring>::iterator it = m_List.begin(); it != m_List.end(); it++ )
	{
		index++;

		if ( ( *it ) == path ) { return index; }
	}

	return -1;// Not Found
}

Texture::Texture( std::string path ): w( 0 ), h( 0 )
{
	assert( g_d3dDevice != 0 ); // check init ok
	FILE* file = fopen( path.c_str(), "r" );
	assert( file != 0 ); // check file ok
	fclose( file );
	D3DX11_IMAGE_INFO info;

	if ( D3D_OK == D3DX11GetImageInfoFromFileA( path.c_str(), 0, &info, 0 ) )
	{
		w = info.Width;
		h = info.Height;
	}

	if ( g_d3dDevice )
	{
		D3DX11CreateShaderResourceViewFromFileA( g_d3dDevice, path.c_str(), 0, 0, &texture, 0 );
		DXUT_SetDebugName( texture, path.c_str() );
	}

	w = info.Width;
	h = info.Height;
}

Texture::Texture( std::wstring path )
{
	assert( g_d3dDevice != 0 ); // check init ok
	FILE* file = _wfopen( path.c_str(), L"r" );
	assert( file != 0 ); // check file ok
	fclose( file );
	D3DX11_IMAGE_INFO info;

	if ( D3D_OK == D3DX11GetImageInfoFromFileW( path.c_str(), 0, &info, 0 ) )
	{
		w = info.Width;
		h = info.Height;
	}

	if ( g_d3dDevice )
	{
		D3DX11CreateShaderResourceViewFromFileW( g_d3dDevice, path.c_str(), 0, 0, &texture, 0 );
	}
}

Texture::Texture( ID3D11ShaderResourceView* rc )
{
	texture = rc;
}



Texture::~Texture()
{
	ReleaseCOM( texture );
}
