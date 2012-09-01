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

// stdafx.h : �i�b�����Y�ɤ��]�t�зǪ��t�� Include �ɡA
// �άO�g�`�ϥΫo�ܤ��ܧ�
// �M�ױM�� Include �ɮ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �q Windows ���Y�ư����`�ϥΪ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ���T�w�q������ CString �غc�禡

// ���� MFC ���ä@�Ǳ`���Υi����ĵ�i�T�����\��
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �֤߻P�зǤ���
#include <afxext.h>         // MFC �X�R�\��


#include <afxdisp.h>        // MFC Automation ���O



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �䴩�� Internet Explorer 4 �q�α��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �䴩�� Windows �q�α��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �\��ϩM����C�� MFC �䴩


//���쥨��
#define ReleaseCOM(x) { if(x){ x->Release();x = 0; }}

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                      \
	{                                                  \
	HRESULT hr = x;                                \
	if(FAILED(hr))                                 \
		{                                              \
		DXTrace(__FILE__, __LINE__, hr, _T(#x), TRUE); \
		}                                              \
	}
#endif
#else
#ifndef HR
#define HR(x) x;
#endif
#endif 

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
#pragma warning(disable:4819)
#pragma warning(disable:4244)
#pragma warning(disable:4005)
#include <fstream>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>

#include <d3d11.h>
#include <windows.h>
#include <d3dx11.h>
#include <vector>
#include <vector>
#include <map>
#include <D3DX11tex.h>
#include <D3DX11.h>
#include <D3DX11core.h>
#include <D3DX11async.h>
#include <dxsdkver.h>
#include <usp10.h>
#include <dimm.h>
#include <sal.h>
#include <windows.h>

