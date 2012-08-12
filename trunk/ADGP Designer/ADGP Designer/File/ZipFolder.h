#ifndef _ZipFolder_H_
#define _ZipFolder_H_
#include "ZipData.h"
#include "ConvStr.h"
#include "CryptoData.h"

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
	bool	WriteToMemory(Bytes& dst);
	bool	ReadFromMemory(const Bytes& src);
	bool	EncryptToDisk(int cryptoType, Byte* password, int len, const std::string& path);
	bool	EncryptToDisk(int cryptoType, Byte* password, int len, const std::wstring& path);
	Bytes	DecryptFromDisk(Byte* password, int len, const std::string& path);
	Bytes	DecryptFromDisk(Byte* password, int len, const std::wstring& path);
	inline int	GetTotalSize(){return m_TotalSize;}
	ZipData*	GetData(const std::string& path);
	ZipData*	GetData(const std::wstring& path);
public:
	std::string	m_Name;		 // ZipFolder name
	ZipData_ptrs	m_ZipDatas;
	ZipFolders	m_ZipFolders;
protected:
	ZipData*	FindData(const std::string& name);
	ZipFolder*	FindFolder(const std::string& name);
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & m_Name;
		ar & m_ZipDatas;
		ar & m_ZipFolders;
		ar & m_TotalSize;
	}
	int	m_TotalSize;
};

#endif // _ZipFolder_H_