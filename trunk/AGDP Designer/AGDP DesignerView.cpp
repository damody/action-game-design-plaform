
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

IMPLEMENT_DYNCREATE(CAGDPDesignerView, CTabView)

BEGIN_MESSAGE_MAP(CAGDPDesignerView, CTabView)
	// 標準列印命令
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

// CAGDPDesignerView 建構/解構

CAGDPDesignerView::CAGDPDesignerView():m_TrackMouse(true),m_LMouseHold(false),m_MMouseHold(false),m_CtrlPress(false),m_KeyAPress(false),m_ShiftPress(false),m_RecordX(0),m_RecordY(0),
m_Pic(0),m_CutH(1),m_CutW(1),m_CutR(1),m_CutC(1),m_PictureID(0)
{
	// TODO: 在此加入建構程式碼
}

CAGDPDesignerView::~CAGDPDesignerView()
{
}

BOOL CAGDPDesignerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CTabView::PreCreateWindow(cs);
}

// CAGDPDesignerView 描繪

void CAGDPDesignerView::OnDraw(CDC* /*pDC*/)
{
	CAGDPDesignerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此加入原生資料的描繪程式碼
	
	
	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
}


// CAGDPDesignerView 列印


void CAGDPDesignerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CAGDPDesignerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CAGDPDesignerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印前額外的初始設定
}

void CAGDPDesignerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印後的清除程式碼
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


// CAGDPDesignerView 診斷

#ifdef _DEBUG
void CAGDPDesignerView::AssertValid() const
{
	CTabView::AssertValid();
}

void CAGDPDesignerView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}

CAGDPDesignerDoc* CAGDPDesignerView::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAGDPDesignerDoc)));
	return (CAGDPDesignerDoc*)m_pDocument;
}


#endif //_DEBUG

void CAGDPDesignerView::InitDx11( HWND hWnd )
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
}

// CAGDPDesignerView 訊息處理常式


void CAGDPDesignerView::OnInitialUpdate()
{
	CTabView::OnInitialUpdate();

	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	InitDx11(this->GetParent()->GetSafeHwnd());
}


void CAGDPDesignerView::OnSize(UINT nType, int cx, int cy)
{
	CTabView::OnSize(nType, cx, cy);

	// TODO: 在此加入您的訊息處理常式程式碼
	if (cx > 0 && cy >0)
		m_D3DApp.OnResize(cx, cy);
}

void CAGDPDesignerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	point.x = 1+(point.x-m_D3DApp.m_Picture_OffsetX)/m_D3DApp.m_Picture_Scale / (int)m_CutW; 
	point.y = 1+(point.y-m_D3DApp.m_Picture_OffsetY)/m_D3DApp.m_Picture_Scale / (int)m_CutH;
	if (point.x <=0 || point.x >m_CutR || point.y <=0 || point.y >m_CutC)
	{
		return;
	}else{
		Update(point.x,point.y);
	}

	

	CTabView::OnLButtonDown(nFlags, point);
}

void CAGDPDesignerView::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_TrackMouse){
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = this->m_hWnd;
		_TrackMouseEvent(&tme);
		m_TrackMouse =false;
	}
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	float dx = point.x - m_RecordX;
	float dy = point.y - m_RecordY;
	m_RecordX = point.x;
	m_RecordY = point.y;
	if(m_MMouseHold)
	{
		m_D3DApp.m_Picture_OffsetX += dx;
		m_D3DApp.m_Picture_OffsetY += dy;
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}

	point.x = 1+(point.x-m_D3DApp.m_Picture_OffsetX)/m_D3DApp.m_Picture_Scale / (int)m_CutW; 
	point.y = 1+(point.y-m_D3DApp.m_Picture_OffsetY)/m_D3DApp.m_Picture_Scale / (int)m_CutH;

	if (point.x <=0 || point.x >m_CutR || point.y <=0 || point.y >m_CutC)
	{
		point.x = 0;
		point.y = 0;
	}

	char buff[100];
	sprintf(buff, "   行: %d 列: %d  ",point.x,point.y);
	CString str(buff);
	((CMainFrame*)(this->GetParent()->GetParentFrame()))->SetStatus(str);

	CTabView::OnMouseMove(nFlags, point);
}

BOOL CAGDPDesignerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if (m_CtrlPress && !m_ShiftPress)
	{
		if (zDelta > 0)
		{
			if (m_D3DApp.m_Picture_Scale < 10)
			{
				m_D3DApp.m_Picture_Scale += 0.1f;
			}
		}else{
			if (m_D3DApp.m_Picture_Scale > 0.1)
			{
				m_D3DApp.m_Picture_Scale -= 0.1f;
			}
		}
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
	char buff[100];
	sprintf(buff, "   顯示比例 %.1f%%", m_D3DApp.m_Picture_Scale * 100);
	CString str(buff);
	((CMainFrame*)(this->GetParent()->GetParentFrame()))->SetStatus(str);
	return CTabView::OnMouseWheel(nFlags, zDelta, pt);
}

void CAGDPDesignerView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_MMouseHold = true;
	CTabView::OnMButtonDown(nFlags, point);
}


void CAGDPDesignerView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_MMouseHold = false;
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
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

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
	

	CTabView::OnKeyDown(nChar, nRepCnt, nFlags);

}

void CAGDPDesignerView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if (nChar==KEY_CTRL)
	{
		m_CtrlPress = false;
	}

	if (nChar==KEY_SHIFT)
	{
		m_ShiftPress = false;
	}
	
	CTabView::OnKeyUp(nChar, nRepCnt, nFlags);
}



void CAGDPDesignerView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此加入您的訊息處理常式程式碼
	// 不要呼叫圖片訊息的 CTabView::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	m_D3DApp.OnResize(rect.Width(), rect.Height());
	m_D3DApp.DrawScene();
}

void CAGDPDesignerView::OnMouseLeave()
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_TrackMouse = true;
	m_MMouseHold = false;
	m_CtrlPress  = false;
	CTabView::OnMouseLeave();
}

//Functions
void CAGDPDesignerView::Init()
{
	m_Pic = NULL;
}

void CAGDPDesignerView::Refresh(PictureData* pic)
{
	m_D3DApp.SetPic(pic);
	m_Pic = pic;

	m_D3DApp.Cut(pic->m_Row,pic->m_Column);
	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
	m_CutR = m_Pic->m_Row;
	m_CutC = m_Pic->m_Column;
	m_CutW = m_D3DApp.GetTextureManager().GetTexture(m_D3DApp.m_PicID)->w / m_Pic->m_Row;
	m_CutH = m_D3DApp.GetTextureManager().GetTexture(m_D3DApp.m_PicID)->h / m_Pic->m_Column;
}

void CAGDPDesignerView::Update( int x,int y )
{
	FramesMap::iterator it_FrameInfos = g_ActiveFramesMap->find(g_FrameName);
	if (it_FrameInfos != g_ActiveFramesMap->end())
	{
		if (g_FrameIndex > -1 && g_FrameIndex < it_FrameInfos->second.size())
		{
			it_FrameInfos->second[g_FrameIndex].m_PictureID = m_PictureID;
			it_FrameInfos->second[g_FrameIndex].m_PictureX = x;
			it_FrameInfos->second[g_FrameIndex].m_PictureY = y;

			//Refresh
			((CMainFrame*)(this->GetParent()->GetParentFrame()))->RefreshFrameEdit();
		}else{
			char buff[100];
			sprintf(buff, "PictureEdit: Frame[%s][%d] does not exist",g_FrameName.c_str(),g_FrameIndex);
			CString str(buff);
			AfxMessageBox(str);
			((CMainFrame*)(this->GetParent()->GetParentFrame()))->AddStrToOutputBuild(str);
			return;
		}
	}else{
		char buff[100];
		sprintf(buff, "PictureEdit: Frame[%s] does not exist",g_FrameName.c_str());
		CString str(buff);
		AfxMessageBox(str);
		((CMainFrame*)(this->GetParent()->GetParentFrame()))->AddStrToOutputBuild(str);
		return;
	}
}


int CAGDPDesignerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	g_NewView = this;
	// TODO:  在此加入特別建立的程式碼

	return 0;
}
