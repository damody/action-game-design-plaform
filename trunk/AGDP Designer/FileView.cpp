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
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "AGDP Designer.h"
#include "ConvStr.h"

#include "game/HeroInfo.h"
#include <auto_link_agal.hpp>
#include <Lua/LuaCell.h>
#include <game/LuaResource.h>
#include <game\LuaMap.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView()
{
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP( CFileView, CDockablePane )
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND( ID_PROPERTIES, OnProperties )
	ON_COMMAND( ID_OPEN, OnFileOpen )
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	//ON_COMMAND(ID_PictureData_Add, &CFileView::OnPicturedataAdd)
	ON_COMMAND( ID_PICTUREDATA_ADD, &CFileView::OnPicturedataAdd )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 訊息處理常式

int CFileView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CDockablePane::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	// 建立檢視:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if ( !m_wndFileView.Create( dwViewStyle, rectDummy, this, 4 ) )
	{
		TRACE0( "無法建立檔案檢視\n" );
		return -1;      // 無法建立
	}

	// 載入檢視影像:
	m_FileViewImages.Create( IDB_FILE_VIEW, 16, 0, RGB( 255, 0, 255 ) );
	m_wndFileView.SetImageList( &m_FileViewImages, TVSIL_NORMAL );
	m_wndToolBar.Create( this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER );
	m_wndToolBar.LoadToolBar( IDR_EXPLORER, 0, 0, TRUE /* 已鎖定 */ );
	OnChangeVisualStyle();
	m_wndToolBar.SetPaneStyle( m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY );
	m_wndToolBar.SetPaneStyle( m_wndToolBar.GetPaneStyle() & ~( CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT ) );
	m_wndToolBar.SetOwner( this );
	// 所有命令都將經由此控制項傳送，而不是經由父框架:
	m_wndToolBar.SetRouteCommandsViaFrame( FALSE );
	// 填入一些靜態樹狀檢視資料 (假程式碼，不需要什麼特別的內容)
	FillFileView();
	LoadData();
	AdjustLayout();
	return 0;
}

void CFileView::OnSize( UINT nType, int cx, int cy )
{
	CDockablePane::OnSize( nType, cx, cy );
	AdjustLayout();
}

void CFileView::FillFileView()
{
	HTREEITEM hResourceDoc  = m_wndFileView.InsertItem( _T( "Resource 資料" ), 0, 0 );
	hAction = m_wndFileView.InsertItem( _T("Action"), 2, 2, hResourceDoc );
	hResourceHeroDoc   = m_wndFileView.InsertItem(_T("Hero"), 0, 0, hResourceDoc );
	hResourceObjectDoc = m_wndFileView.InsertItem(_T("Object"), 0, 0, hResourceDoc );
	m_wndFileView.SetItemState( hResourceDoc, TVIS_BOLD, TVIS_BOLD );
	hHeroDoc = m_wndFileView.InsertItem( _T( "Hero 資料" ), 0, 0 );
	m_wndFileView.SetItemState( hHeroDoc, TVIS_BOLD, TVIS_BOLD );
	hObjectDoc = m_wndFileView.InsertItem( _T( "Object 資料" ), 0, 0 );
	m_wndFileView.SetItemState( hObjectDoc, TVIS_BOLD, TVIS_BOLD );
}

void CFileView::OnContextMenu( CWnd* pWnd, CPoint point )
{
	CTreeCtrl* pWndTree = ( CTreeCtrl* )&m_wndFileView;
	ASSERT_VALID( pWndTree );
	CMenu menu;

	if ( pWnd != pWndTree )
	{
		CDockablePane::OnContextMenu( pWnd, point );
		return;
	}

	HTREEITEM hTreeItem = NULL;

	if ( point != CPoint( -1, -1 ) )
	{
		// 選取按下的項目:
		CPoint ptTree = point;
		pWndTree->ScreenToClient( &ptTree );
		UINT flags = 0;
		hTreeItem = pWndTree->HitTest( ptTree, &flags );
	}
	else
	{
		hTreeItem = pWndTree->GetSelectedItem();
	}

	if ( hTreeItem != NULL )
	{
		if ( m_HeroInfoMap.find( hTreeItem ) != m_HeroInfoMap.end() )
		{
			menu.LoadMenu( IDR_MENU1 );
			//menu.LoadMenu(IDR_POPUP_EXPLORER);
			hHero_Select = hTreeItem;
		}
		else
		{
			menu.LoadMenu( IDR_POPUP_EXPLORER );
		}
	}
	else
	{
		menu.LoadMenu( IDR_POPUP_EXPLORER );
	}

	pWndTree->SetFocus();
	CMenu* pSumMenu = menu.GetSubMenu( 0 );

	if ( AfxGetMainWnd()->IsKindOf( RUNTIME_CLASS( CMDIFrameWndEx ) ) )
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if ( !pPopupMenu->Create( this, point.x, point.y, ( HMENU )pSumMenu->m_hMenu, FALSE, TRUE ) )
		{
			return;
		}

		( ( CMDIFrameWndEx* )AfxGetMainWnd() )->OnShowPopupMenu( pPopupMenu );
		UpdateDialogControls( this, FALSE );
	}
}

void CFileView::AdjustLayout()
{
	if ( GetSafeHwnd() == NULL )
	{
		return;
	}

	CRect rectClient;
	GetClientRect( rectClient );
	int cyTlb = m_wndToolBar.CalcFixedLayout( FALSE, TRUE ).cy;
	m_wndToolBar.SetWindowPos( NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER );
	m_wndFileView.SetWindowPos( NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER );
}

void CFileView::OnProperties()
{
	AfxMessageBox( _T( "屬性...." ) );
}

void CFileView::OnFileOpen()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CFileDialog dlgFile( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T( "Lua Files (*.lua)|*.lua||" ), NULL, 0 );

	if ( dlgFile.DoModal() == IDOK )
	{
		LuaCell_Sptr data = LuaCell_Sptr( new LuaCell );

		if ( data->InputLuaFile( dlgFile.GetPathName() ) )
		{
// 			if (HeroInfo::CheckHeroDataVaild(data))
// 			{
			HTREEITEM hHero = m_wndFileView.InsertItem( dlgFile.GetFileTitle(), 2, 2, hHeroDoc );
			HeroInfo_RawPtr hero = HeroInfo_RawPtr( new HeroInfo );
			g_HeroInfo = hero;
			hero->LoadData( data );

			if (g_HeroInfoMap.find(hero->m_Name) == g_HeroInfoMap.end())
			{
				( ( CMainFrame* )this->GetParentFrame() )->NewHeroViews( hero );
				for ( unsigned int i = 0; i < hero->m_PictureDatas.size(); i++ )
				{
					std::string pic = hero->m_PictureDatas[i].m_Path;
					size_t found;
					found = pic.rfind( '\\' );
					char buff[100];
					sprintf( buff, "%s", pic.substr( found + 1, pic.length() ).c_str() );
					CString str( buff );
					m_wndFileView.InsertItem( str, 2, 2, hHero );
					hero->m_PictureDatas[i].m_TextureID = g_TextureManagerFrame->AddTexture( hero->m_PictureDatas[i].m_Path );
					( ( CMainFrame* )this->GetParentFrame() )->OpenPictureView( str, &hero->m_PictureDatas[i], i,hero );
				}

				m_HeroInfoMap[hHero] = hero;
				g_HeroInfoMap[hero->m_Name] = HeroInfo_Sptr(hero);
				m_wndFileView.Expand( hHeroDoc, TVE_EXPAND );
				g_ActiveFramesMap = &g_HeroInfo->m_FramesMap;
				g_FrameName = "";
				g_FrameIndex = -1;
				( ( CMainFrame* )this->GetParentFrame() )->m_wndClassView.Refresh();
				( ( CMainFrame* )this->GetParentFrame() )->Clear();
			}else{
				AfxMessageBox( _T("Hero HAS been Loaded" ) );
			}
		}
		else
		{
			AfxMessageBox( _T("Lua Loading Failed" ) );
		}
	}
}

void CFileView::OnPaint()
{
	CPaintDC dc( this ); // 繪製的裝置內容
	CRect rectTree;
	m_wndFileView.GetWindowRect( rectTree );
	ScreenToClient( rectTree );
	rectTree.InflateRect( 1, 1 );
	dc.Draw3dRect( rectTree, ::GetSysColor( COLOR_3DSHADOW ), ::GetSysColor( COLOR_3DSHADOW ) );
}

void CFileView::OnSetFocus( CWnd* pOldWnd )
{
	CDockablePane::OnSetFocus( pOldWnd );
	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap( theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 鎖定 */ );
	m_FileViewImages.DeleteImageList();
	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;
	CBitmap bmp;

	if ( !bmp.LoadBitmap( uiBmpId ) )
	{
		TRACE( _T( "無法載入點陣圖: %x\n" ), uiBmpId );
		ASSERT( FALSE );
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap( &bmpObj );
	UINT nFlags = ILC_MASK;
	nFlags |= ( theApp.m_bHiColorIcons ) ? ILC_COLOR24 : ILC_COLOR4;
	m_FileViewImages.Create( 16, bmpObj.bmHeight, nFlags, 0, 0 );
	m_FileViewImages.Add( &bmp, RGB( 255, 0, 255 ) );
	m_wndFileView.SetImageList( &m_FileViewImages, TVSIL_NORMAL );
}

BOOL CFileView::CanFloat() const
{
	return TRUE;
}

BOOL CFileView::CanBeClosed() const
{
	return FALSE;
}

BOOL CFileView::CanAutoHide() const
{
	return FALSE;
}

void CFileView::OnSelectItem( HTREEITEM item )
{
	if ( item == hHeroDoc ) { return; }

	if ( item == hObjectDoc ) { return; }

	if ( item == hAction){
		( ( CMainFrame* )this->GetParentFrame() )->m_wndProperties.InitPropList_Actions(); 
		return;
	}

	HeroInfoHMap::iterator it = m_HeroInfoMap.find( item );

	if ( it != m_HeroInfoMap.end() )
	{
		g_HeroInfo = it->second;
		g_ActiveFramesMap = &g_HeroInfo->m_FramesMap;
		g_FrameName = "";
		g_FrameIndex = -1;
		if (( ( CMainFrame* )this->GetParentFrame() )->NewHeroViews( it->second ))
		{
			for ( unsigned int i = 0; i < it->second->m_PictureDatas.size(); i++ )
			{
				std::string pic = it->second->m_PictureDatas[i].m_Path;
				size_t found;
				found = pic.rfind( '\\' );
				char buff[100];
				sprintf( buff, "%s", pic.substr( found + 1, pic.length() ).c_str() );
				CString str( buff );
				m_wndFileView.InsertItem( str, 2, 2, item );
				it->second ->m_PictureDatas[i].m_TextureID = g_TextureManagerFrame->AddTexture( it->second ->m_PictureDatas[i].m_Path );
				( ( CMainFrame* )this->GetParentFrame() )->OpenPictureView( str, &it->second->m_PictureDatas[i], i, it->second );
			}
		}
		( ( CMainFrame* )this->GetParentFrame() )->m_wndClassView.Refresh();
		( ( CMainFrame* )this->GetParentFrame() )->Clear();
	}
	else
	{
		/*((CMainFrame*)this->GetParentFrame())->SwitchDesigerView(m_wndFileView.GetItemText(item));*/
		HTREEITEM cItem = m_wndFileView.GetChildItem( m_wndFileView.GetParentItem( item ) );
		int i = 0;

		while ( cItem != item && cItem != NULL )
		{
			i++;
			cItem = m_wndFileView.GetNextSiblingItem( cItem );
		}

		( ( CMainFrame* )this->GetParentFrame() )->SwitchPictureView( i );
	}
}

void CFileView::OnPicturedataAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CFileDialog dlgFile( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T( "Data Files (*.bmp;*.png;*.jpg; *.gif)|*.bmp; *.png; *.jpg; *.gif;||" ), NULL, 0 );

	if ( dlgFile.DoModal() == IDOK )
	{
		HeroInfoHMap::iterator it_Hero = m_HeroInfoMap.find( hHero_Select );

		if ( it_Hero == m_HeroInfoMap.end() ) { return; }

		PictureData pic;
		char buff[1000];
		ConvStr::WcharToChar( dlgFile.GetPathName().GetBuffer( 0 ), buff );
		std::string path( buff );
		pic.m_Path = path;
		pic.m_TextureID = g_TextureManagerFrame->AddTexture( path );
		pic.m_Width  = 128;
		pic.m_Height = 128;
		pic.m_Row = 1;
		pic.m_Column = 1;
		m_wndFileView.InsertItem( dlgFile.GetFileName(), 2, 2, hHero_Select );
		it_Hero->second->m_PictureDatas.push_back( pic );
		( ( CMainFrame* )this->GetParentFrame() )->OpenPictureView( dlgFile.GetFileName(), &it_Hero->second->m_PictureDatas.back(), it_Hero->second->m_PictureDatas.size() - 1,it_Hero->second );
	}
}

void CFileView::AddFile( HeroInfo* hero )
{
	g_HeroInfo = hero;
	HTREEITEM hHero = m_wndFileView.InsertItem( CString( hero->m_Name.c_str() ), 2, 2, hHeroDoc );

	if ( ( ( CMainFrame* )this->GetParentFrame() )->NewHeroViews( hero ) )
	{
		for ( unsigned int i = 0; i < hero->m_PictureDatas.size(); i++ )
		{
			std::string pic = hero->m_PictureDatas[i].m_Path;
			size_t found;
			found = pic.rfind( '\\' );
			char buff[100];
			sprintf( buff, "%s", pic.substr( found + 1, pic.length() ).c_str() );
			CString str( buff );
			m_wndFileView.InsertItem( str, 2, 2, hHero );
			hero->m_PictureDatas[i].m_TextureID = g_TextureManagerFrame->AddTexture( hero->m_PictureDatas[i].m_Path );
			( ( CMainFrame* )this->GetParentFrame() )->OpenPictureView( str, &hero->m_PictureDatas[i], i ,hero);
		}

		m_HeroInfoMap[hHero] = hero;
		m_wndFileView.Expand( hHeroDoc, TVE_EXPAND );
		g_ActiveFramesMap = &g_HeroInfo->m_FramesMap;
		g_FrameName = "";
		g_FrameIndex = -1;
		( ( CMainFrame* )this->GetParentFrame() )->m_wndClassView.Refresh();
		( ( CMainFrame* )this->GetParentFrame() )->Clear();
	}
}

void CFileView::LoadData()
{
	g_Actions.LoadData("Script\\Action.lua","Action");

	std::vector<HeroInfo_Sptr> heroInfos;
	heroInfos = LuaResource::LoadLua<HeroInfo>( "hero" );
	for (unsigned int idx = 0; idx < heroInfos.size(); idx++ )
	{
		g_HeroInfoMap[heroInfos[idx]->m_Name] = heroInfos[idx];
		HTREEITEM heroH = m_wndFileView.InsertItem(CString(heroInfos[idx]->m_Name.c_str()),2,2,hResourceHeroDoc);
		m_HeroInfoMap[heroH] = heroInfos[idx].get();
	}

	std::vector<ObjectInfo_Sptr> objectInfos;
	objectInfos = LuaResource::LoadLua<ObjectInfo>( "object" );
	for (unsigned int idx = 0; idx < objectInfos.size(); idx++ )
	{
		g_ObjectInfoMap[objectInfos[idx]->m_Name]=objectInfos[idx];
		m_wndFileView.InsertItem(CString(objectInfos[idx]->m_Name.c_str()),2,2,hResourceObjectDoc);
	}
}

