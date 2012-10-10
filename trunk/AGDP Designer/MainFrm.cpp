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

// MainFrm.cpp : CMainFrame 類別的實作
//

#include "stdafx.h"
#include "AGDP Designer.h"
#include "AGDP DesignerView.h"
#include "MainFrm.h"
#include "FileNewDialog.h"
#include "global.h"

#include "ConvStr.h"
#include "game/HeroInfo.h"
#include "Lua/LuaCell.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CAGDPDesignerView* g_NewView = NULL;
// CMainFrame

IMPLEMENT_DYNAMIC( CMainFrame, CMDIFrameWndEx )

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP( CMainFrame, CMDIFrameWndEx )
	ON_WM_CREATE()
	ON_COMMAND( ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager )
	ON_COMMAND_RANGE( ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook )
	ON_UPDATE_COMMAND_UI_RANGE( ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook )
	ON_COMMAND( ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar )
	ON_UPDATE_COMMAND_UI( ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar )
	ON_COMMAND( ID_TOOLS_OPTIONS, &CMainFrame::OnOptions )
	ON_WM_SETTINGCHANGE()
	ON_COMMAND( ID_FILE_NEW, &CMainFrame::OnFileNew )
	ON_COMMAND( ID_FILE_OPEN,  &CMainFrame::OnFileOpen  )
	ON_COMMAND( ID_LUA_SAVE, &CMainFrame::OnFileSave )
	ON_COMMAND( ID_CHECK_FrameView, &CMainFrame::OnCheckFrameview )
	ON_UPDATE_COMMAND_UI( ID_CHECK_FrameView, &CMainFrame::OnUpdateCheckFrameview )
	ON_COMMAND( ID_CHECK_OutputWindow, &CMainFrame::OnCheckOutputwindow )
	ON_UPDATE_COMMAND_UI( ID_CHECK_OutputWindow, &CMainFrame::OnUpdateCheckOutputwindow )
	ON_COMMAND( ID_CHECK_SolutionManager, &CMainFrame::OnCheckSolutionmanager )
	ON_UPDATE_COMMAND_UI( ID_CHECK_SolutionManager, &CMainFrame::OnUpdateCheckSolutionmanager )
	ON_COMMAND( ID_CHECK_HeroManager, &CMainFrame::OnCheckHeromanager )
	ON_UPDATE_COMMAND_UI( ID_CHECK_HeroManager, &CMainFrame::OnUpdateCheckHeromanager )
	ON_COMMAND( ID_CHECK_Property, &CMainFrame::OnCheckProperty )
	ON_UPDATE_COMMAND_UI( ID_CHECK_Property, &CMainFrame::OnUpdateCheckProperty )
	ON_WM_KEYDOWN()
	ON_COMMAND( ID_BUTTON_RUN, &CMainFrame::OnButtonRun )
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_COMMAND(ID_BUTTONHISTORY, &CMainFrame::OnButtonhistory)
	ON_COMMAND(ID_BUTTON_UNDO, &CMainFrame::OnButtonUndo)
	ON_COMMAND(ID_BUTTON_REDO, &CMainFrame::OnButtonRedo)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_UNDO, &CMainFrame::OnUpdateButtonUndo)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_REDO, &CMainFrame::OnUpdateButtonRedo)
END_MESSAGE_MAP()

// CMainFrame 建構/解構

CMainFrame::CMainFrame()
{
	// TODO: 在此加入成員初始化程式碼
	theApp.m_nAppLook = theApp.GetInt( _T( "ApplicationLook" ), ID_VIEW_APPLOOK_OFF_2007_BLACK );
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CMDIFrameWndEx::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	BOOL bNameValid;
	// 根據持續值設定視覺化管理員和樣式
	OnApplicationLook( theApp.m_nAppLook );
	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // 其他可用樣式...
	mdiTabParams.m_bActiveTabCloseButton = FALSE;      // 設定為 FALSE 可在索引標籤區域右側放置關閉按鈕
	mdiTabParams.m_bTabIcons = FALSE;    // 設定為 TRUE 可在 MDI 索引標籤上啟用文件圖示
	mdiTabParams.m_bAutoColor = TRUE;    // 設定為 FALSE 可停用 MDI 索引標籤的自動著色
	mdiTabParams.m_bDocumentMenu = TRUE; // 啟用索引標籤區域右側的文件功能表
	EnableMDITabbedGroups( TRUE, mdiTabParams );
	m_wndRibbonBar.Create( this );
	m_wndRibbonBar.LoadFromResource( IDR_RIBBON );

	/*CMFCRibbonButton* pBtnWindows = new CMFCRibbonButton ( 0, _T( "Windows\ni" ), -1, 1 );
	pBtnWindows->SetMenu ( IDR_WINDOWS_MENU, TRUE );
	CMFCRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
	                                        _T( "&Home" ),
	                                        0,
	                                        0 );
	CMFCRibbonPanel* pPanelWindow = pCategory->AddPanel (
	                                        _T( "Window\nw" ),
	                                        m_PanelImages.ExtractIcon ( 0 ) );
	pPanelWindow->Add ( pBtnWindows );*/

	if ( !m_wndStatusBar.Create( this ) )
	{
		TRACE0( "無法建立狀態列\n" );
		return -1;      // 無法建立
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString( IDS_STATUS_PANE1 );
	ASSERT( bNameValid );
	bNameValid = strTitlePane2.LoadString( IDS_STATUS_PANE2 );
	ASSERT( bNameValid );
	m_wndStatusBar.AddElement( new CMFCRibbonStatusBarPane( ID_STATUSBAR_PANE1, strTitlePane1, TRUE ), strTitlePane1 );
	m_wndStatusBar.AddExtendedElement( new CMFCRibbonStatusBarPane( ID_STATUSBAR_PANE2, strTitlePane2, TRUE ), strTitlePane2 );
	// 啟用 Visual Studio 2005 樣式停駐視窗行為
	CDockingManager::SetDockingMode( DT_SMART );
	// 啟用 Visual Studio 2005 樣式停駐視窗自動隱藏行為
	EnableAutoHidePanes( CBRS_ALIGN_ANY );

	// 將在左側建立巡覽窗格，所以會暫時停用於左側停駐:
	//EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// 建立標題列:
	if ( !CreateCaptionBar() )
	{
		TRACE0( "無法建立標題列\n" );
		return -1;      // 無法建立
	}

	// Outlook 功能區已建立，而且應該允許於左側停駐。
	EnableDocking( CBRS_ALIGN_LEFT );
	EnableAutoHidePanes( CBRS_ALIGN_RIGHT );
	// 載入功能表項目影像 (不放在任何標準工具列上):
	CMFCToolBar::AddToolBarForImageCollection( IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0 );

	// 建立停駐視窗
	if ( !CreateDockingWindows() )
	{
		TRACE0( "無法建立停駐視窗\n" );
		return -1;
	}

	m_wndFileView.EnableDocking( CBRS_ALIGN_ANY );
	DockPane( &m_wndFileView, 0, CRect( 0, 0, 200, 200 ) );
	m_wndClassView.EnableDocking( CBRS_ALIGN_ANY );
	DockPane( &m_wndClassView, 0, CRect( 0, 0, 200, 200 ) );
	m_wndOutput.EnableDocking( CBRS_ALIGN_ANY );
	DockPane( &m_wndOutput, 0, CRect( 0, 0, 200, 200 ) );
	m_wndProperties.EnableDocking( CBRS_ALIGN_ANY );
	DockPane( &m_wndProperties, 0, CRect( 0, 0, 200, 200 ) );
	m_wndClassView.AttachToTabWnd( &m_wndFileView, DM_SHOW, TRUE, &m_AttachPane );
	m_AttachPane->ToggleAutoHide();
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString( IDS_VIEW_FRAMEEDIT );

	if ( !m_D3DFrameView.Create( strPropertiesWnd, this, CRect( 0, 0, 400, 400 ), TRUE,
	                             ID_VIEW_FRAMEEDIT,
	                             WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI ) )
	{
		TRACE0( "Failed to create Dialog Bar\n" );
		return FALSE;      // fail to create
	}

	m_D3DFrameView.EnableDocking( CBRS_ALIGN_ANY );
	DockPane( &m_D3DFrameView );
	// 啟用增強型視窗管理對話方塊
	EnableWindowsDialog( ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE );
	// 在視窗標題列上切換文件名稱與應用程式名稱的順序。
	// 這可提升工具列的可用性，因為文件名稱會隨著縮圖顯示。
	ModifyStyle( 0, FWS_PREFIXTITLE );

	SetTimer(1,16,0);
	return 0;
}

BOOL CMainFrame::PreCreateWindow( CREATESTRUCT& cs )
{
	if ( !CMDIFrameWndEx::PreCreateWindow( cs ) )
	{
		return FALSE;
	}

	// TODO: 在此經由修改 CREATESTRUCT cs
	// 達到修改視窗類別或樣式的目的
	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// 建立類別檢視
	CString strClassView;
	bNameValid = strClassView.LoadString( IDS_CLASS_VIEW );
	ASSERT( bNameValid );

	if ( !m_wndClassView.Create( strClassView, this, CRect( 0, 0, 200, 200 ), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI ) )
	{
		TRACE0( "無法建立 [類別檢視] 視窗\n" );
		return FALSE; // 無法建立
	}

	// 建立檔案檢視
	CString strFileView;
	bNameValid = strFileView.LoadString( IDS_FILE_VIEW );
	ASSERT( bNameValid );

	if ( !m_wndFileView.Create( strFileView, this, CRect( 0, 0, 200, 200 ), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI ) )
	{
		TRACE0( "無法建立 [檔案檢視] 視窗\n" );
		return FALSE; // 無法建立
	}

	// 建立輸出視窗
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString( IDS_OUTPUT_WND );
	ASSERT( bNameValid );

	if ( !m_wndOutput.Create( strOutputWnd, this, CRect( 0, 0, 100, 100 ), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI ) )
	{
		TRACE0( "無法建立 [輸出] 視窗\n" );
		return FALSE; // 無法建立
	}

	// 建立屬性視窗
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString( IDS_PROPERTIES_WND );
	ASSERT( bNameValid );

	if ( !m_wndProperties.Create( strPropertiesWnd, this, CRect( 0, 0, 200, 200 ), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI ) )
	{
		TRACE0( "無法建立 [屬性] 視窗\n" );
		return FALSE; // 無法建立
	}

	SetDockingWindowIcons( theApp.m_bHiColorIcons );
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons( BOOL bHiColorIcons )
{
	HICON hFileViewIcon = ( HICON ) ::LoadImage( ::AfxGetResourceHandle(), MAKEINTRESOURCE( bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW ), IMAGE_ICON, ::GetSystemMetrics( SM_CXSMICON ), ::GetSystemMetrics( SM_CYSMICON ), 0 );
	m_wndFileView.SetIcon( hFileViewIcon, FALSE );
	HICON hClassViewIcon = ( HICON ) ::LoadImage( ::AfxGetResourceHandle(), MAKEINTRESOURCE( bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW ), IMAGE_ICON, ::GetSystemMetrics( SM_CXSMICON ), ::GetSystemMetrics( SM_CYSMICON ), 0 );
	m_wndClassView.SetIcon( hClassViewIcon, FALSE );
	HICON hOutputBarIcon = ( HICON ) ::LoadImage( ::AfxGetResourceHandle(), MAKEINTRESOURCE( bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND ), IMAGE_ICON, ::GetSystemMetrics( SM_CXSMICON ), ::GetSystemMetrics( SM_CYSMICON ), 0 );
	m_wndOutput.SetIcon( hOutputBarIcon, FALSE );
	HICON hPropertiesBarIcon = ( HICON ) ::LoadImage( ::AfxGetResourceHandle(), MAKEINTRESOURCE( bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND ), IMAGE_ICON, ::GetSystemMetrics( SM_CXSMICON ), ::GetSystemMetrics( SM_CYSMICON ), 0 );
	m_wndProperties.SetIcon( hPropertiesBarIcon, FALSE );
	UpdateMDITabbedBarsIcons();
}

BOOL CMainFrame::CreateCaptionBar()
{
	if ( !m_wndCaptionBar.Create( WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE ) )
	{
		TRACE0( "無法建立標題列\n" );
		return FALSE;
	}

	BOOL bNameValid;
	CString strTemp, strTemp2;
	bNameValid = strTemp.LoadString( IDS_CAPTION_BUTTON );
	ASSERT( bNameValid );
	m_wndCaptionBar.SetButton( strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE );
	bNameValid = strTemp.LoadString( IDS_CAPTION_BUTTON_TIP );
	ASSERT( bNameValid );
	m_wndCaptionBar.SetButtonToolTip( strTemp );
	bNameValid = strTemp.LoadString( IDS_CAPTION_TEXT );
	ASSERT( bNameValid );
	m_wndCaptionBar.SetText( strTemp, CMFCCaptionBar::ALIGN_LEFT );
	m_wndCaptionBar.SetBitmap( IDB_INFO, RGB( 255, 255, 255 ), FALSE, CMFCCaptionBar::ALIGN_LEFT );
	bNameValid = strTemp.LoadString( IDS_CAPTION_IMAGE_TIP );
	ASSERT( bNameValid );
	bNameValid = strTemp2.LoadString( IDS_CAPTION_IMAGE_TEXT );
	ASSERT( bNameValid );
	m_wndCaptionBar.SetImageToolTip( strTemp, strTemp2 );
	return TRUE;
}

// CMainFrame 診斷

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump( CDumpContext& dc ) const
{
	CMDIFrameWndEx::Dump( dc );
}
#endif //_DEBUG


// CMainFrame 訊息處理常式

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook( UINT id )
{
	CWaitCursor wait;
	theApp.m_nAppLook = id;

	switch ( theApp.m_nAppLook )
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager( RUNTIME_CLASS( CMFCVisualManager ) );
		m_wndRibbonBar.SetWindows7Look( FALSE );
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager( RUNTIME_CLASS( CMFCVisualManagerOfficeXP ) );
		m_wndRibbonBar.SetWindows7Look( FALSE );
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager( RUNTIME_CLASS( CMFCVisualManagerWindows ) );
		m_wndRibbonBar.SetWindows7Look( FALSE );
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager( RUNTIME_CLASS( CMFCVisualManagerOffice2003 ) );
		CDockingManager::SetDockingMode( DT_SMART );
		m_wndRibbonBar.SetWindows7Look( FALSE );
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager( RUNTIME_CLASS( CMFCVisualManagerVS2005 ) );
		CDockingManager::SetDockingMode( DT_SMART );
		m_wndRibbonBar.SetWindows7Look( FALSE );
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager( RUNTIME_CLASS( CMFCVisualManagerVS2008 ) );
		CDockingManager::SetDockingMode( DT_SMART );
		m_wndRibbonBar.SetWindows7Look( FALSE );
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager( RUNTIME_CLASS( CMFCVisualManagerWindows7 ) );
		CDockingManager::SetDockingMode( DT_SMART );
		m_wndRibbonBar.SetWindows7Look( TRUE );
		break;

	default:
		switch ( theApp.m_nAppLook )
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle( CMFCVisualManagerOffice2007::Office2007_LunaBlue );
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle( CMFCVisualManagerOffice2007::Office2007_ObsidianBlack );
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle( CMFCVisualManagerOffice2007::Office2007_Silver );
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle( CMFCVisualManagerOffice2007::Office2007_Aqua );
			break;
		}

		CMFCVisualManager::SetDefaultManager( RUNTIME_CLASS( CMFCVisualManagerOffice2007 ) );
		CDockingManager::SetDockingMode( DT_SMART );
		m_wndRibbonBar.SetWindows7Look( FALSE );
	}

	RedrawWindow( NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE );
	theApp.WriteInt( _T( "ApplicationLook" ), theApp.m_nAppLook );
}

void CMainFrame::OnUpdateApplicationLook( CCmdUI* pCmdUI )
{
	pCmdUI->SetRadio( theApp.m_nAppLook == pCmdUI->m_nID );
}

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow( m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW );
	RecalcLayout( FALSE );
}

void CMainFrame::OnUpdateViewCaptionBar( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck( m_wndCaptionBar.IsVisible() );
}

void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog* pOptionsDlg = new CMFCRibbonCustomizeDialog( this, &m_wndRibbonBar );
	ASSERT( pOptionsDlg != NULL );
	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}

void CMainFrame::OnSettingChange( UINT uFlags, LPCTSTR lpszSection )
{
	CMDIFrameWndEx::OnSettingChange( uFlags, lpszSection );
	m_wndOutput.UpdateFonts();
}


void CMainFrame::OnButtonAreaAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


void CMainFrame::OnButtonAreaMove()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


void CMainFrame::OnButtonAreaScale()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


BOOL CMainFrame::OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo )
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	if ( nID == ID_FILE_SAVE && nCode > 0 )
	{
		AfxMessageBox( _T( "save" ) );
	}

	if ( m_D3DFrameView.OnCmdMsg( nID, nCode, pExtra, pHandlerInfo ) )
	{
		return TRUE;
	}

	return CMDIFrameWndEx::OnCmdMsg( nID, nCode, pExtra, pHandlerInfo );
}


void CMainFrame::OnCheckFrameview()
{
	// TODO: 在此加入您的命令處理常式程式碼
	m_D3DFrameView.ShowWindow( m_D3DFrameView.IsVisible() ? SW_HIDE : SW_SHOW );
	RecalcLayout( FALSE );
}


void CMainFrame::OnUpdateCheckFrameview( CCmdUI* pCmdUI )
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->SetCheck( m_D3DFrameView.IsVisible() );
}


void CMainFrame::OnCheckOutputwindow()
{
	// TODO: 在此加入您的命令處理常式程式碼
	m_wndOutput.ShowWindow( m_wndOutput.IsVisible() ? SW_HIDE : SW_SHOW );
	RecalcLayout( FALSE );
}


void CMainFrame::OnUpdateCheckOutputwindow( CCmdUI* pCmdUI )
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->SetCheck( m_wndOutput.IsVisible() );
}


void CMainFrame::OnCheckSolutionmanager()
{
	// TODO: 在此加入您的命令處理常式程式碼
	m_wndFileView.ShowWindow( m_wndFileView.IsVisible() ? SW_HIDE : SW_SHOW );
	RecalcLayout( FALSE );
}


void CMainFrame::OnUpdateCheckSolutionmanager( CCmdUI* pCmdUI )
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->SetCheck( m_wndFileView.IsVisible() );
}


void CMainFrame::OnCheckHeromanager()
{
	// TODO: 在此加入您的命令處理常式程式碼
	m_wndClassView.ShowWindow( m_wndClassView.IsVisible() ? SW_HIDE : SW_SHOW );
	RecalcLayout( FALSE );
}


void CMainFrame::OnUpdateCheckHeromanager( CCmdUI* pCmdUI )
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->SetCheck( m_wndClassView.IsVisible() );
}


void CMainFrame::OnCheckProperty()
{
	// TODO: 在此加入您的命令處理常式程式碼
	m_wndProperties.ShowWindow( m_wndProperties.IsVisible() ? SW_HIDE : SW_SHOW );
	RecalcLayout( FALSE );
}


void CMainFrame::OnUpdateCheckProperty( CCmdUI* pCmdUI )
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
	pCmdUI->SetCheck( m_wndProperties.IsVisible() );
}

void CMainFrame::OnFileNew()
{
	CFileNewDialog fileNew;

	if ( fileNew.DoModal() == IDOK )
	{
		if ( fileNew.m_Type == 0 )
		{
			HeroInfo_RawPtr hero = HeroInfo_RawPtr( new HeroInfo );
			hero->m_Name = std::wstring( fileNew.m_Name.GetBuffer( 0 ) );
			hero->m_FramesMap[std::wstring(L"default")].push_back(DefaultFrameInfo(std::wstring(L"default")));
			hero->m_FramesMap[std::wstring(L"standing")].push_back(DefaultFrameInfo(std::wstring(L"standing")));
			hero->m_FramesMap[std::wstring(L"walking")].push_back(DefaultFrameInfo(std::wstring(L"walking")));
			hero->m_FramesMap[std::wstring(L"in_the_air")].push_back(DefaultFrameInfo(std::wstring(L"in_the_air")));
			hero->m_FramesMap[std::wstring(L"injured")].push_back(DefaultFrameInfo(std::wstring(L"injured")));
			hero->m_FramesMap[std::wstring(L"lying")].push_back(DefaultFrameInfo(std::wstring(L"lying")));
			hero->m_FramesMap[std::wstring(L"injured")].push_back(DefaultFrameInfo(std::wstring(L"injured")));
			hero->m_FramesMap[std::wstring(L"falling_front")].push_back(DefaultFrameInfo(std::wstring(L"falling_front")));
			hero->m_FramesMap[std::wstring(L"falling_back")].push_back(DefaultFrameInfo(std::wstring(L"falling_back")));
			hero->m_FramesMap[std::wstring(L"crouch")].push_back(DefaultFrameInfo(std::wstring(L"crouch")));
			m_wndFileView.AddFile( hero );
		}
	}
}

void CMainFrame::SwitchPictureView( int index )
{
	HeroViews::iterator it = m_HeroViews.find( g_HeroInfo );

	if ( it != m_HeroViews.end() )
	{
		it->second->SwitchPicture( index );
		m_wndProperties.RefreshPropList_PictureData(index);
	}
}

void CMainFrame::UpdatePicture( int index )
{
	HeroViews::iterator it = m_HeroViews.find( g_HeroInfo );

	if ( it != m_HeroViews.end() )
	{
		it->second->Refresh(&g_HeroInfo->m_PictureDatas[index]);
		it->second->SwitchPicture( index );
	}
}

bool CMainFrame::NewHeroViews( HeroInfo* hero )
{
	if ( m_HeroViews.find( hero ) == m_HeroViews.end() )
	{
		theApp.OnFileNew();
		m_HeroViews[hero] = g_NewView;
		return true;
	}
	return false;
}

void CMainFrame::OnFileSave()
{
	if ( g_HeroInfo != NULL )
	{
		CString defaultName( g_HeroInfo->m_Name.c_str() );
		CFileDialog dlgFile( FALSE, _T( "lua" ), defaultName , OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T( "Lua File (*.lua)|*.lua||" ), NULL, 0 );
		dlgFile.DoModal();
		//AfxMessageBox( dlgFile.GetPathName() );
		std::wstring path = dlgFile.GetPathName();
		HeroInfo::WriteLua( g_HeroInfo, path );
	}
}

void CMainFrame::OnFileOpen()
{
	m_wndFileView.OnFileOpen();
}

void CMainFrame::OnButtonRun()
{
	// TODO: 在此加入您的命令處理常式程式碼
	if ( g_HeroInfo != NULL )
	{
		HeroInfo::WriteLua( g_HeroInfo, std::wstring( _T( "Script\\Hero\\temp.lua" ) ) );
		//執行AGDP.exe
#ifdef _DEBUG
		system( "start ../Bin/ActionGameDesignPlaform.exe -hero ..\\AGDP Designer\\Script\\Hero\\temp.lua" );
#else
		system( "start ActionGameDesignPlaform.exe -hero Script\\Hero\\temp.lua" );
#endif
	}
	else
	{
		AfxMessageBox( _T( "No Target" ) );
	}
}

void CMainFrame::OnClose()
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	remove( "AGDP\\temp.lua" );
	CMDIFrameWndEx::OnClose();
}

void CMainFrame::OpenPictureView( CString& name, PictureData* pic, int index, HeroInfo* info )
{
	HeroViews::iterator it = m_HeroViews.find( info );
	if ( it != m_HeroViews.end() )
	{
		it->second->AddPicturedata( name, pic, index );
	}
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_D3DFrameView.NextFrame();
	CMDIFrameWndEx::OnTimer(nIDEvent);
}
void CMainFrame::OnButtonhistory()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


void CMainFrame::OnButtonUndo()
{
	CPropertiesWnd* pWnd = CPropertiesWnd::GetInstance();
	if(pWnd->m_CommandManager != NULL)
	{
		if(pWnd->m_CommandManager->CanUndo())
		{
			pWnd->m_CommandManager->Undo();
		}
	}
}


void CMainFrame::OnButtonRedo()
{
	CPropertiesWnd* pWnd = CPropertiesWnd::GetInstance();
	if(pWnd->m_CommandManager != NULL)
	{
		if(pWnd->m_CommandManager->CanRedo())
		{
			pWnd->m_CommandManager->Redo();
		}
	}
}


void CMainFrame::OnUpdateButtonUndo(CCmdUI *pCmdUI)
{
	CPropertiesWnd* pWnd = CPropertiesWnd::GetInstance();

	if(pWnd->m_CommandManager != NULL)
		pCmdUI->Enable(pWnd->m_CommandManager->CanUndo());
	else
		pCmdUI->Enable(FALSE);
}


void CMainFrame::OnUpdateButtonRedo(CCmdUI *pCmdUI)
{
	CPropertiesWnd* pWnd = CPropertiesWnd::GetInstance();

	if(pWnd->m_CommandManager != NULL)
		pCmdUI->Enable(pWnd->m_CommandManager->CanRedo());
	else
		pCmdUI->Enable(FALSE);
}

FrameInfo CMainFrame::DefaultFrameInfo(std::wstring& frameName)
{
	FrameInfo fi;
	fi.m_FrameName = frameName ;
	fi.m_FrameIndex = 0;
	fi.m_NextFrameName = L"default";
	fi.m_NextFrameIndex = 0;
	fi.m_HeroAction = 0;
	fi.m_Wait = 1;
	fi.m_ClearKeyQueue = false;
	fi.m_PictureID = 0;
	fi.m_CenterX = 0.0f;
	fi.m_CenterY = 0.0f;
	fi.m_PictureX = 1;
	fi.m_PictureY = 1;
	fi.m_Consume.m_JumpRule = 0;
	fi.m_Consume.m_HP = 0;
	fi.m_Consume.m_MP = 0;
	fi.m_Consume.m_NotEnoughFrameName = L"default";
	fi.m_Consume.m_NotEnoughFrame = 0;
	fi.m_DVX = 0.0f;
	fi.m_DVY = 0.0f;
	fi.m_DVZ = 0.0f;
	return fi;
}


