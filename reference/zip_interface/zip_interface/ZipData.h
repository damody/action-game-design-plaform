#ifndef _ZipData_H_
#define _ZipData_H_
#include <zlib.h>
#include <cstdio>
#include "ConvStr.h"
//#include <boost/archive/basic_binary_oarchive.hpp>
//#include <boost/archive/basic_binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
//#include <boost/serialization/shared_ptr.hpp>
//#include <boost/serialization/nvp.hpp>
//#include <boost/serialization/export.hpp>
//#include <boost/serialization/split_free.hpp>



typedef unsigned char Byte;
typedef std::vector<Byte> Bytes;
typedef long int lint;

enum CompressLevel
{
	CL_BEST_COMPRESSION = 9,
	CL_NORMAL = 6,
	CL_BEST_SPEED = 1,
	CL_NO_COMPRESS = 0
};

class ZipData
{
public:
	std::string m_Name;
public:
	ZipData();
	ZipData( unsigned char* src, lint size); // init data from memory, no compress
	ZipData( const std::string& path); // init data from disk, no compress
	ZipData( const std::wstring& path);// init data from disk, no compress
	bool	InitFromMemory( unsigned char* src, lint size);
	bool	InitFromDisk( const std::string& path);
	bool	InitFromDisk( const std::wstring& path);
	inline lint	GetOriginalSize(){return m_OriginalSize;}
	inline lint	GetCompressSize(){return m_CompressSize;}
	inline bool	IsCompressed(){return m_IsCompressed!=CL_NO_COMPRESS;}
	void	UncompressData();
	void	CompressData( CompressLevel cl); // BestSpeed = 1, BestCompression = 9
	inline const Bytes&	GetData() {return m_Data;}

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & m_Name;
		ar & m_OriginalSize;
		ar & m_CompressSize;
		ar & m_IsCompressed;
		ar & m_Data;
	}

	lint	m_OriginalSize; // real size
	lint	m_CompressSize;
	int	m_IsCompressed;
	Bytes	m_Data;
};

typedef std::vector<ZipData*> ZipData_ptrs;

#endif // _ZipData_H_