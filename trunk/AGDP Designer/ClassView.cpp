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
#include "AGDP Designer.h"
#include <comutil.h>
#include "ConvStr.h"
#include "ClassView.h"
#include "ListDialog.h"
#include "AddListDialog.h"

CClassView* CClassView::instance = NULL;

class CClassViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CClassView;

	DECLARE_SERIAL( CClassViewMenuButton )

public:
	CClassViewMenuButton( HMENU hMenu = NULL ) : CMFCToolBarMenuButton( ( UINT ) - 1, hMenu, -1 )
	{
	}

	virtual void OnDraw( CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
	                     BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE )
	{
		pImages = CMFCToolBar::GetImages();
		CAfxDrawState ds;
		pImages->PrepareDrawImage( ds );
		CMFCToolBarMenuButton::OnDraw( pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons );
		pImages->EndDrawImage( ds );
	}
};

IMPLEMENT_SERIAL( CClassViewMenuButton, CMFCToolBarMenuButton, 1 )

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

BEGIN_MESSAGE_MAP( CClassView, CDockablePane )
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND( ID_ANIMATION_ADD, OnAnimationAdd )
	ON_COMMAND( ID_ANIMATION_DELETE, OnAnimationDelete )
	ON_COMMAND( ID_ANIMATION_RENAME, OnAnimationRename )
	ON_COMMAND( ID_FRAME_ADD, OnFrameAdd )
	ON_COMMAND( ID_FRAME_DELETE, OnFrameDelete )
	ON_COMMAND( ID_PROPERTY_VIEW, OnPropertyView )
	ON_COMMAND( ID_NEW_FOLDER, OnNewFolder )
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONUP()
	ON_COMMAND_RANGE( ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort )
	ON_UPDATE_COMMAND_UI_RANGE( ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort )
	ON_COMMAND( ID_BODY_ADD, &CClassView::OnBodyAdd )
	ON_COMMAND( ID_BODY_DELETE, &CClassView::OnBodyDelete )
	ON_COMMAND( ID_ATTACK_DELETE, &CClassView::OnAttackDelete )
	ON_COMMAND( ID_ATTACK_ADD, &CClassView::OnAttackAdd )
	ON_COMMAND( ID_HITDATA_ADD, &CClassView::OnHitdataAdd )
	ON_COMMAND( ID_HITDATA_DELETE, &CClassView::OnHitdataDelete )
	ON_COMMAND( ID_CATCH_ADD, &CClassView::OnCatchAdd )
	ON_COMMAND( ID_CATCH_DELETE, &CClassView::OnCatchDelete )
	ON_COMMAND( ID_BLOODINFO_ADD, &CClassView::OnBloodinfoAdd )
	ON_COMMAND( ID_BLOODINFO_DELETE, &CClassView::OnBloodinfoDelete )
	ON_COMMAND( ID_CREATION_ADD, &CClassView::OnCreationAdd )
	ON_COMMAND( ID_CREATION_DELETE, &CClassView::OnCreationDelete )
	ON_COMMAND(ID_ADDTOCROUCH, &CClassView::OnAddtocrouch)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassView 訊息處理常式

int CClassView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CDockablePane::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	// 建立檢視:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if ( !m_wndClassView.Create( dwViewStyle, rectDummy, this, 2 ) )
	{
		TRACE0( "無法建立 [類別檢視]\n" );
		return -1;      // 無法建立
	}

	m_wndClassView.SetOwner( this );
	// 載入影像:
	m_wndToolBar.Create( this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT );
	m_wndToolBar.LoadToolBar( IDR_SORT, 0, 0, TRUE /* 已鎖定 */ );
	OnChangeVisualStyle();
	m_wndToolBar.SetPaneStyle( m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY );
	m_wndToolBar.SetPaneStyle( m_wndToolBar.GetPaneStyle() & ~( CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT ) );
	m_wndToolBar.SetOwner( this );
	// 所有命令都將經由此控制項傳送，而不是經由父框架:
	m_wndToolBar.SetRouteCommandsViaFrame( FALSE );
	CMenu menuSort;
	menuSort.LoadMenu( IDR_POPUP_SORT );
	m_wndToolBar.ReplaceButton( ID_SORT_MENU, CClassViewMenuButton( menuSort.GetSubMenu( 0 )->GetSafeHmenu() ) );
	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST( CClassViewMenuButton, m_wndToolBar.GetButton( 0 ) );

	if ( pButton != NULL )
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage( GetCmdMgr()->GetCmdImage( m_nCurrSort ) );
		pButton->SetMessageWnd( this );
	}

	// 填入一些靜態樹狀檢視資料 (假程式碼，不需要什麼特別的內容)
	//FillClassView();
	return 0;
}

void CClassView::OnSize( UINT nType, int cx, int cy )
{
	CDockablePane::OnSize( nType, cx, cy );
	AdjustLayout();
}

void CClassView::FillClassView()
{
	HTREEITEM hRoot = m_wndClassView.InsertItem( _T( "John/Jane Doe" ), 0, 0 );
	m_wndClassView.SetItemState( hRoot, TVIS_BOLD, TVIS_BOLD );
}

void CClassView::OnLButtonUp( UINT nFlags, CPoint point )
{
	CDockablePane::OnLButtonUp( nFlags, point );
	//AfxMessageBox(_T("Click..."));
}

void CClassView::OnContextMenu( CWnd* pWnd, CPoint point )
{
	CTreeCtrl* pWndTree = ( CTreeCtrl* )&m_wndClassView;
	ASSERT_VALID( pWndTree );
	CMenu menu;

	if ( pWnd != pWndTree )
	{
		CDockablePane::OnContextMenu( pWnd, point );
		return;
	}

	m_hTreeItem = NULL;

	if ( point != CPoint( -1, -1 ) )
	{
		// 選取按下的項目:
		CPoint ptTree = point;
		pWndTree->ScreenToClient( &ptTree );
		UINT flags = 0;
		m_hTreeItem = pWndTree->HitTest( ptTree, &flags );
	}
	else
	{
		m_hTreeItem = pWndTree->GetSelectedItem();
	}

	if ( m_hTreeItem != NULL )
	{
		pWndTree->SelectItem( m_hTreeItem );

		if ( pWndTree->GetRootItem() == m_hTreeItem )
		{
			menu.LoadMenu( IDR_POPUP_CHARACTER_EDIT );
		}
		else if ( IsAnAnimation( pWndTree, m_hTreeItem ) )
		{
			menu.LoadMenu( IDR_POPUP_ANIMATION_EDIT );
		}
		else if ( IsAnAnimation( pWndTree, m_wndClassView.GetParentItem( m_hTreeItem ) ) )
		{
			menu.LoadMenu( IDR_POPUP_FRAME_EDIT );
		}
		else if ( pWndTree->GetItemText( m_hTreeItem ) == CString( "Bodys" ) )
		{
			menu.LoadMenu( IDR_POPUP_BODYADD );
		}
		else if ( pWndTree->GetItemText( m_hTreeItem ) == CString( "Attacks" ) )
		{
			menu.LoadMenu( IDR_POPUP_ATTACKADD );
		}
		else if ( pWndTree->GetItemText( m_hTreeItem ) == CString( "HitDatas" ) )
		{
			menu.LoadMenu( IDR_POPUP_HITDATAADD );
		}
		else if ( pWndTree->GetItemText( m_hTreeItem ) == CString( "Catchs" ) )
		{
			menu.LoadMenu( IDR_POPUP_CATCHADD );
		}
		else if ( pWndTree->GetItemText( m_hTreeItem ) == CString( "BloodInfos" ) )
		{
			menu.LoadMenu( IDR_POPUP_BLOODINFOADD );
		}
		else if ( pWndTree->GetItemText( m_hTreeItem ) == CString( "Creations" ) )
		{
			menu.LoadMenu( IDR_POPUP_CREATIONADD );
		}
		else if ( pWndTree->GetItemText( m_wndClassView.GetParentItem( m_hTreeItem ) ) == CString( "Bodys" ) )
		{
			menu.LoadMenu( IDR_POPUP_BODYDELETE );
		}
		else if ( pWndTree->GetItemText( m_wndClassView.GetParentItem( m_hTreeItem ) ) == CString( "Attacks" ) )
		{
			menu.LoadMenu( IDR_POPUP_ATTACKDELETE );
		}
		else if ( pWndTree->GetItemText( m_wndClassView.GetParentItem( m_hTreeItem ) ) == CString( "HitDatas" ) )
		{
			menu.LoadMenu( IDR_POPUP_HITDATADELETE );
		}
		else if ( pWndTree->GetItemText( m_wndClassView.GetParentItem( m_hTreeItem ) ) == CString( "Catchs" ) )
		{
			menu.LoadMenu( IDR_POPUP_CATCHDELETE );
		}
		else if ( pWndTree->GetItemText( m_wndClassView.GetParentItem( m_hTreeItem ) ) == CString( "BloodInfos" ) )
		{
			menu.LoadMenu( IDR_POPUP_BLOODINFODELETE );
		}
		else if ( pWndTree->GetItemText( m_wndClassView.GetParentItem( m_hTreeItem ) ) == CString( "Creations" ) )
		{
			menu.LoadMenu( IDR_POPUP_CREATIONDELETE );
		}
	}
	else
	{
		menu.LoadMenu( IDR_POPUP_SORT );
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

void CClassView::AdjustLayout()
{
	if ( GetSafeHwnd() == NULL )
	{
		return;
	}

	CRect rectClient;
	GetClientRect( rectClient );
	int cyTlb = m_wndToolBar.CalcFixedLayout( FALSE, TRUE ).cy;
	m_wndToolBar.SetWindowPos( NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER );
	m_wndClassView.SetWindowPos( NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER );
}

BOOL CClassView::PreTranslateMessage( MSG* pMsg )
{
	return CDockablePane::PreTranslateMessage( pMsg );
}

void CClassView::OnSort( UINT id )
{
	if ( m_nCurrSort == id )
	{
		return;
	}

	m_nCurrSort = id;
	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST( CClassViewMenuButton, m_wndToolBar.GetButton( 0 ) );

	if ( pButton != NULL )
	{
		pButton->SetImage( GetCmdMgr()->GetCmdImage( id ) );
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}
}

void CClassView::OnUpdateSort( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck( pCmdUI->m_nID == m_nCurrSort );
}

int num = 0;
void CClassView::OnAnimationAdd()
{
	CAddListDialog dialog;
	if (dialog.DoModal() == IDOK)
	{
		if (g_ActiveFramesMap->find(dialog.m_Text)==g_ActiveFramesMap->end())
		{
			HTREEITEM root = m_wndClassView.GetRootItem();
			std::wstring frameName = dialog.m_Text;
			if ( g_ActiveFramesMap != NULL )
			{
				( *g_ActiveFramesMap )[frameName] = FrameInfos();
				HTREEITEM item = m_wndClassView.InsertItem( CString(frameName.c_str()), 1, 1, root );
				( *g_ActiveFramesMap )[frameName].push_back( defaultFrameInfo( item ) );
				wchar_t buff[100];
				wsprintf( buff, L"%d", 0 );
				CString str( buff );
				HTREEITEM hClass =  m_wndClassView.InsertItem( str, 3, 3, item );
				m_wndClassView.InsertItem( _T( "Bodys" ), 3, 3, hClass );
				m_wndClassView.InsertItem( _T( "Attacks" ), 3, 3, hClass );
				m_wndClassView.InsertItem( _T( "HitDatas" ), 3, 3, hClass );
				m_wndClassView.InsertItem( _T( "Catchs" ), 3, 3, hClass );
				m_wndClassView.InsertItem( _T( "BloodInfos" ), 3, 3, hClass );
				m_wndClassView.InsertItem( _T( "Creations" ), 3, 3, hClass );
				m_wndClassView.Expand( root, TVE_EXPAND );
				m_wndClassView.ModifyStyle( 0, TVS_EDITLABELS );
				m_wndClassView.EditLabel( item );
				num++;
				//Refresh
				g_FrameName = frameName;
				g_FrameIndex = 0;
				( ( CMainFrame* )this->GetParentFrame() )->RefreshFrameEdit();
				( ( CMainFrame* )this->GetParentFrame() )->m_wndProperties.RefreshPropList_Frame();
			}
		}else{
			AfxMessageBox(L"SAME Animation Name");
		}
	}
}




void CClassView::OnAnimationRename()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();

	if ( item != NULL )
	{
		m_wndClassView.ModifyStyle( 0, TVS_EDITLABELS );
		m_wndClassView.EditLabel( item );
	}
}

void CClassView::OnAnimationDelete()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();

	if ( item != NULL )
	{
		std::wstring str( m_wndClassView.GetItemText( item ) );
		g_ActiveFramesMap->erase( g_ActiveFramesMap->find( str ) );
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = m_wndClassView.GetChildItem( item );

		while ( hChildItem != NULL )
		{
			hNextItem = m_wndClassView.GetNextItem( hChildItem, TVGN_NEXT );
			RemoveTreeItem( hChildItem );
			m_wndClassView.DeleteItem( hChildItem );
			hChildItem = hNextItem;
		}

		m_wndClassView.DeleteItem( item );

		//Clear
		if ( g_FrameName == str )
		{
			g_FrameName = L"";
			g_FrameIndex = -1;
			( ( CMainFrame* )this->GetParentFrame() )->Clear();
		}
	}
}

void CClassView::OnFrameAdd()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();

	if ( item != NULL )
	{
		std::wstring frameName( m_wndClassView.GetItemText( item ) );
		int index = ( *g_ActiveFramesMap )[frameName].size();
		FrameInfo fi = defaultFrameInfo( item );
		fi.m_FrameIndex = index;
		( *g_ActiveFramesMap )[frameName].push_back( fi );
		char buff[100];
		sprintf( buff, "%d", index );
		CString str( buff );
		HTREEITEM hClass =  m_wndClassView.InsertItem( str, 3, 3, item );
		m_wndClassView.InsertItem( _T( "Bodys" ), 3, 3, hClass );
		m_wndClassView.InsertItem( _T( "Attacks" ), 3, 3, hClass );
		m_wndClassView.InsertItem( _T( "HitDatas" ), 3, 3, hClass );
		m_wndClassView.InsertItem( _T( "Catchs" ), 3, 3, hClass );
		m_wndClassView.InsertItem( _T( "BloodInfos" ), 3, 3, hClass );
		m_wndClassView.InsertItem( _T( "Creations" ), 3, 3, hClass );
		m_wndClassView.Expand( item, TVE_EXPAND );
		g_FrameName = frameName;
		g_FrameIndex = index;
		( ( CMainFrame* )this->GetParentFrame() )->RefreshFrameEdit();
		( ( CMainFrame* )this->GetParentFrame() )->m_wndProperties.RefreshPropList_Frame();
	}
}

void CClassView::OnFrameDelete()
{
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int count = _ttoi( m_wndClassView.GetItemText( item ) );
	std::wstring frameName(  m_wndClassView.GetItemText( m_wndClassView.GetParentItem( item ) )  );
	( *g_ActiveFramesMap )[frameName].erase( ( *g_ActiveFramesMap )[frameName].begin() + count );

	if ( item != NULL )
	{
		HTREEITEM tmp_item = m_wndClassView.GetNextSiblingItem( item );

		for ( int i = count;; i++ )
		{
			if ( tmp_item != NULL )
			{
				TCHAR num_str[10];
				wsprintf( num_str, _T( "%d" ), i );
				m_wndClassView.SetItemText( tmp_item, num_str );
				tmp_item = m_wndClassView.GetNextSiblingItem( tmp_item );
			}
			else { break; }
		}

		m_wndClassView.DeleteItem( item );

		//Clear
		if ( g_FrameName == frameName && g_FrameIndex == count )
		{
			( ( CMainFrame* )this->GetParentFrame() )->Clear();
		}
	}
}

void CClassView::OnPropertyView()
{
}

void CClassView::OnNewFolder()
{
	AfxMessageBox( _T( "新增資料夾..." ) );
}

void CClassView::OnPaint()
{
	CPaintDC dc( this ); // 繪製的裝置內容
	CRect rectTree;
	m_wndClassView.GetWindowRect( rectTree );
	ScreenToClient( rectTree );
	rectTree.InflateRect( 1, 1 );
	dc.Draw3dRect( rectTree, ::GetSysColor( COLOR_3DSHADOW ), ::GetSysColor( COLOR_3DSHADOW ) );
}

void CClassView::OnSetFocus( CWnd* pOldWnd )
{
	CDockablePane::OnSetFocus( pOldWnd );
	m_wndClassView.SetFocus();
}

void CClassView::OnChangeVisualStyle()
{
	m_ClassViewImages.DeleteImageList();
	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;
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
	m_ClassViewImages.Create( 16, bmpObj.bmHeight, nFlags, 0, 0 );
	m_ClassViewImages.Add( &bmp, RGB( 255, 0, 0 ) );
	m_wndClassView.SetImageList( &m_ClassViewImages, TVSIL_NORMAL );
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap( theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* 鎖定 */ );
}

void CClassView::OnSelectItem( HTREEITEM item )
{
	CPropertiesWnd* _propWnd = CPropertiesWnd::GetInstance();

	if(item == NULL)
	{
		_propWnd->SwitchCommandManager(item);
		return;
	}

	HTREEITEM pItem = m_wndClassView.GetParentItem( item );

	_propWnd->SwitchCommandManager(item);

	if ( m_wndClassView.GetRootItem() == item )
	{
		m_wndClassView.SelectItem( item );
		m_wndClassView.SetFocus();
		( ( CMainFrame* )( this->GetParentFrame() ) )->m_wndProperties.InitPropList_Hero();
	}
	else if ( IsNumber( m_wndClassView.GetItemText( item ) ) )
	{
		HTREEITEM pItem = m_wndClassView.GetParentItem( item );

		if ( pItem != m_wndClassView.GetRootItem() )
		{
			CString text = m_wndClassView.GetItemText( pItem );

			if ( !text.Compare( CString( "Bodys" ) ) )
			{
				HTREEITEM FrameIndex = m_wndClassView.GetParentItem( pItem );
				HTREEITEM Frame	     = m_wndClassView.GetParentItem( FrameIndex );
				std::wstring FrameName(  m_wndClassView.GetItemText( Frame ).GetBuffer( 0 ) );

				if ( g_FrameName != FrameName || g_FrameIndex != _ttoi( m_wndClassView.GetItemText( FrameIndex ) ) )
				{
					g_FrameName = FrameName;
					g_FrameIndex = _ttoi( m_wndClassView.GetItemText( FrameIndex ) );
					( ( CMainFrame* )( this->GetParentFrame() ) )->RefreshFrameEdit();
				}

				( ( CMainFrame* )( this->GetParentFrame() ) )->EditBody( _ttoi( m_wndClassView.GetItemText( item ) ) );
			}
			else if ( !text.Compare( CString( "Attacks" ) ) )
			{
				HTREEITEM FrameIndex = m_wndClassView.GetParentItem( pItem );
				HTREEITEM Frame	     = m_wndClassView.GetParentItem( FrameIndex );
				std::wstring FrameName( m_wndClassView.GetItemText( Frame ).GetBuffer( 0 ) );

				if ( g_FrameName != FrameName || g_FrameIndex != _ttoi( m_wndClassView.GetItemText( FrameIndex ) ) )
				{
					g_FrameName = FrameName;
					g_FrameIndex = _ttoi( m_wndClassView.GetItemText( FrameIndex ) );
					( ( CMainFrame* )( this->GetParentFrame() ) )->RefreshFrameEdit();
				}

				( ( CMainFrame* )( this->GetParentFrame() ) )->EditAttack( _ttoi( m_wndClassView.GetItemText( item ) ) );
			}
			else if ( !text.Compare( CString( "HitDatas" ) ) )
			{
				HTREEITEM FrameIndex = m_wndClassView.GetParentItem( pItem );
				HTREEITEM Frame	     = m_wndClassView.GetParentItem( FrameIndex );
				std::wstring FrameName(  m_wndClassView.GetItemText( Frame ).GetBuffer( 0 ) );

				if ( g_FrameName != FrameName || g_FrameIndex != _ttoi( m_wndClassView.GetItemText( FrameIndex ) ) )
				{
					g_FrameName = FrameName;
					g_FrameIndex = _ttoi( m_wndClassView.GetItemText( FrameIndex ) );
					( ( CMainFrame* )( this->GetParentFrame() ) )->RefreshFrameEdit();
				}

				( ( CMainFrame* )( this->GetParentFrame() ) )->m_wndProperties.RefreshPropList_HitData(_ttoi( m_wndClassView.GetItemText( item ) ));
			}
			else if ( !text.Compare( CString( "Catchs" ) ) )
			{
				HTREEITEM FrameIndex = m_wndClassView.GetParentItem( pItem );
				HTREEITEM Frame	     = m_wndClassView.GetParentItem( FrameIndex );
				std::wstring FrameName(  m_wndClassView.GetItemText( Frame ).GetBuffer( 0 ) );

				if ( g_FrameName != FrameName || g_FrameIndex != _ttoi( m_wndClassView.GetItemText( FrameIndex ) ) )
				{
					g_FrameName = FrameName;
					g_FrameIndex = _ttoi( m_wndClassView.GetItemText( FrameIndex ) );
					( ( CMainFrame* )( this->GetParentFrame() ) )->RefreshFrameEdit();
				}

				( ( CMainFrame* )( this->GetParentFrame() ) )->EditCatch( _ttoi( m_wndClassView.GetItemText( item ) ) );
			}
			else if ( !text.Compare( CString( "BloodInfos" ) ) )
			{
			}
			else if ( !text.Compare( CString( "Creations" ) ) )
			{
				HTREEITEM FrameIndex = m_wndClassView.GetParentItem( pItem );
				HTREEITEM Frame	     = m_wndClassView.GetParentItem( FrameIndex );
				std::wstring FrameName( m_wndClassView.GetItemText( Frame ).GetBuffer( 0 ) );

				if ( g_FrameName != FrameName || g_FrameIndex != _ttoi( m_wndClassView.GetItemText( FrameIndex ) ) )
				{
					g_FrameName = FrameName;
					g_FrameIndex = _ttoi( m_wndClassView.GetItemText( FrameIndex ) );
					( ( CMainFrame* )( this->GetParentFrame() ) )->RefreshFrameEdit();
				}

				( ( CMainFrame* )( this->GetParentFrame() ) )->EditCreation( _ttoi( m_wndClassView.GetItemText( item ) ) );
			}
			else
			{
				std::wstring FrameName( text.GetBuffer( 0 ) );

				if ( g_ActiveFramesMap->find( FrameName ) != g_ActiveFramesMap->end() )
				{
					g_FrameName = FrameName;
					g_FrameIndex = _ttoi( m_wndClassView.GetItemText( item ) );
					_propWnd->InitPropList_Frame();
					( ( CMainFrame* )( this->GetParentFrame() ) )->RefreshFrameEdit();
					( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditableCenter();
				}
			}

			m_wndClassView.SelectItem( item );
			m_wndClassView.SetFocus();
		}
	}
}

BOOL CClassView::IsAnAnimation( CTreeCtrl* treeCtrl, HTREEITEM item )
{
	return treeCtrl->GetParentItem( item ) == treeCtrl->GetRootItem();
}

BOOL CClassView::IsNumber( CString str )
{
	for ( int i = 0; i < str.GetLength(); i++ )
		if ( str.GetAt( i ) > '9' || str.GetAt( i ) < '0' )
		{
			return FALSE;
		}

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

TreeItemMap& CClassView::GetPropMap()
{
	return m_propMap;
}

void CClassView::RemoveTreeItem( HTREEITEM item )
{
	TreeItemMap::iterator it = m_propMap.find( item );

	if ( it != m_propMap.end() )
	{
		m_propMap.erase( it );
	}
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
	if ( g_HeroInfo != NULL )
	{
		m_wndClassView.DeleteItem( m_wndClassView.GetRootItem() );
		char buff[100];
		CString str( g_HeroInfo->m_Name.c_str() );
		HTREEITEM hRoot = m_wndClassView.InsertItem( str, 0, 0 );
		m_wndClassView.SetItemState( hRoot, TVIS_BOLD, TVIS_BOLD );

		for ( FramesMap::iterator it_FrameMap = g_HeroInfo->m_FramesMap.begin(); it_FrameMap != g_HeroInfo->m_FramesMap.end() ; it_FrameMap++ )
		{
			str = CString( it_FrameMap->first.c_str() );
			HTREEITEM hChild = m_wndClassView.InsertItem( str, 1, 1, hRoot );

			for ( unsigned int i = 0; i < it_FrameMap->second.size() ; i++ )
			{
				sprintf( buff, "%d", i );
				str = CString( buff );
				HTREEITEM hChild2 = m_wndClassView.InsertItem( str, 3, 3, hChild );
				HTREEITEM hChild_Bodys		= m_wndClassView.InsertItem( _T( "Bodys" ), 3, 3, hChild2 );
				HTREEITEM hChild_Attacks	= m_wndClassView.InsertItem( _T( "Attacks" ), 3, 3, hChild2 );
				HTREEITEM hChild_HitDatas	= m_wndClassView.InsertItem( _T( "HitDatas" ), 3, 3, hChild2 );
				HTREEITEM hChild_Catchs		= m_wndClassView.InsertItem( _T( "Catchs" ), 3, 3, hChild2 );
				HTREEITEM hChild_BloodInfos	= m_wndClassView.InsertItem( _T( "BloodInfos" ), 3, 3, hChild2 );
				HTREEITEM hChild_Creations	= m_wndClassView.InsertItem( _T( "Creations" ), 3, 3, hChild2 );

				for ( unsigned int j = 0; j < it_FrameMap->second[i].m_Bodys.size() ; j++ )
				{
					sprintf( buff, "%d", j );
					str = CString( buff );
					m_wndClassView.InsertItem( str, 3, 3, hChild_Bodys );
				}

				for ( unsigned int j = 0; j < it_FrameMap->second[i].m_Attacks.size() ; j++ )
				{
					sprintf( buff, "%d", j );
					str = CString( buff );
					m_wndClassView.InsertItem( str, 3, 3, hChild_Attacks );
				}

				for ( unsigned int j = 0; j < it_FrameMap->second[i].m_HitDatas.size() ; j++ )
				{
					sprintf( buff, "%d", j );
					str = CString( buff );
					m_wndClassView.InsertItem( str, 3, 3, hChild_HitDatas );
				}

				for ( unsigned int j = 0; j < it_FrameMap->second[i].m_Catchs.size() ; j++ )
				{
					sprintf( buff, "%d", j );
					str = CString( buff );
					m_wndClassView.InsertItem( str, 3, 3, hChild_Catchs );
				}

				for ( unsigned int j = 0; j < it_FrameMap->second[i].m_BloodInfos.size() ; j++ )
				{
					sprintf( buff, "%d", j );
					str = CString( buff );
					m_wndClassView.InsertItem( str, 3, 3, hChild_BloodInfos );
				}

				for ( unsigned int j = 0; j < it_FrameMap->second[i].m_Creations.size() ; j++ )
				{
					sprintf( buff, "%d", j );
					str = CString( buff );
					m_wndClassView.InsertItem( str, 3, 3, hChild_Creations );
				}
			}
		}
	}
}

FrameInfo CClassView::defaultFrameInfo( HTREEITEM item )
{
	FrameInfo fi;
	fi.m_FrameName = std::wstring( m_wndClassView.GetItemText( item ) );;
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

void CClassView::OnBodyAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int frameIndex = _ttoi( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( item ) ) );
	std::wstring frameName( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) );
	Body body;
	body.m_Area.Clear();
	body.m_Kind = 1;
	body.m_ZWidth = 1;
	( *g_ActiveFramesMap )[frameName][frameIndex].m_Bodys.push_back( body );
	wchar_t buff[100];
	wsprintf( buff, L"%d", ( *g_ActiveFramesMap )[frameName][frameIndex].m_Bodys.size() - 1 );
	CString str( buff );
	m_wndClassView.InsertItem( str , 3, 3, item );
	m_wndClassView.Expand( item, TVE_EXPAND );

	if ( g_ActiveFramesMap->find( g_FrameName ) != g_ActiveFramesMap->end() )
	{
		if ( g_FrameIndex > -1 && g_FrameIndex < (int)g_ActiveFramesMap->find( g_FrameName )->second.size() )
		{
			( ( CMainFrame* )this->GetParentFrame() )->m_D3DFrameView.Refresh();
		}
	}
}

void CClassView::OnBodyDelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int count = _ttoi( m_wndClassView.GetItemText( item ) );
	int frameIndex = _ttoi( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) );
	std::wstring frameName(  m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) ) );
	( *g_ActiveFramesMap )[frameName][frameIndex].m_Bodys.erase( ( *g_ActiveFramesMap )[frameName][frameIndex].m_Bodys.begin() + count );

	if ( item != NULL )
	{
		HTREEITEM tmp_item = m_wndClassView.GetNextSiblingItem( item );

		for ( int i = count;; i++ )
		{
			if ( tmp_item != NULL )
			{
				TCHAR num_str[10];
				wsprintf( num_str, _T( "%d" ), i );
				m_wndClassView.SetItemText( tmp_item, num_str );
				tmp_item = m_wndClassView.GetNextSiblingItem( tmp_item );
			}
			else { break; }
		}

		m_wndClassView.DeleteItem( item );

		//Clear
		if ( g_FrameName == frameName && g_FrameIndex == count )
		{
			( ( CMainFrame* )this->GetParentFrame() )->Clear();
		}
	}

	if ( g_ActiveFramesMap->find( g_FrameName ) != g_ActiveFramesMap->end() )
	{
		if ( g_FrameIndex > -1 && g_FrameIndex < (int)g_ActiveFramesMap->find( g_FrameName )->second.size() )
		{
			( ( CMainFrame* )this->GetParentFrame() )->m_D3DFrameView.Refresh();
		}
	}
}

void CClassView::OnAttackDelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int count = _ttoi( m_wndClassView.GetItemText( item ) );
	int frameIndex = _ttoi( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) );
	std::wstring frameName( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) ) );
	( *g_ActiveFramesMap )[frameName][frameIndex].m_Attacks.erase( ( *g_ActiveFramesMap )[frameName][frameIndex].m_Attacks.begin() + count );

	if ( item != NULL )
	{
		HTREEITEM tmp_item = m_wndClassView.GetNextSiblingItem( item );

		for ( int i = count;; i++ )
		{
			if ( tmp_item != NULL )
			{
				TCHAR num_str[10];
				wsprintf( num_str, _T( "%d" ), i );
				m_wndClassView.SetItemText( tmp_item, num_str );
				tmp_item = m_wndClassView.GetNextSiblingItem( tmp_item );
			}
			else { break; }
		}

		m_wndClassView.DeleteItem( item );

		//Clear
		if ( g_FrameName == frameName && g_FrameIndex == count )
		{
			( ( CMainFrame* )this->GetParentFrame() )->Clear();
		}
	}

	if ( g_ActiveFramesMap->find( g_FrameName ) != g_ActiveFramesMap->end() )
	{
		if ( g_FrameIndex > -1 && g_FrameIndex < (int)g_ActiveFramesMap->find( g_FrameName )->second.size() )
		{
			( ( CMainFrame* )this->GetParentFrame() )->m_D3DFrameView.Refresh();
		}
	}
}

void CClassView::OnAttackAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int frameIndex = _ttoi( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( item ) ) );
	std::wstring frameName( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) );
	Attack atk;
	atk.m_Kind = 1;
	atk.m_ZWidth = 1;
	atk.m_AttackRest = 0;
	atk.m_ReAttackRest = 0;
	atk.m_DVX = 0;
	atk.m_DVY = 0;
	atk.m_DVZ = 0;
	atk.m_Effect = 0;
	atk.m_Fall = 0;
	atk.m_Injury = 0;
	atk.m_BreakDefend = 0;
	atk.m_Strength = 0;
	( *g_ActiveFramesMap )[frameName][frameIndex].m_Attacks.push_back( atk );
	wchar_t buff[100];
	wsprintf( buff, L"%d", ( *g_ActiveFramesMap )[frameName][frameIndex].m_Attacks.size() - 1 );
	CString str( buff );
	m_wndClassView.InsertItem( str , 3, 3, item );
	m_wndClassView.Expand( item, TVE_EXPAND );

	if ( g_ActiveFramesMap->find( g_FrameName ) != g_ActiveFramesMap->end() )
	{
		if ( g_FrameIndex > -1 && g_FrameIndex < (int)g_ActiveFramesMap->find( g_FrameName )->second.size() )
		{
			( ( CMainFrame* )this->GetParentFrame() )->m_D3DFrameView.Refresh();
		}
	}
}


void CClassView::OnHitdataAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int frameIndex = _ttoi( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( item ) ) );
	std::wstring frameName( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) );
	HitData h;
	h.m_FrameName = L"default";
	h.m_FrameOffset = 0;
	( *g_ActiveFramesMap )[frameName][frameIndex].m_HitDatas.push_back( h );
	wchar_t buff[100];
	wsprintf( buff, L"%d", ( *g_ActiveFramesMap )[frameName][frameIndex].m_HitDatas.size() - 1 );
	CString str( buff );
	m_wndClassView.InsertItem( str , 3, 3, item );
	m_wndClassView.Expand( item, TVE_EXPAND );

	if ( g_ActiveFramesMap->find( g_FrameName ) != g_ActiveFramesMap->end() )
	{
		if ( g_FrameIndex > -1 && g_FrameIndex < (int)g_ActiveFramesMap->find( g_FrameName )->second.size() )
		{
			( ( CMainFrame* )this->GetParentFrame() )->m_D3DFrameView.Refresh();
		}
	}
}


void CClassView::OnHitdataDelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int count = _ttoi( m_wndClassView.GetItemText( item ) );
	int frameIndex = _ttoi( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) );
	std::wstring frameName( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) ) );
	( *g_ActiveFramesMap )[frameName][frameIndex].m_HitDatas.erase( ( *g_ActiveFramesMap )[frameName][frameIndex].m_HitDatas.begin() + count );

	if ( item != NULL )
	{
		HTREEITEM tmp_item = m_wndClassView.GetNextSiblingItem( item );

		for ( int i = count;; i++ )
		{
			if ( tmp_item != NULL )
			{
				TCHAR num_str[10];
				wsprintf( num_str, _T( "%d" ), i );
				m_wndClassView.SetItemText( tmp_item, num_str );
				tmp_item = m_wndClassView.GetNextSiblingItem( tmp_item );
			}
			else { break; }
		}

		m_wndClassView.DeleteItem( item );

		//Clear
		if ( g_FrameName == frameName && g_FrameIndex == count )
		{
			( ( CMainFrame* )this->GetParentFrame() )->Clear();
		}
	}

	if ( g_ActiveFramesMap->find( g_FrameName ) != g_ActiveFramesMap->end() )
	{
		if ( g_FrameIndex > -1 && g_FrameIndex < (int)g_ActiveFramesMap->find( g_FrameName )->second.size() )
		{
			( ( CMainFrame* )this->GetParentFrame() )->m_D3DFrameView.Refresh();
		}
	}
}


void CClassView::OnCatchAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int frameIndex = _ttoi( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( item ) ) );
	std::wstring frameName( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) );
	CatchInfo c;
	c.m_Kind = 0;
	c.m_ZWidth = 1;
	c.m_Injury = 0;
	c.m_Strong = 0;
	c.m_CatchPosition.x = 0;
	c.m_CatchPosition.y = 0;
	c.m_CatchWhere = CatchInfo::CatchPosition::NECK;
	( *g_ActiveFramesMap )[frameName][frameIndex].m_Catchs.push_back( c );
	wchar_t buff[100];
	wsprintf( buff, L"%d", ( *g_ActiveFramesMap )[frameName][frameIndex].m_Catchs.size() - 1 );
	CString str( buff );
	m_wndClassView.InsertItem( str , 3, 3, item );
	m_wndClassView.Expand( item, TVE_EXPAND );

	if ( g_ActiveFramesMap->find( g_FrameName ) != g_ActiveFramesMap->end() )
	{
		if ( g_FrameIndex > -1 && g_FrameIndex < (int)g_ActiveFramesMap->find( g_FrameName )->second.size() )
		{
			( ( CMainFrame* )this->GetParentFrame() )->m_D3DFrameView.Refresh();
		}
	}
}


void CClassView::OnCatchDelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int count = _ttoi( m_wndClassView.GetItemText( item ) );
	int frameIndex = _ttoi( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) );
	std::wstring frameName( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) ) );
	( *g_ActiveFramesMap )[frameName][frameIndex].m_Catchs.erase( ( *g_ActiveFramesMap )[frameName][frameIndex].m_Catchs.begin() + count );

	if ( item != NULL )
	{
		HTREEITEM tmp_item = m_wndClassView.GetNextSiblingItem( item );

		for ( int i = count;; i++ )
		{
			if ( tmp_item != NULL )
			{
				TCHAR num_str[10];
				wsprintf( num_str, _T( "%d" ), i );
				m_wndClassView.SetItemText( tmp_item, num_str );
				tmp_item = m_wndClassView.GetNextSiblingItem( tmp_item );
			}
			else { break; }
		}

		m_wndClassView.DeleteItem( item );

		//Clear
		if ( g_FrameName == frameName && g_FrameIndex == count )
		{
			( ( CMainFrame* )this->GetParentFrame() )->Clear();
		}
	}

	if ( g_ActiveFramesMap->find( g_FrameName ) != g_ActiveFramesMap->end() )
	{
		if ( g_FrameIndex > -1 && g_FrameIndex < (int)g_ActiveFramesMap->find( g_FrameName )->second.size() )
		{
			( ( CMainFrame* )this->GetParentFrame() )->m_D3DFrameView.Refresh();
		}
	}
}


void CClassView::OnBloodinfoAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


void CClassView::OnBloodinfoDelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


void CClassView::OnCreationAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int frameIndex = _ttoi( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( item ) ) );
	std::wstring frameName( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) );
	Creation c;
	c.name = g_HeroInfo->m_Name;
	c.frame = L"default";
	c.frameID = 0;
	c.facing = 0;
	c.HP = 1;
	c.amount = 1;
	c.x = 0;
	c.y = 0;
	c.v0.x = 0;
	c.v0.y = 0;
	c.v0.z = 0;
	( *g_ActiveFramesMap )[frameName][frameIndex].m_Creations.push_back( c );
	wchar_t buff[100];
	wsprintf( buff, L"%d", ( *g_ActiveFramesMap )[frameName][frameIndex].m_Creations.size() - 1 );
	CString str( buff );
	m_wndClassView.InsertItem( str , 3, 3, item );
	m_wndClassView.Expand( item, TVE_EXPAND );

	if ( g_ActiveFramesMap->find( g_FrameName ) != g_ActiveFramesMap->end() )
	{
		if ( g_FrameIndex > -1 && g_FrameIndex < (int)g_ActiveFramesMap->find( g_FrameName )->second.size() )
		{
			( ( CMainFrame* )this->GetParentFrame() )->m_D3DFrameView.Refresh();
		}
	}
}


void CClassView::OnCreationDelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
	HTREEITEM item = m_wndClassView.GetSelectedItem();
	int count = _ttoi( m_wndClassView.GetItemText( item ) );
	int frameIndex = _ttoi( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) );
	std::wstring frameName( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( m_wndClassView.GetParentItem( item ) ) ) ) );
	( *g_ActiveFramesMap )[frameName][frameIndex].m_Creations.erase( ( *g_ActiveFramesMap )[frameName][frameIndex].m_Creations.begin() + count );

	if ( item != NULL )
	{
		HTREEITEM tmp_item = m_wndClassView.GetNextSiblingItem( item );

		for ( int i = count;; i++ )
		{
			if ( tmp_item != NULL )
			{
				TCHAR num_str[10];
				wsprintf( num_str, _T( "%d" ), i );
				m_wndClassView.SetItemText( tmp_item, num_str );
				tmp_item = m_wndClassView.GetNextSiblingItem( tmp_item );
			}
			else { break; }
		}

		m_wndClassView.DeleteItem( item );

		//Clear
		if ( g_FrameName == frameName && g_FrameIndex == count )
		{
			( ( CMainFrame* )this->GetParentFrame() )->Clear();
		}
	}

	if ( g_ActiveFramesMap->find( g_FrameName ) != g_ActiveFramesMap->end() )
	{
		if ( g_FrameIndex > -1 && g_FrameIndex < (int)g_ActiveFramesMap->find( g_FrameName )->second.size() )
		{
			( ( CMainFrame* )this->GetParentFrame() )->m_D3DFrameView.Refresh();
		}
	}
}


void CClassView::OnAddtocrouch()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CListDialog actions = new CListDialog();
	for (LuaMap::iterator it = g_Actions.begin(); it != g_Actions.end(); it++)
	{
		actions.AddList(it->second);
	}
	
	if (actions.DoModal()==IDOK)
	{
		int idx = g_Actions.FindKey(actions.m_Select);
		if (idx==-1)return;
		HTREEITEM pItem = m_wndClassView.GetParentItem( m_hTreeItem );
 		g_HeroInfo->m_CrouchMap[idx] = CrouchData();
 		g_HeroInfo->m_CrouchMap[idx].m_FrameName =  std::wstring(m_wndClassView.GetItemText( pItem ).GetBuffer(0));
 		g_HeroInfo->m_CrouchMap[idx].m_FrameOffset = _ttoi(m_wndClassView.GetItemText( m_hTreeItem ));
		( ( CMainFrame* )this->GetParentFrame() )->m_wndProperties.InitPropList_Hero();
	}
}
