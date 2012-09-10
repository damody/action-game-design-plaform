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

#pragma once

#include "FileTree.h"
#include "game/HeroInfo.h"

typedef std::map<HTREEITEM, HeroInfo_RawPtr> HeroInfohMap;

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI( CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler )
	{
		CMFCToolBar::OnUpdateCmdUI( ( CFrameWnd* ) GetOwner(), bDisableIfNoHndler );
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// �غc
public:
	CFileView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	virtual BOOL CanFloat() const;
	virtual BOOL CanBeClosed() const;
	virtual BOOL CanAutoHide() const;
// �ݩ�
protected:

	CFileTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

protected:
	void FillFileView();

// �{���X��@
public:
	virtual ~CFileView();
	void OnSelectItem( HTREEITEM item );
	afx_msg void OnFileOpen();
private:
	HTREEITEM hHeroDoc;
	HTREEITEM hHero_Select;
	HTREEITEM hObjectDoc;
	HTREEITEM hBackgroundDoc;

	HeroInfohMap m_HeroInfoMap;


protected:
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnContextMenu( CWnd* pWnd, CPoint point );
	afx_msg void OnProperties();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus( CWnd* pOldWnd );

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnPicturedataAdd();
	afx_msg void OnPicturedataAdd();
};

