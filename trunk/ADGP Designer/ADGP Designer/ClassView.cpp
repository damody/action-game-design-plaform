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
#include "Resource.h"
#include "ADGP Designer.h"
#include <comutil.h>

CClassView* CClassView::instance = NULL;

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
	CString("light_weapon_throw"),
	CString("heavy_weapon_throw"),
	CString("light_weapon_jump_throw"),
	CString("heavy_weapon_jump_throw"),
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

const CString CClassView::actionMap[MAX_ACTIONS] = {
	CString("STANDING"),
	CString("WALKING"),
	CString("RUNNING"),
	CString("STOP_RUNNING"),
	CString("HEAVY_WEAPON_WALK"),
	CString("HEAVY_WEAPON_RUN"),
	CString("LIGHT_WEAPON_STAND_ATTACK"),
	CString("LIGHT_WEAPON_JUMP_ATTACK"),
	CString("LIGHT_WEAPON_RUN_ATTACK"),
	CString("LIGHT_WEAPON_DASH_ATTACK"),
	CString("LIGHT_WEAPON_THROW"),
	CString("HEAVY_WEAPON_THROW"),
	CString("LIGHT_WEAPON_JUMP_THROW"),
	CString("HEAVY_WEAPON_JUMP_THROW"),
	CString("DRINK"),
	CString("LIGHT_PUNCH"),
	CString("LIGHT_KICK"),
	CString("HEAVY_PUNCH"),
	CString("HEAVY_KICK"),
	CString("SUPER_PUNCH"),
	CString("SUPER_KICK"),
	CString("JUMP_PUNCH"),
	CString("JUMP_KICK"),
	CString("RUN_PUNCH"),
	CString("RUN_KICK"),
	CString("FORWARD_FLY_ROWING"),
	CString("BACKWARD_FLY_ROWING"),
	CString("FORWARD_ROWING"),
	CString("BACKWARD_ROWING"),
	CString("DEFEND"),
	CString("DEFEND_PUNCH"),
	CString("DEFEND_KICK"),
	CString("CATCHING"),
	CString("CAUGHT"),
	CString("FALLING"),
	CString("JUMP"),
	CString("CROUCH"),
	CString("INJURED"),
	CString("FORWARD_LYING"),
	CString("BACKWARD_LYING"),
	CString("UNIQUE_SKILL")
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

	instance = this;
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
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

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

	/*HTREEITEM hClass = m_wndClassView.InsertItem(_T("standing"), 1, 1, hRoot);
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
	m_wndClassView.Expand(hClass2, TVE_EXPAND);*/
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

	HTREEITEM hTreeItem = NULL;

	if (point != CPoint(-1, -1))
	{
		// 選取按下的項目:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		hTreeItem = pWndTree->HitTest(ptTree, &flags);
	}
	else
	{
		hTreeItem = pWndTree->GetSelectedItem();
	}

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
	HTREEITEM root = m_wndClassView.GetRootItem();
	HTREEITEM item = m_wndClassView.InsertItem(_T("standing"), 1, 1, root);
	FrameInfo fi;
	fi.m_FrameName = std::string("standing");
	fi.m_FrameIndex = 0;
	fi.m_NextFrameName = fi.m_FrameName;
	fi.m_NextFrameIndex = 0;
	fi.m_HeroAction = HeroAction::STANDING;
	fi.m_Wait = 1;
	fi.m_ClearKeyQueue = false;
	fi.m_PictureID = 1;
	fi.m_CenterX = 0.0f;
	fi.m_CenterY = 0.0f;
	fi.m_PictureX = 0;
	fi.m_PictureY = 0;
	fi.m_Consume.m_JumpRule = 0;
	fi.m_Consume.m_HP = 1;
	fi.m_Consume.m_MP = 1;
	fi.m_Consume.m_NotEnoughFrameName = fi.m_FrameName;
	fi.m_Consume.m_NotEnoughFrame = 0;
	fi.m_DVX = 0.0f;
	fi.m_DVY = 0.0f;
	fi.m_DVZ = 0.0f;

	HTREEITEM hClass = m_wndClassView.InsertItem(_T("0"), 3, 3, item);

	m_propMap[hClass] = fi;

	m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass);

	m_wndClassView.Expand(root, TVE_EXPAND);
	m_wndClassView.ModifyStyle(0, TVS_EDITLABELS);
	m_wndClassView.EditLabel(item);
}

void CClassView::OnAnimationRename()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	if(item!=NULL)
	{
		m_wndClassView.ModifyStyle(0, TVS_EDITLABELS);
		m_wndClassView.EditLabel(item);
	}
}

void CClassView::OnAnimationDelete()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	if(item!=NULL)
	{
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = m_wndClassView.GetChildItem(item);

		while (hChildItem != NULL)
		{
			hNextItem = m_wndClassView.GetNextItem(hChildItem, TVGN_NEXT);
			m_propMap.RemoveKey(hChildItem);
			m_wndClassView.DeleteItem(hChildItem);
			hChildItem = hNextItem;
		}

		m_wndClassView.DeleteItem(item);
	}
}

void CClassView::OnFrameAdd()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	
	if(item != NULL)
	{
		CT2CA pszConvertedAnsiString (m_wndClassView.GetItemText(item));
		std::string str2(pszConvertedAnsiString);

		FrameInfo fi;
		fi.m_FrameName = str2;
		fi.m_FrameIndex = 0;
		fi.m_NextFrameName = fi.m_FrameName;
		fi.m_NextFrameIndex = 0;
		fi.m_HeroAction = HeroAction::STANDING;
		fi.m_Wait = 1;
		fi.m_ClearKeyQueue = false;
		fi.m_PictureID = 1;
		fi.m_CenterX = 0.0f;
		fi.m_CenterY = 0.0f;
		fi.m_PictureX = 0;
		fi.m_PictureY = 0;
		fi.m_Consume.m_JumpRule = 0;
		fi.m_Consume.m_HP = 1;
		fi.m_Consume.m_MP = 1;
		fi.m_Consume.m_NotEnoughFrameName = fi.m_FrameName;
		fi.m_Consume.m_NotEnoughFrame = 0;
		fi.m_DVX = 0.0f;
		fi.m_DVY = 0.0f;
		fi.m_DVZ = 0.0f;

		HTREEITEM hClass;
		HTREEITEM tmp_item = m_wndClassView.GetChildItem(item);
		for (int i=0;;++i)
		{
			// need get last node
			if (m_wndClassView.GetNextSiblingItem(tmp_item) != NULL)
			{
				tmp_item = m_wndClassView.GetNextSiblingItem(tmp_item);
				continue;
			}
			TCHAR num_str[10];
			CString item_str = m_wndClassView.GetItemText(tmp_item);
			wsprintf(num_str, _T("%d"), i);
			if (i>298 || num_str == item_str)
			{
				wsprintf(num_str, _T("%d"), i+1);
				hClass = m_wndClassView.InsertItem(num_str, 3, 3, item);
				break;
			}
		}

		m_propMap[hClass] = fi;

		m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass);

		m_wndClassView.Expand(item, TVE_EXPAND);
		m_wndClassView.ModifyStyle(0, TVS_EDITLABELS);
		m_wndClassView.EditLabel(hClass);
	}
}

void CClassView::OnFrameDelete()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	if(item!=NULL)
	{
		m_wndClassView.DeleteItem(item);
	}
}

void CClassView::OnFrameRename()
{
	/*HTREEITEM item = m_wndClassView.GetSelectedItem();
	if(item!=NULL)
	{
		m_wndClassView.ModifyStyle(0, TVS_EDITLABELS);
		m_wndClassView.EditLabel(item);
	}*/
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
	CMFCPropertyGridCtrl* ctrl = CPropertiesWnd::GetInstance()->GetPropList();
	ctrl->RemoveAll();
	ctrl->RedrawWindow();
	((CMainFrame*)(this->GetParentFrame()))->m_wndProperties.RedrawWindow();

	if(IsNumber(m_wndClassView.GetItemText(item)))
	{
		ctrl->AddProperty(CPropertiesWnd::GetInstance()->GetDefaultPropList());

		CMFCPropertyGridProperty* propRoot = ctrl->GetProperty(0);

		VARIANT varFloat;
		varFloat.vt = VT_R4;
		varFloat.fltVal = 0.0f;

		VARIANT varInt;
		varInt.vt = VT_INT;
		varInt.intVal = m_propMap[item].m_FrameIndex;

		VARIANT varBool;
		varBool.vt = VT_BOOL;
		varBool.boolVal = false;

		propRoot->GetSubItem(0)->SetValue(CString(m_propMap[item].m_FrameName.c_str()));
		propRoot->GetSubItem(1)->SetValue(varInt);
		propRoot->GetSubItem(2)->SetValue(CString(m_propMap[item].m_NextFrameName.c_str()));
		varInt.intVal = m_propMap[item].m_NextFrameIndex;
		propRoot->GetSubItem(3)->SetValue(varInt);
		propRoot->GetSubItem(4)->SetValue(CString(actionMap[m_propMap[item].m_HeroAction]));
		varInt.intVal = m_propMap[item].m_Wait;
		propRoot->GetSubItem(5)->SetValue(varInt);
		varBool.boolVal = m_propMap[item].m_ClearKeyQueue;
		propRoot->GetSubItem(6)->SetValue(varBool);
		varInt.intVal = m_propMap[item].m_PictureID;
		propRoot->GetSubItem(7)->SetValue(varInt);
		varFloat.fltVal = m_propMap[item].m_CenterX;
		propRoot->GetSubItem(8)->GetSubItem(0)->SetValue(varFloat);
		varFloat.fltVal = m_propMap[item].m_CenterY;
		propRoot->GetSubItem(8)->GetSubItem(1)->SetValue(varFloat);
		varInt.intVal = m_propMap[item].m_PictureX;
		propRoot->GetSubItem(9)->GetSubItem(0)->SetValue(varInt);
		varInt.intVal = m_propMap[item].m_PictureY;
		propRoot->GetSubItem(9)->GetSubItem(1)->SetValue(varInt);
		varBool.boolVal = m_propMap[item].m_Consume.m_JumpRule;
		propRoot->GetSubItem(10)->GetSubItem(0)->SetValue(varBool);
		varInt.intVal = m_propMap[item].m_Consume.m_HP;
		propRoot->GetSubItem(10)->GetSubItem(1)->SetValue(varInt);
		varInt.intVal = m_propMap[item].m_Consume.m_MP;
		propRoot->GetSubItem(10)->GetSubItem(2)->SetValue(varInt);
		propRoot->GetSubItem(10)->GetSubItem(3)->SetValue(CString(m_propMap[item].m_Consume.m_NotEnoughFrameName.c_str()));
		varInt.intVal = m_propMap[item].m_Consume.m_NotEnoughFrame;
		propRoot->GetSubItem(10)->GetSubItem(4)->SetValue(varInt);
		varFloat.fltVal = m_propMap[item].m_DVX;
		propRoot->GetSubItem(11)->GetSubItem(0)->SetValue(varFloat);
		varFloat.fltVal = m_propMap[item].m_DVY;
		propRoot->GetSubItem(11)->GetSubItem(1)->SetValue(varFloat);
		varFloat.fltVal = m_propMap[item].m_DVZ;
		propRoot->GetSubItem(11)->GetSubItem(2)->SetValue(varFloat);
	}

	CPropertiesWnd::GetInstance()->m_lastSelectedItem = item;
	m_wndClassView.m_lastSelectedItem = item;

	m_wndClassView.SelectItem(item);
	m_wndClassView.SetFocus();
}

BOOL CClassView::IsAnAnimation(CTreeCtrl* treeCtrl, HTREEITEM item)
{
	/*CString caption = treeCtrl->GetItemText(item);
	for(unsigned int i=0;i<MAX_ANIMATIONS;i++)
	{
		if(anims[i].Compare(caption) == 0)
			return TRUE;
	}*/

	return treeCtrl->GetParentItem(item) == treeCtrl->GetRootItem();
}

BOOL CClassView::IsNumber( CString str )
{
	for(int i=0;i<str.GetLength();i++)
		if(str.GetAt(i) > '9' || str.GetAt(i) < '0')
			return FALSE;

	return TRUE;
}

CClassView* CClassView::GetInstance()
{
	return instance;
}

CViewTree* CClassView::GetViewTree()
{
	return &m_wndClassView;
}

LRESULT CClassView::OnPropertyChanged( __in WPARAM wparam, __in LPARAM lparam, HTREEITEM item )
{
	CMFCPropertyGridProperty* prop = (CMFCPropertyGridProperty*)lparam;

	if(item != NULL)
	{
		FrameInfo& fi = m_propMap[item];
		CString caption = prop->GetName();
		COleVariant var = prop->GetValue();

		if(caption.Compare(_T("Frame Name")) == 0)
		{
			fi.m_FrameName = std::string(_com_util::ConvertBSTRToString(var.bstrVal));
		}
		else if(caption.Compare(_T("Frame Index")) == 0)
		{
			fi.m_FrameIndex = var.intVal;
		}
		else if(caption.Compare(_T("Next Frame Name")) == 0)
		{
			fi.m_NextFrameName = std::string(_com_util::ConvertBSTRToString(var.bstrVal));
		}
		else if(caption.Compare(_T("Next Frame Index")) == 0)
		{
			fi.m_NextFrameIndex = var.intVal;
		}
		else if(caption.Compare(_T("Hero Action")) == 0)
		{
			for(int i=0;i<MAX_ACTIONS;i++)
			{
				if(actionMap[i].Compare(var.bstrVal) == 0)
				{
					switch(i)
					{
					case 0:
						fi.m_HeroAction = HeroAction::STANDING;
						break;
					case 1:
						fi.m_HeroAction = HeroAction::WALKING;
						break;
					case 2:
						fi.m_HeroAction = HeroAction::RUNNING;
						break;
					case 3:
						fi.m_HeroAction = HeroAction::STOP_RUNNING;
						break;
					case 4:
						fi.m_HeroAction = HeroAction::HEAVY_WEAPON_WALK;
						break;
					case 5:
						fi.m_HeroAction = HeroAction::HEAVY_WEAPON_RUN;
						break;
					case 6:
						fi.m_HeroAction = HeroAction::LIGHT_WEAPON_STAND_ATTACK;
						break;
					case 7:
						fi.m_HeroAction = HeroAction::LIGHT_WEAPON_JUMP_ATTACK;
						break;
					case 8:
						fi.m_HeroAction = HeroAction::LIGHT_WEAPON_RUN_ATTACK;
						break;
					case 9:
						fi.m_HeroAction = HeroAction::LIGHT_WEAPON_DASH_ATTACK;
						break;
					case 10:
						fi.m_HeroAction = HeroAction::LIGHT_WEAPON_THROW;
						break;
					case 11:
						fi.m_HeroAction = HeroAction::HEAVY_WEAPON_THROW;
						break;
					case 12:
						fi.m_HeroAction = HeroAction::LIGHT_WEAPON_JUMP_THROW;
						break;
					case 13:
						fi.m_HeroAction = HeroAction::HEAVY_WEAPON_JUMP_THROW;
						break;
					case 14:
						fi.m_HeroAction = HeroAction::DRINK;
						break;
					case 15:
						fi.m_HeroAction = HeroAction::LIGHT_PUNCH;
						break;
					case 16:
						fi.m_HeroAction = HeroAction::LIGHT_KICK;
						break;
					case 17:
						fi.m_HeroAction = HeroAction::HEAVY_PUNCH;
						break;
					case 18:
						fi.m_HeroAction = HeroAction::HEAVY_KICK;
						break;
					case 19:
						fi.m_HeroAction = HeroAction::SUPER_PUNCH;
						break;
					case 20:
						fi.m_HeroAction = HeroAction::SUPER_KICK;
						break;
					case 21:
						fi.m_HeroAction = HeroAction::JUMP_PUNCH;
						break;
					case 22:
						fi.m_HeroAction = HeroAction::JUMP_KICK;
						break;
					case 23:
						fi.m_HeroAction = HeroAction::RUN_PUNCH;
						break;
					case 24:
						fi.m_HeroAction = HeroAction::RUN_KICK;
						break;
					case 25:
						fi.m_HeroAction = HeroAction::FORWARD_FLY_ROWING;
						break;
					case 26:
						fi.m_HeroAction = HeroAction::BACKWARD_FLY_ROWING;
						break;
					case 27:
						fi.m_HeroAction = HeroAction::FORWARD_ROWING;
						break;
					case 28:
						fi.m_HeroAction = HeroAction::BACKWARD_ROWING;
						break;
					case 29:
						fi.m_HeroAction = HeroAction::DEFEND;
						break;
					case 30:
						fi.m_HeroAction = HeroAction::DEFEND_PUNCH;
						break;
					case 31:
						fi.m_HeroAction = HeroAction::DEFEND_KICK;
						break;
					case 32:
						fi.m_HeroAction = HeroAction::CATCHING;
						break;
					case 33:
						fi.m_HeroAction = HeroAction::CAUGHT;
						break;
					case 34:
						fi.m_HeroAction = HeroAction::FALLING;
						break;
					case 35:
						fi.m_HeroAction = HeroAction::JUMP;
						break;
					case 36:
						fi.m_HeroAction = HeroAction::CROUCH;
						break;
					case 37:
						fi.m_HeroAction = HeroAction::INJURED;
						break;
					case 38:
						fi.m_HeroAction = HeroAction::FORWARD_LYING;
						break;
					case 39:
						fi.m_HeroAction = HeroAction::BACKWARD_LYING;
						break;
					case 40:
						fi.m_HeroAction = HeroAction::UNIQUE_SKILL;
						break;
					}
					break;
				}
			}
		}
		else if(caption.Compare(_T("Wait")) == 0)
		{
			fi.m_Wait = var.intVal;
		}
		else if(caption.Compare(_T("ClearKeyQueue")) == 0)
		{
			if(var.boolVal == -1)
				fi.m_ClearKeyQueue = true;
			else
				fi.m_ClearKeyQueue = false;
		}
		else if(caption.Compare(_T("Picture ID")) == 0)
		{
			fi.m_PictureID = var.intVal;
		}
		else if(caption.Compare(_T("Center X Offset")) == 0)
		{
			fi.m_CenterX = var.fltVal;
		}
		else if(caption.Compare(_T("Center Y Offset")) == 0)
		{
			fi.m_CenterY = var.fltVal;
		}
		else if(caption.Compare(_T("Picture X Offset")) == 0)
		{
			fi.m_PictureX = var.intVal;
		}
		else if(caption.Compare(_T("Picture Y Offset")) == 0)
		{
			fi.m_PictureY = var.intVal;
		}
		else if(caption.Compare(_T("JumpRule")) == 0)
		{
			fi.m_Consume.m_JumpRule = var.intVal;
		}
		else if(caption.Compare(_T("HP")) == 0)
		{
			fi.m_Consume.m_HP = var.intVal;
		}
		else if(caption.Compare(_T("MP")) == 0)
		{
			fi.m_Consume.m_MP = var.intVal;
		}
		else if(caption.Compare(_T("Not Enough Frame Name")) == 0)
		{
			fi.m_Consume.m_NotEnoughFrameName = std::string(_com_util::ConvertBSTRToString(var.bstrVal));
		}
		else if(caption.Compare(_T("Not Next Frame Index")) == 0)
		{
			fi.m_Consume.m_NotEnoughFrame = var.intVal;
		}
		else if(caption.Compare(_T("DVX")) == 0)
		{
			fi.m_DVX = var.fltVal;
		}
		else if(caption.Compare(_T("DVY")) == 0)
		{
			fi.m_DVY = var.fltVal;
		}
		else if(caption.Compare(_T("DVZ")) == 0)
		{
			fi.m_DVZ = var.fltVal;
		}
	}

	return 0; //Not used
}

CMap<HTREEITEM, HTREEITEM, FrameInfo, FrameInfo>& CClassView::GetPropMap()
{
	return m_propMap;
}

/*
CMFCPropertyGridProperty* CClassView::GetDefaultPropList()
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("主要屬性"));

	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty(_T("Frame Name"), _T("standing"), _T("表示這個 Frame 的名字"));
	AddNormalActionDcase(pProp);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Frame Index"), (_variant_t) 0l, _T("表示在這個 Frame 的哪一格"));
	pProp->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Next Frame Name"), _T("standing"), _T("表示跳到哪一個 Frame"));
	AddNormalActionDcase(pProp);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Next Frame Index"), (_variant_t) 0l, _T("表示跳到 Frame 的哪一格"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Hero Action"), _T("STANDING"), _T("表示動作的狀態"));
	AddNormalActionUcase(pProp);
	pProp->AllowEdit(TRUE);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("Wait"), (_variant_t) 0l, _T("這個 Frame 執行圈數，一圈1/60秒"));
	pProp->EnableSpinControl(TRUE, 0, 10000);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("ClearKeyQueue"), (_variant_t) false, _T("是否要清掉 KeyQueue 的資料"));
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Picture ID"), (_variant_t) 0l, _T("表示用哪一張圖裡面可以顯示的動作"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pGroup1->AddSubItem(pProp);

	CMFCPropertyGridProperty* pCenterSize = new CMFCPropertyGridProperty(_T("Center Offset"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("Center X Offset"), (_variant_t) 0l, _T("人物X方向偏移修正量"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pCenterSize->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("Center Y Offset"), (_variant_t) 0l, _T("人物Y方向偏移修正量"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pCenterSize->AddSubItem(pProp);
	pGroup1->AddSubItem(pCenterSize);

	CMFCPropertyGridProperty* pPicturePos = new CMFCPropertyGridProperty(_T("Picture Offset"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("Picture X Offset"), (_variant_t) 0l, _T("人物圖片X偏移量"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pPicturePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("Picture Y Offset"), (_variant_t) 0l, _T("人物圖片Y偏移量"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pPicturePos->AddSubItem(pProp);
	pGroup1->AddSubItem(pPicturePos);

	CMFCPropertyGridProperty* pConsumePos = new CMFCPropertyGridProperty(_T("Consume"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("JumpRule"), (_variant_t) false, _T("False 時只對next有用，True 時只對 hitdata有用"));
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("HP"), (_variant_t) 0l, _T("要消耗的 hp"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("MP"), (_variant_t) 0l, _T("要消耗的 mp"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("Enough Frame Name"), _T("standing"), _T("夠消耗的話跳到該 Frame"));
	AddNormalActionDcase(pProp);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Enough Frame Index"), (_variant_t) 0l, _T("夠的話跳到該格"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("Not Enough Frame Name"), _T("standing"), _T("不夠消耗的話跳到該 Frame"));
	AddNormalActionDcase(pProp);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Not Next Frame Index"), (_variant_t) 0l, _T("不夠的話跳到該格"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pConsumePos->AddSubItem(pProp);
	pGroup1->AddSubItem(pConsumePos);

	CMFCPropertyGridProperty* pDirectionVector = new CMFCPropertyGridProperty(_T("Direction Vector"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("DVX"), (_variant_t) 0.f, _T("X方向左右的移動向量"));
	pDirectionVector->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("DVY"), (_variant_t) 0.f, _T("Y方向左右的移動向量"));
	pDirectionVector->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("DVZ"), (_variant_t) 0.f, _T("Z方向左右的移動向量"));
	pDirectionVector->AddSubItem(pProp);
	pGroup1->AddSubItem(pDirectionVector);

	return pGroup1;
}*/
