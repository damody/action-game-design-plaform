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
END_MESSAGE_MAP()

// CADGPDesignerView 建構/解構

CADGPDesignerView::CADGPDesignerView()
{
	// TODO: 在此加入建構程式碼

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

void CADGPDesignerView::InitDx11( HWND hWnd )
{
	RECT rect;
	GetWindowRect(&rect);
	// 	m_hWndDX11 = CreateWindowA("edit", "", WS_CHILD | WS_DISABLED | WS_VISIBLE
	// 		, 0, 0, rect.right-rect.left, rect.bottom-rect.top, hWnd, 
	// 		(HMENU)"", 0, NULL);
	m_hWndDX11 = hWnd;
	::ShowWindow(m_hWndDX11, true);
	::UpdateWindow(m_hWndDX11);
	m_D3DApp.initApp(m_hWndDX11, rect.right-rect.left, rect.bottom-rect.top);
	m_D3DApp.buildShaderFX();
}

#endif //_DEBUG


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


void CADGPDesignerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_D3DApp.m_Body.Add(point.x, point.y);
	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
	char buff[100];
	sprintf(buff, "%d %d", point.x, point.y);
	CString str(buff);
	//AfxMessageBox(str);
	((CMainFrame*)(this->GetParent()->GetParentFrame()))->AddStrToOutputDebug(str);
	CView::OnLButtonDown(nFlags, point);
}
