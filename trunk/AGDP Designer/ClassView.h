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

#include "ViewTree.h"
#include "PropertiesWnd.h"
#include <game/FrameInfo.h>

#define MAX_ANIMATIONS 52
#define MAX_ACTIONS 52

class CClassToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI( CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler )
	{
		CMFCToolBar::OnUpdateCmdUI( ( CFrameWnd* ) GetOwner(), bDisableIfNoHndler );
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

typedef std::map<HTREEITEM, FrameInfo>	TreeItemMap;

class CClassView : public CDockablePane
{
public:
	CClassView();
	virtual ~CClassView();

	void Refresh();
	void AdjustLayout();
	void OnChangeVisualStyle();
	void OnSelectItem( HTREEITEM item );
	CViewTree* GetViewTree();
	TreeItemMap& GetPropMap();
	void RemoveTreeItem( HTREEITEM item );

	static CClassView* GetInstance();
	static BOOL IsAnAnimation( CTreeCtrl* treeCtrl, HTREEITEM item );
	static BOOL IsNumber( CString str );

	virtual BOOL CanFloat() const;
	virtual BOOL CanBeClosed() const;
	virtual BOOL CanAutoHide() const;
protected:
	static CClassView* instance;
	CClassToolBar m_wndToolBar;
	CViewTree m_wndClassView;
	CImageList m_ClassViewImages;
	UINT m_nCurrSort;
	FrameInfo defaultFrameInfo( HTREEITEM item );

	TreeItemMap	m_propMap;

	HTREEITEM m_hTreeItem;

	void FillClassView();

// 覆寫
public:
	virtual BOOL PreTranslateMessage( MSG* pMsg );

protected:
	afx_msg int  OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnContextMenu( CWnd* pWnd, CPoint point );
	afx_msg void OnAnimationAdd();
	afx_msg void OnAnimationDelete();
	afx_msg void OnAnimationRename();
	afx_msg void OnFrameAdd();
	afx_msg void OnFrameDelete();
	afx_msg void OnPropertyView();
	afx_msg void OnNewFolder();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus( CWnd* pOldWnd );
	afx_msg LRESULT OnChangeActiveTab( WPARAM, LPARAM );
	afx_msg void OnSort( UINT id );
	afx_msg void OnUpdateSort( CCmdUI* pCmdUI );
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBodyAdd();
	afx_msg void OnBodyDelete();
	afx_msg void OnAttackDelete();
	afx_msg void OnAttackAdd();
	afx_msg void OnHitdataAdd();
	afx_msg void OnHitdataDelete();
	afx_msg void OnCatchAdd();
	afx_msg void OnCatchDelete();
	afx_msg void OnBloodinfoAdd();
	afx_msg void OnBloodinfoDelete();
	afx_msg void OnCreationAdd();
	afx_msg void OnCreationDelete();
	afx_msg void OnAddtocrouch();
};

