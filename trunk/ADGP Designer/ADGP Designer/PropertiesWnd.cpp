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

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "ADGP Designer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 訊息處理常式

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	m_wndObjectCombo.GetWindowRect(&rectCombo);

	int cyCmb = rectCombo.Size().cy;
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 建立下拉式方塊:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("無法建立 [屬性] 下拉式方塊\n");
		return -1;      // 無法建立
	}

	m_wndObjectCombo.AddString(_T("屬性視窗"));
	m_wndObjectCombo.AddString(_T("附加屬性"));
	m_wndObjectCombo.SetCurSel(0);

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("無法建立 [屬性] 方格\n");
		return -1;      // 無法建立
	}

	InitPropList();
	InitPropList_Frame();
	//InitPropList_Body();
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 已鎖定 */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 鎖定 */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// 所有命令都將經由此控制項傳送，而不是經由父框架:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: 在此加入您的命令處理常式程式碼
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 在此加入您的命令處理常式程式碼
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("外觀"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3D 外觀"), (_variant_t) false, _T("指定視窗的字型為非粗體，且控制項有 3D 框線")));

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("框線"), _T("Dialog Frame"), _T("下列其中一項: None、Thin、Resizable 或 Dialog Frame"));
	pProp->AddOption(_T("None"));
	pProp->AddOption(_T("Thin"));
	pProp->AddOption(_T("Resizable"));
	pProp->AddOption(_T("Dialog Frame"));
	pProp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("標題"), (_variant_t) _T("關於"), _T("指定文字將顯示在視窗的標題列")));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("視窗大小"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("高度"), (_variant_t) 250l, _T("指定視窗的高度"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("寬度"), (_variant_t) 150l, _T("指定視窗的寬度"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("字型"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	lstrcpy(lf.lfFaceName, _T("Arial, 新細明體"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("字型"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("指定視窗的預設字型")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("使用系統字型"), (_variant_t) true, _T("指定視窗使用 MS Shell Dlg 字型")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("其他"));
	pProp = new CMFCPropertyGridProperty(_T("(名稱)"), _T("應用程式"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("視窗色彩"), RGB(210, 192, 254), NULL, _T("指定預設的視窗色彩"));
	pColorProp->EnableOtherButton(_T("其他..."));
	pColorProp->EnableAutomaticButton(_T("預設"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("圖示檔(*.ico)|*.ico|所有檔案(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("圖示"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("指定視窗圖示")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("資料夾"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("階層"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("第一子層級"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("第二子層級"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("項目 1"), (_variant_t) _T("值 1"), _T("這是描述")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("項目 2"), (_variant_t) _T("值 2"), _T("這是描述")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("項目 3"), (_variant_t) _T("值 3"), _T("這是描述")));

	pGroup4->Expand(FALSE);
	m_wndPropList.AddProperty(pGroup4);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}

void CPropertiesWnd::InitPropList_Frame()
{
	m_wndPropList.RemoveAll();
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

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

	m_wndPropList.AddProperty(pGroup1);
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::InitPropList_Body()
{
	m_wndPropList.RemoveAll();
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("主要屬性"));

	CMFCPropertyGridProperty* pProp1;
	CMFCPropertyGridProperty* pProp;
	CMFCPropertyGridProperty* pPolygon2D = new CMFCPropertyGridProperty(_T("Direction Vector"), 0, TRUE);
	pProp1 = new CMFCPropertyGridProperty(_T("Point1"), 0, TRUE);
	
	pProp = new CMFCPropertyGridProperty(_T("X"), (_variant_t) 0.f, _T("X位置"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pProp1->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Y"), (_variant_t) 0.f, _T("Y位置"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pProp1->AddSubItem(pProp);
	pPolygon2D->AddSubItem(pProp1);
	pGroup1->AddSubItem(pPolygon2D);
	m_wndPropList.AddProperty(pGroup1);
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::AddNormalActionUcase( CMFCPropertyGridProperty* pProp )
{
	pProp->AddOption(_T("STANDING"));
	pProp->AddOption(_T("WALKING"));
	pProp->AddOption(_T("RUNNING"));
	pProp->AddOption(_T("STOP_RUNNING"));
	pProp->AddOption(_T("HEAVY_WEAPON_WALK"));
	pProp->AddOption(_T("HEAVY_WEAPON_RUN"));
	pProp->AddOption(_T("LIGHT_WEAPON_STAND_ATTACK"));
	pProp->AddOption(_T("LIGHT_WEAPON_JUMP_ATTACK"));
	pProp->AddOption(_T("LIGHT_WEAPON_RUN_ATTACK"));
	pProp->AddOption(_T("LIGHT_WEAPON_DASH_ATTACK"));
	pProp->AddOption(_T("LIGHT_WEAPON_THROW"));
	pProp->AddOption(_T("HEAVY_WEAPON_THROW"));
	pProp->AddOption(_T("LIGHT_WEAPON_JUMP_THROW"));
	pProp->AddOption(_T("HEAVY_WEAPON_JUMP_THROW"));
	pProp->AddOption(_T("DRINK"));
	pProp->AddOption(_T("LIGHT_PUNCH"));
	pProp->AddOption(_T("LIGHT_KICK"));
	pProp->AddOption(_T("HEAVY_PUNCH"));
	pProp->AddOption(_T("HEAVY_KICK"));
	pProp->AddOption(_T("SUPER_PUNCH"));
	pProp->AddOption(_T("SUPER_KICK"));
	pProp->AddOption(_T("JUMP_PUNCH"));
	pProp->AddOption(_T("JUMP_KICK"));
	pProp->AddOption(_T("RUN_PUNCH"));
	pProp->AddOption(_T("RUN_KICK"));
	pProp->AddOption(_T("FORWARD_FLY_ROWING"));
	pProp->AddOption(_T("BACKWARD_FLY_ROWING"));
	pProp->AddOption(_T("FORWARD_ROWING"));
	pProp->AddOption(_T("BACKWARD_ROWING"));
	pProp->AddOption(_T("DEFEND"));
	pProp->AddOption(_T("DEFEND_PUNCH"));
	pProp->AddOption(_T("DEFEND_KICK"));
	pProp->AddOption(_T("CATCHING"));
	pProp->AddOption(_T("CAUGHT"));
	pProp->AddOption(_T("FALLING"));
	pProp->AddOption(_T("JUMP"));
	pProp->AddOption(_T("CROUCH"));
	pProp->AddOption(_T("INJURED"));
	pProp->AddOption(_T("FORWARD_LYING"));
	pProp->AddOption(_T("BACKWARD_LYING"));
	pProp->AddOption(_T("UNIQUE_SKILL"));
}


void CPropertiesWnd::AddNormalActionDcase( CMFCPropertyGridProperty* pProp )
{
	pProp->AddOption(_T("standing"));
	pProp->AddOption(_T("walking"));
	pProp->AddOption(_T("running"));
	pProp->AddOption(_T("stop_running"));
	pProp->AddOption(_T("heavy_weapon_walk"));
	pProp->AddOption(_T("heavy_weapon_run"));
	pProp->AddOption(_T("light_weapon_stand_attack"));
	pProp->AddOption(_T("light_weapon_jump_attack"));
	pProp->AddOption(_T("light_weapon_run_attack"));
	pProp->AddOption(_T("light_weapon_dash_attack"));
	pProp->AddOption(_T("light_weapon_throw"));
	pProp->AddOption(_T("heavy_weapon_throw"));
	pProp->AddOption(_T("light_weapon_jump_throw"));
	pProp->AddOption(_T("heavy_weapon_jump_throw"));
	pProp->AddOption(_T("drink"));
	pProp->AddOption(_T("light_punch"));
	pProp->AddOption(_T("light_kick"));
	pProp->AddOption(_T("heavy_punch"));
	pProp->AddOption(_T("heavy_kick"));
	pProp->AddOption(_T("super_punch"));
	pProp->AddOption(_T("super_kick"));
	pProp->AddOption(_T("jump_punch"));
	pProp->AddOption(_T("jump_kick"));
	pProp->AddOption(_T("run_punch"));
	pProp->AddOption(_T("run_kick"));
	pProp->AddOption(_T("forward_fly_rowing"));
	pProp->AddOption(_T("backward_fly_rowing"));
	pProp->AddOption(_T("forward_rowing"));
	pProp->AddOption(_T("backward_rowing"));
	pProp->AddOption(_T("defend"));
	pProp->AddOption(_T("defend_punch"));
	pProp->AddOption(_T("defend_kick"));
	pProp->AddOption(_T("catching"));
	pProp->AddOption(_T("caught"));
	pProp->AddOption(_T("falling"));
	pProp->AddOption(_T("jump"));
	pProp->AddOption(_T("crouch"));
	pProp->AddOption(_T("injured"));
	pProp->AddOption(_T("forward_lying"));
	pProp->AddOption(_T("backward_lying"));
	pProp->AddOption(_T("unique_skill"));
}

void CPropertiesWnd::AddPointXY( CMFCPropertyGridProperty*& pPolygon2D )
{
	CMFCPropertyGridProperty* pProp1 = new CMFCPropertyGridProperty(_T("Point1"), 0, TRUE);

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("X"), (_variant_t) 0.f, _T("X位置"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pProp1->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Y"), (_variant_t) 0.f, _T("Y位置"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pProp1->AddSubItem(pProp);
	pPolygon2D->AddSubItem(pProp1);
}
