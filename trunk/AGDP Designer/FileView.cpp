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
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "AGDP Designer.h"
#include "ConvStr.h"

#include "game/HeroInfo.h"
#include "Lua/LuaCell.h"
#include <auto_link_agal.hpp>

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
// CWorkspaceBar �T���B�z�`��

int CFileView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CDockablePane::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	// �إ��˵�:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if ( !m_wndFileView.Create( dwViewStyle, rectDummy, this, 4 ) )
	{
		TRACE0( "�L�k�إ��ɮ��˵�\n" );
		return -1;      // �L�k�إ�
	}

	// ���J�˵��v��:
	m_FileViewImages.Create( IDB_FILE_VIEW, 16, 0, RGB( 255, 0, 255 ) );
	m_wndFileView.SetImageList( &m_FileViewImages, TVSIL_NORMAL );
	m_wndToolBar.Create( this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER );
	m_wndToolBar.LoadToolBar( IDR_EXPLORER, 0, 0, TRUE /* �w��w */ );
	OnChangeVisualStyle();
	m_wndToolBar.SetPaneStyle( m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY );
	m_wndToolBar.SetPaneStyle( m_wndToolBar.GetPaneStyle() & ~( CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT ) );
	m_wndToolBar.SetOwner( this );
	// �Ҧ��R�O���N�g�Ѧ�����ǰe�A�Ӥ��O�g�Ѥ��ج[:
	m_wndToolBar.SetRouteCommandsViaFrame( FALSE );
	// ��J�@���R�A���˵���� (���{���X�A���ݭn����S�O�����e)
	FillFileView();
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
	hHeroDoc = m_wndFileView.InsertItem( _T( "Hero ���" ), 0, 0 );
	m_wndFileView.SetItemState( hHeroDoc, TVIS_BOLD, TVIS_BOLD );
	hObjectDoc = m_wndFileView.InsertItem( _T( "Object ���" ), 0, 0 );
	m_wndFileView.SetItemState( hObjectDoc, TVIS_BOLD, TVIS_BOLD );
	hBackgroundDoc = m_wndFileView.InsertItem( _T( "Background ���" ), 0, 0 );
	m_wndFileView.SetItemState( hBackgroundDoc, TVIS_BOLD, TVIS_BOLD );
	/*
		HTREEITEM hInc = m_wndFileView.InsertItem(_T("FakeApp ���Y��"), 0, 0, hRoot);

		m_wndFileView.InsertItem(_T("FakeApp.h"), 2, 2, hInc);
		m_wndFileView.InsertItem(_T("FakeAppDoc.h"), 2, 2, hInc);
		m_wndFileView.InsertItem(_T("FakeAppView.h"), 2, 2, hInc);
		m_wndFileView.InsertItem(_T("Resource.h"), 2, 2, hInc);
		m_wndFileView.InsertItem(_T("MainFrm.h"), 2, 2, hInc);
		m_wndFileView.InsertItem(_T("StdAfx.h"), 2, 2, hInc);

		HTREEITEM hRes = m_wndFileView.InsertItem(_T("FakeApp �귽��"), 0, 0, hRoot);

		m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hRes);
		m_wndFileView.InsertItem(_T("FakeApp.rc2"), 2, 2, hRes);
		m_wndFileView.InsertItem(_T("FakeAppDoc.ico"), 2, 2, hRes);
		m_wndFileView.InsertItem(_T("FakeToolbar.bmp"), 2, 2, hRes);

		m_wndFileView.Expand(hRoot, TVE_EXPAND);
		m_wndFileView.Expand(hSrc, TVE_EXPAND);
		m_wndFileView.Expand(hInc, TVE_EXPAND);
	*/
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
		// ������U������:
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
	AfxMessageBox( _T( "�ݩ�...." ) );
}

void CFileView::OnFileOpen()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
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
			hero->LoadHeroData( data );

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
				}

				for ( unsigned int i = 0; i < hero->m_PictureDatas.size(); i++ )
				{
					std::string pic = hero->m_PictureDatas[i].m_Path;
					size_t found;
					found = pic.rfind( '\\' );
					char buff[100];
					sprintf( buff, "%s", pic.substr( found + 1, pic.length() ).c_str() );
					CString str( buff );
					hero->m_PictureDatas[i].m_TextureID = g_TextureMG_Frame->AddTexture(hero->m_PictureDatas[i].m_Path);
					( ( CMainFrame* )this->GetParentFrame() )->OpenPictureView( str, &hero->m_PictureDatas[i], i );
					
				}

				m_HeroInfoMap[hHero] = hero;
				m_wndFileView.Expand( hHeroDoc, TVE_EXPAND );
				g_ActiveFramesMap = &g_HeroInfo->m_FramesMap;
				g_FrameName = "";
				g_FrameIndex = -1;
				( ( CMainFrame* )this->GetParentFrame() )->m_wndClassView.Refresh();
				( ( CMainFrame* )this->GetParentFrame() )->Clear();
			}

//			}
		}
		else
		{
			char buff[100];
			sprintf( buff, "Lua Loading Failed" );
			CString str( buff );
			AfxMessageBox( str );
		}
	}
}

void CFileView::OnPaint()
{
	CPaintDC dc( this ); // ø�s���˸m���e
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
	m_wndToolBar.LoadBitmap( theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* ��w */ );
	m_FileViewImages.DeleteImageList();
	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;
	CBitmap bmp;

	if ( !bmp.LoadBitmap( uiBmpId ) )
	{
		TRACE( _T( "�L�k���J�I�}��: %x\n" ), uiBmpId );
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

	if ( item == hBackgroundDoc ) { return; }

	HeroInfohMap::iterator it = m_HeroInfoMap.find( item );

	if ( it != m_HeroInfoMap.end() )
	{
		g_HeroInfo = it->second;
		g_ActiveFramesMap = &g_HeroInfo->m_FramesMap;
		g_FrameName = "";
		g_FrameIndex = -1;
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
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	CFileDialog dlgFile( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T( "Data Files (*.bmp;*.png;*.jpg; *.gif)|*.bmp; *.png; *.jpg; *.gif;||" ), NULL, 0 );

	if ( dlgFile.DoModal() == IDOK )
	{
		HeroInfohMap::iterator it_Hero = m_HeroInfoMap.find( hHero_Select );

		if ( it_Hero == m_HeroInfoMap.end() ) { return; }

		PictureData pic;
		char buff[1000];
		ConvStr::WcharToChar( dlgFile.GetPathName().GetBuffer( 0 ), buff );
		std::string path( buff );
		pic.m_Path = path;
		pic.m_TextureID = g_TextureMG_Frame->AddTexture(path);
		pic.m_Width  = 128;
		pic.m_Height = 128;
		pic.m_Row = 1;
		pic.m_Column = 1;
		m_wndFileView.InsertItem( dlgFile.GetFileName(), 2, 2, hHero_Select );
		it_Hero->second->m_PictureDatas.push_back( pic );
		( ( CMainFrame* )this->GetParentFrame() )->OpenPictureView( dlgFile.GetFileName(), &it_Hero->second->m_PictureDatas.back(), it_Hero->second->m_PictureDatas.size() - 1 );
		
	}
}