
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

// ADGP DesignerView.cpp : CADGPDesignerView ���O����@
//

#include "stdafx.h"
// SHARED_HANDLERS �i�H�w�q�b��@�w���B�Y�ϩM�j�M�z�����B�z�`����
// ATL �M�פ��A�ä��\�P�ӱM�צ@�Τ��{���X�C
#ifndef SHARED_HANDLERS
#include "ADGP Designer.h"
#endif

#include "ADGP DesignerDoc.h"
#include "ADGP DesignerView.h"
#include "MainFrm.h"
#include "global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CADGPDesignerView

IMPLEMENT_DYNCREATE(CADGPDesignerView, CView)

BEGIN_MESSAGE_MAP(CADGPDesignerView, CView)
	// �зǦC�L�R�O
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CADGPDesignerView::OnFilePrintPreview)
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
END_MESSAGE_MAP()

// CADGPDesignerView �غc/�Ѻc

CADGPDesignerView::CADGPDesignerView():m_LMouseHold(false),m_MMouseHold(false),m_CtrlPress(false),m_KeyAPress(false),m_ShiftPress(false),m_RecordX(0),m_RecordY(0),
m_Pic(0),m_CutH(1),m_CutW(1),m_CutR(1),m_CutC(1)
{
	// TODO: �b���[�J�غc�{���X
}

CADGPDesignerView::~CADGPDesignerView()
{
}

BOOL CADGPDesignerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �b���g�ѭק� CREATESTRUCT cs 
	// �F��ק�������O�μ˦����ت�

	return CView::PreCreateWindow(cs);
}

// CADGPDesignerView �yø

void CADGPDesignerView::OnDraw(CDC* /*pDC*/)
{
	CADGPDesignerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �b���[�J��͸�ƪ��yø�{���X
	
	
	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
}


// CADGPDesignerView �C�L


void CADGPDesignerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CADGPDesignerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �w�]���ǳƦC�L�{���X
	return DoPreparePrinting(pInfo);
}

void CADGPDesignerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �[�J�C�L�e�B�~����l�]�w
}

void CADGPDesignerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �[�J�C�L�᪺�M���{���X
}

void CADGPDesignerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CADGPDesignerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CADGPDesignerView �E�_

#ifdef _DEBUG
void CADGPDesignerView::AssertValid() const
{
	CView::AssertValid();
}

void CADGPDesignerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CADGPDesignerDoc* CADGPDesignerView::GetDocument() const // ���O�D��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CADGPDesignerDoc)));
	return (CADGPDesignerDoc*)m_pDocument;
}


#endif //_DEBUG

void CADGPDesignerView::InitDx11( HWND hWnd )
{
	CRect rect;
	GetWindowRect(&rect);
	// 	m_hWndDX11 = CreateWindowA("edit", "", WS_CHILD | WS_DISABLED | WS_VISIBLE
	// 		, 0, 0, rect.right-rect.left, rect.bottom-rect.top, hWnd, 
	// 		(HMENU)"", 0, NULL);
	m_hWndDX11 = hWnd;
	::ShowWindow(m_hWndDX11, true);
	::UpdateWindow(m_hWndDX11);
	m_D3DApp.initApp(m_hWndDX11, rect.Width(), rect.Height());
	m_D3DApp.buildShaderFX();

	//*test
	PictureData* temp = new PictureData();
	temp->m_Path = std::string("media\\davis_0.png");
	temp->m_TextureID = m_D3DApp.GetTextureManager().AddTexture(temp->m_Path);
	temp->m_Width = 79;
	temp->m_Height = 79;
	temp->m_Row = 10;
	temp->m_Column = 7;

	SetPic(temp);
	Cut(10,7);
	//*/
}

// CADGPDesignerView �T���B�z�`��


void CADGPDesignerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �b���[�J�S�w���{���X�M (��) �I�s�����O
	InitDx11(this->GetParent()->GetSafeHwnd());
}


void CADGPDesignerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �b���[�J�z���T���B�z�`���{���X
	if (cx > 0 && cy >0)
		m_D3DApp.OnResize(cx, cy);
}

void CADGPDesignerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	point.x = 1+(point.x-g_Picture_OffsetX)/g_Picture_Scale / (int)m_CutW; 
	point.y = 1+(point.y-g_Picture_OffsetY)/g_Picture_Scale / (int)m_CutH;
	if (point.x <=0 || point.x >m_CutR || point.y <=0 || point.y >m_CutC)
	{
		return;
	}else{
		//if (((CMainFrame*)(this->GetParent()->GetParentFrame()))->GetFramePanel() == NULL)return;
		((CMainFrame*)(this->GetParent()->GetParentFrame()))->GetFramePanel().SetPic(m_Pic,point.x,point.y);
	}

	

	CView::OnLButtonDown(nFlags, point);
}

void CADGPDesignerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	float dx = point.x - m_RecordX;
	float dy = point.y - m_RecordY;
	m_RecordX = point.x;
	m_RecordY = point.y;
	if(m_MMouseHold)
	{
		g_Picture_OffsetX += dx;
		g_Picture_OffsetY += dy;
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}

	point.x = 1+(point.x-g_Picture_OffsetX)/g_Picture_Scale / (int)m_CutW; 
	point.y = 1+(point.y-g_Picture_OffsetY)/g_Picture_Scale / (int)m_CutH;

	if (point.x <=0 || point.x >m_CutR || point.y <=0 || point.y >m_CutC)
	{
		point.x = 0;
		point.y = 0;
	}

	char buff[100];
	sprintf(buff, "   ��: %d �C: %d  ",point.x,point.y);
	CString str(buff);
	((CMainFrame*)(this->GetParent()->GetParentFrame()))->SetStatus(str);

	CView::OnMouseMove(nFlags, point);
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

void CADGPDesignerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��

// 	char buff[100];
// 	sprintf(buff, "%d", nChar);
// 	CString str(buff);
// 	AfxMessageBox(str);
	if (nChar==KEY_CTRL)
	{
		m_CtrlPress = true;
	}

	if (nChar==KEY_SHIFT)
	{
		m_ShiftPress = true;
	}
	

	CView::OnKeyDown(nChar, nRepCnt, nFlags);

}

void CADGPDesignerView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	if (nChar==KEY_CTRL)
	{
		m_CtrlPress = false;
	}

	if (nChar==KEY_SHIFT)
	{
		m_ShiftPress = false;
	}
	
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}



void CADGPDesignerView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �b���[�J�z���T���B�z�`���{���X
	// ���n�I�s�Ϥ��T���� CView::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	m_D3DApp.OnResize(rect.Width(), rect.Height());
	m_D3DApp.DrawScene();
}


BOOL CADGPDesignerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	if (m_CtrlPress && !m_ShiftPress)
	{
		if (zDelta > 0)
		{
			if (g_Picture_Scale < 10)
			{
				g_Picture_Scale += 0.1f;
			}
		}else{
			if (g_Picture_Scale > 0.1)
			{
				g_Picture_Scale -= 0.1f;
			}
		}
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
	char buff[100];
	sprintf(buff, "   ��ܤ�� %.1f%%", g_Picture_Scale * 100);
	CString str(buff);
	((CMainFrame*)(this->GetParent()->GetParentFrame()))->SetStatus(str);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CADGPDesignerView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	m_MMouseHold = true;
	CView::OnMButtonDown(nFlags, point);
}


void CADGPDesignerView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	m_MMouseHold = false;
	CView::OnMButtonUp(nFlags, point);
}

//Functions
void CADGPDesignerView::Init()
{
	
}

void CADGPDesignerView::SetPic( PictureData* pic )
{
	m_D3DApp.SetPic(pic);
	m_Pic = pic;
	
}

void CADGPDesignerView::Cut( int r,int c )
{
	if(m_Pic==NULL)return;
	m_D3DApp.Cut(r,c);
	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
	m_CutR = r;
	m_CutC = c;
	m_CutW = m_D3DApp.GetTextureManager().GetTexture(m_Pic->m_TextureID)->w / r;
	m_CutH = m_D3DApp.GetTextureManager().GetTexture(m_Pic->m_TextureID)->h / c;
}



