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

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "ADGP Designer.h"
#include "global.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CMFCPropertyGridPropertyButton, CMFCPropertyGridProperty)

CMFCPropertyGridPropertyButton::CMFCPropertyGridPropertyButton( CMFCPropertyGridCtrl* grid, 
	const CString& strName, const COleVariant& data, LPCTSTR lpszDescr, DWORD_PTR dwData ) 
	: CMFCPropertyGridProperty(strName, data, lpszDescr, dwData)
{
	m_Count = 4;
	m_MotherGrid = grid;
	m_Text = strName;
	AllowEdit(false);
}

void CMFCPropertyGridPropertyButton::OnClickName( CPoint point )
{
	wchar_t tbuffer[10];
	wsprintf(tbuffer, L"Point%d", m_Count++);
	CMFCPropertyGridProperty* pProp1 = new CMFCPropertyGridProperty(tbuffer, 0, TRUE);
	CMFCPropertyGridProperty* pProp;
	this->GetParent()->AddSubItem(pProp1);
	pProp = new CMFCPropertyGridProperty(_T("X"), (_variant_t) 0.f, _T("X��m"));
	pProp1->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Y"), (_variant_t) 0.f, _T("Y��m"));
	pProp1->AddSubItem(pProp);
	m_MotherGrid->AdjustLayout();
}

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd* CPropertiesWnd::instance = NULL;

CPropertiesWnd::CPropertiesWnd()
{
	instance = this;
	m_lastSelectedItem = NULL;
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
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar �T���B�z�`��

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

	// �إߤU�Ԧ����:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("�L�k�إ� [�ݩ�] �U�Ԧ����\n");
		return -1;      // �L�k�إ�
	}

	m_wndObjectCombo.AddString(_T("�ݩʵ���"));
	m_wndObjectCombo.AddString(_T("���[�ݩ�"));
	m_wndObjectCombo.SetCurSel(0);

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("�L�k�إ� [�ݩ�] ���\n");
		return -1;      // �L�k�إ�
	}

	InitPropList();
	InitPropList_Frame();
	InitPropList_Body();
	//m_wndPropList.RemoveAll();
	//InitPropList_Body();
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* �w��w */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* ��w */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// �Ҧ��R�O���N�g�Ѧ�����ǰe�A�Ӥ��O�g�Ѥ��ج[:
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
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: �b���[�J�z���R�O��s UI �B�z�`���{���X
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: �b���[�J�z���R�O��s UI �B�z�`���{���X
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("�~�["));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3D �~�["), (_variant_t) false, _T("���w�������r�����D����A�B����� 3D �ؽu")));

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("�ؽu"), _T("Dialog Frame"), _T("�U�C�䤤�@��: None�BThin�BResizable �� Dialog Frame"));
	pProp->AddOption(_T("None"));
	pProp->AddOption(_T("Thin"));
	pProp->AddOption(_T("Resizable"));
	pProp->AddOption(_T("Dialog Frame"));
	pProp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("���D"), (_variant_t) _T("����"), _T("���w��r�N��ܦb���������D�C")));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("�����j�p"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("����"), (_variant_t) 250l, _T("���w����������"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("�e��"), (_variant_t) 150l, _T("���w�������e��"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("�r��"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	lstrcpy(lf.lfFaceName, _T("Arial, �s�ө���"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("�r��"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("���w�������w�]�r��")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("�ϥΨt�Φr��"), (_variant_t) true, _T("���w�����ϥ� MS Shell Dlg �r��")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("��L"));
	pProp = new CMFCPropertyGridProperty(_T("(�W��)"), _T("���ε{��"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("������m"), RGB(210, 192, 254), NULL, _T("���w�w�]��������m"));
	pColorProp->EnableOtherButton(_T("��L..."));
	pColorProp->EnableAutomaticButton(_T("�w�]"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("�ϥ���(*.ico)|*.ico|�Ҧ��ɮ�(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("�ϥ�"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("���w�����ϥ�")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("��Ƨ�"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("���h"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("�Ĥ@�l�h��"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("�ĤG�l�h��"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("���� 1"), (_variant_t) _T("�� 1"), _T("�o�O�y�z")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("���� 2"), (_variant_t) _T("�� 2"), _T("�o�O�y�z")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("���� 3"), (_variant_t) _T("�� 3"), _T("�o�O�y�z")));

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

	VARIANT varFloat;
	varFloat.vt = VT_R4;
	varFloat.fltVal = 0.0f;

	VARIANT varInt;
	varInt.vt = VT_INT;
	varInt.intVal = 0;

	VARIANT varBool;
	varBool.vt = VT_BOOL;
	varBool.boolVal = false;

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("�D�n�ݩ�"));

	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty(_T("Frame Name"), _T("standing"), _T("��ܳo�� Frame ���W�r"));
	pProp->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp);
	
	pProp = new CMFCPropertyGridProperty(_T("Frame Index"), varInt, _T("��ܦb�o�� Frame �����@��"));
	pProp->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp);
	
	pProp = new CMFCPropertyGridProperty(_T("Next Frame Name"), _T("standing"), _T("��ܸ�����@�� Frame"));
	AddNormalActionDcase(pProp);
	pGroup1->AddSubItem(pProp);
	
	pProp = new CMFCPropertyGridProperty(_T("Next Frame Index"), varInt, _T("��ܸ��� Frame �����@��"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pGroup1->AddSubItem(pProp);
	
	pProp = new CMFCPropertyGridProperty(_T("Hero Action"), _T("STANDING"), _T("��ܰʧ@�����A"));
	AddNormalActionUcase(pProp);
	pProp->AllowEdit(TRUE);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("Wait"), varInt, _T("�o�� Frame �����ơA�@��1/60��"));
	pProp->EnableSpinControl(TRUE, 0, 10000);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("ClearKeyQueue"), varBool, _T("�O�_�n�M�� KeyQueue �����"));
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Picture ID"), varInt, _T("��ܥέ��@�i�ϸ̭��i�H��ܪ��ʧ@"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pGroup1->AddSubItem(pProp);
	
	CMFCPropertyGridProperty* pCenterSize = new CMFCPropertyGridProperty(_T("Center Offset"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("Center X Offset"), varFloat, _T("�H��X��V�����ץ��q"));
	//pProp->EnableSpinControl(TRUE, -1000, 1000);
	pCenterSize->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("Center Y Offset"), varFloat, _T("�H��Y��V�����ץ��q"));
	//pProp->EnableSpinControl(TRUE, -1000, 1000);
	pCenterSize->AddSubItem(pProp);
	pGroup1->AddSubItem(pCenterSize);

	CMFCPropertyGridProperty* pConsumePos = new CMFCPropertyGridProperty(_T("Consume"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("JumpRule"), varBool, _T("False �ɥu��next���ΡATrue �ɥu�� hitdata����"));
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("HP"), varInt, _T("�n���Ӫ� hp"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("MP"), varInt, _T("�n���Ӫ� mp"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pConsumePos->AddSubItem(pProp);
	/*pProp = new CMFCPropertyGridProperty( _T("Enough Frame Name"), _T("standing"), _T("�����Ӫ��ܸ���� Frame"));
	AddNormalActionDcase(pProp);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Enough Frame Index"), (_variant_t) 0l, _T("�����ܸ���Ӯ�"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pConsumePos->AddSubItem(pProp);*/
	pProp = new CMFCPropertyGridProperty( _T("Jump: Frame Name"), _T("standing"), _T("�������Ӫ��ܸ���� Frame"));
	AddNormalActionDcase(pProp);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Jump: Frame Index"), varInt, _T("�������ܸ���Ӯ�"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pConsumePos->AddSubItem(pProp);
	pGroup1->AddSubItem(pConsumePos);

	CMFCPropertyGridProperty* pDirectionVector = new CMFCPropertyGridProperty(_T("Direction Vector"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("DVX"), varFloat, _T("X��V���k�����ʦV�q"));
	pDirectionVector->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("DVY"), varFloat, _T("Y��V���k�����ʦV�q"));
	pDirectionVector->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("DVZ"), varFloat, _T("Z��V���k�����ʦV�q"));
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

	VARIANT varFloat;
	varFloat.vt = VT_R4;
	varFloat.fltVal = 0.0f;

	VARIANT varInt;
	varInt.vt = VT_INT;
	varInt.intVal = 0;

	VARIANT varBool;
	varBool.vt = VT_BOOL;
	varBool.boolVal = false;

	CMFCPropertyGridProperty* m_pBodyGroup = new CMFCPropertyGridProperty(_T("�D�n�ݩ�"));

	CMFCPropertyGridProperty* pProp1;
	CMFCPropertyGridProperty* pProp;
	CMFCPropertyGridProperty* pPolygon2D = new CMFCPropertyGridProperty(_T("Direction Vector"), 0, TRUE);

	pProp = new CMFCPropertyGridPropertyButton(&m_wndPropList, _T("Add Point"),  _T(""), _T("�W�[���I"), 0);
	pPolygon2D->AddSubItem(pProp);

	pProp1 = new CMFCPropertyGridProperty(_T("Point1"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("X"), varFloat, _T("X��m"));
	pProp1->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Y"), varFloat, _T("Y��m"));
	pProp1->AddSubItem(pProp);
	pPolygon2D->AddSubItem(pProp1);
	
	pProp1 = new CMFCPropertyGridProperty(_T("Point2"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("X"), varFloat, _T("X��m"));
	pProp1->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Y"), varFloat, _T("Y��m"));
	pProp1->AddSubItem(pProp);
	pPolygon2D->AddSubItem(pProp1);

	pProp1 = new CMFCPropertyGridProperty(_T("Point3"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("X"), varFloat, _T("X��m"));
	pProp1->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Y"), varFloat, _T("Y��m"));
	pProp1->AddSubItem(pProp);
	pPolygon2D->AddSubItem(pProp1);
	m_pBodyGroup->AddSubItem(pPolygon2D);

	pProp = new CMFCPropertyGridProperty(_T("m_ZWidth"), varFloat, _T("m_ZWidth"));
	m_pBodyGroup->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("m_Kind"), varInt, _T("m_Kind"));
	m_pBodyGroup->AddSubItem(pProp);
	
	m_wndPropList.AddProperty(m_pBodyGroup);
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
	pProp->AddOption(_T("LYING"));
	pProp->AddOption(_T("UNIQUE_SKILL"));
}


void CPropertiesWnd::AddNormalActionDcase( CMFCPropertyGridProperty* pProp )
{

	if (g_ActiveFramesMap != NULL)
	{
		for(FramesMap::iterator it=g_ActiveFramesMap->begin(); it != g_ActiveFramesMap->end() ; it++){
			char buff[100];
			sprintf(buff, "%s",it->first.c_str());
			CString str(buff);
			pProp->AddOption(str);
		}
		
	}
/*
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
	pProp->AddOption(_T("unique_skill"));*/
}

void CPropertiesWnd::AddPointXY( CMFCPropertyGridProperty*& pPolygon2D )
{
	CMFCPropertyGridProperty* pProp1 = new CMFCPropertyGridProperty(_T("Point1"), 0, TRUE);

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("X"), (_variant_t) 0.f, _T("X��m"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pProp1->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Y"), (_variant_t) 0.f, _T("Y��m"));
	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pProp1->AddSubItem(pProp);
	pPolygon2D->AddSubItem(pProp1);
}

CMFCPropertyGridProperty* CPropertiesWnd::GetDefaultPropList()
{
	VARIANT varFloat;
	varFloat.vt = VT_R4;
	varFloat.fltVal = 0.0f;

	VARIANT varInt;
	varInt.vt = VT_INT;
	varInt.intVal = 0;

	VARIANT varBool;
	varBool.vt = VT_BOOL;
	varBool.boolVal = false;

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("�D�n�ݩ�"));

	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty(_T("Frame Name"), _T("standing"), _T("��ܳo�� Frame ���W�r"));
	AddNormalActionDcase(pProp);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Frame Index"), varInt, _T("��ܦb�o�� Frame �����@��"));
	pProp->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Next Frame Name"), _T("standing"), _T("��ܸ�����@�� Frame"));
	AddNormalActionDcase(pProp);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Next Frame Index"), varInt, _T("��ܸ��� Frame �����@��"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Hero Action"), _T("STANDING"), _T("��ܰʧ@�����A"));
	AddNormalActionUcase(pProp);
	pProp->AllowEdit(TRUE);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("Wait"), varInt, _T("�o�� Frame �����ơA�@��1/60��"));
	pProp->EnableSpinControl(TRUE, 0, 10000);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("ClearKeyQueue"), varBool, _T("�O�_�n�M�� KeyQueue �����"));
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Picture ID"), varInt, _T("��ܥέ��@�i�ϸ̭��i�H��ܪ��ʧ@"));
	pProp->EnableSpinControl(TRUE, 0, 300);
	pGroup1->AddSubItem(pProp);

	CMFCPropertyGridProperty* pCenterSize = new CMFCPropertyGridProperty(_T("Center Offset"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("Center X Offset"), varFloat, _T("�H��X��V�����ץ��q"));
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pCenterSize->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("Center Y Offset"), varFloat, _T("�H��Y��V�����ץ��q"));
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pCenterSize->AddSubItem(pProp);
	pGroup1->AddSubItem(pCenterSize);

	CMFCPropertyGridProperty* pPicturePos = new CMFCPropertyGridProperty(_T("Picture Offset"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("Picture X Offset"), varInt, _T("�H���Ϥ�X�����q"));
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pPicturePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("Picture Y Offset"), varInt, _T("�H���Ϥ�Y�����q"));
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pPicturePos->AddSubItem(pProp);
	pGroup1->AddSubItem(pPicturePos);

	CMFCPropertyGridProperty* pConsumePos = new CMFCPropertyGridProperty(_T("Consume"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("JumpRule"), varBool, _T("False �ɥu��next���ΡATrue �ɥu�� hitdata����"));
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("HP"), varInt, _T("�n���Ӫ� hp"));
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty( _T("MP"), varInt, _T("�n���Ӫ� mp"));
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pConsumePos->AddSubItem(pProp);
/*
	pProp = new CMFCPropertyGridProperty( _T("Enough Frame Name"), _T("standing"), _T("�����Ӫ��ܸ���� Frame"));
	AddNormalActionDcase(pProp);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Enough Frame Index"), varInt, _T("�����ܸ���Ӯ�"));
//	pProp->EnableSpinControl(TRUE, 0, 300);
	pConsumePos->AddSubItem(pProp);*/
	pProp = new CMFCPropertyGridProperty( _T("Not Enough Frame Name"), _T("standing"), _T("�������Ӫ��ܸ���� Frame"));
	AddNormalActionDcase(pProp);
	pConsumePos->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Not Next Frame Index"), varInt, _T("�������ܸ���Ӯ�"));
//	pProp->EnableSpinControl(TRUE, 0, 300);
	pConsumePos->AddSubItem(pProp);
	pGroup1->AddSubItem(pConsumePos);

	CMFCPropertyGridProperty* pDirectionVector = new CMFCPropertyGridProperty(_T("Direction Vector"), 0, TRUE);
	pProp = new CMFCPropertyGridProperty(_T("DVX"), varFloat, _T("X��V���k�����ʦV�q"));
	pDirectionVector->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("DVY"), varFloat, _T("Y��V���k�����ʦV�q"));
	pDirectionVector->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("DVZ"), varFloat, _T("Z��V���k�����ʦV�q"));
	pDirectionVector->AddSubItem(pProp);
	pGroup1->AddSubItem(pDirectionVector);

	return pGroup1;
}

LRESULT CPropertiesWnd::OnPropertyChanged( __in WPARAM wparam, __in LPARAM lparam )
{
	return CClassView::GetInstance()->OnPropertyChanged(wparam, lparam, m_lastSelectedItem);
}

BOOL CPropertiesWnd::CanFloat() const
{
	return TRUE;
}

BOOL CPropertiesWnd::CanBeClosed() const
{
	return FALSE;
}

BOOL CPropertiesWnd::CanAutoHide() const
{
	return FALSE;
}

void CPropertiesWnd::SetVSDotNetLook( BOOL bSet )
{
	m_wndPropList.SetVSDotNetLook(bSet);
	m_wndPropList.SetGroupNameFullWidth(bSet);
}

void CPropertiesWnd::RefreshPropList()
{
	InitPropList();
}

void CPropertiesWnd::RefreshPropList_Frame()
{
	InitPropList_Frame();

	VARIANT varFloat;
	varFloat.vt = VT_R4;
	varFloat.fltVal = 0.0f;

	VARIANT varInt;
	varInt.vt = VT_INT;
	varInt.intVal = g_FrameIndex;

	VARIANT varBool;
	varBool.vt = VT_BOOL;
	varBool.boolVal = false;

	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty(0);

	FrameInfo frameInfo = (*g_ActiveFramesMap)[g_FrameName][g_FrameIndex];

	propRoot->GetSubItem(0)->SetValue(CString(g_FrameName.c_str()));
	propRoot->GetSubItem(1)->SetValue(varInt);
	propRoot->GetSubItem(2)->SetValue(CString(frameInfo.m_NextFrameName.c_str()));
	varInt.intVal = frameInfo.m_NextFrameIndex;
	propRoot->GetSubItem(3)->SetValue(varInt);
	propRoot->GetSubItem(4)->SetValue(CString(actionMap[frameInfo.m_HeroAction]));
	varInt.intVal = frameInfo.m_Wait;
	propRoot->GetSubItem(5)->SetValue(varInt);
	varBool.boolVal = frameInfo.m_ClearKeyQueue;
	propRoot->GetSubItem(6)->SetValue(varBool);
	varInt.intVal = frameInfo.m_PictureID;
	propRoot->GetSubItem(7)->SetValue(varInt);
	varFloat.fltVal = frameInfo.m_CenterX;
	propRoot->GetSubItem(8)->GetSubItem(0)->SetValue(varFloat);
	varFloat.fltVal = frameInfo.m_CenterY;
	propRoot->GetSubItem(8)->GetSubItem(1)->SetValue(varFloat);
	varBool.boolVal = frameInfo.m_Consume.m_JumpRule;
	propRoot->GetSubItem(9)->GetSubItem(0)->SetValue(varBool);
	varInt.intVal = frameInfo.m_Consume.m_HP;
	propRoot->GetSubItem(9)->GetSubItem(1)->SetValue(varInt);
	varInt.intVal = frameInfo.m_Consume.m_MP;
	propRoot->GetSubItem(9)->GetSubItem(2)->SetValue(varInt);
	propRoot->GetSubItem(9)->GetSubItem(3)->SetValue(CString(frameInfo.m_Consume.m_NotEnoughFrameName.c_str()));
	varInt.intVal = frameInfo.m_Consume.m_NotEnoughFrame;
	propRoot->GetSubItem(9)->GetSubItem(4)->SetValue(varInt);
	varFloat.fltVal = frameInfo.m_DVX;
	propRoot->GetSubItem(10)->GetSubItem(0)->SetValue(varFloat);
	varFloat.fltVal = frameInfo.m_DVY;
	propRoot->GetSubItem(10)->GetSubItem(1)->SetValue(varFloat);
	varFloat.fltVal = frameInfo.m_DVZ;
	propRoot->GetSubItem(10)->GetSubItem(2)->SetValue(varFloat);

	
}

void CPropertiesWnd::RefreshPropList_Body()
{
	InitPropList_Body();
}

void CPropertiesWnd::RefreshPropList_Attack()
{

}

void CPropertiesWnd::RefreshPropList_CatchInfo()
{

}

void CPropertiesWnd::RefreshPropList_BloodInfo()
{

}

const CString CPropertiesWnd::actionMap[MAX_ACTIONS] = {
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