#include "CryptoData.h"

CryptoData::CryptoData()
{
	m_OriginalSize = 0;
	m_IsEncryption = NO_ENCRYPTION;
	m_Data.clear();
	m_Digest.clear();
}
CryptoData::CryptoData(const Byte* src, size_t size)
{
	m_OriginalSize = size;
	m_IsEncryption = NO_ENCRYPTION;
	m_Data.clear();
	m_Data.assign(src, src+size);
	m_Digest.clear();
}
CryptoData::CryptoData(const Bytes& src)
{
	CryptoData(&src[0], src.size());
}
CryptoData::CryptoData(const std::string& path)
{
	m_OriginalSize = 0;
	m_IsEncryption = NO_ENCRYPTION;
	m_Data.clear();
	FILE* p_File; 
	p_File = fopen(path.c_str(), "rb");
	if(p_File) 
	{
		char* buffer = (char*)malloc(sizeof(char)*65535);
		size_t tempSizeCount;
		while(tempSizeCount = fread(buffer, 1, 65535, p_File))
		{
			m_OriginalSize += (int)tempSizeCount;
			m_Data.insert(m_Data.end(), buffer, buffer+tempSizeCount);
		}
	}
	fclose(p_File);
	m_Digest.clear();
}
CryptoData::CryptoData(const std::wstring& path)
{
	CryptoData(ConvStr::GetStr(path));
}

bool CryptoData::InitFromMemory(const Byte* src, size_t size)
{
	m_OriginalSize = size;
	m_IsEncryption = NO_ENCRYPTION;
	m_Data.clear();
	m_Data.assign(src, src+size);
	m_Digest.clear();
	return 1;
}
bool CryptoData::InitFromMemory(const Bytes& src)
{
	return InitFromMemory(&src[0], src.size());
}
bool CryptoData::InitFromDisk(const std::string& path)
{
	m_OriginalSize = 0;
	m_IsEncryption = NO_ENCRYPTION;
	m_Data.clear();
	m_Digest.clear();

	FILE* p_File; 
	p_File = fopen(path.c_str(), "rb");
	if(p_File) 
	{
		char* buffer = (char*)malloc(sizeof(char)*65535);
		size_t tempSizeCount;
		while(tempSizeCount = fread(buffer, 1, 65535, p_File))
		{
			m_OriginalSize += (int)tempSizeCount;
			m_Data.insert(m_Data.end(), buffer, buffer+tempSizeCount);
		}
		fclose(p_File);
		return 1;
	}
	fclose(p_File);
	return 0;
}
bool CryptoData::InitFromDisk(const std::wstring& path)
{
	return InitFromDisk(ConvStr::GetStr(path));
}

void CryptoData::EncryptData(size_t cl, Byte* password, size_t len)
{
	Bytes temp_Data,output_Data;
	switch(cl)
	{
	case CryptoData::AES:
		m_IsEncryption = CryptoData::AES;
		if(len!=32 && len!=24 && len!=16) break;
		m_EncryptionSize = (int)ceil(m_OriginalSize/(double)(CryptoPP::AES::BLOCKSIZE))*CryptoPP::AES::BLOCKSIZE;
		temp_Data = m_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=CryptoPP::AES::BLOCKSIZE)
		{
			CryptoPP::AESEncryption aesEncryptor = CryptoPP::AESEncryption();
			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::AES::BLOCKSIZE);
			for(int j=0; j<CryptoPP::AES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::AES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::AES::BLOCKSIZE);
			
			memset(xorBlock, 0, CryptoPP::AES::BLOCKSIZE);
			aesEncryptor.SetKey(password,len);
			aesEncryptor.ProcessAndXorBlock(inputBlock,xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+CryptoPP::AES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	case CryptoData::DES:
		m_IsEncryption = CryptoData::DES;
		if(len!=8) break;
		m_EncryptionSize = (int)ceil(m_OriginalSize/(double)(CryptoPP::DES::BLOCKSIZE))*CryptoPP::DES::BLOCKSIZE;
		temp_Data = m_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=CryptoPP::DES::BLOCKSIZE)
		{
			CryptoPP::DESEncryption desEncryptor = CryptoPP::DESEncryption();
			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::DES::BLOCKSIZE);
			for(int j=0; j<CryptoPP::DES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::DES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::DES::BLOCKSIZE);
			
			memset(xorBlock, 0, CryptoPP::DES::BLOCKSIZE);
			desEncryptor.SetKey(password,len);
			desEncryptor.ProcessAndXorBlock(inputBlock,xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+CryptoPP::DES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	case CryptoData::DES3:
		m_IsEncryption = CryptoData::DES3;
		if(len!=24) break;
		m_EncryptionSize = (int)ceil(m_OriginalSize/(double)(CryptoPP::DES::BLOCKSIZE))*CryptoPP::DES::BLOCKSIZE;
		temp_Data = m_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=CryptoPP::DES::BLOCKSIZE)
		{
			CryptoPP::DESEncryption desEncryptor = CryptoPP::DESEncryption();
			CryptoPP::DESDecryption desDecryptor = CryptoPP::DESDecryption();
			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::DES::BLOCKSIZE);
			for(int j=0; j<CryptoPP::DES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::DES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::DES::BLOCKSIZE);
			
			memset(xorBlock, 0, CryptoPP::DES::BLOCKSIZE);
			desEncryptor.SetKey(password,8);
			desEncryptor.ProcessAndXorBlock(inputBlock,xorBlock, outputBlock);
			memset(xorBlock, 0, CryptoPP::DES::BLOCKSIZE);
			desDecryptor.SetKey(password+8, 8);
			desDecryptor.ProcessAndXorBlock(outputBlock, xorBlock, inputBlock);
			memset(xorBlock, 0, CryptoPP::DES::BLOCKSIZE);
			desEncryptor.SetKey(password+16,8);
			desEncryptor.ProcessAndXorBlock(inputBlock,xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+CryptoPP::DES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	}
}
void CryptoData::EncryptData(size_t cl, const std::string& password)
{
	EncryptData(cl, (Byte*)(password.c_str()), password.size());
}
void CryptoData::EncryptData(size_t cl, const std::wstring& password)
{  
	EncryptData(cl, (Byte*)ConvStr::GetStr(password).c_str(), ConvStr::GetStr(password).size());
}

void CryptoData::DecryptData(Byte* password, size_t len)
{
	Bytes temp_Data,output_Data;
	switch(m_IsEncryption)
	{
	case CryptoData::AES:
		if(len!=32 && len!=24 && len!=16) break;
		temp_Data = m_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=CryptoPP::AES::BLOCKSIZE)
		{
			CryptoPP::AESDecryption aesDecryptor = CryptoPP::AESDecryption();
			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::AES::BLOCKSIZE);
			for(int j=0; j<CryptoPP::AES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::AES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::AES::BLOCKSIZE);
			
			memset(xorBlock, 0, CryptoPP::AES::BLOCKSIZE);
			aesDecryptor.SetKey(password, len);
			aesDecryptor.ProcessAndXorBlock(inputBlock, xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+CryptoPP::AES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	case CryptoData::DES:
		if(len!=8) break;
		temp_Data = m_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=CryptoPP::DES::BLOCKSIZE)
		{
			CryptoPP::DESDecryption desDecryptor = CryptoPP::DESDecryption();
			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::DES::BLOCKSIZE);
			for(int j=0; j<CryptoPP::DES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::DES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::DES::BLOCKSIZE);

			memset(xorBlock, 0, CryptoPP::DES::BLOCKSIZE);
			desDecryptor.SetKey(password, len);
			desDecryptor.ProcessAndXorBlock(inputBlock, xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+CryptoPP::DES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	case CryptoData::DES3:
		if(len!=24) break;
		temp_Data = m_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=CryptoPP::DES::BLOCKSIZE)
		{
			CryptoPP::DESEncryption desEncryptor = CryptoPP::DESEncryption();
			CryptoPP::DESDecryption desDecryptor = CryptoPP::DESDecryption();
			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::DES::BLOCKSIZE);
			for(int j=0; j<CryptoPP::DES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::DES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*CryptoPP::DES::BLOCKSIZE);

			memset(xorBlock, 0, CryptoPP::DES::BLOCKSIZE);
			desDecryptor.SetKey(password+16, 8);
			desDecryptor.ProcessAndXorBlock(inputBlock, xorBlock, outputBlock);
			memset(xorBlock, 0, CryptoPP::DES::BLOCKSIZE);
			desEncryptor.SetKey(password+8, 8);
			desEncryptor.ProcessAndXorBlock(outputBlock, xorBlock, inputBlock);
			memset(xorBlock, 0, CryptoPP::DES::BLOCKSIZE);
			desDecryptor.SetKey(password, 8);
			desDecryptor.ProcessAndXorBlock(inputBlock, xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+CryptoPP::DES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	}
}
void CryptoData::DecryptData(const std::string& password)
{
	DecryptData((Byte*)(password.c_str()), password.size());
}
void CryptoData::DecryptData(const std::wstring& password)
{
	DecryptData((Byte*)ConvStr::GetStr(password).c_str(), ConvStr::GetStr(password).size());
}

Bytes CryptoData::CalcuateDigest(bool setDigest)
{
	CryptoPP::SHA256 sha256Calculater = CryptoPP::SHA256();
	Byte* strDigest = (Byte*)malloc(sizeof(Byte)*(sha256Calculater.DigestSize()));
	sha256Calculater.CalculateDigest(strDigest, &m_Data[0], m_Data.size());
	if(setDigest) m_Digest.assign(strDigest,strDigest+sha256Calculater.DigestSize());
	return Bytes(strDigest,strDigest+sha256Calculater.DigestSize());
}
bool CryptoData::VerifyDigest(Bytes digest)
{	
	CryptoPP::SHA256 sha256Calculater = CryptoPP::SHA256();
	if(sha256Calculater.VerifyDigest(&digest[0], &m_Data[0], m_Data.size())) return 1;
	return 0;
}

bool CryptoData::WriteToDisk(const std::string& path)
{
	std::ofstream ofs(path, std::ios::binary);
	if(!ofs.is_open()) return false;
	{
		//boost::archive::text_oarchive oa(ofs);
		boost::archive::binary_oarchive oa(ofs);
		oa << this->m_Name;
		oa << this->m_OriginalSize;
		oa << this->m_EncryptionSize;
		oa << this->m_IsEncryption;
		oa << this->m_Digest;
		oa << this->m_Data;
	}				
	ofs.close();	
	return 1;
}
bool CryptoData::WriteToDisk(const std::wstring& path)
{
	return WriteToDisk(ConvStr::GetStr(path));
}
bool CryptoData::ReadFromDisk(const std::string& path)
{
	std::ifstream ifs(path, std::ios::binary);
	if(!ifs.is_open()) return false;
	{
		//boost::archive::text_iarchive ia(ifs);
		boost::archive::binary_iarchive ia(ifs);
		ia >> this->m_Name;
		ia >> this->m_OriginalSize;
		ia >> this->m_EncryptionSize;
		ia >> this->m_IsEncryption;
		ia >> this->m_Digest;
		ia >> this->m_Data;
		int Nindex = path.find_last_of('\\');
		//this->m_Name.assign(&path[Nindex+1], &path[path.length()]);
	}
	ifs.close();
}
bool CryptoData::ReadFromDisk(const std::wstring& path)
{
	return ReadFromDisk(ConvStr::GetStr(path));
}