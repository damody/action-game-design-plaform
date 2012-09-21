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

#pragma once
#include "Resource.h"

#define MAX_ACTIONS 52

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI( CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler )
	{
		CMFCToolBar::OnUpdateCmdUI( ( CFrameWnd* ) GetOwner(), bDisableIfNoHndler );
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
	CMFCPropertyGridPropertyButton( CMFCPropertyGridCtrl* grid, const CString& strName, const COleVariant& data, LPCTSTR lpszDescr, DWORD_PTR dwData );
	virtual ~CMFCPropertyGridPropertyButton() {}
	DECLARE_DYNAMIC( CMFCPropertyGridPropertyButton )
	void OnDrawName( CDC* pDC, CRect rect )
	{
		if ( m_Brush.m_hObject == NULL )
		{
			m_Brush.CreateSolidBrush( RGB( 220, 220, 220 ) );
		}

		pDC->FillRect( rect, &m_Brush );
		pDC->TextOut( rect.left + 2, rect.top + 2, m_Text );
	}
	void OnClickName( CPoint point );

};

class CMFCPropItem : public CMFCPropertyGridProperty
{
private:
	CMFCPropertyGridCtrl* m_MotherGrid;
	bool m_Update;
	bool m_Edited;
	COleVariant m_Record;
public:
	CMFCPropItem( CMFCPropertyGridCtrl* grid, const CString& strName, const COleVariant& data, LPCTSTR lpszDescr, DWORD_PTR dwData = 0 )
		: CMFCPropertyGridProperty( strName, data, lpszDescr, dwData ) {m_MotherGrid = grid; m_Update = false; m_Record = this->GetValue();}
	CMFCPropItem( CMFCPropertyGridCtrl* grid, const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE )
		: CMFCPropertyGridProperty( strGroupName, dwData, bIsValueList ) {m_MotherGrid = grid; m_Edited = false; m_Record = this->GetValue();}
	~CMFCPropItem() {}
	DECLARE_DYNAMIC( CMFCPropItem )
protected:
	virtual BOOL OnEdit( LPPOINT lptClick );
	virtual BOOL OnEndEdit();
	//virtual BOOL RemoveSubItem(CMFCPropertyGridProperty*& pProp, BOOL bDelete = TRUE);
	//virtual BOOL DeleteProperty(CMFCPropertyGridProperty*& pProp);
public:
	bool IsEdited();
	virtual void SetValue( const COleVariant& varValue );
};

class CPropertiesWnd : public CDockablePane
{
private:
	int m_EditProp;// 0-None 1-Basic 2-Frame 3-Bodys 4-Attack 5-Hit 6-Catch 7-Blood
	int m_Index;
// 建構
public:
	CPropertiesWnd();

	void AdjustLayout();
	virtual BOOL CanFloat() const;
	virtual BOOL CanBeClosed() const;
	virtual BOOL CanAutoHide() const;

	static CPropertiesWnd* GetInstance() {return instance;}
	static CMFCPropertyGridProperty* GetDefaultPropList();
	void SetVSDotNetLook( BOOL bSet );
	CMFCPropertyGridCtrl* GetPropList() {return &m_wndPropList;}
// 屬性
public:
	HTREEITEM m_lastSelectedItem;
protected:
	static CPropertiesWnd* instance;
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;
	static const CString actionMap[MAX_ACTIONS];
public:
	static VARIANT varFloat( float _value = 0 );
	static VARIANT varInt( int _value = 0 );
	static VARIANT varBool( bool _value = false );

// 程式碼實作
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties( CCmdUI* pCmdUI );
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties( CCmdUI* pCmdUI );
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1( CCmdUI* pCmdUI );
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2( CCmdUI* pCmdUI );
	afx_msg void OnSetFocus( CWnd* pOldWnd );
	afx_msg void OnSettingChange( UINT uFlags, LPCTSTR lpszSection );
	afx_msg LRESULT OnPropertyChanged( __in WPARAM wparam, __in LPARAM lparam );

	DECLARE_MESSAGE_MAP()

public:
	void Clear()
	{
		m_EditProp = 0;
		m_wndPropList.RemoveAll();
		SetPropListFont();
	}
	void InitPropList();
	void InitPropList_Frame();
	void InitPropList_Body() {InitPropList_Body(1);}
	void InitPropList_Body(int polygonCount);
	void InitPropList_Attack() {InitPropList_Attack(1);}
	void InitPropList_Attack(int polygonCount);
	void InitPropList_HitData();
	void InitPropList_CatchInfo() {InitPropList_CatchInfo(1);}
	void InitPropList_CatchInfo(int polygonCount);
	void InitPropList_BloodInfo();

	void RefreshPropList();
	void RefreshPropList_Frame();
	void RefreshPropList_Body() {RefreshPropList_Body(0);}
	void RefreshPropList_Body(int index);
	void RefreshPropList_Attack() {RefreshPropList_Attack(0);}
	void RefreshPropList_Attack(int index);
	void RefreshPropList_HitData() {RefreshPropList_HitData(0);}
	void RefreshPropList_HitData(int index);
	void RefreshPropList_CatchInfo() {RefreshPropList_CatchInfo(0);}
	void RefreshPropList_CatchInfo(int index);
	void RefreshPropList_BloodInfo() {RefreshPropList_BloodInfo(0);}
	void RefreshPropList_BloodInfo(int index);

	void SetPropListFont();
	static void AddNormalActionUcase( CMFCPropertyGridProperty* pProp );
	static void AddNormalActionDcase( CMFCPropertyGridProperty* pProp );
	static void AddPointXY( CMFCPropertyGridProperty*& pProp );

	void RefreshCenter();
	void RefreshBodyPoint(int i);
	void RefreshAttackPoint(int i);
public:
	void Update();
	void UpdatePropList_Frame();
	void UpdateBody();
	void UpdateAttack();
	//void DeleteProperty(CMFCPropertyGridProperty* pProp);
};