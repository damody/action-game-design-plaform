#pragma once
#include "DX11\d3dApp_Frame.h"
#include "game\FrameInfo.h"

// CD3DPanelView 對話方塊

class CD3DPanelView : public CDockablePane
{
	DECLARE_DYNAMIC( CD3DPanelView )
private:
	bool m_TrackMouse;
	bool m_LMouseHold;
	bool m_MMouseHold;
	bool m_CtrlPress;
	bool m_ShiftPress;
	bool m_KeyAPress;
	bool m_EnableCtrlCenter;
	int m_BodyID;
	int m_AttackID;

	FrameInfo* m_FrameInfo;

	int m_PointIndex;
	float m_RecordX, m_RecordY;
public:
	void Clear()
	{
		Init();
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
	void Init();
	void Refresh();
	void EditBody( int id );
	void EditBodyPoint( int id);
	void EditAttack( int id );
	void EditCenter();
	void EditCenter( float x, float y );
	void SetPic( PictureData*  pic, float x, float y );
private:
	void InitEdit();
	void StopEdit();

	void UpdateCenter( float x, float y );
	void UpdateBody();
	void UpdateBody( int index );
	void UpdateAddition_BodyPoint( float x, float y );
	void UpdateAttack();
	void UpdateAttack( int index );
	void UpdateAddition_AttackPoint( float x, float y );

	virtual BOOL CanFloat() const;
	virtual BOOL CanBeClosed() const;
	virtual BOOL CanAutoHide() const;
public:
	CD3DPanelView( CWnd* pParent = NULL ); // 標準建構函式
	virtual ~CD3DPanelView();

// 對話方塊資料
	enum { IDD = IDD_DIALOGBAR };
private:
	HWND		m_hWndDX11;
	D3DApp_Frame	m_D3DApp;
	void OnFirstPaint();
	void InitDx11( HWND hWnd );

protected:
	virtual void DoDataExchange( CDataExchange* pDX );  // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	afx_msg void OnMButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnMButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnMouseLeave();
	afx_msg void OnButtonPointadd();
	afx_msg void OnButtonPointsub();
};


