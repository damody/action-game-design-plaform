// �o�� MFC �d�ҭ�l�{���X�|�ܽd�p��ϥ� MFC Microsoft Office Fluent �ϥΪ̤���
// (�uFluent UI�v)�A�åB�ȴ��Ѭ��ѦҸ�ơA����
// MFC �ѦҤ� MFC C++ �{���w�n��
// �H�������q�l��󪺸ɥR�C
// ���� Fluent UI ���ƻs�B�ϥΩδ��o�����v���ګh���O���ѡC
// �p�� Fluent UI ���v�p�����ԲӸ�T�A�гy�X
// http://msdn.microsoft.com/officeui�C
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// AGDP Designer.h : AGDP Designer ���ε{�����D���Y��
//
#pragma once

#ifndef __AFXWIN_H__
#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"       // �D�n�Ÿ�


// CAGDPDesignerApp:
// �аѾ\��@�����O�� AGDP Designer.cpp
//

class CAGDPDesignerApp : public CWinAppEx
{
public:
	CAGDPDesignerApp();


// �мg
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �{���X��@
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
	virtual void OnFileNew();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAGDPDesignerApp theApp;
