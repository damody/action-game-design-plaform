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
#include <game/HeroAction.h>
#include "ConvStr.h"
#include "ClassView.h"

CClassView* CClassView::instance = NULL;

const CString CClassView::anims[MAX_ANIMATIONS] =
{
	CString( "standing" ),
	CString( "walking" ),
	CString( "running" ),
	CString( "stop_running" ),
	CString( "heavy_weapon_walk" ),
	CString( "heavy_weapon_run" ),
	CString( "light_weapon_stand_attack" ),
	CString( "light_weapon_jump_attack" ),
	CString( "light_weapon_run_attack" ),
	CString( "light_weapon_dash_attack" ),
	CString( "light_weapon_throw" ),
	CString( "heavy_weapon_throw" ),
	CString( "light_weapon_jump_throw" ),
	CString( "heavy_weapon_jump_throw" ),
	CString( "drink" ),
	CString( "before_attack" ),
	CString( "attacking" ),
	CString( "after_attack" ),
	CString( "before_super_attack" ),
	CString( "super_attacking" ),
	CString( "after_super_attack" ),
	CString( "before_jump_attack" ),
	CString( "jump_attacking" ),
	CString( "after_jump_attack" ),
	CString( "before_run_attack" ),
	CString( "run_attacking" ),
	CString( "after_run_attack" ),
	CString( "before_dash_attack" ),
	CString( "dash_attacking" ),
	CString( "after_dash_attack" ),
	CString( "flip" ),
	CString( "rolling" ),
	CString( "defend" ),
	CString( "defend_punch" ),
	CString( "defend_kick" ),
	CString( "catching" ),
	CString( "caught" ),
	CString( "falling" ),
	CString( "jump" ),
	CString( "dash" ),
	CString( "crouch" ),
	CString( "injured" ),
	CString( "forward_lying" ),
	CString( "backward_lying" ),
	CString( "in_the_air" ),
	CString( "before_skill" ),
	CString( "after_skill" ),
	CString( "air_skill" ),
	CString( "x_axis_skill" ),
	CString( "z_axis_skill" ),
	CString( "ground_skill" ),
	CString( "unique_skill" ),
};

const CString CClassView::actionMap[MAX_ACTIONS] =
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
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
	ON_COMMAND(ID_BODY_ADD, &CClassView::OnBodyAdd)
	ON_COMMAND(ID_BODY_DELETE, &CClassView::OnBodyDelete)
	ON_COMMAND(ID_ATTACK_DELETE, &CClassView::OnAttackDelete)
	ON_COMMAND(ID_ATTACK_ADD, &CClassView::OnAttackAdd)
	ON_COMMAND(ID_HITDATA_ADD, &CClassView::OnHitdataAdd)
	ON_COMMAND(ID_HITDATA_DELETE, &CClassView::OnHitdataDelete)
	ON_COMMAND(ID_CATCH_ADD, &CClassView::OnCatchAdd)
	ON_COMMAND(ID_CATCH_DELETE, &CClassView::OnCatchDelete)
	ON_COMMAND(ID_BLOODINFO_ADD, &CClassView::OnBloodinfoAdd)
	ON_COMMAND(ID_BLOODINFO_DELETE, &CClassView::OnBloodinfoDelete)
	ON_COMMAND(ID_CREATION_ADD, &CClassView::OnCreationAdd)
	ON_COMMAND(ID_CREATION_DELETE, &CClassView::OnCreationDelete)
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
		pWndTree->SelectItem( hTreeItem );

		if ( pWndTree->GetRootItem() == hTreeItem )
		{
			menu.LoadMenu( IDR_POPUP_CHARACTER_EDIT );
		}
		else if ( IsAnAnimation( pWndTree, hTreeItem ) )
		{
			menu.LoadMenu( IDR_POPUP_ANIMATION_EDIT );
		}
		else if ( IsNumber( pWndTree->GetItemText( hTreeItem ) ) && IsAnAnimation( pWndTree, m_wndClassView.GetParentItem( hTreeItem ) ))
		{
			menu.LoadMenu( IDR_POPUP_FRAME_EDIT );
		}
		else if ( pWndTree->GetItemText( hTreeItem ) == CString("Bodys") )
		{
			menu.LoadMenu(IDR_POPUP_BODYADD);
		}
		else if ( pWndTree->GetItemText( hTreeItem ) == CString("Attacks") )
		{
			menu.LoadMenu(IDR_POPUP_ATTACKADD);
		}
		else if ( pWndTree->GetItemText( hTreeItem ) == CString("Bodys") )
		{

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
	HTREEITEM root = m_wndClassView.GetRootItem();
	char buff[100];
	sprintf(buff, "Default%d", num);
	CString str(buff);
	std::string frameName(buff);

	if ( g_ActiveFramesMap != NULL )
	{
		( *g_ActiveFramesMap )[frameName] = FrameInfos();
		HTREEITEM item = m_wndClassView.InsertItem( str, 1, 1, root );
		( *g_ActiveFramesMap )[frameName].push_back( defaultFrameInfo( item ) );
		sprintf( buff, "%d", 0 );
		CString str( buff );
		HTREEITEM hClass = m_wndClassView.InsertItem( str, 3, 3, item );
		m_wndClassView.InsertItem( _T( "Bodys" ), 3, 3, hClass );
		m_wndClassView.InsertItem( _T( "Attacks" ), 3, 3, hClass );
		m_wndClassView.InsertItem( _T( "HitDatas" ), 3, 3, hClass );
		m_wndClassView.InsertItem( _T( "Catchs" ), 3, 3, hClass );
		m_wndClassView.InsertItem( _T( "BeCatch" ), 3, 3, hClass );
		m_wndClassView.InsertItem( _T( "BloodInfos" ), 3, 3, hClass );
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
		CT2CA pszConvertedAnsiString ( m_wndClassView.GetItemText( item ) );
		std::string str( pszConvertedAnsiString );
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
			g_FrameName = "";
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
		CT2CA pszConvertedAnsiString ( m_wndClassView.GetItemText( item ) );
		std::string frameName( pszConvertedAnsiString );
		int index = ( *g_ActiveFramesMap )[frameName].size();
		FrameInfo fi = defaultFrameInfo( item );
		fi.m_FrameIndex = index;
		( *g_ActiveFramesMap )[frameName].push_back( fi );
		char buff[100];
		sprintf(buff, "%d", index);
		CString str(buff);

		HTREEITEM hClass =  m_wndClassView.InsertItem(str, 3, 3, item);
		m_wndClassView.InsertItem(_T("Bodys"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("Attacks"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("HitDatas"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("Catchs"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("BeCatch"), 3, 3, hClass);
		m_wndClassView.InsertItem(_T("BloodInfos"), 3, 3, hClass);

		m_wndClassView.Expand(item, TVE_EXPAND);

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
	CT2CA pszConvertedAnsiString ( m_wndClassView.GetItemText( m_wndClassView.GetParentItem( item ) ) );
	std::string frameName( pszConvertedAnsiString );
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
	HTREEITEM pItem = m_wndClassView.GetParentItem( item );
	if ( m_wndClassView.GetRootItem() == item )
	{
		m_wndClassView.SelectItem( item );
		m_wndClassView.SetFocus();
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
				char buff[1000];
				ConvStr::WcharToChar( m_wndClassView.GetItemText( Frame ).GetBuffer( 0 ), buff );
				std::string FrameName( buff );

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
				char buff[1000];
				ConvStr::WcharToChar( m_wndClassView.GetItemText( Frame ).GetBuffer( 0 ), buff );
				std::string FrameName( buff );

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
			}
			else if ( !text.Compare( CString( "Catchs" ) ) )
			{
			}
			else if ( !text.Compare( CString( "BloodInfos" ) ) )
			{
			}
			else if ( !text.Compare( CString( "Creations" ) ) )
			{
			}
			else
			{
				char buff[1000];
				ConvStr::WcharToChar( text.GetBuffer( 0 ), buff );
				std::string FrameName( buff );

				if ( g_ActiveFramesMap->find( FrameName ) != g_ActiveFramesMap->end() )
				{
					g_FrameName = FrameName;
					g_FrameIndex = _ttoi( m_wndClassView.GetItemText( item ) );
					_propWnd->InitPropList_Frame();
					( ( CMainFrame* )( this->GetParentFrame() ) )->RefreshFrameEdit();
					( ( CMainFrame* )( this->GetParentFrame() ) )->m_D3DFrameView.EditCenter();
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

LRESULT CClassView::OnPropertyChanged( __in WPARAM wparam, __in LPARAM lparam, HTREEITEM item )
{
	CMFCPropertyGridProperty* prop = ( CMFCPropertyGridProperty* )lparam;

	if ( item != NULL )
	{
		FrameInfo& fi = m_propMap[item];
		CString caption = prop->GetName();
		COleVariant var = prop->GetValue();

		if ( caption.Compare( _T( "Frame Name" ) ) == 0 )
		{
			fi.m_FrameName = std::string( _com_util::ConvertBSTRToString( var.bstrVal ) );
		}
		else if ( caption.Compare( _T( "Frame Index" ) ) == 0 )
		{
			fi.m_FrameIndex = var.intVal;
		}
		else if ( caption.Compare( _T( "Next Frame Name" ) ) == 0 )
		{
			fi.m_NextFrameName = std::string( _com_util::ConvertBSTRToString( var.bstrVal ) );
		}
		else if ( caption.Compare( _T( "Next Frame Index" ) ) == 0 )
		{
			fi.m_NextFrameIndex = var.intVal;
		}
		else if ( caption.Compare( _T( "Hero Action" ) ) == 0 )
		{
			for ( int i = 0; i < MAX_ACTIONS; i++ )
			{
				if ( actionMap[i].Compare( var.bstrVal ) == 0 )
				{
#define SET_ACTION(i, X) case i: fi.m_HeroAction = HeroAction:: X; break;

					switch ( i )
					{
						SET_ACTION( 0, STANDING );
						SET_ACTION( 1, STANDING );
						SET_ACTION( 2, WALKING );
						SET_ACTION( 3, RUNNING );
						SET_ACTION( 4, STOP_RUNNING );
						SET_ACTION( 5, HEAVY_WEAPON_WALK );
						SET_ACTION( 6, HEAVY_WEAPON_RUN );
						SET_ACTION( 7, LIGHT_WEAPON_STAND_ATTACK );
						SET_ACTION( 8, LIGHT_WEAPON_JUMP_ATTACK );
						SET_ACTION( 9, LIGHT_WEAPON_RUN_ATTACK );
						SET_ACTION( 10, LIGHT_WEAPON_DASH_ATTACK );
						SET_ACTION( 11, LIGHT_WEAPON_THROW );
						SET_ACTION( 12, HEAVY_WEAPON_THROW );
						SET_ACTION( 13, LIGHT_WEAPON_JUMP_THROW );
						SET_ACTION( 14, HEAVY_WEAPON_JUMP_THROW );
						SET_ACTION( 15, DRINK );
						SET_ACTION( 16, BEFORE_ATTACK );
						SET_ACTION( 17, ATTACKING );
						SET_ACTION( 18, AFTER_ATTACK );
						SET_ACTION( 19, BEFORE_SUPER_ATTACK );
						SET_ACTION( 20, SUPER_ATTACKING );
						SET_ACTION( 21, AFTER_SUPER_ATTACK );
						SET_ACTION( 22, BEFORE_JUMP_ATTACK );
						SET_ACTION( 23, JUMP_ATTACKING );
						SET_ACTION( 24, AFTER_JUMP_ATTACK );
						SET_ACTION( 25, BEFORE_RUN_ATTACK );
						SET_ACTION( 26, RUN_ATTACKING );
						SET_ACTION( 27, AFTER_RUN_ATTACK );
						SET_ACTION( 28, BEFORE_DASH_ATTACK );
						SET_ACTION( 29, DASH_ATTACKING );
						SET_ACTION( 30, AFTER_DASH_ATTACK );
						SET_ACTION( 31, FLIP );
						SET_ACTION( 32, ROllING );
						SET_ACTION( 33, DEFEND );
						SET_ACTION( 34, DEFEND_PUNCH );
						SET_ACTION( 35, DEFEND_KICK );
						SET_ACTION( 36, CATCHING );
						SET_ACTION( 37, CAUGHT );
						SET_ACTION( 38, FALLING );
						SET_ACTION( 39, JUMP );
						SET_ACTION( 40, DASH );
						SET_ACTION( 41, CROUCH );
						SET_ACTION( 42, INJURED );
						SET_ACTION( 43, LYING );
						SET_ACTION( 44, IN_THE_AIR );
						SET_ACTION( 45, BEFORE_SKILL );
						SET_ACTION( 46, AFTER_SKILL );
						SET_ACTION( 47, AIR_SKILL );
						SET_ACTION( 48, X_AXIS_SKILL );
						SET_ACTION( 49, Z_AXIS_SKILL );
						SET_ACTION( 50, GROUND_SKILL );
						SET_ACTION( 51, UNIQUE_SKILL );
					}

					break;
				}
			}
		}
		else if ( caption.Compare( _T( "Wait" ) ) == 0 )
		{
			fi.m_Wait = var.intVal;
		}
		else if ( caption.Compare( _T( "ClearKeyQueue" ) ) == 0 )
		{
			if ( var.boolVal == -1 )
			{
				fi.m_ClearKeyQueue = true;
			}
			else
			{
				fi.m_ClearKeyQueue = false;
			}
		}
		else if ( caption.Compare( _T( "Picture ID" ) ) == 0 )
		{
			fi.m_PictureID = var.intVal;
		}
		else if ( caption.Compare( _T( "Center X Offset" ) ) == 0 )
		{
			fi.m_CenterX = var.fltVal;
		}
		else if ( caption.Compare( _T( "Center Y Offset" ) ) == 0 )
		{
			fi.m_CenterY = var.fltVal;
		}
		else if ( caption.Compare( _T( "Picture X Offset" ) ) == 0 )
		{
			fi.m_PictureX = var.intVal;
		}
		else if ( caption.Compare( _T( "Picture Y Offset" ) ) == 0 )
		{
			fi.m_PictureY = var.intVal;
		}
		else if ( caption.Compare( _T( "JumpRule" ) ) == 0 )
		{
			fi.m_Consume.m_JumpRule = var.intVal;
		}
		else if ( caption.Compare( _T( "HP" ) ) == 0 )
		{
			fi.m_Consume.m_HP = var.intVal;
		}
		else if ( caption.Compare( _T( "MP" ) ) == 0 )
		{
			fi.m_Consume.m_MP = var.intVal;
		}
		else if ( caption.Compare( _T( "Not Enough Frame Name" ) ) == 0 )
		{
			fi.m_Consume.m_NotEnoughFrameName = std::string( _com_util::ConvertBSTRToString( var.bstrVal ) );
		}
		else if ( caption.Compare( _T( "Not Next Frame Index" ) ) == 0 )
		{
			fi.m_Consume.m_NotEnoughFrame = var.intVal;
		}
		else if ( caption.Compare( _T( "DVX" ) ) == 0 )
		{
			fi.m_DVX = var.fltVal;
		}
		else if ( caption.Compare( _T( "DVY" ) ) == 0 )
		{
			fi.m_DVY = var.fltVal;
		}
		else if ( caption.Compare( _T( "DVZ" ) ) == 0 )
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
		sprintf( buff, "%s", g_HeroInfo->m_Name.c_str() );
		CString str( buff );
		HTREEITEM hRoot = m_wndClassView.InsertItem( str, 0, 0 );
		m_wndClassView.SetItemState( hRoot, TVIS_BOLD, TVIS_BOLD );

		for ( FramesMap::iterator it_FrameMap = g_HeroInfo->m_FramesMap.begin(); it_FrameMap != g_HeroInfo->m_FramesMap.end() ; it_FrameMap++ )
		{
			sprintf( buff, "%s", it_FrameMap->first.c_str() );
			str = CString( buff );
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
	CT2CA pszConvertedAnsiString ( m_wndClassView.GetItemText( item ) );
	std::string str2( pszConvertedAnsiString );
	FrameInfo fi;
	fi.m_FrameName = str2;
	fi.m_FrameIndex = 0;
	fi.m_NextFrameName = fi.m_FrameName;
	fi.m_NextFrameIndex = 0;
	fi.m_HeroAction = HeroAction::STANDING;
	fi.m_Wait = 1;
	fi.m_ClearKeyQueue = false;
	fi.m_PictureID = 0;
	fi.m_CenterX = 0.0f;
	fi.m_CenterY = 0.0f;
	fi.m_PictureX = 1;
	fi.m_PictureY = 1;
	fi.m_Consume.m_JumpRule = 0;
	fi.m_Consume.m_HP = 1;
	fi.m_Consume.m_MP = 1;
	fi.m_Consume.m_NotEnoughFrameName = fi.m_FrameName;
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
	int frameIndex = _ttoi(m_wndClassView.GetItemText(m_wndClassView.GetParentItem(item)));
	char buff[100];
	ConvStr::WcharToChar(m_wndClassView.GetItemText(m_wndClassView.GetParentItem(m_wndClassView.GetParentItem(item))),buff);
	std::string frameName(buff);
	Body body;
	body.m_Kind = 1;
	body.m_ZWidth = 1;
	(*g_ActiveFramesMap)[frameName][frameIndex].m_Bodys.push_back(body);
	sprintf(buff,"%d",(*g_ActiveFramesMap)[frameName][frameIndex].m_Bodys.size()-1);
	CString str(buff);
	m_wndClassView.InsertItem( str , 3, 3, item );
	m_wndClassView.Expand(item, TVE_EXPAND);
}


void CClassView::OnBodyDelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


void CClassView::OnAttackDelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


void CClassView::OnAttackAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


void CClassView::OnHitdataAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


void CClassView::OnHitdataDelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


void CClassView::OnCatchAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


void CClassView::OnCatchDelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
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
}


void CClassView::OnCreationDelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
}
