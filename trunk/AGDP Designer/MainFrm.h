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

// MainFrm.h : CMainFrame ���O������
//

#pragma once

#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "Resource.h"
#include "D3DPanelView.h"
#include "AGDP DesignerView.h"

#include <map>
typedef std::map<HeroInfo*, CAGDPDesignerView*> HeroViews;

extern CAGDPDesignerView* g_NewView;

class COutlookBar : public CMFCOutlookBar
{
	virtual BOOL AllowShowOnPaneMenu() const { return TRUE; }
	virtual void GetPaneName( CString& strName ) const { BOOL bNameValid = strName.LoadString( IDS_OUTLOOKBAR ); ASSERT( bNameValid ); if ( !bNameValid ) { strName.Empty(); } }
};

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC( CMainFrame )
public:
	CMainFrame();

// �ݩ�
public:

// �@�~
public:

// �мg
public:
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
	CMFCTabCtrl m_Tab;
// �{���X��@
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif
	void RefreshFrameEdit()
	{
		m_D3DFrameView.Refresh();
		m_wndProperties.RefreshPropList_Frame();
	}
	void EditBody( int id )
	{
		m_D3DFrameView.EditBody( id );
		m_wndProperties.RefreshPropList_Body( id );
	}
	void EditAttack( int id )
	{
		m_D3DFrameView.EditAttack( id );
		m_wndProperties.RefreshPropList_Attack();
	}
	void EditAttack()
	{
		m_D3DFrameView.EditCenter();
	}

	void SetStatus( const CString& str )
	{
		m_wndStatusBar.SetInformation( str );
	}
	void AddStrToOutputDebug( const CString& strAddToList )
	{
		m_wndOutput.AddStrToOutputDebug( CString( strAddToList ) );
	}
	void AddStrToOutputBuild( const CString& strAddToList )
	{
		m_wndOutput.AddStrToOutputBuild( CString( strAddToList ) );
	}
	void AddStrToOutputFind( const CString& strAddToList )
	{
		m_wndOutput.AddStrToOutputFind( CString( strAddToList ) );
	}
	void Clear()
	{
		m_wndProperties.Clear();
		m_D3DFrameView.Clear();
	}
	void test();
	bool NewHeroViews( HeroInfo* hero );
	void OpenPictureView( CString& name, PictureData* pic, int index );
	void SwitchPictureView( int index );

public:  // ����C���O������
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	CFileView         m_wndFileView;
	CClassView        m_wndClassView;
	CDockablePane*	  m_AttachPane;
	COutputWnd        m_wndOutput;
	CPropertiesWnd    m_wndProperties;
	CMFCShellTreeCtrl m_wndTree;
	CMFCCaptionBar    m_wndCaptionBar;
	CD3DPanelView	  m_D3DFrameView;
	HeroViews	  m_HeroViews;
// ���ͪ��T�������禡
protected:
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg int  OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook( UINT id );
	afx_msg void OnUpdateApplicationLook( CCmdUI* pCmdUI );
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar( CCmdUI* pCmdUI );
	afx_msg void OnOptions();
	afx_msg void OnSettingChange( UINT uFlags, LPCTSTR lpszSection );
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons( BOOL bHiColorIcons );
	BOOL CreateCaptionBar();

	int FindFocusedOutlookWnd( CMFCOutlookBarTabCtrl** ppOutlookWnd );

	CMFCOutlookBarTabCtrl* FindOutlookParent( CWnd* pWnd );
	CMFCOutlookBarTabCtrl* m_pCurrOutlookWnd;
	CMFCOutlookBarPane*    m_pCurrOutlookPage;
public:
	afx_msg void OnButtonAreaAdd();
	afx_msg void OnButtonAreaMove();
	afx_msg void OnButtonAreaScale();
	virtual BOOL OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );
	afx_msg void OnCheckFrameview();
	afx_msg void OnUpdateCheckFrameview( CCmdUI* pCmdUI );
	afx_msg void OnCheckOutputwindow();
	afx_msg void OnUpdateCheckOutputwindow( CCmdUI* pCmdUI );
	afx_msg void OnCheckSolutionmanager();
	afx_msg void OnUpdateCheckSolutionmanager( CCmdUI* pCmdUI );
	afx_msg void OnCheckHeromanager();
	afx_msg void OnUpdateCheckHeromanager( CCmdUI* pCmdUI );
	afx_msg void OnCheckProperty();
	afx_msg void OnUpdateCheckProperty( CCmdUI* pCmdUI );
	afx_msg void OnButtonAddnewarea();
};


