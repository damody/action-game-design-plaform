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

#include "FileTree.h"
#include "game/HeroInfo.h"

typedef std::map<HTREEITEM, HeroInfo_RawPtr> HeroInfohMap;

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI( CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler )
	{
		CMFCToolBar::OnUpdateCmdUI( ( CFrameWnd* ) GetOwner(), bDisableIfNoHndler );
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// 建構
public:
	CFileView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	virtual BOOL CanFloat() const;
	virtual BOOL CanBeClosed() const;
	virtual BOOL CanAutoHide() const;
// 屬性
protected:

	CFileTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

protected:
	void FillFileView();

// 程式碼實作
public:
	virtual ~CFileView();
	void OnSelectItem( HTREEITEM item );
	afx_msg void OnFileOpen();
private:
	HTREEITEM hHeroDoc;
	HTREEITEM hHero_Select;
	HTREEITEM hObjectDoc;
	HTREEITEM hBackgroundDoc;

	HeroInfohMap m_HeroInfoMap;


protected:
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnContextMenu( CWnd* pWnd, CPoint point );
	afx_msg void OnProperties();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus( CWnd* pOldWnd );

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnPicturedataAdd();
	afx_msg void OnPicturedataAdd();
};

