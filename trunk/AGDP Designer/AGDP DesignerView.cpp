
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

// AGDP DesignerView.cpp : CAGDPDesignerView 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "AGDP Designer.h"
#endif

#include "AGDP DesignerDoc.h"
#include "AGDP DesignerView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAGDPDesignerView

IMPLEMENT_DYNCREATE( CAGDPDesignerView, CTabView )

BEGIN_MESSAGE_MAP( CAGDPDesignerView, CTabView )
	// 標準列印命令
	ON_COMMAND( ID_FILE_PRINT, &CTabView::OnFilePrint )
	ON_COMMAND( ID_FILE_PRINT_DIRECT, &CTabView::OnFilePrint )
	ON_COMMAND( ID_FILE_PRINT_PREVIEW, &CAGDPDesignerView::OnFilePrintPreview )
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CAGDPDesignerView 建構/解構

CAGDPDesignerView::CAGDPDesignerView()
{
	// TODO: 在此加入建構程式碼
	g_NewView = this;
}

CAGDPDesignerView::~CAGDPDesignerView()
{
}

BOOL CAGDPDesignerView::PreCreateWindow( CREATESTRUCT& cs )
{
	// TODO: 在此經由修改 CREATESTRUCT cs
	// 達到修改視窗類別或樣式的目的
	return CTabView::PreCreateWindow( cs );
}

// CAGDPDesignerView 描繪

void CAGDPDesignerView::OnDraw( CDC* /*pDC*/ )
{
// 	CAGDPDesignerDoc* pDoc = GetDocument();
// 	ASSERT_VALID(pDoc);
// 	if (!pDoc)
// 		return;
	// TODO: 在此加入原生資料的描繪程式碼
}


// CAGDPDesignerView 列印


void CAGDPDesignerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview( this );
#endif
}

BOOL CAGDPDesignerView::OnPreparePrinting( CPrintInfo* pInfo )
{
	// 預設的準備列印程式碼
	return DoPreparePrinting( pInfo );
}

void CAGDPDesignerView::OnBeginPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ )
{
	// TODO: 加入列印前額外的初始設定
}

void CAGDPDesignerView::OnEndPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ )
{
	// TODO: 加入列印後的清除程式碼
}

void CAGDPDesignerView::OnContextMenu( CWnd* /* pWnd */, CPoint point )
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu( IDR_POPUP_EDIT, point.x, point.y, this, TRUE );
#endif
}


// CAGDPDesignerView 診斷

#ifdef _DEBUG
void CAGDPDesignerView::AssertValid() const
{
	CTabView::AssertValid();
}

void CAGDPDesignerView::Dump( CDumpContext& dc ) const
{
	CTabView::Dump( dc );
}

CAGDPDesignerDoc* CAGDPDesignerView::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT( m_pDocument->IsKindOf( RUNTIME_CLASS( CAGDPDesignerDoc ) ) );
	return ( CAGDPDesignerDoc* )m_pDocument;
}

#endif //_DEBUG


// CAGDPDesignerView 訊息處理常式


int CAGDPDesignerView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CTabView::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	// TODO:  在此加入特別建立的程式碼
// 	AddView(RUNTIME_CLASS(CD3DpictureView),_T("Test1"),1);
// 	AddView(RUNTIME_CLASS(CD3DpictureView),_T("Test2"),2);
	this -> GetTabControl().SetLocation( CMFCTabCtrl:: LOCATION_BOTTOM );
	this -> GetTabControl().ModifyTabStyle( CMFCTabCtrl:: STYLE_3D );
	this -> GetTabControl().EnableAutoColor( TRUE );
	this -> GetTabControl().HideSingleTab( FALSE );
	this -> GetTabControl().EnableTabSwap( FALSE );
	this -> GetTabControl().SetTabBorderSize( 2 );
	return 0;
}


BOOL CAGDPDesignerView::OnEraseBkgnd( CDC* pDC )
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	return TRUE;
}

void CAGDPDesignerView::AddPicturedata( CString name, PictureData* pic, int index )
{
	if ( m_ViewMap.find( pic ) == m_ViewMap.end() )
	{
		AddView( RUNTIME_CLASS( CD3DpictureView ), name, index );
		g_NewPictureView->OnInitialUpdate();
		g_NewPictureView->Refresh( pic );
		m_ViewMap[pic] = g_NewPictureView;
	}
}

void CAGDPDesignerView::SwitchPicture( int index )
{
	SetActiveView( index );
}

void CAGDPDesignerView::Refresh( PictureData* pic )
{
	( ( CD3DpictureView* )GetActiveView() )->Refresh( pic );
}
