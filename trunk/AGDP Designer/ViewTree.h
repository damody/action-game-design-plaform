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
// CViewTree 視窗

class CViewTree : public CTreeCtrl
{
// 建構
public:
	CViewTree();

	HTREEITEM m_lastSelectedItem;

// 覆寫
protected:
	virtual BOOL OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult );
	virtual void OnBeginLabelEdit( NMHDR* pNMHDR, LRESULT* pResult );
	virtual void OnEndLabelEdit( NMHDR* pNMHDR, LRESULT* pResult );

// 程式碼實作
public:
	virtual ~CViewTree();

protected:
	afx_msg void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
};