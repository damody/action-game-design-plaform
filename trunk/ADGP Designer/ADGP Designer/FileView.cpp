// 這個 MFC 範例原始程式碼會示範如何使用 MFC Microsoft Office Fluent 使用者介面
// (「Fluent UI」)，並且僅提供為參考資料，做為
// MFC 參考及 MFC C++ 程式庫軟體
// 隨附相關電子文件的補充。
// 關於 Fluent UI 之複製、使用或散發的授權條款則分別提供。
// 如需 Fluent UI 授權計劃的詳細資訊，請造訪 
// http://msdn.microsoft.com/officeui。
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "ADGP Designer.h"
#include "ConvStr.h"

#include "game/HeroInfo.h"
#include "Lua/LuaCell.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView()
{
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 訊息處理常式

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 建立檢視:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("無法建立檔案檢視\n");
		return -1;      // 無法建立
	}

	// 載入檢視影像:
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* 已鎖定 */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令都將經由此控制項傳送，而不是經由父框架:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// 填入一些靜態樹狀檢視資料 (假程式碼，不需要什麼特別的內容)
	FillFileView();
	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::FillFileView()
{
	hHeroDoc = m_wndFileView.InsertItem(_T("Hero 資料"), 0, 0);
	m_wndFileView.SetItemState(hHeroDoc, TVIS_BOLD, TVIS_BOLD);
	
	hObjectDoc = m_wndFileView.InsertItem(_T("Object 資料"), 0, 0);
	m_wndFileView.SetItemState(hObjectDoc, TVIS_BOLD, TVIS_BOLD);

	hBackgroundDoc = m_wndFileView.InsertItem(_T("Background 資料"), 0, 0);
	m_wndFileView.SetItemState(hBackgroundDoc, TVIS_BOLD, TVIS_BOLD);

/*
	HTREEITEM hInc = m_wndFileView.InsertItem(_T("FakeApp 標頭檔"), 0, 0, hRoot);

	m_wndFileView.InsertItem(_T("FakeApp.h"), 2, 2, hInc);
	m_wndFileView.InsertItem(_T("FakeAppDoc.h"), 2, 2, hInc);
	m_wndFileView.InsertItem(_T("FakeAppView.h"), 2, 2, hInc);
	m_wndFileView.InsertItem(_T("Resource.h"), 2, 2, hInc);
	m_wndFileView.InsertItem(_T("MainFrm.h"), 2, 2, hInc);
	m_wndFileView.InsertItem(_T("StdAfx.h"), 2, 2, hInc);

	HTREEITEM hRes = m_wndFileView.InsertItem(_T("FakeApp 資源檔"), 0, 0, hRoot);

	m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hRes);
	m_wndFileView.InsertItem(_T("FakeApp.rc2"), 2, 2, hRes);
	m_wndFileView.InsertItem(_T("FakeAppDoc.ico"), 2, 2, hRes);
	m_wndFileView.InsertItem(_T("FakeToolbar.bmp"), 2, 2, hRes);

	m_wndFileView.Expand(hRoot, TVE_EXPAND);
	m_wndFileView.Expand(hSrc, TVE_EXPAND);
	m_wndFileView.Expand(hInc, TVE_EXPAND);
*/
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 選取按下的項目:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnProperties()
{
	AfxMessageBox(_T("屬性...."));

}

void CFileView::OnFileOpen()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Lua Files (*.lua)|*.lua||"), NULL, 0);
	
	if (dlgFile.DoModal()==IDOK)
	{
		LuaCell_Sptr data = LuaCell_Sptr(new LuaCell);
		if (data->InputLuaFile(dlgFile.GetPathName()))
		{
// 			if (HeroInfo::CheckHeroDataVaild(data))
// 			{
				HTREEITEM hHero = m_wndFileView.InsertItem(dlgFile.GetFileTitle(),2,2,hHeroDoc);
				HeroInfo_RawPtr hero =HeroInfo_RawPtr(new HeroInfo);
				hero->LoadHeroData(data);
				for (unsigned int i=0;i<hero->m_PictureDatas.size();i++)
				{
					std::string pic = hero->m_PictureDatas[i].m_Path;
					size_t found;
					found=pic.rfind('\\');
					char buff[100];
					sprintf(buff,"%s",pic.substr(found+1,pic.length()).c_str());
					CString str(buff);
					m_wndFileView.InsertItem(str,2,2,hHero);
				}
				m_HeroInfoMap[hHero]=hero;
				m_wndFileView.Expand(hHeroDoc, TVE_EXPAND);
//			}
		}else{
			char buff[100];
			sprintf(buff, "Lua Loading Failed");
			CString str(buff);
			AfxMessageBox(str);
		}	
	}
	
	
}

void CFileView::OnFileOpenWith()
{
	// TODO: 在此加入您的命令處理常式程式碼
}

void CFileView::OnDummyCompile()
{
	// TODO: 在此加入您的命令處理常式程式碼
}

void CFileView::OnEditCut()
{
	// TODO: 在此加入您的命令處理常式程式碼
}

void CFileView::OnEditCopy()
{
	// TODO: 在此加入您的命令處理常式程式碼
}

void CFileView::OnEditClear()
{
	// TODO: 在此加入您的命令處理常式程式碼
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // 繪製的裝置內容

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 鎖定 */);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("無法載入點陣圖: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}


BOOL CFileView::CanFloat() const
{
	return TRUE;
}

BOOL CFileView::CanBeClosed() const
{
	return FALSE;
}

BOOL CFileView::CanAutoHide() const
{
	return FALSE;
}

void CFileView::OnSelectItem( HTREEITEM item )
{
	HeroInfohMap::iterator it = m_HeroInfoMap.find(item);

	if (it!= m_HeroInfoMap.end())
	{
		g_HeroInfo = it->second;
		for(unsigned int i=0;i < g_HeroInfo->m_PictureDatas.size();i++)
		{
			((CMainFrame*)this->GetParentFrame())->OpenDesignerView(i);
		}
		g_ActiveFramesMap = &g_HeroInfo->m_FramesMap;
		g_FrameName = "";
		g_FrameIndex = -1;
		((CMainFrame*)this->GetParentFrame())->m_wndClassView.Refresh();
		((CMainFrame*)this->GetParentFrame())->Clear();
	}
	
	
}


