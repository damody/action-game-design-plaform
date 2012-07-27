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

#include "stdafx.h"
#include "ViewTree.h"
#include "resource.h"
#include "ClassView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYUP()
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginLabelEdit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndLabelEdit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 訊息處理常式

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CViewTree::OnBeginLabelEdit( NMHDR* pNMHDR, LRESULT* pResult )
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	// Limit text to 127 characters
	GetEditControl()->LimitText(127);

	*pResult = 0;
}

void CViewTree::OnEndLabelEdit( NMHDR* pNMHDR, LRESULT* pResult )
{
	*pResult = TRUE;
}

void CViewTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonDown(nFlags, point);

	CString classCaption, caption;
	ASSERT(classCaption.LoadString(IDS_CLASS_VIEW));

	this->GetParent()->GetWindowText(caption);

	if(classCaption.Compare(caption) == 0)
	{
		CPoint pt = point;

		UINT flags = 0;
		HTREEITEM hTreeItem = this->HitTest(pt, &flags);
		if (hTreeItem != NULL)
		{
			((CClassView*)this->GetParent())->OnSelectItem(hTreeItem);
		}
	}
}

void CViewTree::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if(nChar == VK_F2)
	{
		HTREEITEM item = GetSelectedItem();
		if(item != NULL)
		{
			EditLabel(item);
		}
	}
}
