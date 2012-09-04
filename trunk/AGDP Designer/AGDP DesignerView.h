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

// AGDP DesignerView.h : CAGDPDesignerView ���O������
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
public: // �ȱq�ǦC�ƫإ�
	CAGDPDesignerView();
	DECLARE_DYNCREATE(CAGDPDesignerView)

// �ݩ�
public:
	CAGDPDesignerDoc* GetDocument() const;

// �@�~
public:
	
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
	virtual ~CAGDPDesignerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:

// ���ͪ��T�������禡
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

#ifndef _DEBUG  // AGDP DesignerView.cpp ������������
inline CAGDPDesignerDoc* CAGDPDesignerView::GetDocument() const
   { return reinterpret_cast<CAGDPDesignerDoc*>(m_pDocument); }
#endif

