#include "ZipFolder.h"
#include <fstream>


ZipFolder::ZipFolder()
{
	this->m_ZipFolders.clear();
	this->m_Name = "";
	this->m_ZipDatas.clear();
	this->m_TotalSize = 0;
	this->m_PerFolder = 0;
}

void ZipFolder::AddZipDataFromMemory( unsigned char* src, int size, CompressLevel cl /*= NO_COMPRESS*/ )
{
	this->m_ZipDatas.push_back(new ZipData(src, size));
	if(cl!=CL_NO_COMPRESS)
		this->m_ZipDatas.back()->CompressData(cl);
	this->m_TotalSize += this->m_ZipDatas.back()->GetOriginalSize();
}

void ZipFolder::AddZipDataFromDisk( const std::string& path, CompressLevel cl /*= NO_COMPRESS*/ )
{
	this->m_ZipDatas.push_back(new ZipData(path));
	if(cl!=CL_NO_COMPRESS)
		this->m_ZipDatas.back()->CompressData(cl);
	this->m_TotalSize += this->m_ZipDatas.back()->GetOriginalSize();
}

void ZipFolder::AddZipDataFromDisk( const std::wstring& path, CompressLevel cl /*= NO_COMPRESS*/ )
{
	this->AddZipDataFromDisk(ConvStr::GetStr(path), cl);
}

bool ZipFolder::WriteToDisk( const std::string& path )
{
	std::ofstream ofs(path, std::ios::binary);
	if(!ofs.is_open()) return false;
	{
		//boost::archive::text_oarchive oa(ofs);
		boost::archive::binary_oarchive oa(ofs);
		oa << this->m_ZipFolders;
		oa << this->m_Name;
		oa << this->m_TotalSize;
		oa << this->m_ZipDatas;
		oa << this->m_PerFolder;
	}
	ofs.close();
	return true;
}

bool ZipFolder::WriteToDisk( const std::wstring& path )
{
	return this->WriteToDisk(ConvStr::GetStr(path));
}

bool ZipFolder::ReadFromDisk( const std::string& path )
{
	std::ifstream ifs(path, std::ios::binary);
	if(!ifs.is_open()) return false;
	{
		//boost::archive::text_iarchive ia(ifs);
		boost::archive::binary_iarchive ia(ifs);
		ia >> this->m_ZipFolders;
		ia >> this->m_Name;
		ia >> this->m_TotalSize;
		ia >> this->m_ZipDatas;
		ia >> this->m_PerFolder;
	}
	ifs.close();
	return true;
}

bool ZipFolder::ReadFromDisk( const std::wstring& path )
{
	return this->ReadFromDisk(ConvStr::GetStr(path));
}

