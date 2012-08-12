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

#include "ViewTree.h"
#include "PropertiesWnd.h"
#include <game/FrameInfo.h>

#define MAX_ANIMATIONS 52
#define MAX_ACTIONS 52

class CClassToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

typedef std::map<HTREEITEM, FrameInfo>	TreeItemMap;

class CClassView : public CDockablePane
{
public:
	CClassView();
	virtual ~CClassView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	void OnSelectItem(HTREEITEM item);
	CViewTree* GetViewTree();
	TreeItemMap& GetPropMap();
	void RemoveTreeItem(HTREEITEM item);

	static CClassView* GetInstance();
	//static CMFCPropertyGridProperty* GetDefaultPropList();
	static BOOL IsAnAnimation(CTreeCtrl* treeCtrl, HTREEITEM item);
	static BOOL IsNumber(CString str);
protected:
	static CClassView* instance;
	static const CString anims[MAX_ANIMATIONS];
	static const CString actionMap[MAX_ACTIONS];
	CClassToolBar m_wndToolBar;
	CViewTree m_wndClassView;
	CImageList m_ClassViewImages;
	UINT m_nCurrSort;
	
	TreeItemMap	m_propMap;
	FramesMap	m_FrameMap;

	void FillClassView();

// �мg
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAnimationAdd();
	afx_msg void OnAnimationDelete();
	afx_msg void OnAnimationRename();
	afx_msg void OnFrameAdd();
	afx_msg void OnFrameDelete();
	afx_msg void OnFrameRename();
	afx_msg void OnPropertyView();
	afx_msg void OnNewFolder();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);
public:
	afx_msg LRESULT OnPropertyChanged( __in WPARAM wparam, __in LPARAM lparam, HTREEITEM item );


	DECLARE_MESSAGE_MAP()
};

