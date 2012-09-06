#pragma once
#include "StdGame.h"
#include <vector>
#include <map>
#include <cassert>
#include <cstdio>
#include <windows.h>
#include "common/shared_ptr.h"


struct Texture
{
	Texture( std::string path );
	Texture( std::wstring path );
	Texture( ID3D11ShaderResourceView* rc );
	~Texture();
	ID3D11ShaderResourceView* texture;
	operator ID3D11ShaderResourceView* ()
	{
		return texture;
	}
	bool operator < ( const Texture& rhs )
	{
		return texture < rhs.texture;
	}
	bool operator == ( const Texture& rhs )
	{
		return texture == rhs.texture;
	}
	int w, h;
};
SHARE_PTR( Texture )

typedef std::vector<Texture_Sptr> Textures;
typedef std::map<int, Texture_Sptr> TextureMaps;

class TextureManager
{
public:
	TextureManager( void );
	~TextureManager( void );
	int AddTexture( std::string path );
	int AddTexture( std::string name , Texture_Sptr texture );
	int Find( std::string path );
	Texture_Sptr GetTexture( unsigned int index );
private:
	Textures	m_Textures;
	std::vector<std::string> m_List;
	int		m_index;
};

struct DrawVertexGroup
{
	Texture_Sptr	texture;	// §÷½è
	int	VertexCount, StartVertexLocation;
};
typedef std::vector<DrawVertexGroup> DrawVertexGroups;
