// 這個 MFC 範例原始程式碼會示範如何使用 MFC Microsoft Office Fluent 使用者介面
// (「Fluent UI」)，並且僅提供為參考資料，做為
// MFC 參考及 MFC C++ 程式庫軟體
// 隨附相關電子文件的補充。
// 關於 Fluent UI 之複製、使用或散發的授權條款則分別提供。
// 如需 Fluent UI 授權計劃的詳細資訊，請造訪
// http://msdn.microsoft.com/officeui。
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList 視窗

class COutputList : public CListBox
{
// 建構
public:
	COutputList();

// 程式碼實作
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
// 建構
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
// 屬性
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

// 程式碼實作
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, int cx, int cy );

	DECLARE_MESSAGE_MAP()
};

