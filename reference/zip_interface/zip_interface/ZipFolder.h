#ifndef _ZipFolder_H_
#define _ZipFolder_H_
#include "ZipData.h"
#include "ConvStr.h"

class ZipFolder;
typedef std::vector<ZipFolder> ZipFolders;

class ZipFolder
{
public:
	ZipFolder();
public:
	void	AddZipDataFromMemory(unsigned char* src, int size, CompressLevel cl = CL_NO_COMPRESS);
	void	AddZipDataFromDisk(const std::string& path, CompressLevel cl = CL_NO_COMPRESS);
	void	AddZipDataFromDisk(const std::wstring& path, CompressLevel cl = CL_NO_COMPRESS);
	bool	WriteToDisk(const std::string& path);
	bool	WriteToDisk(const std::wstring& path);
	bool	ReadFromDisk(const std::string& path);
	bool	ReadFromDisk(const std::wstring& path);
	inline int	GetTotalSize(){return m_TotalSize;}
public:
	std::string	m_Name;		 // ZipFolder name
	ZipData_ptrs	m_ZipDatas;
	ZipFolders	m_ZipFolders;
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & m_Name;
		ar & m_ZipDatas;
		ar & m_ZipFolders;
		ar & m_PerFolder;
		ar & m_TotalSize;
	}
	ZipFolder* m_PerFolder;
	int	   m_TotalSize;
};

#endif // _ZipFolder_H_