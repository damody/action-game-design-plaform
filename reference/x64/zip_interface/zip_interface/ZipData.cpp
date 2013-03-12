
#include "ZipData.h"
#include <auto_link_zlib.hpp>
#include <auto_link_lzma.hpp>
#include <auto_link_lzo.hpp>
#include <zlib.h>

#include <Types.h>
#include <LzmaLib.h>

#include <lzo\lzoconf.h>
#include <lzo\lzo1x.h>
static const char *progname = NULL;
#define WANT_LZO_MALLOC 1
#define WANT_XMALLOC 1

#include <cstdio>
#include "ConvStr.h"
#include <boost/timer.hpp>
#include <iostream>


ZipData::ZipData()
{
	m_Name = "Unnamed";
	m_OriginalSize = 0;
	m_CompressSize = 0;
	m_IsCompressed = CL_NO_COMPRESS;
	m_Prop.clear();
	m_Data.clear();
}

ZipData::ZipData( unsigned char* src, lint size )
{
	InitFromMemory(src, size);
}

ZipData::ZipData( const std::string& path )
{
	InitFromDisk(path);
}

ZipData::ZipData( const std::wstring& path )
{
	ZipData(ConvStr::GetStr(path));
}

bool ZipData::InitFromMemory( unsigned char* src, lint size )
{
	m_Name = "Unnamed";
	m_OriginalSize = size;
	m_CompressSize = compressBound(size);
	m_IsCompressed = CL_NO_COMPRESS;
	m_Data.resize(size);
	memcpy(&m_Data[0], src, size);

	return true;
}

bool ZipData::InitFromDisk( const std::string& path )
{
	ZipData();
	int Nindex = path.find_last_of('\\');

	m_Name.assign(&path[Nindex+1], &path[path.length()]);
	//m_Name = path;

	FILE* p_File; 
	p_File = fopen(path.c_str(), "rb");
	if(p_File==NULL) return false;

	fseek(p_File, 0, SEEK_END);
	this->m_OriginalSize = ftell(p_File);
	m_CompressSize = compressBound(m_OriginalSize);
	rewind(p_File);

	m_Data.resize(m_OriginalSize);
	fread(&m_Data[0], 1, m_OriginalSize, p_File);

	fclose(p_File);

	return true;
}

bool ZipData::InitFromDisk( const std::wstring& path )
{
	return this->InitFromDisk(ConvStr::GetStr(path));
}

void ZipData::UncompressData()
{
	if(m_IsCompressed==CL_NO_COMPRESS) return;

	boost::timer mytimer;
	mytimer.restart();
	if(CL_ZLIB_1_BAST_SPEED <= m_IsCompressed && m_IsCompressed <= CL_ZLIB_9_BEST_COMPRESSION)
	{
		ZlibUncompressData();
	}
	else if(CL_LZMA_0_BAST_SPEED <= m_IsCompressed && m_IsCompressed <= CL_LZMA_9_BAST_COMPRESSION)
	{
		LzmaUncompressData();
	}
	else if(CL_LZO_1x_1 == m_IsCompressed)
	{
		LzoUncompressData();
	}
	std::cout << "UncompressData time: "<< mytimer.elapsed() << std::endl;
}

void ZipData::CompressData( CompressLevel cl )
{
	if(cl == m_IsCompressed) return;
	if(cl != CL_NO_COMPRESS) UncompressData();

	boost::timer mytimer;
	mytimer.restart();
	if(CL_ZLIB_1_BAST_SPEED <= cl && cl <= CL_ZLIB_9_BEST_COMPRESSION)
	{	
		ZlibCompressData(cl);
	}
	else if(CL_LZMA_0_BAST_SPEED <= cl && cl <= CL_LZMA_9_BAST_COMPRESSION)
	{
		LzmaCompressData(cl);
	}
	else if(CL_LZO_1x_1 == cl)
	{
		LzoCompressData(cl);
	}
	std::cout << "m_OriginalSize:" << m_OriginalSize/1024.0/1024 << "\nm_CompressSize:" << m_CompressSize/1024.0/1024 <<std::endl;
	std::cout << "CompressData time: "<< mytimer.elapsed() << std::endl;
	
}

bool ZipData::ZlibCompressData( CompressLevel cl )
{
	bool finish = false;
	int level = cl - 10;
	unsigned long srcLen = m_OriginalSize;
	unsigned long tmpLen = compressBound(m_OriginalSize);
	unsigned char* tmpbuff = (unsigned char*)malloc(tmpLen);

	memset(tmpbuff, 0, tmpLen);

	if(compress2(tmpbuff, &tmpLen, &m_Data[0], srcLen, level) == Z_OK)
	{
		m_Data.resize(tmpLen);
		memcpy(&m_Data[0], tmpbuff, tmpLen);

		m_CompressSize = tmpLen;
		m_IsCompressed = cl;
		finish = true;

		std::cout << "ZlibCompressData ok\n";
	}
	free(tmpbuff);

	return finish;
}

bool ZipData::ZlibUncompressData()
{
	bool finish = false;
	unsigned long srcLen = m_CompressSize;
	unsigned long tmpLen = m_OriginalSize;
	unsigned char* tmpbuff = (unsigned char*)malloc(tmpLen);

	memset(tmpbuff, 0, tmpLen);

	if(uncompress(tmpbuff, &tmpLen, &m_Data[0], srcLen) == Z_OK)
	{
		m_Data.resize(tmpLen);
		memcpy(&m_Data[0], tmpbuff, tmpLen);

		m_IsCompressed = CL_NO_COMPRESS;
		finish = true;

		std::cout << "ZlibUncompressData ok\n";
	}
	free(tmpbuff);

	return finish;
}

bool ZipData::LzmaCompressData( CompressLevel cl )
{
	bool finish = false;
	int r;
	int level = cl - 20;
	size_t srcLen = m_OriginalSize;
	size_t tmpLen = srcLen + srcLen/3 + 128;
	unsigned char* tmpbuff = (unsigned char*)malloc(tmpLen);
	unsigned char prop[5];
	size_t propSize;

	memset(tmpbuff, 0, tmpLen);
	
	r = LzmaCompress(tmpbuff, &tmpLen, &m_Data[0], srcLen, prop, &propSize, level, 0, 3, 0, 2, 32, 2);

	if(r == SZ_OK)
	{
		m_Data.resize(tmpLen);
		memcpy(&m_Data[0], tmpbuff, tmpLen);
		m_Prop.resize(propSize);
		memcpy(&m_Prop[0], prop, propSize);

		m_CompressSize = tmpLen;
		m_IsCompressed = cl;
		finish = true;
		std::cout << "LzmaCompressData ok\n";
	}else
	{
		std::cout << "Lzma error: " << r << std::endl;
	}
	free(tmpbuff);

	return finish;
}

bool ZipData::LzmaUncompressData()
{
	bool finish = false;
	size_t srcLen = m_CompressSize;
	size_t tmpLen = m_OriginalSize;
	unsigned char* tmpbuff = new unsigned char[tmpLen];

	memset(tmpbuff, 0, tmpLen);

	if(LzmaUncompress(tmpbuff, &tmpLen, &m_Data[0], &srcLen, m_Prop.data(), m_Prop.size()) == SZ_OK)
	{
		m_Data.resize(tmpLen);
		memcpy(&m_Data[0], tmpbuff, tmpLen);

		m_Prop.clear();
		m_IsCompressed = CL_NO_COMPRESS;
		finish = true;
		std::cout << "LzmaUncompressData ok\n";
	}
	delete tmpbuff;

	return finish;
}
 
 bool ZipData::LzoCompressData( CompressLevel cl )
 {
 	bool finish = false;
 	lzo_bytep in;
 	lzo_bytep out;
 	lzo_voidp wrkmem;
 	lzo_uint in_len = m_OriginalSize;
 	lzo_uint out_len = in_len + in_len / 16 + 64 + 3;
 
 	in = (lzo_bytep) malloc(in_len);
 	out = (lzo_bytep) malloc(out_len);
 	wrkmem = (lzo_voidp) malloc(LZO1X_1_MEM_COMPRESS);
 
 	lzo_memcpy(in, &m_Data[0], in_len);
 	
 	if(lzo1x_1_compress(in,in_len,out,&out_len,wrkmem) == LZO_E_OK)
 	{
 		m_Data.resize(out_len);
 		lzo_memcpy(&m_Data[0], out, out_len);
 
 		m_CompressSize = out_len;
 		m_IsCompressed = cl;
 		finish = true;
 		std::cout << "LzoCompressData ok\n";
 	}
 
 	free(wrkmem);
 	free(out);
 	free(in);
 
 	return finish;
 	
 }
 
 bool ZipData::LzoUncompressData()
 {
 	bool finish = false;
 	int r;
 	lzo_bytep in;
 	lzo_bytep out;
 	lzo_uint in_len = m_CompressSize;
 	lzo_uint out_len = m_OriginalSize;
 
 	in = (lzo_bytep) malloc(in_len);
 	out = (lzo_bytep) malloc(out_len);
 	
 	lzo_memcpy(in, &m_Data[0], in_len);
 
 	r = lzo1x_decompress(in, in_len, out, &out_len, NULL);
 	if(LZO_E_OK == r)
 	{
 		m_Data.resize(out_len);
 		lzo_memcpy(&m_Data[0], out, out_len);
 		
 		m_IsCompressed = CL_NO_COMPRESS;
 		finish = true;
 		std::cout << "LzoUncompressData ok\n";
 	}
 	else
 	{
 		std::cout << "internal error - decompression failed: " << r << std::endl;
 	}
 
 	free(in);
 	free(out);
 
 	return finish;
 }
