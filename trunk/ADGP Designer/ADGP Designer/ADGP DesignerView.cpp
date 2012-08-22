
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

// ADGP DesignerView.cpp : CADGPDesignerView 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "ADGP Designer.h"
#endif

#include "ADGP DesignerDoc.h"
#include "ADGP DesignerView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CADGPDesignerView

IMPLEMENT_DYNCREATE(CADGPDesignerView, CView)

BEGIN_MESSAGE_MAP(CADGPDesignerView, CView)
	// 標準列印命令
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
END_MESSAGE_MAP()

// CADGPDesignerView 建構/解構

CADGPDesignerView::CADGPDesignerView():m_LMouseHold(false),m_CtrlPoint(false),m_CtrlPoints(false),m_RecordX(0),m_RecordY(0)
{
	// TODO: 在此加入建構程式碼
	m_BodyPoint = m_D3DApp.m_Body.End();
}

CADGPDesignerView::~CADGPDesignerView()
{
}

BOOL CADGPDesignerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}

// CADGPDesignerView 描繪

void CADGPDesignerView::OnDraw(CDC* /*pDC*/)
{
	CADGPDesignerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此加入原生資料的描繪程式碼
	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
}


// CADGPDesignerView 列印


void CADGPDesignerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CADGPDesignerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CADGPDesignerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印前額外的初始設定
}

void CADGPDesignerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印後的清除程式碼
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


// CADGPDesignerView 診斷

#ifdef _DEBUG
void CADGPDesignerView::AssertValid() const
{
	CView::AssertValid();
}

void CADGPDesignerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CADGPDesignerDoc* CADGPDesignerView::GetDocument() const // 內嵌非偵錯版本
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
}

// CADGPDesignerView 訊息處理常式


void CADGPDesignerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	InitDx11(this->GetParent()->GetSafeHwnd());
}


void CADGPDesignerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此加入您的訊息處理常式程式碼
	if (cx > 0 && cy >0)
		m_D3DApp.OnResize(cx, cy);
}


void CADGPDesignerView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if(!m_CtrlPoint && !m_CtrlPoints)
	{
		m_D3DApp.m_Body.Add(point.x, point.y);
		m_BodyPoint = m_D3DApp.m_Body.End();
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
	
	CView::OnLButtonDblClk(nFlags, point);
}

void CADGPDesignerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_LMouseHold = true;
	if(m_CtrlPoint){
		if(m_BodyPoint==m_D3DApp.m_Body.End()){
			m_BodyPoint = m_D3DApp.m_Body.Select(point.x, point.y);
			m_D3DApp.m_Body.ChangeColor(m_BodyPoint,1.0f,0.0f,0.0f);
		}else{
			m_D3DApp.m_Body.Modify(m_BodyPoint,point.x, point.y);
		}
		
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}

	if (m_CtrlPoints)
	{
		m_RecordX = point.x;
		m_RecordY = point.y;
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CADGPDesignerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_LMouseHold = false;
	CView::OnLButtonUp(nFlags, point);
}

void CADGPDesignerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值


	char buff[100];
	sprintf(buff, "   座標位置( %d , %d )", point.x, point.y);
	CString str(buff);
	((CMainFrame*)(this->GetParent()->GetParentFrame()))->SetStatus(str);

	if(m_CtrlPoint && m_LMouseHold && m_BodyPoint != m_D3DApp.m_Body.End()){
		m_D3DApp.m_Body.Modify(m_BodyPoint,point.x, point.y);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}

	if (m_CtrlPoints && m_LMouseHold)
	{
		m_D3DApp.m_Body.Transale(point.x-m_RecordX, point.y-m_RecordY);
		m_RecordX = point.x;
		m_RecordY = point.y;
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}

	CView::OnMouseMove(nFlags, point);
}

const unsigned int KEY_SHIFT	= 16;
const unsigned int KEY_CTRL	= 17;
const unsigned int KEY_LEFT	= 37;
const unsigned int KEY_UP	= 38;
const unsigned int KEY_RIGHT	= 39;
const unsigned int KEY_DOWN	= 40;
const unsigned int KEY_DELETE	= 46;
const unsigned int KEY_C	= 67;

void CADGPDesignerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

// 	char buff[100];
// 	sprintf(buff, "%d", nChar);
// 	CString str(buff);
// 	AfxMessageBox(str);

	if (nChar==KEY_CTRL)
	{
		m_CtrlPoint = true;
	}

	if (nChar==KEY_SHIFT)
	{
		m_CtrlPoints = true;
	}
	
	if(m_CtrlPoint && m_BodyPoint != m_D3DApp.m_Body.End()){
		switch(nChar)
		{
		case KEY_LEFT:
			m_D3DApp.m_Body.Transale(m_BodyPoint,-1,0);
			break;
		case KEY_UP:
			m_D3DApp.m_Body.Transale(m_BodyPoint,0,-1);
			break;
		case KEY_RIGHT:
			m_D3DApp.m_Body.Transale(m_BodyPoint,1,0);
			break;
		case KEY_DOWN:
			m_D3DApp.m_Body.Transale(m_BodyPoint,0,1);
			break;
		case KEY_DELETE:
			m_D3DApp.m_Body.Erase(m_BodyPoint);
			m_BodyPoint = m_D3DApp.m_Body.End();
			break;
		}
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}

	if(m_CtrlPoints){
		switch(nChar)
		{
		case KEY_LEFT:
			m_D3DApp.m_Body.Transale(-1,0);
			break;
		case KEY_UP:
			m_D3DApp.m_Body.Transale(0,-1);
			break;
		case KEY_RIGHT:
			m_D3DApp.m_Body.Transale(1,0);
			break;
		case KEY_DOWN:
			m_D3DApp.m_Body.Transale(0,1);
			break;
		case KEY_C:
			m_D3DApp.m_Body.Clear();
			m_BodyPoint = m_D3DApp.m_Body.End();
			break;
		}
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);

}

void CADGPDesignerView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	if (nChar==KEY_CTRL)
	{
		m_CtrlPoint = false;
		if(m_BodyPoint != m_D3DApp.m_Body.End()){
			m_D3DApp.m_Body.ChangeColor(m_BodyPoint,1.0f,1.0f,1.0f);
			m_BodyPoint = m_D3DApp.m_Body.End();
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
	}

	if (nChar==KEY_SHIFT)
	{
		m_CtrlPoints = false;
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}



void CADGPDesignerView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此加入您的訊息處理常式程式碼
	// 不要呼叫圖片訊息的 CView::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	m_D3DApp.OnResize(rect.Width(), rect.Height());
	m_D3DApp.DrawScene();
}
