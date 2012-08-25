// D3DPanelView.cpp : 實作檔
//

#include "stdafx.h"
#include "ADGP Designer.h"
#include "D3DPanelView.h"
#include "afxdialogex.h"
#include "global.h"


// CD3DPanelView 對話方塊

IMPLEMENT_DYNAMIC(CD3DPanelView, CDockablePane)

CD3DPanelView::CD3DPanelView(CWnd* pParent /*=NULL*/)
{

}

CD3DPanelView::~CD3DPanelView()
{
}

void CD3DPanelView::DoDataExchange(CDataExchange* pDX)
{
	CDockablePane::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CD3DPanelView, CDockablePane)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CD3DPanelView 訊息處理常式


void CD3DPanelView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此加入您的訊息處理常式程式碼
	// 不要呼叫圖片訊息的 CDockablePane::OnPaint()
	static bool init = false;
	if (!init)
	{
		init = true;
		OnFirstPaint();
	}
	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
}

void CD3DPanelView::OnFirstPaint()
{
	InitDx11(this->GetSafeHwnd());
}

void CD3DPanelView::InitDx11( HWND hWnd )
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

	//*test
	PictureData* temp = new PictureData();
	temp->m_Path = std::string("media\\davis_0.png");
	temp->m_TextureID = m_D3DApp.GetTextureManager().AddTexture(temp->m_Path);
	temp->m_Width = 79;
	temp->m_Height = 79;
	temp->m_Row = 10;
	temp->m_Column = 7;
	m_D3DApp.SetPic(temp,1,1);
	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
	//*/
}


void CD3DPanelView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 在此加入您的訊息處理常式程式碼
	if (cx > 0 && cy >0)
		m_D3DApp.OnResize(cx, cy);
}
