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
#include "AGDP Designer.h"
#include "global.h"
#include "ConvStr.h"
#include <functional>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( CMFCPropertyGridPropertyButton, CMFCPropertyGridProperty )

CMFCPropertyGridPropertyButton::CMFCPropertyGridPropertyButton( CMFCPropertyGridCtrl* grid,
                const CString& strName, const COleVariant& data, LPCTSTR lpszDescr, DWORD_PTR dwData )
	: CMFCPropertyGridProperty( strName, data, lpszDescr, dwData )
{
	m_Count = 3;
	m_MotherGrid = grid;
	m_Text = strName;
	AllowEdit( false );
}

void CMFCPropertyGridPropertyButton::OnClickName( CPoint point )
{
	CString _name = this->GetName();

	if ( !_name.Compare( CString( "Add point" ) ) )
	{
		wchar_t tbuffer[10];
		wsprintf( tbuffer, L"%d", m_Count++ );
		CMFCPropertyGridProperty* pProp1 = new CMFCPropertyGridProperty( tbuffer, 0, TRUE );
		CMFCPropertyGridProperty* pProp;
		this->GetParent()->AddSubItem( pProp1 );
		pProp = new CMFCPropertyGridProperty( _T( "X" ), CPropertiesWnd::varFloat( 0.0f ), _T( "X��m" ) );
		pProp1->AddSubItem( pProp );
		pProp = new CMFCPropertyGridProperty( _T( "Y" ), CPropertiesWnd::varFloat( 0.0f ), _T( "Y��m" ) );
		pProp1->AddSubItem( pProp );
		pProp = new CMFCPropertyGridPropertyButton( m_MotherGrid, _T( "Delete point" ), _T( "" ), _T( "Delete point" ), 0 );
		pProp1->AddSubItem( pProp );
		m_MotherGrid->AdjustLayout();
	}
	else if ( !_name.Compare( CString( "Delete point" ) ) )
	{
		CMFCPropertyGridProperty* _tmp = this->GetParent();
		//_tmp = CMFCPropItem(m_MotherGrid, _T("Delete point"), _T(""), _T("Delete point"));
		//_tmp->
		//m_MotherGrid->DeleteProperty(_tmp);
	}
}
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC( CMFCPropItem, CMFCPropertyGridProperty )

BOOL CMFCPropItem::OnEndEdit()
{
	if ( m_Update )
	{
		m_Update = false;

		if ( IsEdited() )
		{
			( ( CPropertiesWnd* )m_MotherGrid->GetParent() )->Update();
			m_Record = m_varValue;
		}
	}

	return CMFCPropertyGridProperty::OnEndEdit();
}

BOOL CMFCPropItem::OnEdit( LPPOINT lptClick )
{
	if ( CMFCPropertyGridProperty::OnEdit( lptClick ) )
	{
		m_Update = true;
		m_Record = this->GetValue();
		return TRUE;
	}
	else { return FALSE; }
}

/*
BOOL CMFCPropItem::DeleteProperty(CMFCPropertyGridProperty*& pProp)
{
	if(pProp != NULL)
	{
		(pProp->GetParent())->DeleteProperty(pProp);
		return TRUE;
	}
	return FALSE;
}*/

bool CMFCPropItem::IsEdited()
{
	const COleVariant& var = m_varValue;
	const COleVariant  var1 = m_Record;

	switch ( m_varValue.vt )
	{
	case VT_BSTR:
	{
		CString str1 = var.bstrVal;
		CString str2 = var1.bstrVal;
		return str1 != str2;
	}
	break;

	case VT_I2:
		return( short )var.iVal != ( short )var1.iVal;

	case VT_I4:
	case VT_INT:
		return( long )var.lVal != ( long )var1.lVal;

	case VT_UI1:
		return( BYTE )var.bVal != ( BYTE )var1.bVal;

	case VT_UI2:
		return var.uiVal != var1.uiVal;

	case VT_UINT:
	case VT_UI4:
		return var.ulVal != var1.ulVal;

	case VT_R4:
		return( float )var.fltVal != ( float )var1.fltVal;

	case VT_R8:
		return( double )var.dblVal != ( double )var1.dblVal;

	case VT_BOOL:
		return( VARIANT_BOOL )var.boolVal != ( VARIANT_BOOL )var1.boolVal;
	}
}

void CMFCPropItem::SetValue( const COleVariant&  varValue )
{
	ASSERT_VALID( this );

	if ( m_varValue.vt != VT_EMPTY && m_varValue.vt != varValue.vt )
	{
		ASSERT( FALSE );
		return;
	}

	BOOL bInPlaceEdit = m_bInPlaceEdit;

	if ( bInPlaceEdit )
	{
		OnEndEdit();
	}

	m_varValue = varValue;
	m_Update = false;
	m_Record = m_varValue;
	Redraw();

	if ( bInPlaceEdit )
	{
		ASSERT_VALID( m_pWndList );
		m_pWndList->EditItem( this );
	}
}
/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd* CPropertiesWnd::instance = NULL;

CPropertiesWnd::CPropertiesWnd(): m_EditProp( 0 ), m_Index( 0 )
{
	instance = this;
	m_lastSelectedItem = NULL;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP( CPropertiesWnd, CDockablePane )
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND( ID_EXPAND_ALL, OnExpandAllProperties )
	ON_UPDATE_COMMAND_UI( ID_EXPAND_ALL, OnUpdateExpandAllProperties )
	ON_COMMAND( ID_SORTPROPERTIES, OnSortProperties )
	ON_UPDATE_COMMAND_UI( ID_SORTPROPERTIES, OnUpdateSortProperties )
	ON_COMMAND( ID_PROPERTIES1, OnProperties1 )
	ON_UPDATE_COMMAND_UI( ID_PROPERTIES1, OnUpdateProperties1 )
	ON_COMMAND( ID_PROPERTIES2, OnProperties2 )
	ON_UPDATE_COMMAND_UI( ID_PROPERTIES2, OnUpdateProperties2 )
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar �T���B�z�`��

void CPropertiesWnd::AdjustLayout()
{
	if ( GetSafeHwnd() == NULL )
	{
		return;
	}

	CRect rectClient, rectCombo;
	GetClientRect( rectClient );
	m_wndObjectCombo.GetWindowRect( &rectCombo );
	int cyCmb = rectCombo.Size().cy;
	int cyTlb = m_wndToolBar.CalcFixedLayout( FALSE, TRUE ).cy;
	m_wndObjectCombo.SetWindowPos( NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER );
	m_wndToolBar.SetWindowPos( NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER );
	m_wndPropList.SetWindowPos( NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() - ( cyCmb + cyTlb ), SWP_NOACTIVATE | SWP_NOZORDER );
}

int CPropertiesWnd::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CDockablePane::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	// �إߤU�Ԧ����:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if ( !m_wndObjectCombo.Create( dwViewStyle, rectDummy, this, 1 ) )
	{
		TRACE0( "�L�k�إ� [�ݩ�] �U�Ԧ����\n" );
		return -1;      // �L�k�إ�
	}

	m_wndObjectCombo.AddString( _T( "�ݩʵ���" ) );
	m_wndObjectCombo.AddString( _T( "���[�ݩ�" ) );
	m_wndObjectCombo.SetCurSel( 0 );

	if ( !m_wndPropList.Create( WS_VISIBLE | WS_CHILD, rectDummy, this, 2 ) )
	{
		TRACE0( "�L�k�إ� [�ݩ�] ���\n" );
		return -1;      // �L�k�إ�
	}

	InitPropList();
	//InitPropList_Frame();
	//InitPropList_Body();
	m_wndPropList.RemoveAll();
	//InitPropList_Body();
	m_wndToolBar.Create( this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES );
	m_wndToolBar.LoadToolBar( IDR_PROPERTIES, 0, 0, TRUE /* �w��w */ );
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap( theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* ��w */ );
	m_wndToolBar.SetPaneStyle( m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY );
	m_wndToolBar.SetPaneStyle( m_wndToolBar.GetPaneStyle() & ~( CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT ) );
	m_wndToolBar.SetOwner( this );
	// �Ҧ��R�O���N�g�Ѧ�����ǰe�A�Ӥ��O�g�Ѥ��ج[:
	m_wndToolBar.SetRouteCommandsViaFrame( FALSE );
	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize( UINT nType, int cx, int cy )
{
	CDockablePane::OnSize( nType, cx, cy );
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties( CCmdUI* /* pCmdUI */ )
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode( !m_wndPropList.IsAlphabeticMode() );
}

void CPropertiesWnd::OnUpdateSortProperties( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck( m_wndPropList.IsAlphabeticMode() );
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
}

void CPropertiesWnd::OnUpdateProperties1( CCmdUI* /*pCmdUI*/ )
{
	// TODO: �b���[�J�z���R�O��s UI �B�z�`���{���X
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
}

void CPropertiesWnd::OnUpdateProperties2( CCmdUI* /*pCmdUI*/ )
{
	// TODO: �b���[�J�z���R�O��s UI �B�z�`���{���X
}

BOOL CPropertiesWnd::CanFloat() const
{
	return FALSE;
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
	m_wndPropList.SetVSDotNetLook( bSet );
	m_wndPropList.SetGroupNameFullWidth( bSet );
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty( _T( "�~�[" ) );
	pGroup1->AddSubItem( new CMFCPropertyGridProperty( _T( "3D �~�[" ), ( _variant_t ) false, _T( "���w�������r�����D����A�B����� 3D �ؽu" ) ) );
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty( _T( "�ؽu" ), _T( "Dialog Frame" ), _T( "�U�C�䤤�@��: None�BThin�BResizable �� Dialog Frame" ) );
	pProp->AddOption( _T( "None" ) );
	pProp->AddOption( _T( "Thin" ) );
	pProp->AddOption( _T( "Resizable" ) );
	pProp->AddOption( _T( "Dialog Frame" ) );
	pProp->AllowEdit( FALSE );
	pGroup1->AddSubItem( pProp );
	pGroup1->AddSubItem( new CMFCPropertyGridProperty( _T( "���D" ), ( _variant_t ) _T( "����" ), _T( "���w��r�N��ܦb���������D�C" ) ) );
	m_wndPropList.AddProperty( pGroup1 );
	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty( _T( "�����j�p" ), 0, TRUE );
	pProp = new CMFCPropertyGridProperty( _T( "����" ), ( _variant_t ) 250l, _T( "���w����������" ) );
	pProp->EnableSpinControl( TRUE, 50, 300 );
	pSize->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "�e��" ), ( _variant_t ) 150l, _T( "���w�������e��" ) );
	pProp->EnableSpinControl( TRUE, 50, 200 );
	pSize->AddSubItem( pProp );
	m_wndPropList.AddProperty( pSize );
	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty( _T( "�r��" ) );
	LOGFONT lf;
	CFont* font = CFont::FromHandle( ( HFONT ) GetStockObject( DEFAULT_GUI_FONT ) );
	font->GetLogFont( &lf );
	lstrcpy( lf.lfFaceName, _T( "Arial, �s�ө���" ) );
	pGroup2->AddSubItem( new CMFCPropertyGridFontProperty( _T( "�r��" ), lf, CF_EFFECTS | CF_SCREENFONTS, _T( "���w�������w�]�r��" ) ) );
	pGroup2->AddSubItem( new CMFCPropertyGridProperty( _T( "�ϥΨt�Φr��" ), ( _variant_t ) true, _T( "���w�����ϥ� MS Shell Dlg �r��" ) ) );
	m_wndPropList.AddProperty( pGroup2 );
	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty( _T( "��L" ) );
	pProp = new CMFCPropertyGridProperty( _T( "(�W��)" ), _T( "���ε{��" ) );
	pProp->Enable( FALSE );
	pGroup3->AddSubItem( pProp );
	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty( _T( "������m" ), RGB( 210, 192, 254 ), NULL, _T( "���w�w�]��������m" ) );
	pColorProp->EnableOtherButton( _T( "��L..." ) );
	pColorProp->EnableAutomaticButton( _T( "�w�]" ), ::GetSysColor( COLOR_3DFACE ) );
	pGroup3->AddSubItem( pColorProp );
	static const TCHAR szFilter[] = _T( "�ϥ���(*.ico)|*.ico|�Ҧ��ɮ�(*.*)|*.*||" );
	pGroup3->AddSubItem( new CMFCPropertyGridFileProperty( _T( "�ϥ�" ), TRUE, _T( "" ), _T( "ico" ), 0, szFilter, _T( "���w�����ϥ�" ) ) );
	pGroup3->AddSubItem( new CMFCPropertyGridFileProperty( _T( "��Ƨ�" ), _T( "c:\\" ) ) );
	m_wndPropList.AddProperty( pGroup3 );
	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty( _T( "���h" ) );
	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty( _T( "�Ĥ@�l�h��" ) );
	pGroup4->AddSubItem( pGroup41 );
	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty( _T( "�ĤG�l�h��" ) );
	pGroup41->AddSubItem( pGroup411 );
	pGroup411->AddSubItem( new CMFCPropertyGridProperty( _T( "���� 1" ), ( _variant_t ) _T( "�� 1" ), _T( "�o�O�y�z" ) ) );
	pGroup411->AddSubItem( new CMFCPropertyGridProperty( _T( "���� 2" ), ( _variant_t ) _T( "�� 2" ), _T( "�o�O�y�z" ) ) );
	pGroup411->AddSubItem( new CMFCPropertyGridProperty( _T( "���� 3" ), ( _variant_t ) _T( "�� 3" ), _T( "�o�O�y�z" ) ) );
	pGroup4->Expand( FALSE );
	m_wndPropList.AddProperty( pGroup4 );
}

void CPropertiesWnd::OnSetFocus( CWnd* pOldWnd )
{
	CDockablePane::OnSetFocus( pOldWnd );
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange( UINT uFlags, LPCTSTR lpszSection )
{
	CDockablePane::OnSettingChange( uFlags, lpszSection );
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject( m_fntPropList.Detach() );
	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont( &lf );
	NONCLIENTMETRICS info;
	info.cbSize = sizeof( info );
	afxGlobalData.GetNonClientMetrics( info );
	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;
	m_fntPropList.CreateFontIndirect( &lf );
	m_wndPropList.SetFont( &m_fntPropList );
	m_wndObjectCombo.SetFont( &m_fntPropList );
}

void CPropertiesWnd::InitPropList_Frame()
{
	m_EditProp = 2;
	m_wndPropList.RemoveAll();
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "�D�n�ݩ�" ) );
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty( _T( "Frame Name" ), _T( "standing" ), _T( "��ܳo�� Frame ���W�r" ) );
	pProp->AllowEdit( FALSE );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Frame Index" ), varInt(), _T( "��ܦb�o�� Frame �����@��" ) );
	pProp->AllowEdit( FALSE );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Next Frame Name" ), _T( "default" ), _T( "��ܸ�����@�� Frame" ) );
	AddNormalActionDcase( pProp );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Next Frame Index" ), varInt(), _T( "��ܸ��� Frame �����@��" ) );
	pProp->EnableSpinControl( TRUE, 0, 300 );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Hero Action" ), _T( "STANDING" ), _T( "��ܰʧ@�����A" ) );
	AddNormalActionUcase( pProp );
	pProp->AllowEdit( TRUE );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Wait" ), varInt(), _T( "�o�� Frame �����ơA�@��1/60��" ) );
	pProp->EnableSpinControl( TRUE, 0, 10000 );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "ClearKeyQueue" ), varBool(), _T( "�O�_�n�M�� KeyQueue �����" ) );
	pPropMain->AddSubItem( pProp );
	CMFCPropertyGridProperty* pPicdate = new CMFCPropertyGridProperty( _T( "Picture" ), 0, TRUE );
	pPicdate->AllowEdit( FALSE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Picture ID" ), varInt(), _T( "��ܥέ��@�i�ϸ̭��i�H��ܪ��ʧ@" ) );
	pProp->EnableSpinControl( TRUE, 0, 300 );
	pPicdate->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Picture X" ), varInt(), _T( "��:��X�Ӥ��ΰ϶�" ) );
	pPicdate->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Picture Y" ), varInt(), _T( "�C:��Y�Ӥ��ΰ϶�" ) );
	pPicdate->AddSubItem( pProp );
	pPropMain->AddSubItem( pPicdate );
	CMFCPropertyGridProperty* pCenterSize = new CMFCPropertyGridProperty( _T( "Center Offset" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Center X Offset" ), varFloat(), _T( "�H��X��V�����ץ��q" ) );
	pCenterSize->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Center Y Offset" ), varFloat(), _T( "�H��Y��V�����ץ��q" ) );
	pCenterSize->AddSubItem( pProp );
	pPropMain->AddSubItem( pCenterSize );
	CMFCPropertyGridProperty* pConsumePos = new CMFCPropertyGridProperty( _T( "Consume" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "JumpRule" ), varBool(), _T( "False �ɥu��next���ΡATrue �ɥu�� hitdata����" ) );
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "HP" ), varInt(), _T( "�n���Ӫ� hp" ) );
	pProp->EnableSpinControl( TRUE, -1000, 1000 );
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "MP" ), varInt(), _T( "�n���Ӫ� mp" ) );
	pProp->EnableSpinControl( TRUE, -1000, 1000 );
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Jump: Frame Name" ), _T( "standing" ), _T( "�������Ӫ��ܸ���� Frame" ) );
	AddNormalActionDcase( pProp );
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Jump: Frame Index" ), varInt(), _T( "�������ܸ���Ӯ�" ) );
	pProp->EnableSpinControl( TRUE, 0, 300 );
	pConsumePos->AddSubItem( pProp );
	pPropMain->AddSubItem( pConsumePos );
	CMFCPropertyGridProperty* pDirectionVector = new CMFCPropertyGridProperty( _T( "Direction Vector" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "DVX" ), varFloat(), _T( "X��V���k�����ʦV�q" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "DVY" ), varFloat(), _T( "Y��V���k�����ʦV�q" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "DVZ" ), varFloat(), _T( "Z��V���k�����ʦV�q" ) );
	pDirectionVector->AddSubItem( pProp );
	pPropMain->AddSubItem( pDirectionVector );
	m_wndPropList.AddProperty( pPropMain );
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::InitPropList_Body( int polygonCount )
{
	m_EditProp = 3;
	m_wndPropList.RemoveAll();
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "�D�n�ݩ�" ) );
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty( _T( "m_Area" ) );
	CMFCPropertyGridProperty* pPropPointGroup;
	CMFCPropertyGridProperty* pPropPoint;

	for ( int i = 0; i < polygonCount; i++ )
	{
		CString s_count; s_count.Format( _T( "%d" ), i );
		pPropPointGroup = new CMFCPropItem( &m_wndPropList, s_count, 0, TRUE );
		pPropPoint = new CMFCPropItem( &m_wndPropList, _T( "X" ), varFloat(), _T( "X��m" ) );
		pPropPointGroup->AddSubItem( pPropPoint );
		pPropPoint = new CMFCPropItem( &m_wndPropList, _T( "Y" ), varFloat(), _T( "Y��m" ) );
		pPropPointGroup->AddSubItem( pPropPoint );
		pProp->AddSubItem( pPropPointGroup );
	}

	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Z Width" ), varFloat(), _T( "�����bZ�b�W���p��" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Kind" ), varInt(), _T( "��������" ) );
	pPropMain->AddSubItem( pProp );
	m_wndPropList.AddProperty( pPropMain );
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::InitPropList_Attack( int polygonCount )
{
	m_EditProp = 4;
	m_wndPropList.RemoveAll();
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "�D�n�ݩ�" ) );
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty( _T( "m_Area" ) );
	CMFCPropertyGridProperty* pPropPointGroup;
	CMFCPropertyGridProperty* pPropPoint;

	for ( int i = 0; i < polygonCount; i++ )
	{
		CString s_count; s_count.Format( _T( "%d" ), i );
		pPropPointGroup = new CMFCPropItem( &m_wndPropList, s_count, 0, TRUE );
		pPropPoint = new CMFCPropItem( &m_wndPropList, _T( "X" ), varFloat(), _T( "X��m" ) );
		pPropPointGroup->AddSubItem( pPropPoint );
		pPropPoint = new CMFCPropItem( &m_wndPropList, _T( "Y" ), varFloat(), _T( "Y��m" ) );
		pPropPointGroup->AddSubItem( pPropPoint );
		pProp->AddSubItem( pPropPointGroup );
	}

	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Kind" ), varInt(), _T( "��������" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Effect" ), varInt(), _T( "�����ĪG" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Z Width" ), varFloat(), _T( "�����bZ�b�W���p��" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Strength" ), varInt(), _T( "�����j��" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Injury" ), varInt(), _T( "�������誺�l��" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Fall" ), varInt(), _T( "�Ϩ������̶^�˼ƭ�" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "BreakDefend" ), varInt(), _T( "�}���ƭ�" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Attack Rest" ), varInt(), _T( "����������w��ɶ�" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "ReAttack Rest" ), varInt(), _T( "��������i�A�Q�P������������ɶ�" ) );
	pPropMain->AddSubItem( pProp );
	CMFCPropertyGridProperty* pDirectionVector = new CMFCPropertyGridProperty( _T( "Direction Vector" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "DVX" ), varFloat(), _T( "��������X��V�����ʦV�q" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "DVY" ), varFloat(), _T( "��������Y��V�����ʦV�q" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "DVZ" ), varFloat(), _T( "��������Z��V�����ʦV�q" ) );
	pDirectionVector->AddSubItem( pProp );
	pPropMain->AddSubItem( pDirectionVector );
	m_wndPropList.AddProperty( pPropMain );
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::InitPropList_HitData()
{
	m_EditProp = 5;
	m_wndPropList.RemoveAll();
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "�D�n�ݩ�" ) );
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_KeyQueue" ), _T( "" ), _T( "m_KeyQueue" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_FrameName" ), _T( "none" ), _T( "m_FrameName" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_FrameOffest" ), varInt(), _T( "m_FrameOffest" ) );
	pPropMain->AddSubItem( pProp );
	m_wndPropList.AddProperty( pPropMain );
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::InitPropList_CatchInfo( int polygonCount )
{
	m_EditProp = 6;
	m_wndPropList.RemoveAll();
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "�D�n�ݩ�" ) );
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty( _T( "Area" ) );
	CMFCPropertyGridProperty* pPropPointGroup;
	CMFCPropertyGridProperty* pPropPoint;

	for ( int i = 0; i < polygonCount; i++ )
	{
		CString s_count; s_count.Format( _T( "%d" ), i );
		pPropPointGroup = new CMFCPropItem( &m_wndPropList, s_count, 0, TRUE );
		pPropPoint = new CMFCPropItem( &m_wndPropList, _T( "X" ), varFloat(), _T( "X��m" ) );
		pPropPointGroup->AddSubItem( pPropPoint );
		pPropPoint = new CMFCPropItem( &m_wndPropList, _T( "Y" ), varFloat(), _T( "Y��m" ) );
		pPropPointGroup->AddSubItem( pPropPoint );
		pProp->AddSubItem( pPropPointGroup );
	}

	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_ZWidth" ), varFloat(), _T( "m_ZWidth" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_Injury" ), varInt(), _T( "m_Injury" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_Kind" ), varInt(), _T( "m_Kind" ) );
	pPropMain->AddSubItem( pProp );
	CMFCPropertyGridProperty* pDirectionVector = new CMFCPropertyGridProperty( _T( "m_CatchPosition" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "X" ), varFloat(), _T( "X" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Y" ), varFloat(), _T( "Y" ) );
	pDirectionVector->AddSubItem( pProp );
	pPropMain->AddSubItem( pDirectionVector );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_CatchWhere" ), _T( "NECK" ), _T( "m_CatchWhere" ) );
	pProp->AddOption( _T( "NECK" ) );
	pProp->AddOption( _T( "LEG" ) );
	pProp->AddOption( _T( "WAIST" ) );
	pProp->AllowEdit( TRUE );
	pPropMain->AddSubItem( pProp );
	m_wndPropList.AddProperty( pPropMain );
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::InitPropList_BloodInfo()
{
	m_EditProp = 7;
	m_wndPropList.RemoveAll();
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "�D�n�ݩ�" ) );
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty( _T( "m_Scale" ), varFloat(), _T( "m_Scale" ) );
	pPropMain->AddSubItem( pProp );
	CMFCPropertyGridProperty* pDirectionVector = new CMFCPropertyGridProperty( _T( "m_Position" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "X" ), varFloat(), _T( "X" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Y" ), varFloat(), _T( "Y" ) );
	pDirectionVector->AddSubItem( pProp );
	pPropMain->AddSubItem( pDirectionVector );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_EnableValue" ), varFloat(), _T( "m_EnableValue" ) );
	pPropMain->AddSubItem( pProp );
	m_wndPropList.AddProperty( pPropMain );
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::InitPropList_Creation()
{
	m_EditProp = 7;
	m_wndPropList.RemoveAll();
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "�D�n�ݩ�" ) );
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Name" ), _T(""), _T( "�гy���W��" ) );
	pPropMain->AddSubItem( pProp );
	for (HeroInfoMap::iterator it = g_HeroInfoMap.begin(); it != g_HeroInfoMap.end(); it++)
	{
		pProp->AddOption( it->second->m_Name.c_str() );
	}
	for (ObjectInfoMap::iterator it = g_ObjectInfoMap.begin(); it != g_ObjectInfoMap.end(); it++)
	{
		pProp->AddOption( it->second->m_Name.c_str() );
	}
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Frame" ), _T(""), _T( "�гy����l�ʧ@" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Frame Index" ), varInt(), _T( "�гy����l�ʧ@�v��" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Amount" ), varInt(), _T( "�гy���ƶq" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Hp" ), varInt(), _T( "�гy����q" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "AI" ), varInt(), _T( "�гy��AI" ) );
	pPropMain->AddSubItem( pProp );
	CMFCPropertyGridProperty* pPosition = new CMFCPropertyGridProperty( _T( "Position" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "X" ), varFloat(), _T( "X" ) );
	pPosition->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Y" ), varFloat(), _T( "Y" ) );
	pPosition->AddSubItem( pProp );
	pPropMain->AddSubItem( pPosition );
	CMFCPropertyGridProperty* pVelocity = new CMFCPropertyGridProperty( _T( "Velocity" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "X" ), varFloat(), _T( "X" ) );
	pVelocity->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Y" ), varFloat(), _T( "Y" ) );
	pVelocity->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Z" ), varFloat(), _T( "Z" ) );
	pVelocity->AddSubItem( pProp );
	pPropMain->AddSubItem( pVelocity );

	m_wndPropList.AddProperty( pPropMain );
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::RefreshPropList_Creation( int index )
{
	if ( m_EditProp != 7 )
	{
		InitPropList_Creation();
		m_EditProp = 7;
	}
	m_Index = index;
	if ( g_ActiveFramesMap->find( g_FrameName ) == g_ActiveFramesMap->end() )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s] does not exist", g_FrameName.c_str() );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}
	else if ( g_FrameIndex < -1 || g_FrameIndex > ( *g_ActiveFramesMap )[g_FrameName].size() - 1 )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s][%d] does not exist", g_FrameName.c_str(), g_FrameIndex );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}
	FrameInfo frameInfo = ( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	
	( ( CMFCPropItem* )propRoot->GetSubItem( 0 ) )->SetValue( CString( frameInfo.m_Creations[index].name.c_str() ) );

	ObjectInfoMap::iterator it_Object = g_ObjectInfoMap.find(frameInfo.m_Creations[index].name);
	if (it_Object != g_ObjectInfoMap.end())
	{
		for ( FramesMap::iterator it = it_Object->second->m_FramesMap.begin(); it != it_Object->second->m_FramesMap.end() ; it++ )
		{
			propRoot->GetSubItem( 1 )->AddOption( it->first.c_str() );
		}
	}
	HeroInfoMap::iterator it_Hero = g_HeroInfoMap.find(frameInfo.m_Creations[index].name);
	if (it_Hero != g_HeroInfoMap.end())
	{
		for ( FramesMap::iterator it = it_Hero->second->m_FramesMap.begin(); it != it_Hero->second->m_FramesMap.end() ; it++ )
		{
			propRoot->GetSubItem( 1 )->AddOption( it->first.c_str() );
		}
	}
	
	( ( CMFCPropItem* )propRoot->GetSubItem( 1 ) )->SetValue( CString( frameInfo.m_Creations[index].frame.c_str()) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->SetValue( varInt(frameInfo.m_Creations[index].frameID) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 3 ) )->SetValue( varInt(frameInfo.m_Creations[index].amount) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 4 ) )->SetValue(varInt(frameInfo.m_Creations[index].HP) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 6 )->GetSubItem( 0 ) )->SetValue( varFloat(frameInfo.m_Creations[index].x) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 6 )->GetSubItem( 1 ) )->SetValue( varFloat(-frameInfo.m_Creations[index].y) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 0 ) )->SetValue( varFloat(frameInfo.m_Creations[index].v0.x) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 1 ) )->SetValue( varFloat(frameInfo.m_Creations[index].v0.y) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 2 ) )->SetValue( varFloat(frameInfo.m_Creations[index].v0.z) );
	
}

void CPropertiesWnd::UpdateCreation()
{

}

void CPropertiesWnd::InitPropList_PictureData()
{
	m_EditProp = 8;
	m_wndPropList.RemoveAll();
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "�D�n�ݩ�" ) );
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty( _T( "Picture ID" ), varInt(), _T( "�Ϥ��s��" ) );
	pProp->AllowEdit( FALSE );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Picture Path" ), _T(" "), _T( "�Ϥ����|" ) );
	pProp->AllowEdit( FALSE );
	pPropMain->AddSubItem( pProp );
	
	CMFCPropertyGridProperty* pRowColumn = new CMFCPropertyGridProperty( _T( "���Φ�C" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "��" ), varInt() , _T( " " ));
	pRowColumn->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "�C" ), varInt() , _T( " " ));
	pRowColumn->AddSubItem( pProp );
	pPropMain->AddSubItem( pRowColumn );

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty( _T( "Size" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "�e" ), varInt(), _T( "�Ϥ��K�X���e��" ) );
	pSize->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "��" ), varInt(), _T( "�Ϥ��K�X������" ) );
	pSize->AddSubItem( pProp );
	pPropMain->AddSubItem( pSize );

	m_wndPropList.AddProperty( pPropMain );
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::InitPropList_Actions()
{
	m_wndPropList.RemoveAll();
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "�ʧ@" ) );
	CMFCPropertyGridProperty* pProp;

	for (LuaMap::iterator it = g_Actions.begin(); it != g_Actions.end(); it++)
	{
		pProp = new CMFCPropertyGridProperty( CString(it->second.c_str()), varInt(it->first), _T( "�ʧ@�νs�X" ) );
		pProp->AllowEdit( FALSE );
		pPropMain->AddSubItem( pProp );
	}

	m_wndPropList.AddProperty( pPropMain );
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::AddNormalActionUcase( CMFCPropertyGridProperty* pProp )
{
	for (LuaMap::iterator it = g_Actions.begin(); it != g_Actions.end(); it++)
	{
		pProp->AddOption( CString( it->second.c_str() ) );
	}
}

void CPropertiesWnd::AddNormalActionDcase( CMFCPropertyGridProperty* pProp )
{
	if ( g_ActiveFramesMap != NULL )
	{
		for ( FramesMap::iterator it = g_ActiveFramesMap->begin(); it != g_ActiveFramesMap->end() ; it++ )
		{
			pProp->AddOption( CString( it->first.c_str() ) );
		}
	}
}

void CPropertiesWnd::AddPointXY( CMFCPropertyGridProperty*& pPolygon2D )
{
	CMFCPropertyGridProperty* pProp1 = new CMFCPropertyGridProperty( _T( "Point1" ), 0, TRUE );
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty( _T( "X" ), ( _variant_t ) 0.f, _T( "X��m" ) );
	pProp->EnableSpinControl( TRUE, -1000, 1000 );
	pProp1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Y" ), ( _variant_t ) 0.f, _T( "Y��m" ) );
	pProp->EnableSpinControl( TRUE, -1000, 1000 );
	pProp1->AddSubItem( pProp );
	pPolygon2D->AddSubItem( pProp1 );
}

CMFCPropertyGridProperty* CPropertiesWnd::GetDefaultPropList()
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty( _T( "�D�n�ݩ�" ) );
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty( _T( "Frame Name" ), _T( "standing" ), _T( "��ܳo�� Frame ���W�r" ) );
	AddNormalActionDcase( pProp );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Frame Index" ), varInt(), _T( "��ܦb�o�� Frame �����@��" ) );
	pProp->AllowEdit( FALSE );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Next Frame Name" ), _T( "standing" ), _T( "��ܸ�����@�� Frame" ), 0 );
	AddNormalActionDcase( pProp );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Next Frame Index" ), varInt(), _T( "��ܸ��� Frame �����@��" ) );
	pProp->EnableSpinControl( TRUE, 0, 300 );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Hero Action" ), _T( "STANDING" ), _T( "��ܰʧ@�����A" ) );
	AddNormalActionUcase( pProp );
	pProp->AllowEdit( TRUE );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Wait" ), varInt(), _T( "�o�� Frame �����ơA�@��1/60��" ) );
	pProp->EnableSpinControl( TRUE, 0, 10000 );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "ClearKeyQueue" ), varBool(), _T( "�O�_�n�M�� KeyQueue �����" ) );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Picture ID" ), varInt(), _T( "��ܥέ��@�i�ϸ̭��i�H��ܪ��ʧ@" ) );
	pProp->EnableSpinControl( TRUE, 0, 300 );
	pGroup1->AddSubItem( pProp );
	CMFCPropertyGridProperty* pCenterSize = new CMFCPropertyGridProperty( _T( "Center Offset" ), 0, TRUE );
	pProp = new CMFCPropertyGridProperty( _T( "Center X Offset" ), varFloat(), _T( "�H��X��V�����ץ��q" ) );
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pCenterSize->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Center Y Offset" ), varFloat(), _T( "�H��Y��V�����ץ��q" ) );
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pCenterSize->AddSubItem( pProp );
	pGroup1->AddSubItem( pCenterSize );
	CMFCPropertyGridProperty* pPicturePos = new CMFCPropertyGridProperty( _T( "Picture Offset" ), 0, TRUE );
	pProp = new CMFCPropertyGridProperty( _T( "Picture X Offset" ), varInt(), _T( "�H���Ϥ�X�����q" ) );
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pPicturePos->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Picture Y Offset" ), varInt(), _T( "�H���Ϥ�Y�����q" ) );
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pPicturePos->AddSubItem( pProp );
	pGroup1->AddSubItem( pPicturePos );
	CMFCPropertyGridProperty* pConsumePos = new CMFCPropertyGridProperty( _T( "Consume" ), 0, TRUE );
	pProp = new CMFCPropertyGridProperty( _T( "JumpRule" ), varBool(), _T( "False �ɥu��next���ΡATrue �ɥu�� hitdata����" ) );
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "HP" ), varInt(), _T( "�n���Ӫ� hp" ) );
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "MP" ), varInt(), _T( "�n���Ӫ� mp" ) );
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Not Enough Frame Name" ), _T( "standing" ), _T( "�������Ӫ��ܸ���� Frame" ) );
	AddNormalActionDcase( pProp );
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Not Next Frame Index" ), varInt(), _T( "�������ܸ���Ӯ�" ) );
//	pProp->EnableSpinControl(TRUE, 0, 300);
	pConsumePos->AddSubItem( pProp );
	pGroup1->AddSubItem( pConsumePos );
	CMFCPropertyGridProperty* pDirectionVector = new CMFCPropertyGridProperty( _T( "Direction Vector" ), 0, TRUE );
	pProp = new CMFCPropertyGridProperty( _T( "DVX" ), varFloat(), _T( "X��V���k�����ʦV�q" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "DVY" ), varFloat(), _T( "Y��V���k�����ʦV�q" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "DVZ" ), varFloat(), _T( "Z��V���k�����ʦV�q" ) );
	pDirectionVector->AddSubItem( pProp );
	pGroup1->AddSubItem( pDirectionVector );
	return pGroup1;
}

void CPropertiesWnd::RefreshPropList()
{
	InitPropList();
	
}

void CPropertiesWnd::RefreshPropList_Frame()
{
	if ( m_EditProp != 2 )
	{
		InitPropList_Frame();
		m_EditProp = 2;
	}

	if ( g_ActiveFramesMap->find( g_FrameName ) == g_ActiveFramesMap->end() )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s] does not exist", g_FrameName.c_str() );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}
	else if ( g_FrameIndex < -1 || g_FrameIndex > ( *g_ActiveFramesMap )[g_FrameName].size() - 1 )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s][%d] does not exist", g_FrameName.c_str(), g_FrameIndex );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}

	FrameInfo frameInfo = ( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	propRoot->GetSubItem( 0 )->SetValue( CString( g_FrameName.c_str() ) );
	propRoot->GetSubItem( 1 )->SetValue( varInt( g_FrameIndex ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->SetValue( CString( frameInfo.m_NextFrameName.c_str() ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 3 ) )->SetValue( varInt( frameInfo.m_NextFrameIndex ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 4 ) )->SetValue( CString( g_Actions[frameInfo.m_HeroAction].c_str() ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 5 ) )->SetValue( varInt( frameInfo.m_Wait ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 6 ) )->SetValue( varBool( frameInfo.m_ClearKeyQueue ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 0 ) )->SetValue( varInt( frameInfo.m_PictureID ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 1 ) )->SetValue( varInt( frameInfo.m_PictureX ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 2 ) )->SetValue( varInt( frameInfo.m_PictureY ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 8 )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo.m_CenterX ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 8 )->GetSubItem( 1 ) )->SetValue( varFloat( frameInfo.m_CenterY ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 0 ) )->SetValue( varBool( frameInfo.m_Consume.m_JumpRule ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 1 ) )->SetValue( varInt( frameInfo.m_Consume.m_HP ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 2 ) )->SetValue( varInt( frameInfo.m_Consume.m_MP ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 3 ) )->SetValue( CString( frameInfo.m_Consume.m_NotEnoughFrameName.c_str() ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 4 ) )->SetValue( varInt( frameInfo.m_Consume.m_NotEnoughFrame ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 10 )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo.m_DVX ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 10 )->GetSubItem( 1 ) )->SetValue( varFloat( frameInfo.m_DVY ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 10 )->GetSubItem( 2 ) )->SetValue( varFloat( frameInfo.m_DVZ ) );
}

void CPropertiesWnd::UpdatePropList_Frame()
{
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	FrameInfo* frameInfo = &( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	CommandLambda* command = new CommandLambda();

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->IsEdited() )
	{
		char buff[1000];
		COleVariant v = propRoot->GetSubItem( 2 )->GetValue();
		v.ChangeType( VT_BSTR, NULL );
		std::wstring FrameName( CString( v ).GetBuffer( 0 ) );

		if ( g_ActiveFramesMap->find( FrameName ) != g_ActiveFramesMap->end() )
		{
			std::wstring OldFrameName = frameInfo->m_NextFrameName;
			command->AddRedoFunction([=](){frameInfo->m_NextFrameName = FrameName;});
			command->AddUndoFunction([=](){frameInfo->m_NextFrameName = OldFrameName;});
			//frameInfo->m_NextFrameName = FrameName;
		}
		else
		{
			char buff[100];
			sprintf( buff, "Properties: Frame[%s] does not exist", FrameName.c_str() );
			CString str( buff );
			AfxMessageBox( str );
			( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 3 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 3 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int i = v.intVal;

		if ( i < ( *g_ActiveFramesMap )[frameInfo->m_NextFrameName].size() && i > -1 )
		{
			int OldFrameIndex = frameInfo->m_NextFrameIndex;
			command->AddRedoFunction([=](){frameInfo->m_NextFrameIndex = i;});
			command->AddUndoFunction([=](){frameInfo->m_NextFrameIndex = OldFrameIndex;});
			//frameInfo->m_NextFrameIndex = i;
		}
		else
		{
			char buff[100];
			sprintf( buff, "Properties: Frame[%s][%d] does not exist", frameInfo->m_NextFrameName.c_str(), i );
			CString str( buff );
			AfxMessageBox( str );
			( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 4 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 4 )->GetValue();
		v.ChangeType( VT_BSTR, NULL );
		std::wstring action( CString( v ).GetBuffer( 0 ) );
		int key = g_Actions.FindKey(action);
		if (key != -1)
		{
			int OldHeroAction = frameInfo->m_HeroAction;
			command->AddRedoFunction([=](){frameInfo->m_HeroAction = key;});
			command->AddUndoFunction([=](){frameInfo->m_HeroAction = OldHeroAction;});
		}else{
			AfxMessageBox(_T("Action does NOT exist"));
		}
		


	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 5 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 5 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int i = v.intVal;

		int OldWait = frameInfo->m_Wait;
		command->AddRedoFunction([=](){frameInfo->m_Wait = i;});
		command->AddUndoFunction([=](){frameInfo->m_Wait = OldWait;});

		//frameInfo->m_Wait = i;
	}

	if ( propRoot->GetSubItem( 6 )->OnEndEdit() )
	{
		COleVariant v = propRoot->GetSubItem( 6 )->GetValue();

		bool OldClearKeyQueue = frameInfo->m_ClearKeyQueue;
		if ( v.boolVal )
		{
			command->AddRedoFunction([=](){frameInfo->m_ClearKeyQueue = true;});
			command->AddUndoFunction([=](){frameInfo->m_ClearKeyQueue = OldClearKeyQueue;});
			//frameInfo->m_ClearKeyQueue = true;
		}
		else
		{
			command->AddRedoFunction([=](){frameInfo->m_ClearKeyQueue = false;});
			command->AddUndoFunction([=](){frameInfo->m_ClearKeyQueue = OldClearKeyQueue;});
			//frameInfo->m_ClearKeyQueue = false;
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 0 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 7 )->GetSubItem( 0 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int i = v.intVal;

		if ( i < g_HeroInfo->m_PictureDatas.size() && i > -1 )
		{
			int OldPictureID = frameInfo->m_PictureID;
			int OldPictureX = frameInfo->m_PictureX;
			int OldPictureY = frameInfo->m_PictureY;
			command->AddRedoFunction([=](){
					frameInfo->m_PictureID = i;
					frameInfo->m_PictureX  = 1;
					frameInfo->m_PictureY  = 1;
					( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 1 ) )->SetValue( varInt( 1 ) );
					( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 2 ) )->SetValue( varInt( 1 ) );
					( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.Refresh();
			});
			command->AddUndoFunction([=](){
				frameInfo->m_PictureID = OldPictureID;
				frameInfo->m_PictureX  = OldPictureX;
				frameInfo->m_PictureY  = OldPictureY;
				( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 1 ) )->SetValue( varInt( OldPictureX ) );
				( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 2 ) )->SetValue( varInt( OldPictureY ) );
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.Refresh();
			});
			/*frameInfo->m_PictureID = i;
			frameInfo->m_PictureX  = 1;
			frameInfo->m_PictureY  = 1;
			( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 1 ) )->SetValue( varInt( 1 ) );
			( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 2 ) )->SetValue( varInt( 1 ) );
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.Refresh();*/
		}
		else
		{
			char buff[100];
			sprintf( buff, "Properties: PictureData[%d] does not exist", i );
			CString str( buff );
			AfxMessageBox( str );
			( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 1 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 7 )->GetSubItem( 1 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int i = v.intVal;

		if ( i <= g_HeroInfo->m_PictureDatas[frameInfo->m_PictureID].m_Row && i > 0 )
		{
			int OldPictureX = frameInfo->m_PictureX;
			command->AddRedoFunction([=](){
				frameInfo->m_PictureX  = i;
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.Refresh();
			});
			command->AddUndoFunction([=](){
				frameInfo->m_PictureX  = OldPictureX;
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.Refresh();
			});
			/*frameInfo->m_PictureX  = i;
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.Refresh();*/
		}
		else
		{
			char buff[100];
			sprintf( buff, "Properties: PictureX Cannot be %d", i );
			CString str( buff );
			AfxMessageBox( str );
			( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 2 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 7 )->GetSubItem( 2 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int i = v.intVal;

		if ( i <= g_HeroInfo->m_PictureDatas[frameInfo->m_PictureID].m_Column && i > 0 )
		{
			int OldPictureY = frameInfo->m_PictureY;
			command->AddRedoFunction([=](){
				frameInfo->m_PictureY  = i;
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.Refresh();
			});
			command->AddUndoFunction([=](){
				frameInfo->m_PictureY  = OldPictureY;
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.Refresh();
			});
			/*frameInfo->m_PictureY  = i;
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.Refresh();*/
		}
		else
		{
			char buff[100];
			sprintf( buff, "Properties: PictureY Cannot be %d", i );
			CString str( buff );
			AfxMessageBox( str );
			( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 8 )->GetSubItem( 0 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 8 )->GetSubItem( 0 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		float i = v.fltVal;
		float OldCenterX = frameInfo->m_CenterX;
		command->AddRedoFunction([=](){
			frameInfo->m_CenterX = i;
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCenter( frameInfo->m_CenterX, frameInfo->m_CenterY );
		});
		command->AddUndoFunction([=](){
			frameInfo->m_CenterX = OldCenterX;
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCenter( frameInfo->m_CenterX, frameInfo->m_CenterY );
		});
		/*frameInfo->m_CenterX = i;
		( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCenter( frameInfo->m_CenterX, frameInfo->m_CenterY );*/
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 8 )->GetSubItem( 1 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 8 )->GetSubItem( 1 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		float i = v.fltVal;
		float OldCenterY = frameInfo->m_CenterY;
		command->AddRedoFunction([=](){
			frameInfo->m_CenterY = i;
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCenter( frameInfo->m_CenterX, frameInfo->m_CenterY );
		});
		command->AddUndoFunction([=](){
			frameInfo->m_CenterY = OldCenterY;
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCenter( frameInfo->m_CenterX, frameInfo->m_CenterY );
		});
		/*frameInfo->m_CenterY = i;
		( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCenter( frameInfo->m_CenterX, frameInfo->m_CenterY );*/
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 0 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 9 )->GetSubItem( 0 )->GetValue();
		v.ChangeType( VT_BOOL, NULL );

		bool OldJumpRule = frameInfo->m_Consume.m_JumpRule;
		if ( v.boolVal )
		{
			command->AddRedoFunction([=](){frameInfo->m_ClearKeyQueue = true;});
			command->AddUndoFunction([=](){frameInfo->m_ClearKeyQueue = OldJumpRule;});
			//frameInfo->m_Consume.m_JumpRule = true;
		}
		else
		{
			command->AddRedoFunction([=](){frameInfo->m_Consume.m_JumpRule = false;});
			command->AddUndoFunction([=](){frameInfo->m_Consume.m_JumpRule = OldJumpRule;});
			//frameInfo->m_Consume.m_JumpRule = false;
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 1 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 9 )->GetSubItem( 1 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int i = v.intVal;
		int OldHP = frameInfo->m_Consume.m_HP;
		command->AddRedoFunction([=](){frameInfo->m_Consume.m_HP = i;});
		command->AddUndoFunction([=](){frameInfo->m_Consume.m_HP = OldHP;});
		//frameInfo->m_Consume.m_HP = i;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 2 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 9 )->GetSubItem( 2 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int i = v.intVal;
		int OldMP = frameInfo->m_Consume.m_MP;
		command->AddRedoFunction([=](){frameInfo->m_Consume.m_MP = i;});
		command->AddUndoFunction([=](){frameInfo->m_Consume.m_MP = OldMP;});
		//frameInfo->m_Consume.m_MP = i;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 3 ) )->IsEdited() )
	{
		char buff[1000];
		COleVariant v = propRoot->GetSubItem( 9 )->GetSubItem( 3 )->GetValue();
		v.ChangeType( VT_BSTR, NULL );
		std::wstring FrameName( CString( v ).GetBuffer( 0 ) );

		if ( g_ActiveFramesMap->find( FrameName ) != g_ActiveFramesMap->end() )
		{
			std::wstring OldFrameName = frameInfo->m_Consume.m_NotEnoughFrameName;
			command->AddRedoFunction([=](){frameInfo->m_Consume.m_NotEnoughFrameName = FrameName;});
			command->AddUndoFunction([=](){frameInfo->m_Consume.m_NotEnoughFrameName = OldFrameName;});
			//frameInfo->m_Consume.m_NotEnoughFrameName = FrameName;
		}
		else
		{
			char buff[100];
			sprintf( buff, "Properties: Frame[%s] does not exist", FrameName.c_str() );
			CString str( buff );
			AfxMessageBox( str );
			( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 4 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 9 )->GetSubItem( 4 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int i = v.intVal;

		if ( i < ( *g_ActiveFramesMap )[frameInfo->m_Consume.m_NotEnoughFrameName].size() && i > -1 )
		{
			int OldFrameIndex = frameInfo->m_Consume.m_NotEnoughFrame;
			command->AddRedoFunction([=](){frameInfo->m_Consume.m_NotEnoughFrame = i;});
			command->AddUndoFunction([=](){frameInfo->m_Consume.m_NotEnoughFrame = OldFrameIndex;});
			//frameInfo->m_Consume.m_NotEnoughFrame = i;
		}
		else
		{
			char buff[100];
			sprintf( buff, "Properties: Frame[%s][%d] does not exist", frameInfo->m_Consume.m_NotEnoughFrameName.c_str(), i );
			CString str( buff );
			AfxMessageBox( str );
			( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 10 )->GetSubItem( 0 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 10 )->GetSubItem( 0 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		float i = v.fltVal;
		float OldDVX = frameInfo->m_DVX;
		command->AddRedoFunction([=](){frameInfo->m_DVX = i;});
		command->AddUndoFunction([=](){frameInfo->m_DVX = OldDVX;});
		//frameInfo->m_DVX = i;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 10 )->GetSubItem( 1 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 10 )->GetSubItem( 1 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		float i = v.fltVal;
		float OldDVY = frameInfo->m_DVY;
		command->AddRedoFunction([=](){frameInfo->m_DVY = i;});
		command->AddUndoFunction([=](){frameInfo->m_DVY = OldDVY;});
		//frameInfo->m_DVY = i;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 2 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 10 )->GetSubItem( 2 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		float i = v.fltVal;
		float OldDVZ = frameInfo->m_DVZ;
		command->AddRedoFunction([=](){frameInfo->m_DVZ = i;});
		command->AddUndoFunction([=](){frameInfo->m_DVZ = OldDVZ;});
		//frameInfo->m_DVZ = i;
	}

	m_CommandManager.CallCommand(command);
}

void CPropertiesWnd::RefreshPropList_Body( int index )
{
	m_EditProp = 3;
	m_Index = index;

	if ( g_ActiveFramesMap->find( g_FrameName ) == g_ActiveFramesMap->end() )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s] does not exist", g_FrameName.c_str() );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}
	else if ( g_FrameIndex < -1 || g_FrameIndex > ( *g_ActiveFramesMap )[g_FrameName].size() - 1 )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s][%d] does not exist", g_FrameName.c_str(), g_FrameIndex );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}

	FrameInfo frameInfo = ( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	InitPropList_Body( frameInfo.m_Bodys[index].m_Area.Points().size() );
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );

	for ( int i = 0; i < frameInfo.m_Bodys[index].m_Area.Points().size(); i++ )
	{
		( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo.m_Bodys[index].m_Area.Points()[i].x() ) );
		( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 ) )->SetValue( varFloat( -frameInfo.m_Bodys[index].m_Area.Points()[i].y() ) );
	}

	( ( CMFCPropItem* )propRoot->GetSubItem( 1 ) )->SetValue( varFloat( frameInfo.m_Bodys[index].m_ZWidth ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->SetValue( varInt( frameInfo.m_Bodys[index].m_Kind ) );
}

void CPropertiesWnd::UpdateBody()
{
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	FrameInfo* frameInfo = &( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	int n = propRoot->GetSubItem( 0 )->GetSubItemsCount();
	CommandLambda* command = new CommandLambda();

	for ( int i = 0 ; i < n ; i++ )
	{
		if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 ) )->IsEdited() )
		{
			COleVariant v = propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 )->GetValue();
			v.ChangeType( VT_R4, NULL );
			float var = v.fltVal;
			float OldX = frameInfo->m_Bodys[m_Index].m_Area.Points()[i].x();
			command->AddRedoFunction([=](){
				frameInfo->m_Bodys[m_Index].m_Area.Points()[i].x( var);
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditBodyPoint( i );
			});
			command->AddUndoFunction([=](){
				frameInfo->m_Bodys[m_Index].m_Area.Points()[i].x( OldX);
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditBodyPoint( i );
			});

			/*frameInfo->m_Bodys[m_Index].m_Area.Points()[i].x( propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 )->GetValue().fltVal);
			//Refresh
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditBodyPoint( i );*/
		}

		if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 ) )->IsEdited() )
		{
			COleVariant v = propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 )->GetValue();
			v.ChangeType( VT_R4, NULL );
			float var = v.fltVal;
			float OldY = frameInfo->m_Bodys[m_Index].m_Area.Points()[i].y();
			command->AddRedoFunction([=](){
				frameInfo->m_Bodys[m_Index].m_Area.Points()[i].y( -var);
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditBodyPoint( i );
			});
			command->AddUndoFunction([=](){
				frameInfo->m_Bodys[m_Index].m_Area.Points()[i].y( OldY);
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditBodyPoint( i );
			});
			/*frameInfo->m_Bodys[m_Index].m_Area.Points()[i].y( -propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 )->GetValue().fltVal);
			//Refresh
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditBodyPoint( i );*/
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 1 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 1 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		float var = v.fltVal;
		float OldZWidth = frameInfo->m_Bodys[m_Index].m_ZWidth;
		command->AddRedoFunction([=](){
			frameInfo->m_Bodys[m_Index].m_ZWidth = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Bodys[m_Index].m_ZWidth = OldZWidth;
		});
		//frameInfo->m_Bodys[m_Index].m_ZWidth = propRoot->GetSubItem( 1 )->GetValue().fltVal;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 2 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;

		int OldKind = frameInfo->m_Bodys[m_Index].m_Kind;
		command->AddRedoFunction([=](){
			frameInfo->m_Bodys[m_Index].m_Kind = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Bodys[m_Index].m_Kind = OldKind;
		});
		//frameInfo->m_Bodys[m_Index].m_Kind = propRoot->GetSubItem( 2 )->GetValue().intVal;
	}

	m_CommandManager.CallCommand(command);
}

void CPropertiesWnd::RefreshPropList_Attack( int index )
{
	m_EditProp = 4;
	m_Index = index;

	if ( g_ActiveFramesMap->find( g_FrameName ) == g_ActiveFramesMap->end() )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s] does not exist", g_FrameName.c_str() );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}
	else if ( g_FrameIndex < -1 || g_FrameIndex > ( *g_ActiveFramesMap )[g_FrameName].size() - 1 )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s][%d] does not exist", g_FrameName.c_str(), g_FrameIndex );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}

	FrameInfo frameInfo = ( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	InitPropList_Attack( frameInfo.m_Attacks[index].m_Area.Points().size() );
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );

	for ( int i = 0; i < frameInfo.m_Attacks[index].m_Area.Points().size(); i++ )
	{
		( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo.m_Attacks[index].m_Area.Points()[i].x() ) );
		( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 ) )->SetValue( varFloat( -frameInfo.m_Attacks[index].m_Area.Points()[i].y() ) );
	}

	( ( CMFCPropItem* )propRoot->GetSubItem( 1 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_Kind ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_Effect ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 3 ) )->SetValue( varFloat( frameInfo.m_Attacks[index].m_ZWidth ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 4 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_Strength ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 5 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_Injury ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 6 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_Fall ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 7 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_BreakDefend ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 8 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_AttackRest ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 6 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_ReAttackRest ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 10 )->GetSubItem ( 0 ) )->SetValue( varFloat( frameInfo.m_Attacks[index].m_DVX ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 10 )->GetSubItem ( 1 ) )->SetValue( varFloat( frameInfo.m_Attacks[index].m_DVY ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 10 )->GetSubItem ( 2 ) )->SetValue( varFloat( frameInfo.m_Attacks[index].m_DVZ ) );
}

void CPropertiesWnd::UpdateAttack()
{
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	FrameInfo* frameInfo = &( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	int n = propRoot->GetSubItem( 0 )->GetSubItemsCount();
	CommandLambda* command = new CommandLambda();

	for ( int i = 0 ; i < n ; i++ )
	{
		if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 ) )->IsEdited() )
		{
			COleVariant v = propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 )->GetValue();
			v.ChangeType( VT_R4, NULL );
			float var = v.fltVal;
			float OldX = frameInfo->m_Attacks[m_Index].m_Area.Points()[i].x();
			command->AddRedoFunction([=](){
				frameInfo->m_Attacks[m_Index].m_Area.Points()[i].x( var);
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditAttackPoint( i );
			});
			command->AddUndoFunction([=](){
				frameInfo->m_Attacks[m_Index].m_Area.Points()[i].x( OldX);
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditAttackPoint( i );
			});

			/*frameInfo->m_Attacks[m_Index].m_Area.Points()[i].x( propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 )->GetValue().fltVal);
			//Refresh
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditAttackPoint( i );*/
		}

		if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 ) )->IsEdited() )
		{
			COleVariant v = propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 )->GetValue();
			v.ChangeType( VT_R4, NULL );
			float var = v.fltVal;
			float OldY = frameInfo->m_Attacks[m_Index].m_Area.Points()[i].y();
			command->AddRedoFunction([=](){
				frameInfo->m_Attacks[m_Index].m_Area.Points()[i].y( -var);
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditAttackPoint( i );
			});
			command->AddUndoFunction([=](){
				frameInfo->m_Attacks[m_Index].m_Area.Points()[i].y( OldY);
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditAttackPoint( i );
			});

			/*frameInfo->m_Attacks[m_Index].m_Area.Points()[i].y( -propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 )->GetValue().fltVal);
			//Refresh
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditAttackPoint( i );*/
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 1 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 1 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;
		int OldKind = frameInfo->m_Attacks[m_Index].m_Kind;
		command->AddRedoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_Kind = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_Kind = OldKind;
		});

		//frameInfo->m_Attacks[m_Index].m_Kind = propRoot->GetSubItem( 1 )->GetValue().intVal;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 2 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;
		int OldEffect = frameInfo->m_Attacks[m_Index].m_Effect;
		command->AddRedoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_Effect = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_Effect = OldEffect;
		});

		//frameInfo->m_Attacks[m_Index].m_Effect = propRoot->GetSubItem( 2 )->GetValue().intVal;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 3 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 3 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		float var = v.fltVal;
		float OldZWidth = frameInfo->m_Attacks[m_Index].m_ZWidth;
		command->AddRedoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_ZWidth = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_ZWidth = OldZWidth;
		});

		//frameInfo->m_Attacks[m_Index].m_ZWidth = propRoot->GetSubItem( 3 )->GetValue().fltVal;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 4 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 4 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;
		int OldStrength = frameInfo->m_Attacks[m_Index].m_Strength;
		command->AddRedoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_Strength = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_Strength = OldStrength;
		});

		//frameInfo->m_Attacks[m_Index].m_Strength = propRoot->GetSubItem( 4 )->GetValue().intVal;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 5 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 5 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;
		int OldInjury = frameInfo->m_Attacks[m_Index].m_Injury;
		command->AddRedoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_Injury = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_Injury = OldInjury;
		});

		//frameInfo->m_Attacks[m_Index].m_Injury = propRoot->GetSubItem( 5 )->GetValue().intVal;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 6 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 6 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;
		int OldFall = frameInfo->m_Attacks[m_Index].m_Fall;
		command->AddRedoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_Fall = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_Fall = OldFall;
		});

		//frameInfo->m_Attacks[m_Index].m_Fall = propRoot->GetSubItem( 6 )->GetValue().intVal;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 7 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 7 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;
		int OldBreakDefend = frameInfo->m_Attacks[m_Index].m_BreakDefend;
		command->AddRedoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_BreakDefend = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_BreakDefend = OldBreakDefend;
		});

		//frameInfo->m_Attacks[m_Index].m_BreakDefend = propRoot->GetSubItem( 7 )->GetValue().intVal;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 8 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 8 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;
		int OldAttackRest = frameInfo->m_Attacks[m_Index].m_AttackRest;
		command->AddRedoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_AttackRest = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_AttackRest = OldAttackRest;
		});

		//frameInfo->m_Attacks[m_Index].m_AttackRest = propRoot->GetSubItem( 8 )->GetValue().intVal;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 9 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 9 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;
		int OldReAttackRest = frameInfo->m_Attacks[m_Index].m_ReAttackRest;
		command->AddRedoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_ReAttackRest = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_ReAttackRest = OldReAttackRest;
		});

		//frameInfo->m_Attacks[m_Index].m_ReAttackRest = propRoot->GetSubItem( 9 )->GetValue().intVal;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 10 )->GetSubItem( 0 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 10 )->GetSubItem( 0 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		float var = v.fltVal;
		float OldDVX = frameInfo->m_Attacks[m_Index].m_DVX;
		command->AddRedoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_DVX = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_DVX = OldDVX;
		});

		//frameInfo->m_Attacks[m_Index].m_DVX = propRoot->GetSubItem( 10 )->GetSubItem( 0 )->GetValue().fltVal;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 10 )->GetSubItem( 1 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 10 )->GetSubItem( 1 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		float var = v.fltVal;
		float OldDVY = frameInfo->m_Attacks[m_Index].m_DVY;
		command->AddRedoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_DVY = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_DVY = OldDVY;
		});

		//frameInfo->m_Attacks[m_Index].m_DVY = propRoot->GetSubItem( 10 )->GetSubItem( 1 )->GetValue().fltVal;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 10 )->GetSubItem( 2 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 10 )->GetSubItem( 2 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		float var = v.fltVal;
		float OldDVZ = frameInfo->m_Attacks[m_Index].m_DVZ;
		command->AddRedoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_DVZ = var;
		});
		command->AddUndoFunction([=](){
			frameInfo->m_Attacks[m_Index].m_DVZ = OldDVZ;
		});

		//frameInfo->m_Attacks[m_Index].m_DVZ = propRoot->GetSubItem( 10 )->GetSubItem( 2 )->GetValue().fltVal;
	}

	m_CommandManager.CallCommand(command);
}

void CPropertiesWnd::RefreshPropList_HitData( int index )
{
	if ( m_EditProp != 5 )
	{
		InitPropList_Body();
		m_EditProp = 5;
	}

	if ( g_ActiveFramesMap->find( g_FrameName ) == g_ActiveFramesMap->end() )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s] does not exist", g_FrameName.c_str() );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}
	else if ( g_FrameIndex < -1 || g_FrameIndex > ( *g_ActiveFramesMap )[g_FrameName].size() - 1 )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s][%d] does not exist", g_FrameName.c_str(), g_FrameIndex );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}

	FrameInfo frameInfo = ( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	CString _tmpstr; _tmpstr = frameInfo.m_HitDatas[index].m_KeyQueue.c_str();
	( ( CMFCPropItem* )propRoot->GetSubItem( 0 ) )->SetValue( _tmpstr );
	_tmpstr = frameInfo.m_HitDatas[index].m_FrameName.c_str();
	( ( CMFCPropItem* )propRoot->GetSubItem( 1 ) )->SetValue( _tmpstr );
	( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->SetValue( varInt( frameInfo.m_HitDatas[index].m_FrameOffset ) );
}

void CPropertiesWnd::RefreshPropList_CatchInfo( int index )
{
	m_EditProp = 6;
	m_Index = index;

	if ( g_ActiveFramesMap->find( g_FrameName ) == g_ActiveFramesMap->end() )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s] does not exist", g_FrameName.c_str() );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}
	else if ( g_FrameIndex < -1 || g_FrameIndex > ( *g_ActiveFramesMap )[g_FrameName].size() - 1 )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s][%d] does not exist", g_FrameName.c_str(), g_FrameIndex );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}

	FrameInfo frameInfo = ( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	InitPropList_CatchInfo( frameInfo.m_Catchs[index].m_Area.Points().size() );
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );

	for ( int i = 0; i < frameInfo.m_Catchs[index].m_Area.Points().size(); i++ )
	{
		( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo.m_Catchs[index].m_Area.Points()[i].x() ) );
		( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 ) )->SetValue( varFloat( -frameInfo.m_Catchs[index].m_Area.Points()[i].y() ) );
	}

	( ( CMFCPropItem* )propRoot->GetSubItem( 1 ) )->SetValue( varFloat( frameInfo.m_Catchs[index].m_ZWidth ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->SetValue( varInt( frameInfo.m_Catchs[index].m_Injury ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 3 ) )->SetValue( varInt( frameInfo.m_Catchs[index].m_Kind ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 4 )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo.m_Catchs[index].m_CatchPosition.x ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 4 )->GetSubItem( 1 ) )->SetValue( varFloat( frameInfo.m_Catchs[index].m_CatchPosition.y ) );

	if ( frameInfo.m_Catchs[index].m_CatchWhere == CatchInfo::CatchPosition::NECK ) { ( ( CMFCPropItem* )propRoot->GetSubItem( 5 ) )->SetValue( _T( "NECK" ) ); }
	else if ( frameInfo.m_Catchs[index].m_CatchWhere == CatchInfo::CatchPosition::LEG ) { ( ( CMFCPropItem* )propRoot->GetSubItem( 5 ) )->SetValue( _T( "LEG" ) ); }
	else { ( ( CMFCPropItem* )propRoot->GetSubItem( 5 ) )->SetValue( _T( "WAIST" ) ); }
}

void CPropertiesWnd::UpdateCatch()
{
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	FrameInfo* frameInfo = &( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	int n = propRoot->GetSubItem( 0 )->GetSubItemsCount();
	CommandLambda* command = new CommandLambda();

	for ( int i = 0 ; i < n ; i++ )
	{
		if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 ) )->IsEdited() )
		{
			COleVariant v = propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 )->GetValue();
			v.ChangeType( VT_R4, NULL );
			float var = v.fltVal;
			float OldX = frameInfo->m_Catchs[m_Index].m_Area.Points()[i].x();
			command->AddRedoFunction([=](){
				frameInfo->m_Catchs[m_Index].m_Area.Points()[i].x( var);
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCatchPoint( i );
			});
			command->AddUndoFunction([=](){
				frameInfo->m_Catchs[m_Index].m_Area.Points()[i].x( OldX);
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCatchPoint( i );
			});

			/*frameInfo->m_Catchs[m_Index].m_Area.Points()[i].x( propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 )->GetValue().fltVal);
			//Refresh
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCatchPoint( i );*/
		}

		if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 ) )->IsEdited() )
		{
			COleVariant v = propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 )->GetValue();
			v.ChangeType( VT_R4, NULL );
			float var = v.fltVal;
			float OldY = frameInfo->m_Catchs[m_Index].m_Area.Points()[i].y();
			command->AddRedoFunction([=](){
				frameInfo->m_Catchs[m_Index].m_Area.Points()[i].y( -var);
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCatchPoint( i );
			});
			command->AddUndoFunction([=](){
				frameInfo->m_Catchs[m_Index].m_Area.Points()[i].y( OldY);
				( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCatchPoint( i );
			});

			/*frameInfo->m_Catchs[m_Index].m_Area.Points()[i].y( -propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 )->GetValue().fltVal);
			//Refresh
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCatchPoint( i );*/
		}
	}

	m_CommandManager.CallCommand(command);
}

void CPropertiesWnd::RefreshPropList_BloodInfo( int index )
{
	if ( m_EditProp != 7 )
	{
		InitPropList_Body();
		m_EditProp = 7;
	}

	if ( g_ActiveFramesMap->find( g_FrameName ) == g_ActiveFramesMap->end() )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s] does not exist", g_FrameName.c_str() );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}
	else if ( g_FrameIndex < -1 || g_FrameIndex > ( *g_ActiveFramesMap )[g_FrameName].size() - 1 )
	{
		char buff[100];
		sprintf( buff, "Properties: Frame[%s][%d] does not exist", g_FrameName.c_str(), g_FrameIndex );
		CString str( buff );
		AfxMessageBox( str );
		( ( CMainFrame* )( this->GetParentFrame() ) )->AddStrToOutputBuild( str );
		return;
	}

	FrameInfo frameInfo = ( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	( ( CMFCPropItem* )propRoot->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo.m_BloodInfos[index].m_Scale ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 1 )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo.m_BloodInfos[index].m_Position.x ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 1 )->GetSubItem( 1 ) )->SetValue( varFloat( frameInfo.m_BloodInfos[index].m_Position.y ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->SetValue( varFloat( frameInfo.m_BloodInfos[index].m_EnableValue ) );
}

void CPropertiesWnd::RefreshPropList_PictureData( int index )
{
	if ( m_EditProp != 8 )
	{
		InitPropList_PictureData();
		m_EditProp = 8;
		m_Index = index;
	}

	if (g_HeroInfo == NULL)
	{
		AfxMessageBox(_T("No Target"));
	}else if (index >= g_HeroInfo->m_PictureDatas.size() || index <0)
	{
		AfxMessageBox(_T("No Picture Data"));
	}

	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );

	propRoot->GetSubItem( 0 ) ->SetValue( varInt( index ) );
	propRoot->GetSubItem( 1 ) ->SetValue( CString(g_HeroInfo->m_PictureDatas[index].m_Path.c_str()) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 2 )->GetSubItem(0) )->SetValue( varInt( g_HeroInfo->m_PictureDatas[index].m_Row ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 2 )->GetSubItem(1) )->SetValue( varInt( g_HeroInfo->m_PictureDatas[index].m_Column ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 3 )->GetSubItem(0) )->SetValue( varInt( g_HeroInfo->m_PictureDatas[index].m_Width ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 3 )->GetSubItem(1) )->SetValue( varInt( g_HeroInfo->m_PictureDatas[index].m_Height ) );

}

void CPropertiesWnd::UpdatePictureData()
{
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	CommandLambda* command = new CommandLambda();

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 2 )->GetSubItem( 0 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 2 )->GetSubItem( 0 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;
		int OldRow = g_HeroInfo->m_PictureDatas[m_Index].m_Row;
		command->AddRedoFunction([=](){
			g_HeroInfo->m_PictureDatas[m_Index].m_Row = var;
			( ( CMainFrame* )( this->GetParentFrame() ) )->UpdatePicture( m_Index );
		});
		command->AddUndoFunction([=](){
			g_HeroInfo->m_PictureDatas[m_Index].m_Row = OldRow;
			( ( CMainFrame* )( this->GetParentFrame() ) )->UpdatePicture( m_Index );
		});

		/*g_HeroInfo->m_PictureDatas[m_Index].m_Row = propRoot->GetSubItem( 2 )->GetSubItem( 0 )->GetValue().intVal;
		//Refresh
		( ( CMainFrame* )( this->GetParentFrame() ) )->UpdatePicture( m_Index );*/
	}
	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 2 )->GetSubItem( 1 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 2 )->GetSubItem( 1 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;
		int OldColumn = g_HeroInfo->m_PictureDatas[m_Index].m_Column;
		command->AddRedoFunction([=](){
			g_HeroInfo->m_PictureDatas[m_Index].m_Column = var;
			( ( CMainFrame* )( this->GetParentFrame() ) )->UpdatePicture( m_Index );
		});
		command->AddUndoFunction([=](){
			g_HeroInfo->m_PictureDatas[m_Index].m_Column = OldColumn;
			( ( CMainFrame* )( this->GetParentFrame() ) )->UpdatePicture( m_Index );
		});

		/*g_HeroInfo->m_PictureDatas[m_Index].m_Column = propRoot->GetSubItem( 2 )->GetSubItem( 1 )->GetValue().intVal;
		//Refresh
		( ( CMainFrame* )( this->GetParentFrame() ) )->UpdatePicture( m_Index );*/
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 3 )->GetSubItem( 0 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 3 )->GetSubItem( 0 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;
		int OldWidth = g_HeroInfo->m_PictureDatas[m_Index].m_Width;
		command->AddRedoFunction([=](){
			g_HeroInfo->m_PictureDatas[m_Index].m_Width = var;
		});
		command->AddUndoFunction([=](){
			g_HeroInfo->m_PictureDatas[m_Index].m_Width = OldWidth;
		});

		//g_HeroInfo->m_PictureDatas[m_Index].m_Width = propRoot->GetSubItem( 2 )->GetSubItem( 0 )->GetValue().intVal;
	}
	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 3 )->GetSubItem( 1 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 3 )->GetSubItem( 1 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int var = v.intVal;
		int OldHeight = g_HeroInfo->m_PictureDatas[m_Index].m_Height;
		command->AddRedoFunction([=](){
			g_HeroInfo->m_PictureDatas[m_Index].m_Height = var;
		});
		command->AddUndoFunction([=](){
			g_HeroInfo->m_PictureDatas[m_Index].m_Height = OldHeight;
		});

		//g_HeroInfo->m_PictureDatas[m_Index].m_Height = propRoot->GetSubItem( 2 )->GetSubItem( 0 )->GetValue().intVal;
	}

	m_CommandManager.CallCommand(command);
}

VARIANT CPropertiesWnd::varFloat( float _value )
{
	VARIANT _varFloat;
	_varFloat.vt = VT_R4;
	_varFloat.fltVal = _value;
	return _varFloat;
}

VARIANT CPropertiesWnd::varInt( int _value )
{
	VARIANT _varInt;
	_varInt.vt = VT_INT;
	_varInt.intVal = _value;
	return _varInt;
}

VARIANT CPropertiesWnd::varBool( bool _value )
{
	VARIANT _varBool;
	_varBool.vt = VT_BOOL;

	if ( _value )
	{
		_varBool.boolVal = -1;
	}
	else
	{
		_varBool.boolVal = 0;
	}

	return _varBool;
}

void CPropertiesWnd::Update()
{
	switch ( m_EditProp )
	{
	case 2:
		UpdatePropList_Frame();
		break;

	case 3:
		UpdateBody();
		break;

	case 4:
		UpdateAttack();

	case 6:
		UpdateCatch();
	case 8:
		UpdatePictureData();
	}
}

void CPropertiesWnd::RefreshCenter()
{
	if ( m_EditProp == 2 )
	{
		CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
		FrameInfo frameInfo = ( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
		( ( CMFCPropItem* )propRoot->GetSubItem( 8 )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo.m_CenterX ) );
		( ( CMFCPropItem* )propRoot->GetSubItem( 8 )->GetSubItem( 1 ) )->SetValue( varFloat( frameInfo.m_CenterY ) );
	}
	else
	{
		RefreshPropList_Frame();
	}
}

void CPropertiesWnd::RefreshBodyPoint( int i )
{
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	FrameInfo* frameInfo = &( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo->m_Bodys[m_Index].m_Area.Points()[i].x() ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 ) )->SetValue( varFloat( -frameInfo->m_Bodys[m_Index].m_Area.Points()[i].y() ) );
}

void CPropertiesWnd::RefreshAttackPoint( int i )
{
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	FrameInfo* frameInfo = &( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo->m_Attacks[m_Index].m_Area.Points()[i].x() ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 ) )->SetValue( varFloat( -frameInfo->m_Attacks[m_Index].m_Area.Points()[i].y() ) );
}

void CPropertiesWnd::RefreshCatchPoint( int i )
{
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	FrameInfo* frameInfo = &( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo->m_Catchs[m_Index].m_Area.Points()[i].x() ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem( 1 ) )->SetValue( varFloat( -frameInfo->m_Catchs[m_Index].m_Area.Points()[i].y() ) );
}

void CPropertiesWnd::RefreshCreationPoint(  )
{
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	FrameInfo* frameInfo = &( *g_ActiveFramesMap )[g_FrameName][g_FrameIndex];
	( ( CMFCPropItem* )propRoot->GetSubItem( 6 )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo->m_Creations[m_Index].x ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 6 )->GetSubItem( 1 ) )->SetValue( varFloat( -frameInfo->m_Creations[m_Index].y ) );
}






