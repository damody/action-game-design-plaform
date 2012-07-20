
#include "ZipData.h"
#include <auto_link_zlib.hpp>

ZipData::ZipData()
{
	m_Name = "";
	m_OriginalSize = 0;
	m_CompressSize = 0;
	m_IsCompressed = CL_NO_COMPRESS;
	m_Data.clear();
}

ZipData::ZipData( unsigned char* src, lint size )
{
	m_Name = "";
	m_OriginalSize = size;
	m_CompressSize = compressBound(size);
	m_IsCompressed = CL_NO_COMPRESS;
	m_Data.resize(size);
	memcpy(&m_Data[0], src, size);
}

ZipData::ZipData( const std::string& path )
{
	int Nindex = path.find_last_of('\\');
	
	m_Name.assign(&path[Nindex+1], &path[path.length()]);
	//m_Name = path;
	m_OriginalSize = 0;
	m_CompressSize = 0;
	m_IsCompressed = CL_NO_COMPRESS;
	m_Data.clear();

	FILE* p_File;
	p_File = fopen(path.c_str(), "rb");
	if(p_File==NULL) return;

	fseek(p_File, 0, SEEK_END);
	this->m_OriginalSize = ftell(p_File);
	m_CompressSize = compressBound(m_OriginalSize);
	rewind(p_File);

	m_Data.resize(m_OriginalSize);
	fread(&m_Data[0], 1, m_OriginalSize, p_File);

	fclose(p_File);
}

ZipData::ZipData( const std::wstring& path )
{
	ZipData(ConvStr::GetStr(path));
}

bool ZipData::InitFromMemory( unsigned char* src, lint size )
{
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
	unsigned long srcLen = m_CompressSize;
	unsigned long tmpLen = m_OriginalSize;
	unsigned char* srcbuff = new unsigned char[srcLen];
	unsigned char* tmpbuff = new unsigned char[tmpLen];

	memset(tmpbuff, 0, tmpLen);
	memcpy(srcbuff, m_Data.data(), srcLen);

	if(uncompress(tmpbuff, &tmpLen, srcbuff, srcLen) == Z_OK)
	{
		m_Data.resize(tmpLen);
		memcpy(&m_Data[0], tmpbuff, tmpLen);

		m_IsCompressed = CL_NO_COMPRESS;
	}

	delete srcbuff;
	delete tmpbuff;
}

void ZipData::CompressData( CompressLevel cl )
{
	if(cl != CL_NO_COMPRESS)
	{
		if(m_IsCompressed!=cl) UncompressData();
		else return;
		unsigned long srcLen = m_OriginalSize;
		unsigned long tmpLen = compressBound(m_OriginalSize);
		unsigned char* srcbuff = new unsigned char[srcLen];
		unsigned char* tmpbuff = new unsigned char[tmpLen];

		memset(tmpbuff, 0, tmpLen);
		memcpy(srcbuff, m_Data.data(), srcLen);

		if(compress2(tmpbuff, &tmpLen, srcbuff, srcLen, cl) == Z_OK)
		{
			m_Data.resize(tmpLen);
			memcpy(&m_Data[0], tmpbuff, tmpLen);

			m_CompressSize = tmpLen;
			m_IsCompressed = cl;
		}

		delete srcbuff;
		delete tmpbuff;
	}
}
