#pragma once
#include <auto_link_crypto.hpp>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <windows.h>
#include <fstream>
#include <aes.h>
#include <des.h>
#include <sha.h>
#include "ConvStr.h"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

typedef unsigned char Byte;
typedef std::vector<Byte> Bytes;

class CryptoData
{
public:
	std::string m_Name;
public:
	enum EncryptionType
	{
		NO_ENCRYPTION = 0,
		//RSA = 1,
		AES = 512,	//0x200
		DES = 768,	//0x300
		DES3 = 1024	//0x400 
	};
public:
	CryptoData();
	CryptoData(const Byte* src, size_t size);	// init data from memory, no compress
	CryptoData(const Bytes& src);
	CryptoData(const std::string& path);		// init data from memory, no compress
	CryptoData(const std::wstring& path);		// init data from memory, no compress
	~CryptoData(){}
	bool	InitFromMemory(const Byte* src, size_t size);
	bool	InitFromMemory(const Bytes& src);
	bool	InitFromDisk(const std::string& path);
	bool	InitFromDisk(const std::wstring& path);
	bool	WriteToDisk(const std::string& path);
	bool	WriteToDisk(const std::wstring& path);
	bool	ReadFromDisk(const std::string& path);
	bool	ReadFromDisk(const std::wstring& path);
	inline int	GetOriginalSize() {return m_OriginalSize;}
	inline int	GetEncryptionSize() {if(m_IsEncryption){return m_EncryptionSize;} return 0;}
	inline const Bytes&	GetData() {return m_Data;}
	inline const Bytes& GetDigest() {return m_Digest;}
	inline int	IsEncryption() {return m_IsEncryption;}
	void	DecryptData(Byte* password, size_t len);
	void	DecryptData(const std::string& password);
	void	DecryptData(const std::wstring& password);
	void	EncryptData(size_t cl, Byte* password, size_t len);
	void	EncryptData(size_t cl, const std::string& password);
	void	EncryptData(size_t cl, const std::wstring& password);
	Bytes	CalcuateDigest(bool setDigest);
	bool	VerifyDigest(Bytes digest);
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & m_Name;
		ar & m_OriginalSize;
		ar & m_EncryptionSize;
		ar & m_IsEncryption;
		ar & m_Digest;
		ar & m_Data;
	}

	size_t		m_OriginalSize;		// real size
	size_t		m_EncryptionSize;
	size_t		m_IsEncryption;
	Bytes	m_Digest;
	Bytes	m_Data;
};
typedef std::vector<CryptoData*> CryptoData_ptrs;