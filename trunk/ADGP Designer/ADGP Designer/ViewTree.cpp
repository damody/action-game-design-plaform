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
#include "global.h"
#include "MainFrm.h"

#include <wchar.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
	m_lastSelectedItem = NULL;
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYUP()
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginLabelEdit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndLabelEdit)
	ON_WM_LBUTTONDBLCLK()
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
	*pResult = 1;

	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR); 
	HTREEITEM item = pTVDispInfo->item.hItem;

	//AfxMessageBox(this->GetItemText(item));
	//AfxMessageBox(pTVDispInfo->item.pszText);

	if (pTVDispInfo->item.pszText==LPWSTR())
	{
		return;
	}
	

	CString str(this->GetItemText(item));
	CT2CA pszConvertedAnsiString (str);
	std::string origFrameName(pszConvertedAnsiString);

	str=CString(pTVDispInfo->item.pszText);
	CT2CA pszConvertedAnsiString2 (str);
	std::string newFrameName(pszConvertedAnsiString2);

	if (g_ActiveFramesMap->find(newFrameName)!=g_ActiveFramesMap->end())
	{
		char buff[100];
		sprintf(buff,"Class View: Frame[%s] has existed",newFrameName.c_str());
		str = CString(buff);
		((CMainFrame*)this->GetParent()->GetParentFrame())->AddStrToOutputBuild(str);
		AfxMessageBox(str);
		pTVDispInfo->item.pszText = this->GetItemText(item).AllocSysString();
	}else{
		FramesMap::iterator it = g_ActiveFramesMap->find(origFrameName);
		for (FrameInfos::iterator it_info = it->second.begin(); it_info != it->second.end(); it_info++)
		{
			it_info->m_FrameName = newFrameName;
		}

		(*g_ActiveFramesMap)[newFrameName] = it->second;
		g_ActiveFramesMap->erase(it);

		for (FramesMap::iterator it_map = g_ActiveFramesMap->begin(); it_map != g_ActiveFramesMap->end(); it_map++)
		{
			for (FrameInfos::iterator it_info = it_map->second.begin(); it_info != it_map->second.end(); it_info++)
			{
				if (it_info->m_NextFrameName == origFrameName)
				{
					it_info->m_NextFrameName = newFrameName;
				}

				if (it_info->m_Consume.m_NotEnoughFrameName == origFrameName)
				{
					it_info->m_Consume.m_NotEnoughFrameName == newFrameName;
				}
			}
		}
	}

	this->ModifyStyle(TVS_EDITLABELS, 0);
}

void CViewTree::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if(nChar == VK_F2)
	{
		HTREEITEM item = GetSelectedItem();
		if(item != NULL)
		{
			if(CClassView::IsAnAnimation(this, item))
			{
				this->ModifyStyle(0, TVS_EDITLABELS);
			}
			else if(this->GetRootItem() == item)
			{
				this->ModifyStyle(0, TVS_EDITLABELS);
			}
			EditLabel(item);
		}
	}
	else if(nChar == VK_DELETE)
	{
		HTREEITEM item = GetSelectedItem();
		if(item != NULL)
		{
			if(CClassView::IsAnAnimation(this, item))
			{
				HTREEITEM hNextItem;
				HTREEITEM hChildItem = this->GetChildItem(item);

				while (hChildItem != NULL)
				{
					hNextItem = this->GetNextItem(hChildItem, TVGN_NEXT);
					CClassView::GetInstance()->RemoveTreeItem(hChildItem);
					this->DeleteItem(hChildItem);
					hChildItem = hNextItem;
				}

				this->DeleteItem(item);
			}
			else if(CClassView::IsNumber(this->GetItemText(item)))
			{
				this->DeleteItem(item);
			}
		}
	}
}


void CViewTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{

	CPoint pt = point;
	UINT flags = 0;

	HTREEITEM hTreeItem = this->HitTest(pt, &flags);
	if (hTreeItem != NULL)
	{
		((CClassView*)this->GetParent())->OnSelectItem(hTreeItem);
	}
}
