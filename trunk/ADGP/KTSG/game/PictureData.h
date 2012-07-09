#pragma once
#include <vector>

struct PictureBlock
{
	int x;
	int y;
	int w;
	int h;
};
typedef std::vector<PictureBlock> PictureBlocks;

struct PictureData
{
	//是否自動分割區塊
	bool		m_AutoClip;
	//TextureID
	int             m_TextureID;
	//圖片路徑
	std::string	m_Path;
	int		m_Width;
	int		m_Height;
	int		m_Row;
	int		m_Column;
	PictureBlocks	m_PictureBlocks;
};
typedef std::vector<PictureData> PictureDatas;

