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
// CViewTree �T���B�z�`��

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
