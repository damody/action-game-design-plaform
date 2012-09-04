#pragma once

#include "DX11\D3DApp_Picture.h"
#include "game\PictureData.h"
#include "global.h"

// CD3DpictureView 檢視

class CD3DpictureView : public CView
{
	DECLARE_DYNCREATE(CD3DpictureView)
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
	int m_PictureID;
	HWND		m_hWndDX11;
	D3DApp_Picture	m_D3DApp;

	void InitDx11(HWND hWnd);

	void Init();
	void Refresh(PictureData* pic);
private:
	void Update(int x,int y);
protected:
	CD3DpictureView();           // 動態建立所使用的保護建構函式
	virtual ~CD3DpictureView();

public:
	virtual void OnDraw(CDC* pDC);      // 覆寫以描繪此檢視
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseLeave();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
};


