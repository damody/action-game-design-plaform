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
#include "MainFrm.h"
#include "ClassView.h"
#include "Resource.h"
#include "ADGP Designer.h"
#include <game/FrameInfo.h>


const CString CClassView::anims[MAX_ANIMATIONS] = {
	CString("standing"),
	CString("walking"),
	CString("running"),
	CString("stop_running"),
	CString("heavy_weapon_walk"),
	CString("heavy_weapon_run"),
	CString("light_weapon_stand_attack"),
	CString("light_weapon_jump_attack"),
	CString("light_weapon_run_attack"),
	CString("light_weapon_dash_attack"),
	CString("light_weaponCStringhrow"),
	CString("heavy_weaponCStringhrow"),
	CString("light_weapon_jumpCStringhrow"),
	CString("heavy_weapon_jumpCStringhrow"),
	CString("drink"),
	CString("light_punch"),
	CString("light_kick"),
	CString("heavy_punch"),
	CString("heavy_kick"),
	CString("super_punch"),
	CString("super_kick"),
	CString("jump_punch"),
	CString("jump_kick"),
	CString("run_punch"),
	CString("run_kick"),
	CString("forward_fly_rowing"),
	CString("backward_fly_rowing"),
	CString("forward_rowing"),
	CString("backward_rowing"),
	CString("defend"),
	CString("defend_punch"),
	CString("defend_kick"),
	CString("catching"),
	CString("caught"),
	CString("falling"),
	CString("jump"),
	CString("crouch"),
	CString("injured"),
	CString("forward_lying"),
	CString("backward_lying"),
	CString("unique_skill")
};

class CClassViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CClassView;

	DECLARE_SERIAL(CClassViewMenuButton)

public:
	CClassViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CClassViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// 建構/解構
//////////////////////////////////////////////////////////////////////

CClassView::CClassView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CClassView::~CClassView()
{
}

BEGIN_MESSAGE_MAP(CClassView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ANIMATION_ADD, OnAnimationAdd)
	ON_COMMAND(ID_ANIMATION_DELETE, OnAnimationDelete)
	ON_COMMAND(ID_ANIMATION_RENAME, OnAnimationRename)
	ON_COMMAND(ID_FRAME_ADD, OnFrameAdd)
	ON_COMMAND(ID_FRAME_DELETE, OnFrameDelete)
	ON_COMMAND(ID_FRAME_RENAME, OnFrameRename)
	ON_COMMAND(ID_PROPERTY_VIEW, OnPropertyView)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONUP()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassView 訊息處理常式

int CClassView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 建立檢視:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_EDITLABELS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndClassView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("無法建立 [類別檢視]\n");
		return -1;      // 無法建立
	}

	m_wndClassView.SetOwner(this);

	// 載入影像:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* 已鎖定 */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令都將經由此控制項傳送，而不是經由父框架:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CClassViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}

	// 填入一些靜態樹狀檢視資料 (假程式碼，不需要什麼特別的內容)
	FillClassView();

	return 0;
}

void CClassView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CClassView::FillClassView()
{
	HTREEITEM hRoot = m_wndClassView.InsertItem(_T("人名"), 0, 0);
	m_wndClassView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hClass = m_wndClassView.InsertItem(_T("standing"), 1, 1, hRoot);
	HTREEITEM hClass2 = m_wndClassView.InsertItem(_T("0"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass2);
	hClass2 = m_wndClassView.InsertItem(_T("1"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass2);
	hClass2 = m_wndClassView.InsertItem(_T("2"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass2);
	hClass2 = m_wndClassView.InsertItem(_T("3"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass2);

	hClass = m_wndClassView.InsertItem(_T("walking"), 1, 1, hRoot);
	hClass2 = m_wndClassView.InsertItem(_T("0"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass2);
	hClass2 = m_wndClassView.InsertItem(_T("1"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass2);
	hClass2 = m_wndClassView.InsertItem(_T("2"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass2);
	hClass2 = m_wndClassView.InsertItem(_T("3"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass2);

	hClass = m_wndClassView.InsertItem(_T("jump"), 1, 1, hRoot);
	hClass2 = m_wndClassView.InsertItem(_T("0"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass2);
	hClass2 = m_wndClassView.InsertItem(_T("1"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass2);
	hClass2 = m_wndClassView.InsertItem(_T("2"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass2);
	hClass2 = m_wndClassView.InsertItem(_T("3"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass2);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass2);

	m_wndClassView.Expand(hRoot, TVE_EXPAND);
	m_wndClassView.Expand(hClass, TVE_EXPAND);
	m_wndClassView.Expand(hClass2, TVE_EXPAND);
}

void CClassView::OnLButtonUp(UINT nFlags, CPoint point)
{
	//CDockablePane::OnLButtonDown(nFlags, point);

	AfxMessageBox(_T("Click..."));
}

void CClassView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);

	CMenu menu;

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 選取按下的項目:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
			if(IsAnAnimation(pWndTree, hTreeItem))
			{
				menu.LoadMenu(IDR_POPUP_ANIMATION_EDIT);
			}
			else if(pWndTree->GetRootItem() == hTreeItem)
			{
				menu.LoadMenu(IDR_POPUP_CHARACTER_EDIT);
			}
			else if(IsNumber(pWndTree->GetItemText(hTreeItem)))
			{
				menu.LoadMenu(IDR_POPUP_FRAME_EDIT);
			}
			else
			{
				menu.LoadMenu(IDR_POPUP_OTHER_EDIT);
			}
		}
		else
		{
			menu.LoadMenu(IDR_POPUP_SORT);
		}
	}

	pWndTree->SetFocus();

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CClassView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndClassView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CClassView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CClassView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}
}

void CClassView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CClassView::OnAnimationAdd()
{
	AfxMessageBox(_T("新增成員函式..."));
}

void CClassView::OnAnimationRename()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	if(item!=NULL)
	{
		m_wndClassView.EditLabel(item);
	}
}

void CClassView::OnAnimationDelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
}

void CClassView::OnFrameAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
}

void CClassView::OnFrameDelete()
{

}

void CClassView::OnFrameRename()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	if(item!=NULL)
	{
		m_wndClassView.EditLabel(item);
	}
}

void CClassView::OnPropertyView()
{

}

void CClassView::OnNewFolder()
{
	AfxMessageBox(_T("新增資料夾..."));
}

void CClassView::OnPaint()
{
	CPaintDC dc(this); // 繪製的裝置內容

	CRect rectTree;
	m_wndClassView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CClassView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndClassView.SetFocus();
}

void CClassView::OnChangeVisualStyle()
{
	m_ClassViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("無法載入點陣圖: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ClassViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ClassViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndClassView.SetImageList(&m_ClassViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* 鎖定 */);
}

void CClassView::OnSelectItem(HTREEITEM item)
{
	m_wndClassView.SelectItem(item);
	m_wndClassView.SetFocus();
}

BOOL CClassView::IsAnAnimation(CTreeCtrl* treeCtrl, HTREEITEM item)
{
	CString caption = treeCtrl->GetItemText(item);
	for(unsigned int i=0;i<MAX_ANIMATIONS;i++)
	{
		if(anims[i].Compare(caption) == 0)
			return TRUE;
	}

	return FALSE;
}

BOOL CClassView::IsNumber( CString str )
{
	for(int i=0;i<str.GetLength();i++)
		if(str.GetAt(i) > '9' || str.GetAt(i) < '0')
			return FALSE;

	return TRUE;
}
