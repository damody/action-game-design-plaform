// FileTree.cpp : ��@��
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



// CFileTree �T���B�z�`��




void CFileTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	CPoint pt = point;
	UINT flags = 0;

	HTREEITEM hTreeItem = this->HitTest(pt, &flags);
	if (hTreeItem != NULL)
	{
		((CFileView*)this->GetParent())->OnSelectItem(hTreeItem);
	}
	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}
