
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

// ADGP DesignerView.cpp : CADGPDesignerView ���O����@
//

#include "stdafx.h"
// SHARED_HANDLERS �i�H�w�q�b��@�w���B�Y�ϩM�j�M�z�����B�z�`����
// ATL �M�פ��A�ä��\�P�ӱM�צ@�Τ��{���X�C
#ifndef SHARED_HANDLERS
#include "ADGP Designer.h"
#endif

#include "ADGP DesignerDoc.h"
#include "ADGP DesignerView.h"
#include "MainFrm.h"
#include "global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CADGPDesignerView

IMPLEMENT_DYNCREATE(CADGPDesignerView, CView)

BEGIN_MESSAGE_MAP(CADGPDesignerView, CView)
	// �зǦC�L�R�O
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CADGPDesignerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CADGPDesignerView �غc/�Ѻc

CADGPDesignerView::CADGPDesignerView():m_LMouseHold(false),m_CtrlPress(false),m_KeyAPress(false),m_EnableCtrlCenter(false),m_ShiftPress(false),m_RecordX(0),m_RecordY(0),m_BodyID(-1)
{
	// TODO: �b���[�J�غc�{���X
}

CADGPDesignerView::~CADGPDesignerView()
{
}

BOOL CADGPDesignerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �b���g�ѭק� CREATESTRUCT cs 
	// �F��ק�������O�μ˦����ت�

	return CView::PreCreateWindow(cs);
}

// CADGPDesignerView �yø

void CADGPDesignerView::OnDraw(CDC* /*pDC*/)
{
	CADGPDesignerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �b���[�J��͸�ƪ��yø�{���X
	
	
// 	m_D3DApp.buildPoint();
// 	m_D3DApp.DrawScene();
}


// CADGPDesignerView �C�L


void CADGPDesignerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CADGPDesignerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �w�]���ǳƦC�L�{���X
	return DoPreparePrinting(pInfo);
}

void CADGPDesignerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �[�J�C�L�e�B�~����l�]�w
}

void CADGPDesignerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �[�J�C�L�᪺�M���{���X
}

void CADGPDesignerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CADGPDesignerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CADGPDesignerView �E�_

#ifdef _DEBUG
void CADGPDesignerView::AssertValid() const
{
	CView::AssertValid();
}

void CADGPDesignerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CADGPDesignerDoc* CADGPDesignerView::GetDocument() const // ���O�D��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CADGPDesignerDoc)));
	return (CADGPDesignerDoc*)m_pDocument;
}


#endif //_DEBUG

void CADGPDesignerView::InitDx11( HWND hWnd )
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
	temp->m_TextureID = g_TextureManager.AddTexture(temp->m_Path);
	temp->m_Width = 79;
	temp->m_Height = 79;
	temp->m_Row = 10;
	temp->m_Column = 7;
	m_D3DApp.SetPic(temp,1,1);
	m_D3DApp.buildPoint();
	m_D3DApp.DrawScene();
	//*/
}

// CADGPDesignerView �T���B�z�`��


void CADGPDesignerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �b���[�J�S�w���{���X�M (��) �I�s�����O
	//InitDx11(this->GetParent()->GetSafeHwnd());
}


void CADGPDesignerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �b���[�J�z���T���B�z�`���{���X
	if (cx > 0 && cy >0)
		m_D3DApp.OnResize(cx, cy);
}

void CADGPDesignerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
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

	

	CView::OnLButtonDown(nFlags, point);
}

void CADGPDesignerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	m_LMouseHold = false;
	CView::OnLButtonUp(nFlags, point);
}

void CADGPDesignerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	point.x =(point.x-g_Frame_OffsetX)/g_Frame_Scale;
	point.y =(point.y-g_Frame_OffsetY)/g_Frame_Scale;

	char buff[100];
	sprintf(buff, "   �y�Ц�m( %d , %d )", point.x, point.y);
	CString str(buff);
	((CMainFrame*)(this->GetParent()->GetParentFrame()))->SetStatus(str);


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
			m_D3DApp.m_Attack[m_AttackID].Transale(point.x-m_RecordX, point.y-m_RecordY);
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

	m_RecordX = point.x;
	m_RecordY = point.y;
	CView::OnMouseMove(nFlags, point);
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

void CADGPDesignerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��

// 	char buff[100];
// 	sprintf(buff, "%d", nChar);
// 	CString str(buff);
// 	AfxMessageBox(str);

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

	CView::OnKeyDown(nChar, nRepCnt, nFlags);

}

void CADGPDesignerView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��

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
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}



void CADGPDesignerView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �b���[�J�z���T���B�z�`���{���X
	// ���n�I�s�Ϥ��T���� CView::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	m_D3DApp.OnResize(rect.Width(), rect.Height());
	m_D3DApp.DrawScene();
}


BOOL CADGPDesignerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	if (m_CtrlPress && !m_ShiftPress)
	{
		if (zDelta > 0)
		{
			if (g_Frame_Scale < 10)
			{
				g_Frame_Scale += 0.1f;
			}
		}else{
			if (g_Frame_Scale > 1)
			{
				g_Frame_Scale -= 0.1f;
			}
		}
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

//Functions
void CADGPDesignerView::Init()
{
	StopEdit();
	m_D3DApp.m_Attack.clear();
	m_D3DApp.m_Body.clear();
}

void CADGPDesignerView::SetPic( PictureData *pic,float x,float y )
{
	m_D3DApp.SetPic(pic,x,y);
}

void CADGPDesignerView::StopEdit()
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

int CADGPDesignerView::AddBody()
{
	m_D3DApp.m_Body.push_back(PointManager());
	return m_D3DApp.m_Body.size()-1;
}

void CADGPDesignerView::EditBody( int id )
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

void CADGPDesignerView::DeleteBody( int id )
{
	StopEdit();
	if(id < (int)m_D3DApp.m_Body.size() && id>-1){
		m_D3DApp.m_Body.erase(m_D3DApp.m_Body.begin()+id);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
}

int CADGPDesignerView::AddAttack()
{
	m_D3DApp.m_Attack.push_back(PointManager());
	return m_D3DApp.m_Attack.size()-1;
}

void CADGPDesignerView::EditAttack( int id )
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

void CADGPDesignerView::DeleteAttack( int id )
{
	StopEdit();
	if(id < (int)m_D3DApp.m_Attack.size() && id>-1){
		m_D3DApp.m_Attack.erase(m_D3DApp.m_Attack.begin()+id);
		m_D3DApp.buildPoint();
		m_D3DApp.DrawScene();
	}
}


