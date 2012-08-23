#pragma once
#include "DX11\d3dApp_Frame.h"

// CD3DPanelView ��ܤ��

class CD3DPanelView : public CDockablePane
{
	DECLARE_DYNAMIC(CD3DPanelView)

public:
	CD3DPanelView(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CD3DPanelView();

// ��ܤ�����
	enum { IDD = IDD_DIALOGBAR };
private:
	HWND		m_hWndDX11;
	D3DApp_Frame	m_D3DApp;
	void OnFirstPaint();
	void InitDx11( HWND hWnd );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
