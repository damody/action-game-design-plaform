#pragma once


// CFileNewDialog 對話方塊

class CFileNewDialog : public CDialogEx
{
	DECLARE_DYNAMIC( CFileNewDialog )
public:
	CFileNewDialog( CWnd* pParent = NULL ); // 標準建構函式
	virtual ~CFileNewDialog();
	CString m_Name;
	int m_Type;
// 對話方塊資料
	enum { IDD = IDD_FILENEW};

protected:
	virtual void DoDataExchange( CDataExchange* pDX );  // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCreatehero();
	afx_msg void OnBnClickedCreateobject();
	afx_msg void OnBnClickedCreatebg();
	afx_msg void OnEnChangeEditname();
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
};
