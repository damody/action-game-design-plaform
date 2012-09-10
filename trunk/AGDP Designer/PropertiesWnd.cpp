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
#include "AGDP Designer.h"
#include "global.h"
#include "ConvStr.h"

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
		pProp = new CMFCPropertyGridProperty( _T( "X" ), CPropertiesWnd::varFloat( 0.0f ), _T( "X位置" ) );
		pProp1->AddSubItem( pProp );
		pProp = new CMFCPropertyGridProperty( _T( "Y" ), CPropertiesWnd::varFloat( 0.0f ), _T( "Y位置" ) );
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

CPropertiesWnd::CPropertiesWnd(): m_EditProp( 0 )
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
	ON_REGISTERED_MESSAGE( AFX_WM_PROPERTY_CHANGED, OnPropertyChanged )
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 訊息處理常式

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
	// 建立下拉式方塊:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if ( !m_wndObjectCombo.Create( dwViewStyle, rectDummy, this, 1 ) )
	{
		TRACE0( "無法建立 [屬性] 下拉式方塊\n" );
		return -1;      // 無法建立
	}

	m_wndObjectCombo.AddString( _T( "屬性視窗" ) );
	m_wndObjectCombo.AddString( _T( "附加屬性" ) );
	m_wndObjectCombo.SetCurSel( 0 );

	if ( !m_wndPropList.Create( WS_VISIBLE | WS_CHILD, rectDummy, this, 2 ) )
	{
		TRACE0( "無法建立 [屬性] 方格\n" );
		return -1;      // 無法建立
	}

	InitPropList();
	InitPropList_Frame();
	InitPropList_Body();
	//m_wndPropList.RemoveAll();
	//InitPropList_Body();
	m_wndToolBar.Create( this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES );
	m_wndToolBar.LoadToolBar( IDR_PROPERTIES, 0, 0, TRUE /* 已鎖定 */ );
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap( theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 鎖定 */ );
	m_wndToolBar.SetPaneStyle( m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY );
	m_wndToolBar.SetPaneStyle( m_wndToolBar.GetPaneStyle() & ~( CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT ) );
	m_wndToolBar.SetOwner( this );
	// 所有命令都將經由此控制項傳送，而不是經由父框架:
	m_wndToolBar.SetRouteCommandsViaFrame( FALSE );
	AdjustLayout();
	//SetTimer(0,)
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
	// TODO: 在此加入您的命令處理常式程式碼
}

void CPropertiesWnd::OnUpdateProperties1( CCmdUI* /*pCmdUI*/ )
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 在此加入您的命令處理常式程式碼
}

void CPropertiesWnd::OnUpdateProperties2( CCmdUI* /*pCmdUI*/ )
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty( _T( "外觀" ) );
	pGroup1->AddSubItem( new CMFCPropertyGridProperty( _T( "3D 外觀" ), ( _variant_t ) false, _T( "指定視窗的字型為非粗體，且控制項有 3D 框線" ) ) );
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty( _T( "框線" ), _T( "Dialog Frame" ), _T( "下列其中一項: None、Thin、Resizable 或 Dialog Frame" ) );
	pProp->AddOption( _T( "None" ) );
	pProp->AddOption( _T( "Thin" ) );
	pProp->AddOption( _T( "Resizable" ) );
	pProp->AddOption( _T( "Dialog Frame" ) );
	pProp->AllowEdit( FALSE );
	pGroup1->AddSubItem( pProp );
	pGroup1->AddSubItem( new CMFCPropertyGridProperty( _T( "標題" ), ( _variant_t ) _T( "關於" ), _T( "指定文字將顯示在視窗的標題列" ) ) );
	m_wndPropList.AddProperty( pGroup1 );
	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty( _T( "視窗大小" ), 0, TRUE );
	pProp = new CMFCPropertyGridProperty( _T( "高度" ), ( _variant_t ) 250l, _T( "指定視窗的高度" ) );
	pProp->EnableSpinControl( TRUE, 50, 300 );
	pSize->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "寬度" ), ( _variant_t ) 150l, _T( "指定視窗的寬度" ) );
	pProp->EnableSpinControl( TRUE, 50, 200 );
	pSize->AddSubItem( pProp );
	m_wndPropList.AddProperty( pSize );
	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty( _T( "字型" ) );
	LOGFONT lf;
	CFont* font = CFont::FromHandle( ( HFONT ) GetStockObject( DEFAULT_GUI_FONT ) );
	font->GetLogFont( &lf );
	lstrcpy( lf.lfFaceName, _T( "Arial, 新細明體" ) );
	pGroup2->AddSubItem( new CMFCPropertyGridFontProperty( _T( "字型" ), lf, CF_EFFECTS | CF_SCREENFONTS, _T( "指定視窗的預設字型" ) ) );
	pGroup2->AddSubItem( new CMFCPropertyGridProperty( _T( "使用系統字型" ), ( _variant_t ) true, _T( "指定視窗使用 MS Shell Dlg 字型" ) ) );
	m_wndPropList.AddProperty( pGroup2 );
	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty( _T( "其他" ) );
	pProp = new CMFCPropertyGridProperty( _T( "(名稱)" ), _T( "應用程式" ) );
	pProp->Enable( FALSE );
	pGroup3->AddSubItem( pProp );
	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty( _T( "視窗色彩" ), RGB( 210, 192, 254 ), NULL, _T( "指定預設的視窗色彩" ) );
	pColorProp->EnableOtherButton( _T( "其他..." ) );
	pColorProp->EnableAutomaticButton( _T( "預設" ), ::GetSysColor( COLOR_3DFACE ) );
	pGroup3->AddSubItem( pColorProp );
	static const TCHAR szFilter[] = _T( "圖示檔(*.ico)|*.ico|所有檔案(*.*)|*.*||" );
	pGroup3->AddSubItem( new CMFCPropertyGridFileProperty( _T( "圖示" ), TRUE, _T( "" ), _T( "ico" ), 0, szFilter, _T( "指定視窗圖示" ) ) );
	pGroup3->AddSubItem( new CMFCPropertyGridFileProperty( _T( "資料夾" ), _T( "c:\\" ) ) );
	m_wndPropList.AddProperty( pGroup3 );
	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty( _T( "階層" ) );
	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty( _T( "第一子層級" ) );
	pGroup4->AddSubItem( pGroup41 );
	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty( _T( "第二子層級" ) );
	pGroup41->AddSubItem( pGroup411 );
	pGroup411->AddSubItem( new CMFCPropertyGridProperty( _T( "項目 1" ), ( _variant_t ) _T( "值 1" ), _T( "這是描述" ) ) );
	pGroup411->AddSubItem( new CMFCPropertyGridProperty( _T( "項目 2" ), ( _variant_t ) _T( "值 2" ), _T( "這是描述" ) ) );
	pGroup411->AddSubItem( new CMFCPropertyGridProperty( _T( "項目 3" ), ( _variant_t ) _T( "值 3" ), _T( "這是描述" ) ) );
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
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "主要屬性" ) );
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty( _T( "Frame Name" ), _T( "standing" ), _T( "表示這個 Frame 的名字" ) );
	pProp->AllowEdit( FALSE );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Frame Index" ), varInt(), _T( "表示在這個 Frame 的哪一格" ) );
	pProp->AllowEdit( FALSE );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Next Frame Name" ), _T( "standing" ), _T( "表示跳到哪一個 Frame" ) );
	AddNormalActionDcase( pProp );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Next Frame Index" ), varInt(), _T( "表示跳到 Frame 的哪一格" ) );
	pProp->EnableSpinControl( TRUE, 0, 300 );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Hero Action" ), _T( "STANDING" ), _T( "表示動作的狀態" ) );
	AddNormalActionUcase( pProp );
	pProp->AllowEdit( TRUE );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Wait" ), varInt(), _T( "這個 Frame 執行圈數，一圈1/60秒" ) );
	pProp->EnableSpinControl( TRUE, 0, 10000 );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "ClearKeyQueue" ), varBool(), _T( "是否要清掉 KeyQueue 的資料" ) );
	pPropMain->AddSubItem( pProp );
	CMFCPropertyGridProperty* pPicdate = new CMFCPropertyGridProperty( _T( "Picture" ), 0, TRUE );
	pPicdate->AllowEdit( FALSE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Picture ID" ), varInt(), _T( "表示用哪一張圖裡面可以顯示的動作" ) );
	pProp->EnableSpinControl( TRUE, 0, 300 );
	pPicdate->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Picture X" ), varInt(), _T( "行:第X個分割區塊" ) );
	pPicdate->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Picture Y" ), varInt(), _T( "列:第Y個分割區塊" ) );
	pPicdate->AddSubItem( pProp );
	pPropMain->AddSubItem( pPicdate );
	CMFCPropertyGridProperty* pCenterSize = new CMFCPropertyGridProperty( _T( "Center Offset" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Center X Offset" ), varFloat(), _T( "人物X方向偏移修正量" ) );
	pCenterSize->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Center Y Offset" ), varFloat(), _T( "人物Y方向偏移修正量" ) );
	pCenterSize->AddSubItem( pProp );
	pPropMain->AddSubItem( pCenterSize );
	CMFCPropertyGridProperty* pConsumePos = new CMFCPropertyGridProperty( _T( "Consume" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "JumpRule" ), varBool(), _T( "False 時只對next有用，True 時只對 hitdata有用" ) );
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "HP" ), varInt(), _T( "要消耗的 hp" ) );
	pProp->EnableSpinControl( TRUE, -1000, 1000 );
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "MP" ), varInt(), _T( "要消耗的 mp" ) );
	pProp->EnableSpinControl( TRUE, -1000, 1000 );
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Jump: Frame Name" ), _T( "standing" ), _T( "不夠消耗的話跳到該 Frame" ) );
	AddNormalActionDcase( pProp );
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "Jump: Frame Index" ), varInt(), _T( "不夠的話跳到該格" ) );
	pProp->EnableSpinControl( TRUE, 0, 300 );
	pConsumePos->AddSubItem( pProp );
	pPropMain->AddSubItem( pConsumePos );
	CMFCPropertyGridProperty* pDirectionVector = new CMFCPropertyGridProperty( _T( "Direction Vector" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "DVX" ), varFloat(), _T( "X方向左右的移動向量" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "DVY" ), varFloat(), _T( "Y方向左右的移動向量" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "DVZ" ), varFloat(), _T( "Z方向左右的移動向量" ) );
	pDirectionVector->AddSubItem( pProp );
	pPropMain->AddSubItem( pDirectionVector );
	m_wndPropList.AddProperty( pPropMain );
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::InitPropList_Body(int polygonCount)
{
	m_EditProp = 3;
	m_wndPropList.RemoveAll();
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "主要屬性" ) );
	CMFCPropertyGridProperty* pProp;

	pProp = new CMFCPropertyGridProperty(_T("m_Area"));
	CMFCPropertyGridProperty* pPropPointGroup;
	CMFCPropertyGridProperty* pPropPoint;
	for(int i=0; i<polygonCount; i++)
	{
		CString s_count; s_count.Format(_T("%d"), i);
		pPropPointGroup = new CMFCPropItem(&m_wndPropList, s_count, 0, TRUE);
		pPropPoint = new CMFCPropItem(&m_wndPropList, _T("X"), varFloat(), _T("X位置"));
		pPropPointGroup->AddSubItem(pPropPoint);
		pPropPoint = new CMFCPropItem(&m_wndPropList, _T("Y"), varFloat(), _T("Y位置"));
		pPropPointGroup->AddSubItem(pPropPoint);
		pProp->AddSubItem(pPropPointGroup);
	}
	pPropMain->AddSubItem(pProp);

	pProp = new CMFCPropItem(&m_wndPropList,_T("m_ZWidth"), varFloat(), _T("m_ZWidth"));
	pPropMain->AddSubItem(pProp);
	pProp = new CMFCPropItem(&m_wndPropList,_T("m_Kind"), varInt(), _T("m_Kind"));
	pPropMain->AddSubItem(pProp);
	
	m_wndPropList.AddProperty(pPropMain);
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::InitPropList_Attack(int polygonCount)
{
	m_EditProp = 4;
	m_wndPropList.RemoveAll();
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "主要屬性" ) );
	CMFCPropertyGridProperty* pProp;

	pProp = new CMFCPropertyGridProperty(_T("m_Area"));
	CMFCPropertyGridProperty* pPropPointGroup;
	CMFCPropertyGridProperty* pPropPoint;
	for(int i=0; i<polygonCount; i++)
	{
		CString s_count; s_count.Format(_T("%d"), i);
		pPropPointGroup = new CMFCPropItem(&m_wndPropList, s_count, 0, TRUE);
		pPropPoint = new CMFCPropItem(&m_wndPropList, _T("X"), varFloat(), _T("X位置"));
		pPropPointGroup->AddSubItem(pPropPoint);
		pPropPoint = new CMFCPropItem(&m_wndPropList, _T("Y"), varFloat(), _T("Y位置"));
		pPropPointGroup->AddSubItem(pPropPoint);
		pProp->AddSubItem(pPropPointGroup);
	}
	pPropMain->AddSubItem(pProp);

	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_Injury" ), varInt(), _T( "m_Injury" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_Strength" ), varInt(), _T( "m_Strength" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_Kind" ), varInt(), _T( "m_Kind" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_Effect" ), varInt(), _T( "m_Effect" ) );
	pPropMain->AddSubItem( pProp );

	CMFCPropertyGridProperty* pDirectionVector = new CMFCPropertyGridProperty( _T( "Direction Vector" ), 0, TRUE );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "DVX" ), varFloat(), _T( "X方向左右的移動向量" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "DVY" ), varFloat(), _T( "Y方向左右的移動向量" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "DVZ" ), varFloat(), _T( "Z方向左右的移動向量" ) );
	pDirectionVector->AddSubItem( pProp );
	pPropMain->AddSubItem( pDirectionVector );

	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_ZWidth" ), varFloat(), _T( "m_ZWidth" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_Fall" ), varInt(), _T( "m_Fall" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_BreakDefend" ), varInt(), _T( "m_BreakDefend" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_AttackRest" ), varInt(), _T( "m_AttackRest" ) );
	pPropMain->AddSubItem( pProp );
	pProp = new CMFCPropItem( &m_wndPropList, _T( "m_ReAttackRest" ), varInt(), _T( "m_ReAttackRest" ) );
	pPropMain->AddSubItem( pProp );
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
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "主要屬性" ) );
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

void CPropertiesWnd::InitPropList_CatchInfo(int polygonCount)
{
	m_EditProp = 6;
	m_wndPropList.RemoveAll();
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl( FALSE );
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "主要屬性" ) );
	CMFCPropertyGridProperty* pProp;

	pProp = new CMFCPropertyGridProperty(_T("m_Area"));
	CMFCPropertyGridProperty* pPropPointGroup;
	CMFCPropertyGridProperty* pPropPoint;
	for(int i=0; i<polygonCount; i++)
	{
		CString s_count; s_count.Format(_T("%d"), i);
		pPropPointGroup = new CMFCPropItem(&m_wndPropList, s_count, 0, TRUE);
		pPropPoint = new CMFCPropItem(&m_wndPropList, _T("X"), varFloat(), _T("X位置"));
		pPropPointGroup->AddSubItem(pPropPoint);
		pPropPoint = new CMFCPropItem(&m_wndPropList, _T("Y"), varFloat(), _T("Y位置"));
		pPropPointGroup->AddSubItem(pPropPoint);
		pProp->AddSubItem(pPropPointGroup);
	}
	pPropMain->AddSubItem(pProp);

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
	CMFCPropertyGridProperty* pPropMain = new CMFCPropertyGridProperty( _T( "主要屬性" ) );
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

void CPropertiesWnd::AddNormalActionUcase( CMFCPropertyGridProperty* pProp )
{
	pProp->AddOption( _T( "STANDING" ) );
	pProp->AddOption( _T( "WALKING" ) );
	pProp->AddOption( _T( "RUNNING" ) );
	pProp->AddOption( _T( "STOP_RUNNING" ) );
	pProp->AddOption( _T( "HEAVY_WEAPON_WALK" ) );
	pProp->AddOption( _T( "HEAVY_WEAPON_RUN" ) );
	pProp->AddOption( _T( "LIGHT_WEAPON_STAND_ATTACK" ) );
	pProp->AddOption( _T( "LIGHT_WEAPON_JUMP_ATTACK" ) );
	pProp->AddOption( _T( "LIGHT_WEAPON_RUN_ATTACK" ) );
	pProp->AddOption( _T( "LIGHT_WEAPON_DASH_ATTACK" ) );
	pProp->AddOption( _T( "LIGHT_WEAPON_THROW" ) );
	pProp->AddOption( _T( "HEAVY_WEAPON_THROW" ) );
	pProp->AddOption( _T( "LIGHT_WEAPON_JUMP_THROW" ) );
	pProp->AddOption( _T( "HEAVY_WEAPON_JUMP_THROW" ) );
	pProp->AddOption( _T( "DRINK" ) );
	pProp->AddOption( _T( "LIGHT_PUNCH" ) );
	pProp->AddOption( _T( "LIGHT_KICK" ) );
	pProp->AddOption( _T( "HEAVY_PUNCH" ) );
	pProp->AddOption( _T( "HEAVY_KICK" ) );
	pProp->AddOption( _T( "SUPER_PUNCH" ) );
	pProp->AddOption( _T( "SUPER_KICK" ) );
	pProp->AddOption( _T( "JUMP_PUNCH" ) );
	pProp->AddOption( _T( "JUMP_KICK" ) );
	pProp->AddOption( _T( "RUN_PUNCH" ) );
	pProp->AddOption( _T( "RUN_KICK" ) );
	pProp->AddOption( _T( "FORWARD_FLY_ROWING" ) );
	pProp->AddOption( _T( "BACKWARD_FLY_ROWING" ) );
	pProp->AddOption( _T( "FORWARD_ROWING" ) );
	pProp->AddOption( _T( "BACKWARD_ROWING" ) );
	pProp->AddOption( _T( "DEFEND" ) );
	pProp->AddOption( _T( "DEFEND_PUNCH" ) );
	pProp->AddOption( _T( "DEFEND_KICK" ) );
	pProp->AddOption( _T( "CATCHING" ) );
	pProp->AddOption( _T( "CAUGHT" ) );
	pProp->AddOption( _T( "FALLING" ) );
	pProp->AddOption( _T( "JUMP" ) );
	pProp->AddOption( _T( "CROUCH" ) );
	pProp->AddOption( _T( "INJURED" ) );
	pProp->AddOption( _T( "LYING" ) );
	pProp->AddOption( _T( "UNIQUE_SKILL" ) );
}


void CPropertiesWnd::AddNormalActionDcase( CMFCPropertyGridProperty* pProp )
{
	if ( g_ActiveFramesMap != NULL )
	{
		for ( FramesMap::iterator it = g_ActiveFramesMap->begin(); it != g_ActiveFramesMap->end() ; it++ )
		{
			char buff[100];
			sprintf( buff, "%s", it->first.c_str() );
			CString str( buff );
			pProp->AddOption( str );
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
	CMFCPropertyGridProperty* pProp1 = new CMFCPropertyGridProperty( _T( "Point1" ), 0, TRUE );
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty( _T( "X" ), ( _variant_t ) 0.f, _T( "X位置" ) );
	pProp->EnableSpinControl( TRUE, -1000, 1000 );
	pProp1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Y" ), ( _variant_t ) 0.f, _T( "Y位置" ) );
	pProp->EnableSpinControl( TRUE, -1000, 1000 );
	pProp1->AddSubItem( pProp );
	pPolygon2D->AddSubItem( pProp1 );
}

CMFCPropertyGridProperty* CPropertiesWnd::GetDefaultPropList()
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty( _T( "主要屬性" ) );
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty( _T( "Frame Name" ), _T( "standing" ), _T( "表示這個 Frame 的名字" ) );
	AddNormalActionDcase( pProp );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Frame Index" ), varInt(), _T( "表示在這個 Frame 的哪一格" ) );
	pProp->AllowEdit( FALSE );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Next Frame Name" ), _T( "standing" ), _T( "表示跳到哪一個 Frame" ), 0 );
	AddNormalActionDcase( pProp );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Next Frame Index" ), varInt(), _T( "表示跳到 Frame 的哪一格" ) );
	pProp->EnableSpinControl( TRUE, 0, 300 );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Hero Action" ), _T( "STANDING" ), _T( "表示動作的狀態" ) );
	AddNormalActionUcase( pProp );
	pProp->AllowEdit( TRUE );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Wait" ), varInt(), _T( "這個 Frame 執行圈數，一圈1/60秒" ) );
	pProp->EnableSpinControl( TRUE, 0, 10000 );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "ClearKeyQueue" ), varBool(), _T( "是否要清掉 KeyQueue 的資料" ) );
	pGroup1->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Picture ID" ), varInt(), _T( "表示用哪一張圖裡面可以顯示的動作" ) );
	pProp->EnableSpinControl( TRUE, 0, 300 );
	pGroup1->AddSubItem( pProp );
	CMFCPropertyGridProperty* pCenterSize = new CMFCPropertyGridProperty( _T( "Center Offset" ), 0, TRUE );
	pProp = new CMFCPropertyGridProperty( _T( "Center X Offset" ), varFloat(), _T( "人物X方向偏移修正量" ) );
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pCenterSize->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Center Y Offset" ), varFloat(), _T( "人物Y方向偏移修正量" ) );
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pCenterSize->AddSubItem( pProp );
	pGroup1->AddSubItem( pCenterSize );
	CMFCPropertyGridProperty* pPicturePos = new CMFCPropertyGridProperty( _T( "Picture Offset" ), 0, TRUE );
	pProp = new CMFCPropertyGridProperty( _T( "Picture X Offset" ), varInt(), _T( "人物圖片X偏移量" ) );
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pPicturePos->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Picture Y Offset" ), varInt(), _T( "人物圖片Y偏移量" ) );
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pPicturePos->AddSubItem( pProp );
	pGroup1->AddSubItem( pPicturePos );
	CMFCPropertyGridProperty* pConsumePos = new CMFCPropertyGridProperty( _T( "Consume" ), 0, TRUE );
	pProp = new CMFCPropertyGridProperty( _T( "JumpRule" ), varBool(), _T( "False 時只對next有用，True 時只對 hitdata有用" ) );
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "HP" ), varInt(), _T( "要消耗的 hp" ) );
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "MP" ), varInt(), _T( "要消耗的 mp" ) );
//	pProp->EnableSpinControl(TRUE, -1000, 1000);
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Not Enough Frame Name" ), _T( "standing" ), _T( "不夠消耗的話跳到該 Frame" ) );
	AddNormalActionDcase( pProp );
	pConsumePos->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "Not Next Frame Index" ), varInt(), _T( "不夠的話跳到該格" ) );
//	pProp->EnableSpinControl(TRUE, 0, 300);
	pConsumePos->AddSubItem( pProp );
	pGroup1->AddSubItem( pConsumePos );
	CMFCPropertyGridProperty* pDirectionVector = new CMFCPropertyGridProperty( _T( "Direction Vector" ), 0, TRUE );
	pProp = new CMFCPropertyGridProperty( _T( "DVX" ), varFloat(), _T( "X方向左右的移動向量" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "DVY" ), varFloat(), _T( "Y方向左右的移動向量" ) );
	pDirectionVector->AddSubItem( pProp );
	pProp = new CMFCPropertyGridProperty( _T( "DVZ" ), varFloat(), _T( "Z方向左右的移動向量" ) );
	pDirectionVector->AddSubItem( pProp );
	pGroup1->AddSubItem( pDirectionVector );
	return pGroup1;
}

LRESULT CPropertiesWnd::OnPropertyChanged( __in WPARAM wparam, __in LPARAM lparam )
{
	return CClassView::GetInstance()->OnPropertyChanged( wparam, lparam, m_lastSelectedItem );
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
	( ( CMFCPropItem* )propRoot->GetSubItem( 4 ) )->SetValue( CString( actionMap[frameInfo.m_HeroAction] ) );
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

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->IsEdited() )
	{
		char buff[1000];
		COleVariant v = propRoot->GetSubItem( 2 )->GetValue();
		v.ChangeType( VT_BSTR, NULL );
		ConvStr::WcharToChar( CString( v ).GetBuffer( 0 ), buff );
		std::string FrameName( buff );

		if ( g_ActiveFramesMap->find( FrameName ) != g_ActiveFramesMap->end() )
		{
			frameInfo->m_NextFrameName = FrameName;
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
			frameInfo->m_NextFrameIndex = i;
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
		char buff[100];
		sprintf( buff, "Undo" );
		CString str( buff );
		AfxMessageBox( str );
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 5 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 5 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int i = v.intVal;
		frameInfo->m_Wait = i;
	}

	if ( propRoot->GetSubItem( 6 )->OnEndEdit() )
	{
		COleVariant v = propRoot->GetSubItem( 6 )->GetValue();

		if ( v.boolVal )
		{
			frameInfo->m_ClearKeyQueue = true;
		}
		else
		{
			frameInfo->m_ClearKeyQueue = false;
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 0 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 7 )->GetSubItem( 0 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int i = v.intVal;

		if ( i < g_HeroInfo->m_PictureDatas.size() && i > -1 )
		{
			frameInfo->m_PictureID = i;
			frameInfo->m_PictureX  = 1;
			frameInfo->m_PictureY  = 1;
			( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 1 ) )->SetValue( varInt( 1 ) );
			( ( CMFCPropItem* )propRoot->GetSubItem( 7 )->GetSubItem( 2 ) )->SetValue( varInt( 1 ) );
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.Refresh();
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
			frameInfo->m_PictureX  = i;
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.Refresh();
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
			frameInfo->m_PictureY  = i;
			( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.Refresh();
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
		int i = v.fltVal;
		frameInfo->m_CenterX = i;
		( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCenter( frameInfo->m_CenterX, frameInfo->m_CenterY );
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 8 )->GetSubItem( 1 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 8 )->GetSubItem( 1 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		int i = v.fltVal;
		frameInfo->m_CenterX = i;
		( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCenter( frameInfo->m_CenterX, frameInfo->m_CenterY );
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 0 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 9 )->GetSubItem( 0 )->GetValue();
		v.ChangeType( VT_BOOL, NULL );

		if ( v.boolVal )
		{
			frameInfo->m_Consume.m_JumpRule = true;
		}
		else
		{
			frameInfo->m_Consume.m_JumpRule = false;
		}
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 1 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 9 )->GetSubItem( 1 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int i = v.intVal;
		frameInfo->m_Consume.m_HP = i;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 2 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 9 )->GetSubItem( 2 )->GetValue();
		v.ChangeType( VT_INT, NULL );
		int i = v.intVal;
		frameInfo->m_Consume.m_MP = i;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 3 ) )->IsEdited() )
	{
		char buff[1000];
		COleVariant v = propRoot->GetSubItem( 9 )->GetSubItem( 3 )->GetValue();
		v.ChangeType( VT_BSTR, NULL );
		ConvStr::WcharToChar( CString( v ).GetBuffer( 0 ), buff );
		std::string FrameName( buff );

		if ( g_ActiveFramesMap->find( FrameName ) != g_ActiveFramesMap->end() )
		{
			frameInfo->m_Consume.m_NotEnoughFrameName = FrameName;
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
			frameInfo->m_Consume.m_NotEnoughFrame = i;
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
		int i = v.fltVal;
		frameInfo->m_DVX = i;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 10 )->GetSubItem( 1 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 10 )->GetSubItem( 1 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		int i = v.fltVal;
		frameInfo->m_DVY = i;
	}

	if ( ( ( CMFCPropItem* )propRoot->GetSubItem( 9 )->GetSubItem( 2 ) )->IsEdited() )
	{
		COleVariant v = propRoot->GetSubItem( 10 )->GetSubItem( 2 )->GetValue();
		v.ChangeType( VT_R4, NULL );
		int i = v.fltVal;
		frameInfo->m_DVZ = i;
	}
}


void CPropertiesWnd::RefreshPropList_Body(int index)
{
	if ( m_EditProp != 3 )
	{
		InitPropList_Body();
		m_EditProp = 3;
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
	if(frameInfo.m_Bodys[index].m_Area.Points().size() != 1) {InitPropList_Body(frameInfo.m_Bodys[index].m_Area.Points().size());}
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	for(int i=0; i<frameInfo.m_Bodys[index].m_Area.Points().size(); i++)
	{
		( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem(0) )->SetValue( varFloat(frameInfo.m_Bodys[index].m_Area.Points()[i].x) );
		( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem(1) )->SetValue( varFloat(frameInfo.m_Bodys[index].m_Area.Points()[i].y) );
	}
	( ( CMFCPropItem* )propRoot->GetSubItem( 1 ) )->SetValue( varFloat( frameInfo.m_Bodys[index].m_ZWidth ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->SetValue( varInt( frameInfo.m_Bodys[index].m_Kind ) );
}

void CPropertiesWnd::RefreshPropList_Attack(int index)
{
	if ( m_EditProp != 4 )
	{
		InitPropList_Attack();
		m_EditProp = 4;
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
	if(frameInfo.m_Attacks[index].m_Area.Points().size() != 1) {InitPropList_Attack(frameInfo.m_Attacks[index].m_Area.Points().size());}
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	for(int i=0; i<frameInfo.m_Attacks[index].m_Area.Points().size(); i++)
	{
		( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem(0) )->SetValue( varFloat(frameInfo.m_Attacks[index].m_Area.Points()[i].x) );
		( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem(1) )->SetValue( varFloat(frameInfo.m_Attacks[index].m_Area.Points()[i].y) );
	}
	( ( CMFCPropItem* )propRoot->GetSubItem( 1 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_Injury ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_Strength ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 3 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_Kind ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 4 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_Effect ) );

	( ( CMFCPropItem* )propRoot->GetSubItem( 5 )->GetSubItem ( 0 ) )->SetValue( varFloat( frameInfo.m_Attacks[index].m_DVX ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 5 )->GetSubItem ( 1 ) )->SetValue( varFloat( frameInfo.m_Attacks[index].m_DVY ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 5 )->GetSubItem ( 2 ) )->SetValue( varFloat( frameInfo.m_Attacks[index].m_DVZ ) );

	( ( CMFCPropItem* )propRoot->GetSubItem( 6 ) )->SetValue( varFloat( frameInfo.m_Attacks[index].m_ZWidth ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 7 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_Fall ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 8 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_BreakDefend ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 9 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_AttackRest ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 10 ) )->SetValue( varInt( frameInfo.m_Attacks[index].m_ReAttackRest ) );
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


void CPropertiesWnd::RefreshPropList_CatchInfo(int index)
{
	if ( m_EditProp != 6 )
	{
		InitPropList_Body();
		m_EditProp = 6;
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
	if(frameInfo.m_Catchs[index].m_Area.Points().size() != 1) {InitPropList_Body(frameInfo.m_Catchs[index].m_Area.Points().size());}
	CMFCPropertyGridProperty* propRoot =  m_wndPropList.GetProperty( 0 );
	for(int i=0; i<frameInfo.m_Catchs[index].m_Area.Points().size(); i++)
	{
		( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem(0) )->SetValue( varFloat(frameInfo.m_Catchs[index].m_Area.Points()[i].x) );
		( ( CMFCPropItem* )propRoot->GetSubItem( 0 )->GetSubItem( i )->GetSubItem(1) )->SetValue( varFloat(frameInfo.m_Catchs[index].m_Area.Points()[i].y) );
	}
	( ( CMFCPropItem* )propRoot->GetSubItem( 1 ) )->SetValue( varFloat( frameInfo.m_Catchs[index].m_ZWidth ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 2 ) )->SetValue( varInt( frameInfo.m_Catchs[index].m_Injury ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 3 ) )->SetValue( varInt( frameInfo.m_Catchs[index].m_Kind ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 4 )->GetSubItem( 0 ) )->SetValue( varFloat( frameInfo.m_Catchs[index].m_CatchPosition.x ) );
	( ( CMFCPropItem* )propRoot->GetSubItem( 4 )->GetSubItem( 1 ) )->SetValue( varFloat( frameInfo.m_Catchs[index].m_CatchPosition.y ) );
	if(frameInfo.m_Catchs[index].m_CatchWhere == CatchInfo::CatchPosition::NECK) ( ( CMFCPropItem* )propRoot->GetSubItem( 5 ) )->SetValue( _T( "NECK" ) );
	else if(frameInfo.m_Catchs[index].m_CatchWhere == CatchInfo::CatchPosition::LEG) ( ( CMFCPropItem* )propRoot->GetSubItem( 5 ) )->SetValue( _T( "LEG" ) );
	else ( ( CMFCPropItem* )propRoot->GetSubItem( 5 ) )->SetValue( _T( "WAIST" ) );
}

void CPropertiesWnd::RefreshPropList_BloodInfo(int index)
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


const CString CPropertiesWnd::actionMap[MAX_ACTIONS] =
{
	CString( "STANDING" ),
	CString( "WALKING" ),
	CString( "RUNNING" ),
	CString( "STOP_RUNNING" ),
	CString( "HEAVY_WEAPON_WALK" ),
	CString( "HEAVY_WEAPON_RUN" ),
	CString( "LIGHT_WEAPON_STAND_ATTACK" ),
	CString( "LIGHT_WEAPON_JUMP_ATTACK" ),
	CString( "LIGHT_WEAPON_RUN_ATTACK" ),
	CString( "LIGHT_WEAPON_DASH_ATTACK" ),
	CString( "LIGHT_WEAPON_THROW" ),
	CString( "HEAVY_WEAPON_THROW" ),
	CString( "LIGHT_WEAPON_JUMP_THROW" ),
	CString( "HEAVY_WEAPON_JUMP_THROW" ),
	CString( "DRINK" ),
	CString( "BEFORE_ATTACK" ),
	CString( "ATTACKING" ),
	CString( "AFTER_ATTACK" ),
	CString( "BEFORE_SUPER_ATTACK" ),
	CString( "SUPER_ATTACKING" ),
	CString( "AFTER_SUPER_ATTACK" ),
	CString( "BEFORE_JUMP_ATTACK" ),
	CString( "JUMP_ATTACKING" ),
	CString( "AFTER_JUMP_ATTACK" ),
	CString( "BEFORE_RUN_ATTACK" ),
	CString( "RUN_ATTACKING" ),
	CString( "AFTER_RUN_ATTACK" ),
	CString( "BEFORE_DASH_ATTACK" ),
	CString( "DASH_ATTACKING" ),
	CString( "AFTER_DASH_ATTACK" ),
	CString( "FLIP" ),
	CString( "ROLLING" ),
	CString( "DEFEND" ),
	CString( "DEFEND_PUNCH" ),
	CString( "DEFEND_KICK" ),
	CString( "CATCHING" ),
	CString( "CAUGHT" ),
	CString( "FALLING" ),
	CString( "JUMP" ),
	CString( "DASH" ),
	CString( "CROUCH" ),
	CString( "INJURED" ),
	CString( "FORWARD_LYING" ),
	CString( "BACKWARD_LYING" ),
	CString( "IN_THE_AIR" ),
	CString( "BEFORE_SKILL" ),
	CString( "AFTER_SKILL" ),
	CString( "AIR_SKILL" ),
	CString( "X_AXIS_SKILL" ),
	CString( "Z_AXIS_SKILL" ),
	CString( "GROUND_SKILL" ),
	CString( "UNIQUE_SKILL" ),
};

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
/*
void CPropertiesWnd::DeleteProperty(CMFCPropertyGridProperty* pProp)
{
	m_wndPropList.DeleteProperty(pProp);
}*/
