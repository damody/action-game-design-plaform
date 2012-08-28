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

// ADGP DesignerView.h : CADGPDesignerView ���O������
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

protected: // �ȱq�ǦC�ƫإ�
	CADGPDesignerView();
	DECLARE_DYNCREATE(CADGPDesignerView)

// �ݩ�
public:
	CADGPDesignerDoc* GetDocument() const;

// �@�~
public:
	HWND		m_hWndDX11;
	D3DApp_Picture	m_D3DApp;
// �мg
public:
	virtual void OnDraw(CDC* pDC);  // �мg�H�yø���˵�
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �{���X��@
public:
	virtual ~CADGPDesignerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void InitDx11(HWND hWnd);
protected:

// ���ͪ��T�������禡
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

#ifndef _DEBUG  // ADGP DesignerView.cpp ������������
inline CADGPDesignerDoc* CADGPDesignerView::GetDocument() const
   { return reinterpret_cast<CADGPDesignerDoc*>(m_pDocument); }
#endif

