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
#include "Resource.h"

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CMFCPropertyGridPropertyButton : public CMFCPropertyGridProperty
{
private:
	CBrush m_Brush;
	CString m_Text;
	CMFCPropertyGridCtrl* m_MotherGrid;
public:
	int	m_Count;
	CMFCPropertyGridPropertyButton(CMFCPropertyGridCtrl* grid, const CString& strName, const COleVariant& data, LPCTSTR lpszDescr, DWORD_PTR dwData);
	virtual ~CMFCPropertyGridPropertyButton(){}
	DECLARE_DYNAMIC(CMFCPropertyGridPropertyButton)
	void OnDrawName( CDC* pDC, CRect rect )
	{
		if (m_Brush.m_hObject == NULL)
			m_Brush.CreateSolidBrush(RGB(220,220,220));
		pDC->FillRect(rect,&m_Brush);
		pDC->TextOut(rect.left+2,rect.top+2, m_Text);	
	}
	void OnClickName( CPoint point );
};

class CPropertiesWnd : public CDockablePane
{
// �غc
public:
	CPropertiesWnd();

	void AdjustLayout();
	virtual BOOL CanFloat() const;
	virtual BOOL CanBeClosed() const;
	virtual BOOL CanAutoHide() const;

	static CPropertiesWnd* GetInstance(){return instance;}
	static CMFCPropertyGridProperty* GetDefaultPropList();
	void SetVSDotNetLook(BOOL bSet);
	CMFCPropertyGridCtrl* GetPropList(){return &m_wndPropList;}
// �ݩ�
public:
	HTREEITEM m_lastSelectedItem;
protected:
	static CPropertiesWnd* instance;
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

// �{���X��@
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT OnPropertyChanged( __in WPARAM wparam, __in LPARAM lparam );

	DECLARE_MESSAGE_MAP()

public:
	void InitPropList();
	void InitPropList_Frame();
	void InitPropList_Body();
	void InitPropList_Attack();
	void InitPropList_HitData();
	void InitPropList_CatchInfo();
	void InitPropList_BloodInfo();
	void SetPropListFont();
	static void AddNormalActionUcase(CMFCPropertyGridProperty* pProp);
	static void AddNormalActionDcase(CMFCPropertyGridProperty* pProp);
	static void AddPointXY(CMFCPropertyGridProperty*& pProp);

};


