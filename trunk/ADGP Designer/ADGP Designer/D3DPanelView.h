#pragma once
#include "DX11\d3dApp_Frame.h"

// CD3DPanelView 對話方塊

class CD3DPanelView : public CDockablePane
{
	DECLARE_DYNAMIC(CD3DPanelView)
private:
	bool m_LMouseHold;
	bool m_CtrlPress;
	bool m_ShiftPress;
	bool m_KeyAPress;
	bool m_EnableCtrlCenter;
	int m_BodyID;
	int m_AttackID;

	Points::iterator m_CtrlPoint;
	float m_RecordX,m_RecordY;
public:
	void Init();
	//Init(FrameInfo *info);
	void SetPic(PictureData  *pic,float x,float y);
	void StopEdit();
	int AddBody();
	void DeleteBody(int id);
	void EditBody(int id);
	int AddAttack();
	void DeleteAttack(int id);
	void EditAttack(int id);

public:
	CD3DPanelView(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CD3DPanelView();

// 對話方塊資料
	enum { IDD = IDD_DIALOGBAR };
private:
	HWND		m_hWndDX11;
	D3DApp_Frame	m_D3DApp;
	void OnFirstPaint();
	void InitDx11( HWND hWnd );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
