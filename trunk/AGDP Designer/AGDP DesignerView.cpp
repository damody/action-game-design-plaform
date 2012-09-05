
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

// AGDP DesignerView.cpp : CAGDPDesignerView ���O����@
//

#include "stdafx.h"
// SHARED_HANDLERS �i�H�w�q�b��@�w���B�Y�ϩM�j�M�z�����B�z�`����
// ATL �M�פ��A�ä��\�P�ӱM�צ@�Τ��{���X�C
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
	// �зǦC�L�R�O
	ON_COMMAND( ID_FILE_PRINT, &CTabView::OnFilePrint )
	ON_COMMAND( ID_FILE_PRINT_DIRECT, &CTabView::OnFilePrint )
	ON_COMMAND( ID_FILE_PRINT_PREVIEW, &CAGDPDesignerView::OnFilePrintPreview )
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CAGDPDesignerView �غc/�Ѻc

CAGDPDesignerView::CAGDPDesignerView()
{
	// TODO: �b���[�J�غc�{���X
	g_NewView = this;
}

CAGDPDesignerView::~CAGDPDesignerView()
{
}

BOOL CAGDPDesignerView::PreCreateWindow( CREATESTRUCT& cs )
{
	// TODO: �b���g�ѭק� CREATESTRUCT cs
	// �F��ק�������O�μ˦����ت�
	return CTabView::PreCreateWindow( cs );
}

// CAGDPDesignerView �yø

void CAGDPDesignerView::OnDraw( CDC* /*pDC*/ )
{
// 	CAGDPDesignerDoc* pDoc = GetDocument();
// 	ASSERT_VALID(pDoc);
// 	if (!pDoc)
// 		return;
	// TODO: �b���[�J��͸�ƪ��yø�{���X
}


// CAGDPDesignerView �C�L


void CAGDPDesignerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview( this );
#endif
}

BOOL CAGDPDesignerView::OnPreparePrinting( CPrintInfo* pInfo )
{
	// �w�]���ǳƦC�L�{���X
	return DoPreparePrinting( pInfo );
}

void CAGDPDesignerView::OnBeginPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ )
{
	// TODO: �[�J�C�L�e�B�~����l�]�w
}

void CAGDPDesignerView::OnEndPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ )
{
	// TODO: �[�J�C�L�᪺�M���{���X
}

void CAGDPDesignerView::OnContextMenu( CWnd* /* pWnd */, CPoint point )
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu( IDR_POPUP_EDIT, point.x, point.y, this, TRUE );
#endif
}


// CAGDPDesignerView �E�_

#ifdef _DEBUG
void CAGDPDesignerView::AssertValid() const
{
	CTabView::AssertValid();
}

void CAGDPDesignerView::Dump( CDumpContext& dc ) const
{
	CTabView::Dump( dc );
}

CAGDPDesignerDoc* CAGDPDesignerView::GetDocument() const // ���O�D��������
{
	ASSERT( m_pDocument->IsKindOf( RUNTIME_CLASS( CAGDPDesignerDoc ) ) );
	return ( CAGDPDesignerDoc* )m_pDocument;
}

#endif //_DEBUG


// CAGDPDesignerView �T���B�z�`��


int CAGDPDesignerView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CTabView::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	// TODO:  �b���[�J�S�O�إߪ��{���X
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
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
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
