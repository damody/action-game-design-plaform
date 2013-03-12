#ifndef _ZipData_H_
#define _ZipData_H_

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
	CL_NO_COMPRESS = 0,

	CL_ZLIB_9_BEST_COMPRESSION = 19,
	CL_ZLIB_8 = 18,
	CL_ZLIB_7 = 17,
	CL_ZLIB_6_NORMAL = 16,
	CL_ZLIB_5 = 15,
	CL_ZLIB_4 = 14,
	CL_ZLIB_3 = 13,
	CL_ZLIB_2 = 12,
	CL_ZLIB_1_BAST_SPEED = 11,

	CL_LZMA_9_BAST_COMPRESSION = 29,
	CL_LZMA_8 = 28,
	CL_LZMA_7 = 27,
	CL_LZMA_6 = 26,
	CL_LZMA_5_NORMAL = 25,
	CL_LZMA_4 = 24,
	CL_LZMA_3 = 23,
	CL_LZMA_2 = 22,
	CL_LZMA_1 = 21,
	CL_LZMA_0_BAST_SPEED = 20,

	CL_LZO_1x_1 = 30

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
	void	CompressData( CompressLevel cl); 
	inline const Bytes&	GetData() {return m_Data;}
protected:
	bool ZlibCompressData( CompressLevel cl);
	bool ZlibUncompressData();

	bool LzmaCompressData( CompressLevel cl);
	bool LzmaUncompressData();
 	
 	bool LzoCompressData( CompressLevel cl);
 	bool LzoUncompressData();

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & m_Name;
		ar & m_OriginalSize;
		ar & m_CompressSize;
		ar & m_IsCompressed;
		ar & m_Prop;
		ar & m_Data;
	}

	lint	m_OriginalSize; // real size
	lint	m_CompressSize;
	int	m_IsCompressed;
	Bytes   m_Prop; // for lzma
	Bytes	m_Data;
};

typedef std::vector<ZipData*> ZipData_ptrs;

#endif // _ZipData_H_