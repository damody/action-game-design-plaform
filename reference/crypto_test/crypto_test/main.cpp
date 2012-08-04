#include <iostream>
#include <cstdio>
using namespace std;
#include "CryptoData.h" 

int main() 
{
	Byte* temp = (Byte*)malloc(sizeof(Byte)*18);
	for(int i=0; i<18; i++) temp[i] = i+1;
	Byte* password = (Byte*)malloc(sizeof(Byte)*16);
	for(int i=0; i<16; i++) password[i] = (i*i)%7;
	CryptoData test(temp,18);
	
	Bytes temp2 = Bytes(password,password+16);

	test.EncryptData(CryptoData::AES, &temp2[0], temp2.size());
	for(int i=0; i<test.GetEncryptionSize(); i++) cout << hex << (int)(test.GetData().at(i)) << " ";
	cout << endl;

	test.DecryptData(&temp2[0], temp2.size());
	for(int i=0; i<test.GetOriginalSize(); i++) cout << hex << (int)(test.GetData().at(i)) << " ";
	cout << endl;


	
	

	//system("PAUSE");
	return 0;
}