// FileTree.cpp : 實作檔
//

#include "stdafx.h"
#include "AGDP Designer.h"
#include "FileTree.h"
#include "FileView.h"

// CFileTree

IMPLEMENT_DYNAMIC(CFileTree, CTreeCtrl)

CFileTree::CFileTree()
{

}

CFileTree::~CFileTree()
{
}


BEGIN_MESSAGE_MAP(CFileTree, CTreeCtrl)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CFileTree 訊息處理常式




void CFileTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	CPoint pt = point;
	UINT flags = 0;

	HTREEITEM hTreeItem = this->HitTest(pt, &flags);
	if (hTreeItem != NULL)
	{
		((CFileView*)this->GetParent())->OnSelectItem(hTreeItem);
	}
	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}
