
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

IMPLEMENT_DYNCREATE(CAGDPDesignerView, CTabView)

BEGIN_MESSAGE_MAP(CAGDPDesignerView, CTabView)
	// �зǦC�L�R�O
	ON_COMMAND(ID_FILE_PRINT, &CTabView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CTabView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CAGDPDesignerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSELEAVE()
//	ON_WM_CREATE()
ON_WM_CREATE()
END_MESSAGE_MAP()

// CAGDPDesignerView �غc/�Ѻc

CAGDPDesignerView::CAGDPDesignerView()
{
	// TODO: �b���[�J�غc�{���X
}

CAGDPDesignerView::~CAGDPDesignerView()
{
}

BOOL CAGDPDesignerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �b���g�ѭק� CREATESTRUCT cs 
	// �F��ק�������O�μ˦����ت�

	return CTabView::PreCreateWindow(cs);
}

// CAGDPDesignerView �yø

void CAGDPDesignerView::OnDraw(CDC* /*pDC*/)
{
	CAGDPDesignerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �b���[�J��͸�ƪ��yø�{���X
}


// CAGDPDesignerView �C�L


void CAGDPDesignerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CAGDPDesignerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �w�]���ǳƦC�L�{���X
	return DoPreparePrinting(pInfo);
}

void CAGDPDesignerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �[�J�C�L�e�B�~����l�]�w
}

void CAGDPDesignerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �[�J�C�L�᪺�M���{���X
}

void CAGDPDesignerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAGDPDesignerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CAGDPDesignerView �E�_

#ifdef _DEBUG
void CAGDPDesignerView::AssertValid() const
{
	CTabView::AssertValid();
}

void CAGDPDesignerView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}

CAGDPDesignerDoc* CAGDPDesignerView::GetDocument() const // ���O�D��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAGDPDesignerDoc)));
	return (CAGDPDesignerDoc*)m_pDocument;
}


#endif //_DEBUG


// CAGDPDesignerView �T���B�z�`��

void CAGDPDesignerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	
	
	

	CTabView::OnLButtonDown(nFlags, point);
}

void CAGDPDesignerView::OnMouseMove(UINT nFlags, CPoint point)
{
	

	CTabView::OnMouseMove(nFlags, point);
}

BOOL CAGDPDesignerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	
	return CTabView::OnMouseWheel(nFlags, zDelta, pt);
}

void CAGDPDesignerView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	
	CTabView::OnMButtonDown(nFlags, point);
}


void CAGDPDesignerView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	CTabView::OnMButtonUp(nFlags, point);
}


const unsigned int KEY_SHIFT	= 16;
const unsigned int KEY_CTRL	= 17;
const unsigned int KEY_LEFT	= 37;
const unsigned int KEY_UP	= 38;
const unsigned int KEY_RIGHT	= 39;
const unsigned int KEY_DOWN	= 40;
const unsigned int KEY_DELETE	= 46;
const unsigned int KEY_A	= 65;
const unsigned int KEY_C	= 67;
const unsigned int KEY_E	= 69;
const unsigned int KEY_ADD	= 107;
const unsigned int KEY_SUB	= 109;
const unsigned int KEY_EQUAL	= 187;

void CAGDPDesignerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��

// 	char buff[100];
// 	sprintf(buff, "%d", nChar);
// 	CString str(buff);
// 	AfxMessageBox(str);
	
	

	CTabView::OnKeyDown(nChar, nRepCnt, nFlags);

}

void CAGDPDesignerView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	
}



void CAGDPDesignerView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �b���[�J�z���T���B�z�`���{���X
	// ���n�I�s�Ϥ��T���� CTabView::OnPaint()
}

void CAGDPDesignerView::OnMouseLeave()
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	
	CTabView::OnMouseLeave();
}

int CAGDPDesignerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	g_NewView = this;
	// TODO:  �b���[�J�S�O�إߪ��{���X

	return 0;
}
