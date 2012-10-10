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

// MainFrm.cpp : CMainFrame ���O����@
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

// CMainFrame �غc/�Ѻc

CMainFrame::CMainFrame()
{
	// TODO: �b���[�J������l�Ƶ{���X
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
	// �ھګ���ȳ]�w��ı�ƺ޲z���M�˦�
	OnApplicationLook( theApp.m_nAppLook );
	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // ��L�i�μ˦�...
	mdiTabParams.m_bActiveTabCloseButton = FALSE;      // �]�w�� FALSE �i�b���޼��Ұϰ�k����m�������s
	mdiTabParams.m_bTabIcons = FALSE;    // �]�w�� TRUE �i�b MDI ���޼��ҤW�ҥΤ��ϥ�
	mdiTabParams.m_bAutoColor = TRUE;    // �]�w�� FALSE �i���� MDI ���޼��Ҫ��۰ʵۦ�
	mdiTabParams.m_bDocumentMenu = TRUE; // �ҥί��޼��Ұϰ�k�������\���
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
		TRACE0( "�L�k�إߪ��A�C\n" );
		return -1;      // �L�k�إ�
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString( IDS_STATUS_PANE1 );
	ASSERT( bNameValid );
	bNameValid = strTitlePane2.LoadString( IDS_STATUS_PANE2 );
	ASSERT( bNameValid );
	m_wndStatusBar.AddElement( new CMFCRibbonStatusBarPane( ID_STATUSBAR_PANE1, strTitlePane1, TRUE ), strTitlePane1 );
	m_wndStatusBar.AddExtendedElement( new CMFCRibbonStatusBarPane( ID_STATUSBAR_PANE2, strTitlePane2, TRUE ), strTitlePane2 );
	// �ҥ� Visual Studio 2005 �˦����n�����欰
	CDockingManager::SetDockingMode( DT_SMART );
	// �ҥ� Visual Studio 2005 �˦����n�����۰����æ欰
	EnableAutoHidePanes( CBRS_ALIGN_ANY );

	// �N�b�����إߨ�������A�ҥH�|�Ȯɰ��Ω󥪰����n:
	//EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// �إ߼��D�C:
	if ( !CreateCaptionBar() )
	{
		TRACE0( "�L�k�إ߼��D�C\n" );
		return -1;      // �L�k�إ�
	}

	// Outlook �\��Ϥw�إߡA�ӥB���Ӥ��\�󥪰����n�C
	EnableDocking( CBRS_ALIGN_LEFT );
	EnableAutoHidePanes( CBRS_ALIGN_RIGHT );
	// ���J�\����ؼv�� (����b����зǤu��C�W):
	CMFCToolBar::AddToolBarForImageCollection( IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0 );

	// �إ߰��n����
	if ( !CreateDockingWindows() )
	{
		TRACE0( "�L�k�إ߰��n����\n" );
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
	// �ҥμW�j�������޲z��ܤ��
	EnableWindowsDialog( ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE );
	// �b�������D�C�W�������W�ٻP���ε{���W�٪����ǡC
	// �o�i���ɤu��C���i�ΩʡA�]�����W�ٷ|�H���Y����ܡC
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

	// TODO: �b���g�ѭק� CREATESTRUCT cs
	// �F��ק�������O�μ˦����ت�
	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// �إ����O�˵�
	CString strClassView;
	bNameValid = strClassView.LoadString( IDS_CLASS_VIEW );
	ASSERT( bNameValid );

	if ( !m_wndClassView.Create( strClassView, this, CRect( 0, 0, 200, 200 ), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI ) )
	{
		TRACE0( "�L�k�إ� [���O�˵�] ����\n" );
		return FALSE; // �L�k�إ�
	}

	// �إ��ɮ��˵�
	CString strFileView;
	bNameValid = strFileView.LoadString( IDS_FILE_VIEW );
	ASSERT( bNameValid );

	if ( !m_wndFileView.Create( strFileView, this, CRect( 0, 0, 200, 200 ), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI ) )
	{
		TRACE0( "�L�k�إ� [�ɮ��˵�] ����\n" );
		return FALSE; // �L�k�إ�
	}

	// �إ߿�X����
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString( IDS_OUTPUT_WND );
	ASSERT( bNameValid );

	if ( !m_wndOutput.Create( strOutputWnd, this, CRect( 0, 0, 100, 100 ), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI ) )
	{
		TRACE0( "�L�k�إ� [��X] ����\n" );
		return FALSE; // �L�k�إ�
	}

	// �إ��ݩʵ���
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString( IDS_PROPERTIES_WND );
	ASSERT( bNameValid );

	if ( !m_wndProperties.Create( strPropertiesWnd, this, CRect( 0, 0, 200, 200 ), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI ) )
	{
		TRACE0( "�L�k�إ� [�ݩ�] ����\n" );
		return FALSE; // �L�k�إ�
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
		TRACE0( "�L�k�إ߼��D�C\n" );
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

// CMainFrame �E�_

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


// CMainFrame �T���B�z�`��

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
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
}


void CMainFrame::OnButtonAreaMove()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
}


void CMainFrame::OnButtonAreaScale()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
}


BOOL CMainFrame::OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo )
{
	// TODO: �b���[�J�S�w���{���X�M (��) �I�s�����O
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
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	m_D3DFrameView.ShowWindow( m_D3DFrameView.IsVisible() ? SW_HIDE : SW_SHOW );
	RecalcLayout( FALSE );
}


void CMainFrame::OnUpdateCheckFrameview( CCmdUI* pCmdUI )
{
	// TODO: �b���[�J�z���R�O��s UI �B�z�`���{���X
	pCmdUI->SetCheck( m_D3DFrameView.IsVisible() );
}


void CMainFrame::OnCheckOutputwindow()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	m_wndOutput.ShowWindow( m_wndOutput.IsVisible() ? SW_HIDE : SW_SHOW );
	RecalcLayout( FALSE );
}


void CMainFrame::OnUpdateCheckOutputwindow( CCmdUI* pCmdUI )
{
	// TODO: �b���[�J�z���R�O��s UI �B�z�`���{���X
	pCmdUI->SetCheck( m_wndOutput.IsVisible() );
}


void CMainFrame::OnCheckSolutionmanager()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	m_wndFileView.ShowWindow( m_wndFileView.IsVisible() ? SW_HIDE : SW_SHOW );
	RecalcLayout( FALSE );
}


void CMainFrame::OnUpdateCheckSolutionmanager( CCmdUI* pCmdUI )
{
	// TODO: �b���[�J�z���R�O��s UI �B�z�`���{���X
	pCmdUI->SetCheck( m_wndFileView.IsVisible() );
}


void CMainFrame::OnCheckHeromanager()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	m_wndClassView.ShowWindow( m_wndClassView.IsVisible() ? SW_HIDE : SW_SHOW );
	RecalcLayout( FALSE );
}


void CMainFrame::OnUpdateCheckHeromanager( CCmdUI* pCmdUI )
{
	// TODO: �b���[�J�z���R�O��s UI �B�z�`���{���X
	pCmdUI->SetCheck( m_wndClassView.IsVisible() );
}


void CMainFrame::OnCheckProperty()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	m_wndProperties.ShowWindow( m_wndProperties.IsVisible() ? SW_HIDE : SW_SHOW );
	RecalcLayout( FALSE );
}


void CMainFrame::OnUpdateCheckProperty( CCmdUI* pCmdUI )
{
	// TODO: �b���[�J�z���R�O��s UI �B�z�`���{���X
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
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	if ( g_HeroInfo != NULL )
	{
		HeroInfo::WriteLua( g_HeroInfo, std::wstring( _T( "Script\\Hero\\temp.lua" ) ) );
		//����AGDP.exe
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
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
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
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	m_D3DFrameView.NextFrame();
	CMDIFrameWndEx::OnTimer(nIDEvent);
}
void CMainFrame::OnButtonhistory()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
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


