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

// AGDP DesignerView.h : CAGDPDesignerView 類別的介面
//

#pragma once
#include "DX11\D3DApp_Picture.h"
#include "game\PictureData.h"
#include "AGDP DesignerDoc.h"
#include "global.h"
#include "D3DpictureView.h"
#include <vector>

class CAGDPDesignerView : public CTabView
{
public:
	std::vector<CD3DpictureView*> m_Views;
public: // 僅從序列化建立
	CAGDPDesignerView();
	DECLARE_DYNCREATE(CAGDPDesignerView)

// 屬性
public:
	CAGDPDesignerDoc* GetDocument() const;

// 作業
public:
	
// 覆寫
public:
	virtual void OnDraw(CDC* pDC);  // 覆寫以描繪此檢視
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 程式碼實作
public:
	virtual ~CAGDPDesignerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:

// 產生的訊息對應函式
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	void AddPicturedata(CString name,PictureData *pic,int index);
	void SwitchPicture(int index);
	void Refresh(PictureData *pic);
};

#ifndef _DEBUG  // AGDP DesignerView.cpp 中的偵錯版本
inline CAGDPDesignerDoc* CAGDPDesignerView::GetDocument() const
   { return reinterpret_cast<CAGDPDesignerDoc*>(m_pDocument); }
#endif

