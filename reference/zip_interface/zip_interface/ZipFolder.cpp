#include "ZipFolder.h"
#include <fstream>


ZipFolder::ZipFolder()
{
	this->m_ZipFolders.clear();
	this->m_Name = "Unnamed";
	this->m_ZipDatas.clear();
	this->m_TotalSize = 0;
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
		int Nindex = path.find_last_of('\\');
		this->m_Name.assign(&path[Nindex+1], &path[path.length()]);
	}
	ifs.close();
	return true;
}

bool ZipFolder::ReadFromDisk( const std::wstring& path )
{
	return this->ReadFromDisk(ConvStr::GetStr(path));
}


ZipData* ZipFolder::FindData( const std::string& name )
{
	for(int i = 0; i < this->m_ZipDatas.size(); i++)
	{
		if(this->m_ZipDatas[i]->m_Name == name)
		{
			return this->m_ZipDatas[i];
		}
	}
	return 0;
}

ZipFolder* ZipFolder::FindFolder( const std::string& name )
{
	for(int i = 0; i < this->m_ZipFolders.size(); i++)
	{
		if(this->m_ZipFolders[i].m_Name == name)
		{
			return &this->m_ZipFolders[i];
		}
	}
	return 0;
}


ZipData* ZipFolder::GetData( const std::string& path )
{
	ZipFolder* ZF = this;
	ZipData* ZD;
	std::string name;
	int t_start = path.find_first_not_of('\\');
	int t_end;

	for(int i = t_start; i < path.length(); i++)
	{
		if(path[i] == '\\')
		{
			t_end = i;
			name.assign(&path[t_start], &path[t_end]);
			ZF = ZF->FindFolder(name);
			t_start = t_end;
		}
		if(ZF==0) return 0;
	}
	
	name.assign(&path[t_start], &path[path.length()]);
	return ZF->FindData(name);
}

ZipData* ZipFolder::GetData( const std::wstring& path )
{
	return this->GetData(ConvStr::GetStr(path));
}

