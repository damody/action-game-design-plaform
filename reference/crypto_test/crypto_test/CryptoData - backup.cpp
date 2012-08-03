#include "CryptoData.h"

CryptoData::CryptoData()
{
	m_OriginalSize = 0;
	m_IsEncryption = NO_ENCRYPTION;
	m_Data.clear();
}
CryptoData::CryptoData(unsigned char* src, int size)
{
	m_OriginalSize = size;
	m_IsEncryption = NO_ENCRYPTION;
	m_Data.clear();
	m_Data.assign(src, src+size);
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
			m_Data.assign(buffer, buffer+tempSizeCount);
		}
	}
	fclose(p_File);
}

bool CryptoData::InitFromMemory(unsigned char* src, int size)
{
	m_OriginalSize = size;
	m_IsEncryption = NO_ENCRYPTION;
	m_Data.clear();
	m_Data.assign(src, src+size);
	return 1;
}
bool CryptoData::InitFromDisk(const std::string& path)
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
			m_Data.assign(buffer, buffer+tempSizeCount);
		}
		fclose(p_File);
		return 1;
	}
	fclose(p_File);
	return 0;
}
bool CryptoData::InitFromDisk(const std::wstring& path)
{
	m_OriginalSize = 0;
	m_IsEncryption = NO_ENCRYPTION;
	m_Data.clear();

	FILE* p_File; 
	p_File = fopen(CryptoData::wctoch(path.c_str()), "rb");
	if(p_File) 
	{
		char* buffer = (char*)malloc(sizeof(char)*65535);
		size_t tempSizeCount;
		while(tempSizeCount = fread(buffer, 1, 65535, p_File))
		{
			m_OriginalSize += (int)tempSizeCount;
			m_Data.assign(buffer, buffer+tempSizeCount);
		}
		fclose(p_File);
		return 1;
	}
	fclose(p_File);
	return 0;
}
char* CryptoData::wctoch(const wchar_t* wcharString)
{
	char* temp = 0;
	wcstombs(temp, wcharString, INT_MAX);
	return temp;
}

void CryptoData::EncryptData(EncryptionType cl, Byte* password, int len)
{
	switch(cl)
	{
	case CryptoData::AES:
		m_IsEncryption = CryptoData::AES;
		if(len!=32 && len!=24 && len!=16) break;
		m_EncryptionSize = (int)ceil(m_OriginalSize/(double)(AES::BLOCKSIZE))*AES::BLOCKSIZE;
		Bytes temp_Data = m_Data,output_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=AES::BLOCKSIZE)
		{
			AESEncryption aesEncryptor = AESEncryption();

			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			for(int j=0; j<AES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			memset(xorBlock, 0, AES::BLOCKSIZE);

			aesEncryptor.SetKey(password,len);
			aesEncryptor.ProcessAndXorBlock(inputBlock,xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+AES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	}
}
void CryptoData::EncryptData(EncryptionType cl, Bytes password)
{
	switch(cl)
	{
	case CryptoData::AES:
		m_IsEncryption = CryptoData::AES;
		if(password.size()!=32 && password.size()!=24 && password.size()!=16) break;
		m_EncryptionSize = (int)ceil(m_OriginalSize/(double)(AES::BLOCKSIZE))*AES::BLOCKSIZE;
		Bytes temp_Data = m_Data,output_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=AES::BLOCKSIZE)
		{
			AESEncryption aesEncryptor = AESEncryption();

			Byte* passwordBlock = (Byte*)malloc(sizeof(Byte)*password.size());
			for(int j=0; j<password.size(); j++) passwordBlock[j] = password.at(j);
			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			for(int j=0; j<AES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			memset(xorBlock, 0, AES::BLOCKSIZE);

			aesEncryptor.SetKey(passwordBlock,password.size());
			aesEncryptor.ProcessAndXorBlock(inputBlock,xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+AES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	}
}
void CryptoData::EncryptData(EncryptionType cl, const std::string& password)
{
	switch(cl)
	{
	case CryptoData::AES:
		m_IsEncryption = CryptoData::AES;
		if(password.size()!=32 && password.size()!=24 && password.size()!=16) break;
		m_EncryptionSize = (int)ceil(m_OriginalSize/(double)(AES::BLOCKSIZE))*AES::BLOCKSIZE;
		Bytes temp_Data = m_Data,output_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=AES::BLOCKSIZE)
		{
			AESEncryption aesEncryptor = AESEncryption();

			const char* passwordChar = password.c_str();
			Byte* passwordBlock = (Byte*)malloc(sizeof(Byte)*password.size());
			for(int j=0; j<password.size(); j++) passwordBlock[j] = passwordChar[j];
			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			for(int j=0; j<AES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			memset(xorBlock, 0, AES::BLOCKSIZE);

			aesEncryptor.SetKey(passwordBlock,password.size());
			aesEncryptor.ProcessAndXorBlock(inputBlock,xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+AES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	}
}
void CryptoData::EncryptData(EncryptionType cl, const std::wstring& password)
{
	switch(cl)
	{
	case CryptoData::AES:
		m_IsEncryption = CryptoData::AES;
		if(password.size()!=32 && password.size()!=24 && password.size()!=16) break;
		m_EncryptionSize = (int)ceil(m_OriginalSize/(double)(AES::BLOCKSIZE))*AES::BLOCKSIZE;
		Bytes temp_Data = m_Data,output_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=AES::BLOCKSIZE)
		{
			AESEncryption aesEncryptor = AESEncryption();

			char* passwordChar = wctoch(password.c_str());
			Byte* passwordBlock = (Byte*)malloc(sizeof(Byte)*password.size());
			for(int j=0; j<password.size(); j++) passwordBlock[j] = passwordChar[j];
			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			for(int j=0; j<AES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			memset(xorBlock, 0, AES::BLOCKSIZE);

			aesEncryptor.SetKey(passwordBlock,password.size());
			aesEncryptor.ProcessAndXorBlock(inputBlock,xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+AES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	}
}

void CryptoData::DecryptData(Byte* password, int len)
{
	switch(m_IsEncryption)
	{
	case CryptoData::AES:
		if(len!=32 && len!=24 && len!=16) break;

		Bytes temp_Data = m_Data,output_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=AES::BLOCKSIZE)
		{
			AESDecryption aesDecryptor = AESDecryption();

			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			for(int j=0; j<AES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			memset(xorBlock, 0, AES::BLOCKSIZE);

			aesDecryptor.SetKey(password, len);
			aesDecryptor.ProcessAndXorBlock(inputBlock, xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+AES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	}
}
void CryptoData::DecryptData(Bytes password)
{
	switch(m_IsEncryption)
	{
	case CryptoData::AES:
		if(password.size()!=32 && password.size()!=24 && password.size()!=16) break;

		Bytes temp_Data = m_Data,output_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=AES::BLOCKSIZE)
		{
			AESDecryption aesDecryptor = AESDecryption();

			Byte* passwordBlock = (Byte*)malloc(sizeof(Byte)*password.size());
			for(int j=0; j<password.size(); j++) passwordBlock[j] = password.at(j);
			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			for(int j=0; j<AES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			memset(xorBlock, 0, AES::BLOCKSIZE);

			aesDecryptor.SetKey(passwordBlock, password.size());
			aesDecryptor.ProcessAndXorBlock(inputBlock, xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+AES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	}
}
void CryptoData::DecryptData( const std::string& password )
{
	switch(m_IsEncryption)
	{
	case CryptoData::AES:
		if(password.size()!=32 && password.size()!=24 && password.size()!=16) break;

		Bytes temp_Data = m_Data,output_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=AES::BLOCKSIZE)
		{
			AESDecryption aesDecryptor = AESDecryption();

			const char* passwordChar = password.c_str();
			Byte* passwordBlock = (Byte*)malloc(sizeof(Byte)*password.size());
			for(int j=0; j<password.size(); j++) passwordBlock[j] = passwordChar[j];
			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			for(int j=0; j<AES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			memset(xorBlock, 0, AES::BLOCKSIZE);

			aesDecryptor.SetKey(passwordBlock, password.size());
			aesDecryptor.ProcessAndXorBlock(inputBlock, xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+AES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	}
}
void CryptoData::DecryptData( const std::wstring& password )
{
	switch(m_IsEncryption)
	{
	case CryptoData::AES:
		if(password.size()!=32 && password.size()!=24 && password.size()!=16) break;

		Bytes temp_Data = m_Data,output_Data;
		temp_Data.resize(m_EncryptionSize, (Byte)0);
		output_Data.clear();
		for(int i=0; i<m_EncryptionSize; i+=AES::BLOCKSIZE)
		{
			AESDecryption aesDecryptor = AESDecryption();

			const char* passwordChar = wctoch(password.c_str());
			Byte* passwordBlock = (Byte*)malloc(sizeof(Byte)*password.size());
			for(int j=0; j<password.size(); j++) passwordBlock[j] = passwordChar[j];
			Byte* inputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			for(int j=0; j<AES::BLOCKSIZE; j++) inputBlock[j] = temp_Data.at(i+j); 
			Byte* outputBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			Byte* xorBlock = (Byte*)malloc(sizeof(Byte)*AES::BLOCKSIZE);
			memset(xorBlock, 0, AES::BLOCKSIZE);

			aesDecryptor.SetKey(passwordBlock, password.size());
			aesDecryptor.ProcessAndXorBlock(inputBlock, xorBlock, outputBlock);
			output_Data.insert(output_Data.end(), outputBlock, outputBlock+AES::BLOCKSIZE);
		}
		m_Data = output_Data;
		break;
	}
}
