// D3DpictureView.cpp : 實作檔
//

#include "stdafx.h"
#include "AGDP Designer.h"
#include "D3DpictureView.h"
#include "MainFrm.h"

// CD3DpictureView

IMPLEMENT_DYNCREATE(CD3DpictureView, CView)

CD3DpictureView::CD3DpictureView()
:m_TrackMouse(true),m_LMouseHold(false),m_MMouseHold(false),m_CtrlPress(false),m_KeyAPress(false),m_ShiftPress(false),m_RecordX(0),m_RecordY(0),
 m_Pic(0),m_CutH(1),m_CutW(1),m_CutR(1),m_CutC(1)
{

}

CD3DpictureView::~CD3DpictureView()
{
}

BEGIN_MESSAGE_MAP(CD3DpictureView, CView)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSELEAVE()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CD3DpictureView 描繪

void CD3DpictureView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此加入描繪程式碼

	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
}


// CD3DpictureView 診斷

#ifdef _DEBUG
void CD3DpictureView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CD3DpictureView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

void CD3DpictureView::InitDx11( HWND hWnd )
{
	CRect rect;
	GetWindowRect(&rect);
	m_hWndDX11 = hWnd;
	::ShowWindow(m_hWndDX11, true);
	::UpdateWindow(m_hWndDX11);
	m_D3DApp.initApp(m_hWndDX11, rect.Width(), rect.Height());
	m_D3DApp.buildShaderFX();
}

#endif
#endif //_DEBUG


// CD3DpictureView 訊息處理常式

void CD3DpictureView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	InitDx11(this->GetParent()->GetSafeHwnd());
}

void CD3DpictureView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此加入您的訊息處理常式程式碼
	if (cx > 0 && cy >0)
		m_D3DApp.OnResize(cx, cy);
}




void CD3DpictureView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	point.x = 1+(point.x-m_D3DApp.m_Picture_OffsetX)/m_D3DApp.m_Picture_Scale / (int)m_CutW; 
	point.y = 1+(point.y-m_D3DApp.m_Picture_OffsetY)/m_D3DApp.m_Picture_Scale / (int)m_CutH;
	if (point.x <=0 || point.x >m_CutR || point.y <=0 || point.y >m_CutC)
	{
		return;
	}else{
		Update(point.x,point.y);
	}

	CView::OnLButtonDown(nFlags, point);
}


void CD3DpictureView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CView::OnLButtonUp(nFlags, point);
}


void CD3DpictureView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if(m_TrackMouse){
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = this->m_hWnd;
		_TrackMouseEvent(&tme);
		m_TrackMouse =false;
	}
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	float dx = point.x - m_RecordX;
	float dy = point.y - m_RecordY;
	m_RecordX = point.x;
	m_RecordY = point.y;
	if(m_MMouseHold)
	{
		m_D3DApp.m_Picture_OffsetX += dx;
		m_D3DApp.m_Picture_OffsetY += dy;
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}

	point.x = 1+(point.x-m_D3DApp.m_Picture_OffsetX)/m_D3DApp.m_Picture_Scale / (int)m_CutW; 
	point.y = 1+(point.y-m_D3DApp.m_Picture_OffsetY)/m_D3DApp.m_Picture_Scale / (int)m_CutH;

	if (point.x <=0 || point.x >m_CutR || point.y <=0 || point.y >m_CutC)
	{
		point.x = 0;
		point.y = 0;
	}

	char buff[100];
	sprintf(buff, "   行: %d 列: %d  ",point.x,point.y);
	CString str(buff);
	((CMainFrame*)(this->GetParent()->GetParent()->GetParent()->GetParentFrame()))->SetStatus(str);
	CView::OnMouseMove(nFlags, point);
}


BOOL CD3DpictureView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if (m_CtrlPress && !m_ShiftPress)
	{
		if (zDelta > 0)
		{
			if (m_D3DApp.m_Picture_Scale < 10)
			{
				m_D3DApp.m_Picture_Scale += 0.1f;
			}
		}else{
			if (m_D3DApp.m_Picture_Scale > 0.1)
			{
				m_D3DApp.m_Picture_Scale -= 0.1f;
			}
		}
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
	char buff[100];
	sprintf(buff, "   顯示比例 %.1f%%", m_D3DApp.m_Picture_Scale * 100);
	CString str(buff);
	((CMainFrame*)(this->GetParent()->GetParent()->GetParent()->GetParentFrame()))->SetStatus(str);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CD3DpictureView::OnMouseLeave()
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_TrackMouse = true;
	m_MMouseHold = false;
	m_CtrlPress  = false;
	CView::OnMouseLeave();
}


void CD3DpictureView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_MMouseHold = true;
	CView::OnMButtonDown(nFlags, point);
}


void CD3DpictureView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_MMouseHold = false;
	CView::OnMButtonUp(nFlags, point);
}

const unsigned int KEY_SHIFT	= 16;
const unsigned int KEY_CTRL	= 17;
const unsigned int KEY_LEFT	= 37;
const unsigned int KEY_UP	= 38;
const unsigned int KEY_RIGHT	= 39;
const unsigned int KEY_DOWN	= 40;
const unsigned int KEY_DELETE	= 46;
const unsigned int KEY_A	= 65;
const unsigned int KEY_C	= 67;
const unsigned int KEY_E	= 69;
const unsigned int KEY_ADD	= 107;
const unsigned int KEY_SUB	= 109;
const unsigned int KEY_EQUAL	= 187;

void CD3DpictureView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if (nChar==KEY_CTRL)
	{
		m_CtrlPress = true;
	}

	if (nChar==KEY_SHIFT)
	{
		m_ShiftPress = true;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CD3DpictureView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if (nChar==KEY_CTRL)
	{
		m_CtrlPress = false;
	}

	if (nChar==KEY_SHIFT)
	{
		m_ShiftPress = false;
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CD3DpictureView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此加入您的訊息處理常式程式碼
	// 不要呼叫圖片訊息的 CView::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	m_D3DApp.OnResize(rect.Width(), rect.Height());
	m_D3DApp.DrawScene();
}

void CD3DpictureView::Init()
{
	m_Pic = NULL;
}

void CD3DpictureView::Refresh( PictureData* pic )
{
	m_D3DApp.SetPic(pic);
	m_Pic = pic;

	m_D3DApp.Cut(pic->m_Row,pic->m_Column);
	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
	m_CutR = m_Pic->m_Row;
	m_CutC = m_Pic->m_Column;
	m_CutW = m_D3DApp.GetTextureManager().GetTexture(m_D3DApp.m_PicID)->w / m_Pic->m_Row;
	m_CutH = m_D3DApp.GetTextureManager().GetTexture(m_D3DApp.m_PicID)->h / m_Pic->m_Column;m_D3DApp.SetPic(pic);
	m_Pic = pic;

	m_D3DApp.Cut(pic->m_Row,pic->m_Column);
	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
	m_CutR = m_Pic->m_Row;
	m_CutC = m_Pic->m_Column;
	m_CutW = m_D3DApp.GetTextureManager().GetTexture(m_D3DApp.m_PicID)->w / m_Pic->m_Row;
	m_CutH = m_D3DApp.GetTextureManager().GetTexture(m_D3DApp.m_PicID)->h / m_Pic->m_Column;
}

void CD3DpictureView::Update( int x,int y )
{
	FramesMap::iterator it_FrameInfos = g_ActiveFramesMap->find(g_FrameName);
	if (it_FrameInfos != g_ActiveFramesMap->end())
	{
		if (g_FrameIndex > -1 && g_FrameIndex < it_FrameInfos->second.size())
		{
			it_FrameInfos->second[g_FrameIndex].m_PictureID = m_PictureID;
			it_FrameInfos->second[g_FrameIndex].m_PictureX = x;
			it_FrameInfos->second[g_FrameIndex].m_PictureY = y;

			//Refresh
			((CMainFrame*)(this->GetParent()->GetParentFrame()))->RefreshFrameEdit();
		}else{
			char buff[100];
			sprintf(buff, "PictureEdit: Frame[%s][%d] does not exist",g_FrameName.c_str(),g_FrameIndex);
			CString str(buff);
			AfxMessageBox(str);
			((CMainFrame*)(this->GetParent()->GetParentFrame()))->AddStrToOutputBuild(str);
			return;
		}
	}else{
		char buff[100];
		sprintf(buff, "PictureEdit: Frame[%s] does not exist",g_FrameName.c_str());
		CString str(buff);
		AfxMessageBox(str);
		((CMainFrame*)(this->GetParent()->GetParentFrame()))->AddStrToOutputBuild(str);
		return;
	}
}

