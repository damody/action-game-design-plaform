// D3DPanelView.cpp : 實作檔
//

#include "stdafx.h"
#include "ADGP Designer.h"
#include "D3DPanelView.h"
#include "afxdialogex.h"
#include "global.h"
#include "MainFrm.h"

// CD3DPanelView 對話方塊

IMPLEMENT_DYNAMIC(CD3DPanelView, CDockablePane)

CD3DPanelView::CD3DPanelView(CWnd* pParent /*=NULL*/):m_LMouseHold(false),m_MMouseHold(false),m_CtrlPress(false),m_KeyAPress(false),m_EnableCtrlCenter(false),m_ShiftPress(false),m_RecordX(0),m_RecordY(0),m_BodyID(-1),m_AttackID(-1)
{
	this->Init();
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
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
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

void CD3DPanelView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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

	if (nChar==KEY_A)
	{
		m_KeyAPress = true;
	}

	if(nChar==KEY_C)
	{
		StopEdit();
		m_EnableCtrlCenter = true;
	}

	if(!m_D3DApp.m_Body.empty() && m_BodyID > -1){
		if(m_CtrlPress && !m_ShiftPress &&m_CtrlPoint != m_D3DApp.m_Body[m_BodyID].End()){
			switch(nChar)
			{
			case KEY_LEFT:
				m_D3DApp.m_Body[m_BodyID].Transale(m_CtrlPoint,-1,0);
				break;
			case KEY_UP:
				m_D3DApp.m_Body[m_BodyID].Transale(m_CtrlPoint,0,-1);
				break;
			case KEY_RIGHT:
				m_D3DApp.m_Body[m_BodyID].Transale(m_CtrlPoint,1,0);
				break;
			case KEY_DOWN:
				m_D3DApp.m_Body[m_BodyID].Transale(m_CtrlPoint,0,1);
				break;
			case KEY_DELETE:
				m_D3DApp.m_Body[m_BodyID].Erase(m_CtrlPoint);
				m_CtrlPoint = m_D3DApp.m_Body[m_BodyID].End();
				break;
			}
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}

		if(m_ShiftPress && m_CtrlPress){
			switch(nChar)
			{
			case KEY_LEFT:
				m_D3DApp.m_Body[m_BodyID].Transale(-1,0);
				break;
			case KEY_UP:
				m_D3DApp.m_Body[m_BodyID].Transale(0,-1);
				break;
			case KEY_RIGHT:
				m_D3DApp.m_Body[m_BodyID].Transale(1,0);
				break;
			case KEY_DOWN:
				m_D3DApp.m_Body[m_BodyID].Transale(0,1);
				break;
			case KEY_DELETE:
				m_D3DApp.m_Body[m_BodyID].Clear();
				m_CtrlPoint = m_D3DApp.m_Body[m_BodyID].End();
				break;
			}
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
	}

	if(!m_D3DApp.m_Attack.empty() && m_AttackID > -1){
		if(m_CtrlPress && !m_ShiftPress &&m_CtrlPoint != m_D3DApp.m_Attack[m_AttackID].End()){
			switch(nChar)
			{
			case KEY_LEFT:
				m_D3DApp.m_Attack[m_AttackID].Transale(m_CtrlPoint,-1,0);
				break;
			case KEY_UP:
				m_D3DApp.m_Attack[m_AttackID].Transale(m_CtrlPoint,0,-1);
				break;
			case KEY_RIGHT:
				m_D3DApp.m_Attack[m_AttackID].Transale(m_CtrlPoint,1,0);
				break;
			case KEY_DOWN:
				m_D3DApp.m_Attack[m_AttackID].Transale(m_CtrlPoint,0,1);
				break;
			case KEY_DELETE:
				m_D3DApp.m_Attack[m_AttackID].Erase(m_CtrlPoint);
				m_CtrlPoint = m_D3DApp.m_Attack[m_AttackID].End();
				break;
			}
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}

		if(m_ShiftPress && m_CtrlPress){
			switch(nChar)
			{
			case KEY_LEFT:
				m_D3DApp.m_Attack[m_AttackID].Transale(-1,0);
				break;
			case KEY_UP:
				m_D3DApp.m_Attack[m_AttackID].Transale(0,-1);
				break;
			case KEY_RIGHT:
				m_D3DApp.m_Attack[m_AttackID].Transale(1,0);
				break;
			case KEY_DOWN:
				m_D3DApp.m_Attack[m_AttackID].Transale(0,1);
				break;
			case KEY_DELETE:
				m_D3DApp.m_Attack[m_AttackID].Clear();
				m_CtrlPoint = m_D3DApp.m_Attack[m_AttackID].End();
				break;
			}
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
	}

	CDockablePane::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CD3DPanelView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if (nChar==KEY_CTRL)
	{
		m_CtrlPress = false;

		if(!m_D3DApp.m_Body.empty() && m_BodyID > -1)
		{
			if(m_CtrlPoint != m_D3DApp.m_Body[m_BodyID].End()){
				m_D3DApp.m_Body[m_BodyID].ChangeColor(m_CtrlPoint,0.0f,0.0f,0.0f);
				m_CtrlPoint = m_D3DApp.m_Body[m_BodyID].End();
				m_D3DApp.buildPoint();
				m_D3DApp.DrawScene();
			}
		}

		if(!m_D3DApp.m_Attack.empty() && m_AttackID > -1)
		{
			if(m_CtrlPoint != m_D3DApp.m_Attack[m_AttackID].End()){
				m_D3DApp.m_Attack[m_AttackID].ChangeColor(m_CtrlPoint,0.0f,0.0f,0.0f);
				m_CtrlPoint = m_D3DApp.m_Attack[m_AttackID].End();
				m_D3DApp.buildPoint();
				m_D3DApp.DrawScene();
			}
		}
	}

	if (nChar==KEY_SHIFT)
	{
		m_ShiftPress = false;
	}

	if (nChar==KEY_A)
	{
		m_KeyAPress = false;
	}

	//*test
	if(nChar==KEY_ADD)
	{
		EditBody(AddBody());
	}
	if(nChar==KEY_SUB)
	{
		DeleteBody(m_BodyID);

	}
	if (nChar==KEY_EQUAL)
	{
		EditAttack(AddAttack());
	}
	//*/

	CDockablePane::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CD3DPanelView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	point.x =(point.x-g_Frame_OffsetX)/g_Frame_Scale;
	point.y =(point.y-g_Frame_OffsetY)/g_Frame_Scale;

	m_LMouseHold = true;

	if (m_EnableCtrlCenter && m_CtrlPress)
	{
		m_D3DApp.SetCenter(point.x,point.y);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}

	if(!m_D3DApp.m_Body.empty() && m_BodyID > -1){
		if(m_KeyAPress && !m_CtrlPress && !m_ShiftPress){
			m_D3DApp.m_Body[m_BodyID].Add(point.x, point.y);
			m_CtrlPoint = m_D3DApp.m_Body[m_BodyID].End();
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
		if(m_CtrlPress && !m_ShiftPress){
			if(m_CtrlPoint==m_D3DApp.m_Body[m_BodyID].End()){
				m_CtrlPoint = m_D3DApp.m_Body[m_BodyID].Select(point.x, point.y);
				m_D3DApp.m_Body[m_BodyID].ChangeColor(m_CtrlPoint,1.0f,1.0f,0.0f);
			}else{
				m_D3DApp.m_Body[m_BodyID].Modify(m_CtrlPoint,point.x, point.y);
			}

			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}

	}

	if(!m_D3DApp.m_Attack.empty() && m_AttackID > -1){
		if(m_KeyAPress && !m_CtrlPress && !m_ShiftPress){
			m_D3DApp.m_Attack[m_AttackID].Add(point.x, point.y);
			m_CtrlPoint = m_D3DApp.m_Attack[m_AttackID].End();
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
		if(m_CtrlPress && !m_ShiftPress){
			if(m_CtrlPoint==m_D3DApp.m_Attack[m_AttackID].End()){
				m_CtrlPoint = m_D3DApp.m_Attack[m_AttackID].Select(point.x, point.y);
				m_D3DApp.m_Attack[m_AttackID].ChangeColor(m_CtrlPoint,1.0f,1.0f,0.0f);
			}else{
				m_D3DApp.m_Attack[m_AttackID].Modify(m_CtrlPoint,point.x, point.y);
			}

			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
	}

	CDockablePane::OnLButtonDown(nFlags, point);
}


void CD3DPanelView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_LMouseHold = false;
	CDockablePane::OnLButtonUp(nFlags, point);
}


void CD3DPanelView::OnMouseMove(UINT nFlags, CPoint point)
{
	float dx = point.x - m_RecordX;
	float dy = point.y - m_RecordY;
	m_RecordX = point.x;
	m_RecordY = point.y;
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	point.x =(point.x-g_Frame_OffsetX)/g_Frame_Scale;
	point.y =(point.y-g_Frame_OffsetY)/g_Frame_Scale;

	char buff[100];
	sprintf(buff, "   座標位置( %d , %d )", point.x, point.y);
	CString str(buff);
	((CMainFrame*)(this->GetParentFrame()))->SetStatus(str);


	if(!m_D3DApp.m_Body.empty() && m_BodyID > -1){
		if(m_CtrlPress && !m_ShiftPress && m_LMouseHold && m_CtrlPoint != m_D3DApp.m_Body[m_BodyID].End()){
			m_D3DApp.m_Body[m_BodyID].Modify(m_CtrlPoint,point.x, point.y);
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}

		if (m_ShiftPress && m_CtrlPress && m_LMouseHold)
		{
			m_D3DApp.m_Body[m_BodyID].Transale(point.x-m_RecordX, point.y-m_RecordY);
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
	}

	if(!m_D3DApp.m_Attack.empty() && m_AttackID > -1){
		if(m_CtrlPress && !m_ShiftPress && m_LMouseHold && m_CtrlPoint != m_D3DApp.m_Attack[m_AttackID].End()){
			m_D3DApp.m_Attack[m_AttackID].Modify(m_CtrlPoint,point.x, point.y);
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}

		if (m_ShiftPress && m_CtrlPress && m_LMouseHold)
		{
			m_D3DApp.m_Attack[m_AttackID].Transale(dx,dy);
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
	}

	if (m_EnableCtrlCenter && m_CtrlPress && m_LMouseHold)
	{
		m_D3DApp.SetCenter(point.x,point.y);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}

	if(m_MMouseHold)
	{
		g_Frame_OffsetX += dx;
		g_Frame_OffsetY += dy;
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}

	
	CDockablePane::OnMouseMove(nFlags, point);
}


BOOL CD3DPanelView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if (m_CtrlPress && !m_ShiftPress)
	{
		if (zDelta > 0)
		{
			if (g_Frame_Scale < 10)
			{
				g_Frame_Scale += 0.1f;
			}
		}else{
			if (g_Frame_Scale > 0.1)
			{
				g_Frame_Scale -= 0.1f;
			}
		}
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}

	char buff[100];
	sprintf(buff, "   顯示比例 %.1f%%", g_Frame_Scale * 100);
	CString str(buff);
	((CMainFrame*)(this->GetParentFrame()))->SetStatus(str);

	return CDockablePane::OnMouseWheel(nFlags, zDelta, pt);
}

//Functions

void CD3DPanelView::SetPic( PictureData *pic,float x,float y )
{
	m_D3DApp.SetPic(pic,x,y);
	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
}


void CD3DPanelView::StopEdit()
{
	if (m_BodyID > -1)
	{
		m_D3DApp.m_Body[m_BodyID].SetLineColor(0,0,1);
		m_D3DApp.m_Body[m_BodyID].ChangeColor(0,0,1);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
		m_BodyID = -1;
	}
	if (m_AttackID > -1)
	{
		m_D3DApp.m_Attack[m_AttackID].SetLineColor(1,0,0);
		m_D3DApp.m_Attack[m_AttackID].ChangeColor(1,0,0);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
		m_AttackID = -1;
	}

	m_EnableCtrlCenter = false;
}

int CD3DPanelView::AddBody()
{
	m_D3DApp.m_Body.push_back(PointManager());
	return m_D3DApp.m_Body.size()-1;
}

void CD3DPanelView::DeleteBody( int id )
{
	StopEdit();
	if(id < (int)m_D3DApp.m_Body.size() && id>-1){
		m_D3DApp.m_Body.erase(m_D3DApp.m_Body.begin()+id);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
}

void CD3DPanelView::EditBody( int id )
{
	StopEdit();
	if(id < (int)m_D3DApp.m_Body.size() && id>-1){
		m_BodyID=id;
		m_CtrlPoint = m_D3DApp.m_Body[id].End();
		m_D3DApp.m_Body[id].SetLineColor(0,0,0);
		m_D3DApp.m_Body[id].ChangeColor(0,0,0);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
}

int CD3DPanelView::AddAttack()
{
	m_D3DApp.m_Attack.push_back(PointManager());
	return m_D3DApp.m_Attack.size()-1;
}

void CD3DPanelView::DeleteAttack( int id )
{
	StopEdit();
	if(id < (int)m_D3DApp.m_Attack.size() && id>-1){
		m_D3DApp.m_Attack.erase(m_D3DApp.m_Attack.begin()+id);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
}

void CD3DPanelView::EditAttack( int id )
{
	StopEdit();
	if(id < (int)m_D3DApp.m_Attack.size() && id>-1){
		m_AttackID=id;
		m_CtrlPoint = m_D3DApp.m_Attack[id].End();
		m_D3DApp.m_Attack[id].SetLineColor(0,0,0);
		m_D3DApp.m_Attack[id].ChangeColor(0,0,0);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
}

void CD3DPanelView::Init()
{
	StopEdit();
	m_D3DApp.m_Attack.clear();
	m_D3DApp.m_Body.clear();
}
BOOL CD3DPanelView::CanFloat() const
{
	return TRUE;
}

BOOL CD3DPanelView::CanBeClosed() const
{
	return FALSE;
}

BOOL CD3DPanelView::CanAutoHide() const
{
	return FALSE;
}

void CD3DPanelView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_MMouseHold =true;
	CDockablePane::OnMButtonDown(nFlags, point);
}


void CD3DPanelView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_MMouseHold =false;
	CDockablePane::OnMButtonUp(nFlags, point);
}
