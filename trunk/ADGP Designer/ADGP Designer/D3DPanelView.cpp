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

CD3DPanelView::CD3DPanelView(CWnd* pParent /*=NULL*/):m_TrackMouse(true),m_LMouseHold(false),m_MMouseHold(false),m_CtrlPress(false),m_KeyAPress(false),m_EnableCtrlCenter(false),m_ShiftPress(false),
m_RecordX(0),m_RecordY(0),m_BodyID(-1),m_AttackID(-1),m_FrameInfo(NULL),m_PointIndex(-1)
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
	ON_WM_MOUSELEAVE()
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
		if(m_CtrlPress && !m_ShiftPress && m_PointIndex > -1){
			switch(nChar)
			{
			case KEY_LEFT:
				m_D3DApp.m_Body[m_BodyID].Transale(m_PointIndex,-1,0);
				UpdateAttack(m_PointIndex);
				break;
			case KEY_UP:
				m_D3DApp.m_Body[m_BodyID].Transale(m_PointIndex,0,-1);
				UpdateAttack(m_PointIndex);
				break;
			case KEY_RIGHT:
				m_D3DApp.m_Body[m_BodyID].Transale(m_PointIndex,1,0);
				UpdateAttack(m_PointIndex);
				break;
			case KEY_DOWN:
				m_D3DApp.m_Body[m_BodyID].Transale(m_PointIndex,0,1);
				UpdateAttack(m_PointIndex);
				break;
			case KEY_DELETE:
				m_D3DApp.m_Body[m_BodyID].Erase(m_PointIndex);
				UpdateBody();
				m_PointIndex = -1;
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
				UpdateBody();
				break;
			case KEY_UP:
				m_D3DApp.m_Body[m_BodyID].Transale(0,-1);
				UpdateBody();
				break;
			case KEY_RIGHT:
				m_D3DApp.m_Body[m_BodyID].Transale(1,0);
				UpdateBody();
				break;
			case KEY_DOWN:
				m_D3DApp.m_Body[m_BodyID].Transale(0,1);
				UpdateBody();
				break;
			case KEY_DELETE:
				m_D3DApp.m_Body[m_BodyID].Clear();
				m_PointIndex = -1;
				break;
			}
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
	}

	if(!m_D3DApp.m_Attack.empty() && m_AttackID > -1){
		if(m_CtrlPress && !m_ShiftPress && m_PointIndex > -1){
			switch(nChar)
			{
			case KEY_LEFT:
				m_D3DApp.m_Attack[m_AttackID].Transale(m_PointIndex,-1,0);
				UpdateAttack(m_PointIndex);
				break;
			case KEY_UP:
				m_D3DApp.m_Attack[m_AttackID].Transale(m_PointIndex,0,-1);
				UpdateAttack(m_PointIndex);
				break;
			case KEY_RIGHT:
				m_D3DApp.m_Attack[m_AttackID].Transale(m_PointIndex,1,0);
				UpdateAttack(m_PointIndex);
				break;
			case KEY_DOWN:
				m_D3DApp.m_Attack[m_AttackID].Transale(m_PointIndex,0,1);
				UpdateAttack(m_PointIndex);
				break;
			case KEY_DELETE:
				m_D3DApp.m_Attack[m_AttackID].Erase(m_PointIndex);
				UpdateAttack();
				m_PointIndex = -1;
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
				UpdateAttack();
				break;
			case KEY_UP:
				m_D3DApp.m_Attack[m_AttackID].Transale(0,-1);
				UpdateAttack();
				break;
			case KEY_RIGHT:
				m_D3DApp.m_Attack[m_AttackID].Transale(1,0);
				UpdateAttack();
				break;
			case KEY_DOWN:
				m_D3DApp.m_Attack[m_AttackID].Transale(0,1);
				UpdateAttack();
				break;
			case KEY_DELETE:
				m_D3DApp.m_Attack[m_AttackID].Clear();
				UpdateAttack();
				m_PointIndex = -1;
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
			if(m_PointIndex > -1){
				m_D3DApp.m_Body[m_BodyID].ChangeColor(m_PointIndex,0.0f,0.0f,0.0f);
				m_PointIndex = -1;
				m_D3DApp.buildPoint();
				m_D3DApp.DrawScene();
			}
		}

		if(!m_D3DApp.m_Attack.empty() && m_AttackID > -1)
		{
			if(m_PointIndex > -1){
				m_D3DApp.m_Attack[m_AttackID].ChangeColor(m_PointIndex,0.0f,0.0f,0.0f);
				m_PointIndex = -1;
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
			UpdateAddition_BodyPoint(point.x,point.y);
			m_PointIndex = -1;
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
		if(m_CtrlPress && !m_ShiftPress){
			if(m_PointIndex < 0){
				m_PointIndex = m_D3DApp.m_Body[m_BodyID].Select_GetIndex(point.x, point.y);
				m_D3DApp.m_Body[m_BodyID].ChangeColor(m_PointIndex,1.0f,1.0f,0.0f);
			}else{
				m_D3DApp.m_Body[m_BodyID].Modify(m_PointIndex,point.x, point.y);
				UpdateBody(m_PointIndex);
			}

			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
	}

	if(!m_D3DApp.m_Attack.empty() && m_AttackID > -1){
		if(m_KeyAPress && !m_CtrlPress && !m_ShiftPress){
			m_D3DApp.m_Attack[m_AttackID].Add(point.x, point.y);
			UpdateAddition_AttackPoint(point.x, point.y);
			m_PointIndex = -1;
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
		if(m_CtrlPress && !m_ShiftPress){
			if(m_PointIndex < 0){
				m_PointIndex = m_D3DApp.m_Attack[m_AttackID].Select_GetIndex(point.x, point.y);
				m_D3DApp.m_Attack[m_AttackID].ChangeColor(m_PointIndex,1.0f,1.0f,0.0f);
			}else{
				m_D3DApp.m_Attack[m_AttackID].Modify(m_PointIndex,point.x, point.y);
				UpdateAttack(m_PointIndex);
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
	if(m_TrackMouse){
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = this->m_hWnd;
		_TrackMouseEvent(&tme);
		m_TrackMouse =false;
	}
	

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
		if(m_CtrlPress && !m_ShiftPress && m_LMouseHold && m_PointIndex > -1){
			m_D3DApp.m_Body[m_BodyID].Modify(m_PointIndex,point.x, point.y);
			UpdateBody(m_PointIndex);
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}

		if (m_ShiftPress && m_CtrlPress && m_LMouseHold)
		{
			m_D3DApp.m_Body[m_BodyID].Transale(point.x-m_RecordX, point.y-m_RecordY);
			m_D3DApp.buildPoint();
			UpdateBody();
			m_D3DApp.DrawScene();
		}
	}

	if(!m_D3DApp.m_Attack.empty() && m_AttackID > -1){
		if(m_CtrlPress && !m_ShiftPress && m_LMouseHold && m_PointIndex > -1){
			m_D3DApp.m_Attack[m_AttackID].Modify(m_PointIndex,point.x, point.y);
			UpdateAttack(m_PointIndex);
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}

		if (m_ShiftPress && m_CtrlPress && m_LMouseHold)
		{
			m_D3DApp.m_Attack[m_AttackID].Transale(dx,dy);
			UpdateAttack();
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
	}

	if (m_EnableCtrlCenter && m_CtrlPress && m_LMouseHold)
	{
		m_D3DApp.SetCenter(point.x,point.y);
		UpdateCenter(point.x,point.y);
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

void CD3DPanelView::OnMouseLeave()
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
// 	char buff[100];
// 	sprintf(buff, "Leave");
// 	CString str(buff);
// 	AfxMessageBox(str);
	InitEdit();
	
	CDockablePane::OnMouseLeave();
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

void CD3DPanelView::EditBody( int id )
{
	StopEdit();
	if(id < (int)m_D3DApp.m_Body.size() && id>-1){
		m_BodyID=id;
		m_PointIndex = -1;
		m_D3DApp.m_Body[id].SetLineColor(0,0,0);
		m_D3DApp.m_Body[id].ChangeColor(0,0,0);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
}

void CD3DPanelView::EditAttack( int id )
{
	StopEdit();
	if(id < (int)m_D3DApp.m_Attack.size() && id>-1){
		m_AttackID=id;
		m_PointIndex = -1;
		m_D3DApp.m_Attack[id].SetLineColor(0,0,0);
		m_D3DApp.m_Attack[id].ChangeColor(0,0,0);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
}

void CD3DPanelView::EditCenter()
{
	StopEdit();
	m_EnableCtrlCenter = true;
}

void CD3DPanelView::Init()
{
	StopEdit();
	InitEdit();
	m_FrameInfo = NULL;
	m_D3DApp.Init();
}

void CD3DPanelView::Refresh()
{
	Init();
	FramesMap::iterator it_FrameInfos = g_ActiveFramesMap->find(g_FrameName);
	if (it_FrameInfos != g_ActiveFramesMap->end())
	{
		if (g_FrameIndex > -1 && g_FrameIndex < it_FrameInfos->second.size())
		{
			m_D3DApp.SetPic(&g_HeroInfo->m_PictureDatas[m_FrameInfo->m_PictureID],m_FrameInfo->m_PictureX,m_FrameInfo->m_PictureY);
			m_D3DApp.SetCenter(m_FrameInfo->m_CenterX,m_FrameInfo->m_CenterY);

			m_FrameInfo = &it_FrameInfos->second[g_FrameIndex];
			for (Bodys::iterator it_body=m_FrameInfo->m_Bodys.begin(); it_body != m_FrameInfo->m_Bodys.end();it_body++)
			{
				PointManager pm;
				for (Vec2s::iterator it_v = it_body->m_Area.Points().begin(); it_v !=it_body->m_Area.Points().end(); it_v++)
				{
					pm.Add(it_v->x,it_v->y,0,0,1);
				}
				pm.SetLineColor(0,0,1);
				m_D3DApp.m_Body.push_back(pm);
			}

			for (Attacks::iterator it_att=m_FrameInfo->m_Attacks.begin(); it_att != m_FrameInfo->m_Attacks.end();it_att++)
			{
				PointManager pm;
				for (Vec2s::iterator it_v = it_att->m_Area.Points().begin(); it_v !=it_att->m_Area.Points().end(); it_v++)
				{
					pm.Add(it_v->x,it_v->y,1,0,0);
				}
				pm.SetLineColor(1,0,0);
				m_D3DApp.m_Attack.push_back(pm);
			}

			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}else{
			char buff[100];
			sprintf(buff, "FrameEdit: Frame[%s][%d] does not exist",g_FrameName.c_str(),g_FrameIndex);
			CString str(buff);
			AfxMessageBox(str);
			((CMainFrame*)(this->GetParentFrame()))->AddStrToOutputBuild(str);
			return;
		}
	}else{
		char buff[100];
		sprintf(buff, "FrameEdit: Frame[%s] does not exist",g_FrameName.c_str());
		CString str(buff);
		AfxMessageBox(str);
		((CMainFrame*)(this->GetParentFrame()))->AddStrToOutputBuild(str);
		return;
	}
}

void CD3DPanelView::InitEdit()
{
	m_TrackMouse = true;
	m_LMouseHold = false;
	m_MMouseHold = false;
	m_CtrlPress = false;
	m_KeyAPress = false;
	m_ShiftPress = false;

	if(!m_D3DApp.m_Body.empty() && m_BodyID > -1)
	{
		if(m_PointIndex > -1){
			m_D3DApp.m_Body[m_BodyID].ChangeColor(m_PointIndex,0.0f,0.0f,0.0f);
			m_PointIndex = -1;
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
	}

	if(!m_D3DApp.m_Attack.empty() && m_AttackID > -1)
	{
		if(m_PointIndex > -1){
			m_D3DApp.m_Attack[m_AttackID].ChangeColor(m_PointIndex,0.0f,0.0f,0.0f);
			m_PointIndex = -1;
			m_D3DApp.buildPoint();
			m_D3DApp.DrawScene();
		}
	}
}

void CD3DPanelView::UpdateCenter( float x,float y )
{
	if(m_FrameInfo != NULL){
		m_FrameInfo->m_CenterX = x;
		m_FrameInfo->m_CenterY = y;
	}
	//Refresh
}

void CD3DPanelView::UpdateBody()
{
	if(m_FrameInfo==NULL)return;
	m_FrameInfo->m_Bodys[m_BodyID].m_Area.Clear();
	for(Points::iterator it = m_D3DApp.m_Body[m_BodyID].GetPoints().begin(); it != m_D3DApp.m_Body[m_BodyID].GetPoints().end(); ++it)
	{
		m_FrameInfo->m_Bodys[m_BodyID].m_Area.AddPoint(it->x,it->y);
	}

	//Refresh
}

void CD3DPanelView::UpdateBody( int index )
{
	if(m_FrameInfo==NULL)return;
	m_FrameInfo->m_Bodys[m_BodyID].m_Area.Points()[index].x = m_D3DApp.m_Body[m_BodyID].GetPoints()[index].x;
	m_FrameInfo->m_Bodys[m_BodyID].m_Area.Points()[index].y = m_D3DApp.m_Body[m_BodyID].GetPoints()[index].y;

	//Refresh
}

void CD3DPanelView::UpdateAddition_BodyPoint( float x,float y )
{
	if(m_FrameInfo==NULL)return;
	m_FrameInfo->m_Bodys[m_BodyID].m_Area.AddPoint(x,y);

	//Refresh
}

void CD3DPanelView::UpdateAttack()
{
	if(m_FrameInfo==NULL)return;
	m_FrameInfo->m_Attacks[m_BodyID].m_Area.Clear();
	for(Points::iterator it = m_D3DApp.m_Attack[m_BodyID].GetPoints().begin(); it != m_D3DApp.m_Attack[m_BodyID].GetPoints().end(); ++it)
	{
		m_FrameInfo->m_Attacks[m_BodyID].m_Area.AddPoint(it->x,it->y);
	}

	//Refresh
}

void CD3DPanelView::UpdateAttack( int index )
{
	if(m_FrameInfo==NULL)return;
	m_FrameInfo->m_Attacks[m_BodyID].m_Area.Points()[index].x = m_D3DApp.m_Attack[m_BodyID].GetPoints()[index].x;
	m_FrameInfo->m_Attacks[m_BodyID].m_Area.Points()[index].y = m_D3DApp.m_Attack[m_BodyID].GetPoints()[index].y;

	//Refresh
}

void CD3DPanelView::UpdateAddition_AttackPoint( float x,float y )
{
	if(m_FrameInfo==NULL)return;
	m_FrameInfo->m_Attacks[m_BodyID].m_Area.AddPoint(x,y);

	//Refresh
}






