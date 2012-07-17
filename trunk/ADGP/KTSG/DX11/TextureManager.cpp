
#include "TextureManager.h"
#include "d3dApp.h"
#include "global.h"

TextureManager::TextureManager(void):m_index(-1)
{
}

TextureManager::~TextureManager(void)
{
}

int TextureManager::AddTexture( std::string path)
{
		m_Textures.push_back(Texture_Sptr(new Texture(path)));
		m_List.push_back(path);
		m_index++;
		return m_index;
}

Texture_Sptr TextureManager::GetTexture(unsigned int index )
{
	if(index < m_Textures.size())
				return m_Textures[index];
}

int TextureManager::Find( std::string path )
{
	int index=-1;
	for(std::vector<std::string>::iterator it = m_List.begin();it != m_List.end(); it++)
	{
		index++;
		if((*it)==path)return index;
	}
	return -1;// Not Found
}

Texture::Texture( std::string path )
{
	assert(g_d3dDevice!=0); // check init ok
	FILE* file = fopen(path.c_str(), "r");
	assert(file!=0); // check file ok
	fclose(file);
	if (g_d3dDevice)
		D3DX11CreateShaderResourceViewFromFileA(g_d3dDevice, path.c_str(), 0, 0, &texture, 0);
}

Texture::Texture( std::wstring path )
{
	assert(g_d3dDevice!=0); // check init ok
	FILE* file = _wfopen(path.c_str(), L"r");
	assert(file!=0); // check file ok
	fclose(file);
	if (g_d3dDevice)
		D3DX11CreateShaderResourceViewFromFileW(g_d3dDevice, path.c_str(), 0, 0, &texture, 0);
}

Texture::~Texture()
{
	ReleaseCOM(texture);
}
