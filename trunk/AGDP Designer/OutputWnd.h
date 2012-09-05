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

#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList ����

class COutputList : public CListBox
{
// �غc
public:
	COutputList();

// �{���X��@
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu( CWnd* pWnd, CPoint point );
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

class COutputWnd : public CDockablePane
{
// �غc
public:
	COutputWnd();

	void UpdateFonts();
	void AddStrToOutputDebug( CString& strAddToList )
	{
		m_wndOutputDebug.AddString( strAddToList );
		int nCount = m_wndOutputDebug.GetCount();
		m_wndOutputDebug.SetTopIndex( nCount - 1 );
	}
	void AddStrToOutputBuild( CString& strAddToList )
	{
		m_wndOutputBuild.AddString( strAddToList );
		int nCount = m_wndOutputBuild.GetCount();
		m_wndOutputBuild.SetTopIndex( nCount - 1 );
	}
	void AddStrToOutputFind( CString& strAddToList )
	{
		m_wndOutputFind.AddString( strAddToList );
		int nCount = m_wndOutputFind.GetCount();
		m_wndOutputFind.SetTopIndex( nCount - 1 );
	}
	virtual BOOL CanFloat() const;
	virtual BOOL CanBeClosed() const;
	virtual BOOL CanAutoHide() const;
// �ݩ�
protected:
	CMFCTabCtrl	m_wndTabs;

	COutputList m_wndOutputBuild;
	COutputList m_wndOutputDebug;
	COutputList m_wndOutputFind;

protected:
	void FillBuildWindow();
	void FillDebugWindow();
	void FillFindWindow();

	void AdjustHorzScroll( CListBox& wndListBox );

// �{���X��@
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, int cx, int cy );

	DECLARE_MESSAGE_MAP()
};

