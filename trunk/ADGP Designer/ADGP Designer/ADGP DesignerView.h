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

// ADGP DesignerView.h : CADGPDesignerView 類別的介面
//

#pragma once
#include "DX11\D3DApp_Picture.h"
#include "game\PictureData.h"
#include "ADGP DesignerDoc.h"
#include "global.h"

class CADGPDesignerView : public CView
{
private:
	bool m_TrackMouse;
	bool m_LMouseHold;
	bool m_MMouseHold;
	bool m_CtrlPress;
	bool m_ShiftPress;
	bool m_KeyAPress;
	PictureData *m_Pic;

	float m_RecordX,m_RecordY;

	float m_CutH;
	float m_CutW;
	int   m_CutR;
	int   m_CutC;
public:
	int  m_PictureID;
	void Init();
	void Refresh(PictureData* pic);
private:
	void Update(int x,int y);

protected: // 僅從序列化建立
	CADGPDesignerView();
	DECLARE_DYNCREATE(CADGPDesignerView)

// 屬性
public:
	CADGPDesignerDoc* GetDocument() const;

// 作業
public:
	HWND		m_hWndDX11;
	D3DApp_Picture	m_D3DApp;
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
	virtual ~CADGPDesignerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void InitDx11(HWND hWnd);
protected:

// 產生的訊息對應函式
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // ADGP DesignerView.cpp 中的偵錯版本
inline CADGPDesignerDoc* CADGPDesignerView::GetDocument() const
   { return reinterpret_cast<CADGPDesignerDoc*>(m_pDocument); }
#endif

