#pragma once
#include <vector>
namespace boost {namespace serialization {class access;}}
struct PictureBlock
{
	int x;
	int y;
	int w;
	int h;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& x;
		ar& y;
		ar& w;
		ar& h;
	}
};
typedef std::vector<PictureBlock> PictureBlocks;

struct PictureData
{
	//�O�_�۰ʤ��ΰ϶�
	bool			m_AutoClip;
	//TextureID
	int				m_TextureID;
	//�Ϥ����|
	std::wstring	m_Path;
	int				m_Width;
	int				m_Height;
	int				m_Row;
	int				m_Column;
	PictureBlocks	m_PictureBlocks;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& 	m_AutoClip;
		ar&     m_TextureID;
		ar& 	m_Path;
		ar& 	m_Width;
		ar& 	m_Height;
		ar& 	m_Row;
		ar& 	m_Column;
		ar& 	m_PictureBlocks;
	}
};
typedef std::vector<PictureData> PictureDatas;

