
// zip_interface.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// Czip_interfaceApp:
// �аѾ\��@�����O�� zip_interface.cpp
//

class Czip_interfaceApp : public CWinApp
{
public:
	Czip_interfaceApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern Czip_interfaceApp theApp;