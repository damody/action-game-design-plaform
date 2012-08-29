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
#include "MainFrm.h"
#include "Resource.h"
#include "ADGP Designer.h"
#include <comutil.h>
#include <game/HeroAction.h>
#include "ConvStr.h"
#include "ClassView.h"

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
	CString("before_attack"),
	CString("attacking"),
	CString("after_attack"),
	CString("before_super_attack"),
	CString("super_attacking"),
	CString("after_super_attack"),
	CString("before_jump_attack"),
	CString("jump_attacking"),
	CString("after_jump_attack"),
	CString("before_run_attack"),
	CString("run_attacking"),
	CString("after_run_attack"),
	CString("before_dash_attack"),
	CString("dash_attacking"),
	CString("after_dash_attack"),
	CString("flip"),
	CString("rolling"),
	CString("defend"),
	CString("defend_punch"),
	CString("defend_kick"),
	CString("catching"),
	CString("caught"),
	CString("falling"),
	CString("jump"),
	CString("dash"),
	CString("crouch"),
	CString("injured"),
	CString("forward_lying"),
	CString("backward_lying"),
	CString("in_the_air"),
	CString("before_skill"),
	CString("after_skill"),
	CString("air_skill"),
	CString("x_axis_skill"),
	CString("z_axis_skill"),
	CString("ground_skill"),
	CString("unique_skill"),
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
	CString("BEFORE_ATTACK"),
	CString("ATTACKING"),
	CString("AFTER_ATTACK"),
	CString("BEFORE_SUPER_ATTACK"),
	CString("SUPER_ATTACKING"),
	CString("AFTER_SUPER_ATTACK"),
	CString("BEFORE_JUMP_ATTACK"),
	CString("JUMP_ATTACKING"),
	CString("AFTER_JUMP_ATTACK"),
	CString("BEFORE_RUN_ATTACK"),
	CString("RUN_ATTACKING"),
	CString("AFTER_RUN_ATTACK"),
	CString("BEFORE_DASH_ATTACK"),
	CString("DASH_ATTACKING"),
	CString("AFTER_DASH_ATTACK"),
	CString("FLIP"),
	CString("ROLLING"),
	CString("DEFEND"),
	CString("DEFEND_PUNCH"),
	CString("DEFEND_KICK"),
	CString("CATCHING"),
	CString("CAUGHT"),
	CString("FALLING"),
	CString("JUMP"),
	CString("DASH"),
	CString("CROUCH"),
	CString("INJURED"),
	CString("FORWARD_LYING"),
	CString("BACKWARD_LYING"),
	CString("IN_THE_AIR"),
	CString("BEFORE_SKILL"),
	CString("AFTER_SKILL"),
	CString("AIR_SKILL"),
	CString("X_AXIS_SKILL"),
	CString("Z_AXIS_SKILL"),
	CString("GROUND_SKILL"),
	CString("UNIQUE_SKILL"),
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
// �غc/�Ѻc
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
	ON_COMMAND(ID_PROPERTY_VIEW, OnPropertyView)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONUP()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
	ON_COMMAND(ID_POINT_ADD, &CClassView::OnPointAdd)
	ON_COMMAND(ID_POINT_DELETE, &CClassView::OnPointDelete)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassView �T���B�z�`��

int CClassView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// �إ��˵�:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndClassView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("�L�k�إ� [���O�˵�]\n");
		return -1;      // �L�k�إ�
	}

	m_wndClassView.SetOwner(this);

	// ���J�v��:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* �w��w */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// �Ҧ��R�O���N�g�Ѧ�����ǰe�A�Ӥ��O�g�Ѥ��ج[:
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

	// ��J�@���R�A���˵���� (���{���X�A���ݭn����S�O�����e)
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
	HTREEITEM hRoot = m_wndClassView.InsertItem(_T("�H�W"), 0, 0);
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
	CDockablePane::OnLButtonUp(nFlags, point);

	//AfxMessageBox(_T("Click..."));
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
		// ������U������:
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
		else if(IsNumber(pWndTree->GetItemText(m_wndClassView.GetParentItem(hTreeItem))))
		{
			menu.LoadMenu(IDR_POPUP_POINTS_EDIT);
		}
		else if(1 == 1)
		{
			menu.LoadMenu(IDR_POPUP_POINT_EDIT);
		}
		else
		{
			//menu.LoadMenu(IDR_POPUP_OTHER_EDIT);
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
	HTREEITEM item = m_wndClassView.InsertItem(_T("standing123"), 1, 1, root);
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
	fi.m_Bodys.resize(1);
	fi.m_Bodys[0].m_Area = Polygon2D();
	fi.m_Bodys[0].m_Area.AddPoint(0.0f, 0.0f);
	fi.m_Bodys[0].m_Area.AddPoint(0.0f, 0.0f);
	fi.m_Bodys[0].m_Area.AddPoint(0.0f, 0.0f);
	fi.m_Bodys[0].m_ZWidth = 0.0f;
	fi.m_Bodys[0].m_Kind = 0;

	HTREEITEM hClass = m_wndClassView.InsertItem(_T("0"), 3, 3, item);

	m_propMap[hClass] = fi;



	HTREEITEM temp_item;

	temp_item = m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("0"), 3 , 3, temp_item);
	m_wndClassView.InsertItem(_T("1"), 3 , 3, temp_item);

	temp_item = m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("0"), 3 , 3, temp_item);
	m_wndClassView.InsertItem(_T("1"), 3 , 3, temp_item);

	m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass);

	temp_item = m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("0"), 3 , 3, temp_item);
	m_wndClassView.InsertItem(_T("1"), 3 , 3, temp_item);

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
			RemoveTreeItem(hChildItem);
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
		fi.m_Bodys.resize(1);
		fi.m_Bodys[0].m_Area = Polygon2D();
		fi.m_Bodys[0].m_Area.AddPoint(0.0f, 0.0f);
		fi.m_Bodys[0].m_Area.AddPoint(0.0f, 0.0f);
		fi.m_Bodys[0].m_Area.AddPoint(0.0f, 0.0f);
		fi.m_Bodys[0].m_ZWidth = 0.0f;
		fi.m_Bodys[0].m_Kind = 0;

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

		HTREEITEM temp_item;

		temp_item = m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("0"), 3 , 3, temp_item);
		m_wndClassView.InsertItem(_T("1"), 3 , 3, temp_item);

		temp_item = m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("0"), 3 , 3, temp_item);
		m_wndClassView.InsertItem(_T("1"), 3 , 3, temp_item);

		m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass);

		temp_item = m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("0"), 3 , 3, temp_item);
		m_wndClassView.InsertItem(_T("1"), 3 , 3, temp_item);

		m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass);

		m_wndClassView.Expand(item, TVE_EXPAND);
		//m_wndClassView.ModifyStyle(0, TVS_EDITLABELS);
		//m_wndClassView.EditLabel(hClass);
	}
}

void CClassView::OnFrameDelete()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int count = _ttoi(m_wndClassView.GetItemText(item));
	if(item!=NULL)
	{
		HTREEITEM tmp_item = m_wndClassView.GetNextSiblingItem(item);
		for(int i=count;;i++)
		{
			if(tmp_item != NULL)
			{
				TCHAR num_str[10];
				wsprintf(num_str, _T("%d"), i);
				m_wndClassView.SetItemText(tmp_item, num_str);
				tmp_item = m_wndClassView.GetNextSiblingItem(tmp_item);
			}
			else break;
		}
		m_wndClassView.DeleteItem(item);
	}

}

void CClassView::OnPointAdd()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();
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
			m_wndClassView.InsertItem(num_str, 3, 3, item);
			break;
		}
	}
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
}


void CClassView::OnPointDelete()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int count = _ttoi(m_wndClassView.GetItemText(item));
	if(item!=NULL)
	{
		HTREEITEM tmp_item = m_wndClassView.GetNextSiblingItem(item);
		for(int i=count;;i++)
		{
			if(tmp_item != NULL)
			{
				TCHAR num_str[10];
				wsprintf(num_str, _T("%d"), i);
				m_wndClassView.SetItemText(tmp_item, num_str);
				tmp_item = m_wndClassView.GetNextSiblingItem(tmp_item);
			}
			else break;
		}
		m_wndClassView.DeleteItem(item);
	}
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
}

void CClassView::OnPropertyView()
{

}

void CClassView::OnNewFolder()
{
	AfxMessageBox(_T("�s�W��Ƨ�..."));
}

void CClassView::OnPaint()
{
	CPaintDC dc(this); // ø�s���˸m���e

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
		TRACE(_T("�L�k���J�I�}��: %x\n"), uiBmpId);
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
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* ��w */);
}

void CClassView::OnSelectItem(HTREEITEM item)
{
	/*CMFCPropertyGridCtrl* ctrl = CPropertiesWnd::GetInstance()->GetPropList();
	ctrl->RemoveAll();
	ctrl->RedrawWindow();
	((CMainFrame*)(this->GetParentFrame()))->m_wndProperties.RedrawWindow();

	if(m_wndClassView.GetRootItem() == item)
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

		propRoot->GetSubItem(0)->SetValue(CString(m_propMap[item].m_Name.c_str()));
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
	else if(IsNumber(m_wndClassView.GetItemText(item)))
	{
		CPropertiesWnd* _propWnd = CPropertiesWnd::GetInstance();
		_propWnd->InitPropList_Frame();

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
	else if(!m_wndClassView.GetItemText(item).Compare(CString("Bodys"))){
		HTREEITEM pItem = m_wndClassView.GetParentItem(item);
		CPropertiesWnd* _propWnd = CPropertiesWnd::GetInstance();
		_propWnd->InitPropList_Body();

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

		varFloat.fltVal = m_propMap[pItem].m_Bodys.at(0).m_Area.Points().at(0).x;
		propRoot->GetSubItem(0)->GetSubItem(1)->GetSubItem(0)->SetValue(varFloat);
		varFloat.fltVal = m_propMap[pItem].m_Bodys.at(0).m_Area.Points().at(0).y;
		propRoot->GetSubItem(0)->GetSubItem(1)->GetSubItem(1)->SetValue(varFloat);
		varFloat.fltVal = m_propMap[pItem].m_Bodys.at(0).m_Area.Points().at(1).x;
		propRoot->GetSubItem(0)->GetSubItem(2)->GetSubItem(0)->SetValue(varFloat);
		varFloat.fltVal = m_propMap[pItem].m_Bodys.at(0).m_Area.Points().at(1).y;
		propRoot->GetSubItem(0)->GetSubItem(2)->GetSubItem(1)->SetValue(varFloat);
		varFloat.fltVal = m_propMap[pItem].m_Bodys.at(0).m_Area.Points().at(2).x;
		propRoot->GetSubItem(0)->GetSubItem(3)->GetSubItem(0)->SetValue(varFloat);
		varFloat.fltVal = m_propMap[pItem].m_Bodys.at(0).m_Area.Points().at(2).y;
		propRoot->GetSubItem(0)->GetSubItem(3)->GetSubItem(1)->SetValue(varFloat);
		varFloat.fltVal = m_propMap[pItem].m_Bodys.at(0).m_ZWidth;
		propRoot->GetSubItem(1)->SetValue(varFloat);
		varInt.intVal = m_propMap[pItem].m_Bodys.at(0).m_Kind;
		propRoot->GetSubItem(2)->SetValue(varInt);
	}

	CPropertiesWnd::GetInstance()->m_lastSelectedItem = item;
	m_wndClassView.m_lastSelectedItem = item;*/
	if(m_wndClassView.GetRootItem() == item){
		
		m_wndClassView.SelectItem(item);
		m_wndClassView.SetFocus();
	}else if(IsNumber(m_wndClassView.GetItemText(item))){

		HTREEITEM pItem = m_wndClassView.GetParentItem(item);
		if (pItem != m_wndClassView.GetRootItem())
		{
			CString text = m_wndClassView.GetItemText(pItem);

			if(!text.Compare(CString("Bodys"))){
				HTREEITEM FrameIndex = m_wndClassView.GetParentItem(pItem);
				HTREEITEM Frame	     = m_wndClassView.GetParentItem(FrameIndex);
				char buff[1000];
				ConvStr::WcharToChar(m_wndClassView.GetItemText(Frame).GetBuffer(0),buff);
				std::string FrameName(buff);

				g_FrameName = FrameName;
				g_FrameIndex = _ttoi(m_wndClassView.GetItemText(FrameIndex));
				

				((CMainFrame*)(this->GetParentFrame()))->EditBody(_ttoi(m_wndClassView.GetItemText(item)));

			}else if(!text.Compare(CString("Attacks"))){
				HTREEITEM FrameIndex = m_wndClassView.GetParentItem(pItem);
				HTREEITEM Frame	     = m_wndClassView.GetParentItem(FrameIndex);
				char buff[1000];
				ConvStr::WcharToChar(m_wndClassView.GetItemText(Frame).GetBuffer(0),buff);
				std::string FrameName(buff);

				g_FrameName = FrameName;
				g_FrameIndex = _ttoi(m_wndClassView.GetItemText(FrameIndex));

				((CMainFrame*)(this->GetParentFrame()))->EditAttack(_ttoi(m_wndClassView.GetItemText(item)));

			}else if(!text.Compare(CString("HitDatas"))){

			}else if(!text.Compare(CString("Catchs"))){

			}else if(!text.Compare(CString("BloodInfos"))){

			}else if(!text.Compare(CString("Creations"))){

			}else{
				char buff[1000];
				ConvStr::WcharToChar(text.GetBuffer(0),buff);
				std::string FrameName(buff);
				if(g_ActiveFramesMap->find(FrameName) != g_ActiveFramesMap->end()){
					g_FrameName = FrameName;
					g_FrameIndex = _ttoi(m_wndClassView.GetItemText(item));
					((CMainFrame*)(this->GetParentFrame()))->RefreshFrameEdit();
				}
			}

			m_wndClassView.SelectItem(item);
			m_wndClassView.SetFocus();
		}
	}
	
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
#define SET_ACTION(i, X) case i: fi.m_HeroAction = HeroAction:: X; break;
					switch(i)
					{
					SET_ACTION( 0, STANDING);
					SET_ACTION( 1, STANDING);
					SET_ACTION( 2, WALKING);
					SET_ACTION( 3, RUNNING);
					SET_ACTION( 4, STOP_RUNNING);
					SET_ACTION( 5, HEAVY_WEAPON_WALK);
					SET_ACTION( 6, HEAVY_WEAPON_RUN);
					SET_ACTION( 7, LIGHT_WEAPON_STAND_ATTACK);
					SET_ACTION( 8, LIGHT_WEAPON_JUMP_ATTACK);
					SET_ACTION( 9, LIGHT_WEAPON_RUN_ATTACK);
					SET_ACTION(10, LIGHT_WEAPON_DASH_ATTACK);
					SET_ACTION(11, LIGHT_WEAPON_THROW);
					SET_ACTION(12, HEAVY_WEAPON_THROW);
					SET_ACTION(13, LIGHT_WEAPON_JUMP_THROW);
					SET_ACTION(14, HEAVY_WEAPON_JUMP_THROW);
					SET_ACTION(15, DRINK);
					SET_ACTION(16, BEFORE_ATTACK);
					SET_ACTION(17, ATTACKING);
					SET_ACTION(18, AFTER_ATTACK);
					SET_ACTION(19, BEFORE_SUPER_ATTACK);
					SET_ACTION(20, SUPER_ATTACKING);
					SET_ACTION(21, AFTER_SUPER_ATTACK);
					SET_ACTION(22, BEFORE_JUMP_ATTACK);
					SET_ACTION(23, JUMP_ATTACKING);
					SET_ACTION(24, AFTER_JUMP_ATTACK);
					SET_ACTION(25, BEFORE_RUN_ATTACK);
					SET_ACTION(26, RUN_ATTACKING);
					SET_ACTION(27, AFTER_RUN_ATTACK);
					SET_ACTION(28, BEFORE_DASH_ATTACK);
					SET_ACTION(29, DASH_ATTACKING);
					SET_ACTION(30, AFTER_DASH_ATTACK);
					SET_ACTION(31, FLIP);
					SET_ACTION(32, ROllING);
					SET_ACTION(33, DEFEND);
					SET_ACTION(34, DEFEND_PUNCH);
					SET_ACTION(35, DEFEND_KICK);
					SET_ACTION(36, CATCHING);
					SET_ACTION(37, CAUGHT);
					SET_ACTION(38, FALLING);
					SET_ACTION(39, JUMP);
					SET_ACTION(40, DASH);
					SET_ACTION(41, CROUCH);
					SET_ACTION(42, INJURED);
					SET_ACTION(43, LYING);
					SET_ACTION(44, IN_THE_AIR);
					SET_ACTION(45, BEFORE_SKILL);
					SET_ACTION(46, AFTER_SKILL);
					SET_ACTION(47, AIR_SKILL);
					SET_ACTION(48, X_AXIS_SKILL);
					SET_ACTION(49, Z_AXIS_SKILL);
					SET_ACTION(50, GROUND_SKILL);
					SET_ACTION(51, UNIQUE_SKILL);
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

TreeItemMap& CClassView::GetPropMap()
{
	return m_propMap;
}

void CClassView::RemoveTreeItem( HTREEITEM item )
{
	TreeItemMap::iterator it = m_propMap.find(item);
	if (it != m_propMap.end())
		m_propMap.erase(it);
}


BOOL CClassView::CanFloat() const
{
	return TRUE;
}

BOOL CClassView::CanBeClosed() const
{
	return FALSE;
}

BOOL CClassView::CanAutoHide() const
{
	return FALSE;
}

void CClassView::Refresh()
{
	if(g_HeroInfo != NULL){
		m_wndClassView.DeleteItem(m_wndClassView.GetRootItem());

		char buff[100];
		sprintf(buff, "%s",g_HeroInfo->m_Name.c_str());
		CString str(buff);
		HTREEITEM hRoot = m_wndClassView.InsertItem(str, 0, 0);
		m_wndClassView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

		for (FramesMap::iterator it_FrameMap=g_HeroInfo->m_FramesMap.begin(); it_FrameMap != g_HeroInfo->m_FramesMap.end() ; it_FrameMap++)
		{
			sprintf(buff, "%s", it_FrameMap->first.c_str());
			str = CString(buff);
			HTREEITEM hChild = m_wndClassView.InsertItem(str,1,1,hRoot);

			for (unsigned int i = 0; i < it_FrameMap->second.size() ; i++)
			{
				sprintf(buff,"%d", i);
				str = CString(buff);
				HTREEITEM hChild2 = m_wndClassView.InsertItem(str,3,3,hChild);

				HTREEITEM hChild_Bodys		= m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hChild2);
				HTREEITEM hChild_Attacks	= m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hChild2);
				HTREEITEM hChild_HitDatas	= m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hChild2);
				HTREEITEM hChild_Catchs		= m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hChild2);
				HTREEITEM hChild_BloodInfos	= m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hChild2);
				HTREEITEM hChild_Creations	= m_wndClassView.InsertItem(_T("Creations"), 3, 3, hChild2);

				for (unsigned int j=0; j<it_FrameMap->second[i].m_Bodys.size() ; j++)
				{
					sprintf(buff,"%d", j);
					str = CString(buff);
					m_wndClassView.InsertItem(str,3,3,hChild_Bodys);
				}
				for (unsigned int j=0; j<it_FrameMap->second[i].m_Attacks.size() ; j++)
				{
					sprintf(buff,"%d", j);
					str = CString(buff);
					m_wndClassView.InsertItem(str,3,3,hChild_Attacks);
				}
				for (unsigned int j=0; j<it_FrameMap->second[i].m_HitDatas.size() ; j++)
				{
					sprintf(buff,"%d", j);
					str = CString(buff);
					m_wndClassView.InsertItem(str,3,3,hChild_HitDatas);
				}
				for (unsigned int j=0; j<it_FrameMap->second[i].m_Catchs.size() ; j++)
				{
					sprintf(buff,"%d", j);
					str = CString(buff);
					m_wndClassView.InsertItem(str,3,3,hChild_Catchs);
				}
				for (unsigned int j=0; j<it_FrameMap->second[i].m_BloodInfos.size() ; j++)
				{
					sprintf(buff,"%d", j);
					str = CString(buff);
					m_wndClassView.InsertItem(str,3,3,hChild_BloodInfos);
				}
				for (unsigned int j=0; j<it_FrameMap->second[i].m_Creations.size() ; j++)
				{
					sprintf(buff,"%d", j);
					str = CString(buff);
					m_wndClassView.InsertItem(str,3,3,hChild_Creations);
				}
			}
		}
		
	}
}



/*
CMFCPropertyGridProperty* CClassView::GetDefaultPropList()
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("�D�n�ݩ�"));

	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty(_T("Frame Name"), _T("standing"), _T("��ܳo�� Frame ���W�r"));
	AddNormalActionDcase(pProp);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Frame Index"), (_variant_t) 0l, _T("��ܦb�o�� Frame �����@��"));
	pProp->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Next Frame Name"), _T("standing"), _T("��ܸ�����@�� Frame"));
	AddNormalActionDcase(pProp);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Next Frame Index"), (_variant_t) 0l, _T("��ܸ��� Frame �����@��"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Hero Action"), _T("STANDING"), _T("��ܰʧ@�����A"));
	AddNormalActionUcase(pProp);
	pProp->AllowEdit(TRUE);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("Wait"), (_variant_t) 0l, _T("�o�� Frame �����ơA�@��1/60��"));
	pProp->EnableSpinControl(TRUE, 0, 10000);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("ClearKeyQueue"), (_variant_t) false, _T("�O�_�n�M�� KeyQueue �����"));
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Picture ID"), (_variant_t) 0l, _T("��ܥέ��@�i�ϸ̭��i�H��ܪ��ʧ@"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pGroup1->AddSubItem(pProp);

	CMFCPropertyGridProperty* pCenterSize = new CMFCPropertyGridProperty(_T("Center Offset"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("Center X Offset"), (_variant_t) 0l, _T("�H��X��V�����ץ��q"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pCenterSize->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("Center Y Offset"), (_variant_t) 0l, _T("�H��Y��V�����ץ��q"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pCenterSize->AddSubItem(pProp);
	pGroup1->AddSubItem(pCenterSize);

	CMFCPropertyGridProperty* pPicturePos = new CMFCPropertyGridProperty(_T("Picture Offset"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("Picture X Offset"), (_variant_t) 0l, _T("�H���Ϥ�X�����q"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pPicturePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("Picture Y Offset"), (_variant_t) 0l, _T("�H���Ϥ�Y�����q"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pPicturePos->AddSubItem(pProp);
	pGroup1->AddSubItem(pPicturePos);

	CMFCPropertyGridProperty* pConsumePos = new CMFCPropertyGridProperty(_T("Consume"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("JumpRule"), (_variant_t) false, _T("False �ɥu��next���ΡATrue �ɥu�� hitdata����"));
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("HP"), (_variant_t) 0l, _T("�n���Ӫ� hp"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("MP"), (_variant_t) 0l, _T("�n���Ӫ� mp"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("Enough Frame Name"), _T("standing"), _T("�����Ӫ��ܸ���� Frame"));
	AddNormalActionDcase(pProp);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Enough Frame Index"), (_variant_t) 0l, _T("�����ܸ���Ӯ�"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("Not Enough Frame Name"), _T("standing"), _T("�������Ӫ��ܸ���� Frame"));
	AddNormalActionDcase(pProp);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Not Next Frame Index"), (_variant_t) 0l, _T("�������ܸ���Ӯ�"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pConsumePos->AddSubItem(pProp);
	pGroup1->AddSubItem(pConsumePos);

	CMFCPropertyGridProperty* pDirectionVector = new CMFCPropertyGridProperty(_T("Direction Vector"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("DVX"), (_variant_t) 0.f, _T("X��V���k�����ʦV�q"));
	pDirectionVector->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("DVY"), (_variant_t) 0.f, _T("Y��V���k�����ʦV�q"));
	pDirectionVector->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("DVZ"), (_variant_t) 0.f, _T("Z��V���k�����ʦV�q"));
	pDirectionVector->AddSubItem(pProp);
	pGroup1->AddSubItem(pDirectionVector);

	return pGroup1;
}*/

