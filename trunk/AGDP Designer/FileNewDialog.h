#pragma once


// CFileNewDialog ��ܤ��

class CFileNewDialog : public CDialogEx
{
	DECLARE_DYNAMIC( CFileNewDialog )
public:
	CFileNewDialog( CWnd* pParent = NULL ); // �зǫغc�禡
	virtual ~CFileNewDialog();
	CString m_Name;
	int m_Type;
// ��ܤ�����
	enum { IDD = IDD_FILENEW};

protected:
	virtual void DoDataExchange( CDataExchange* pDX );  // DDX/DDV �䴩
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCreatehero();
	afx_msg void OnBnClickedCreateobject();
	afx_msg void OnBnClickedCreatebg();
	afx_msg void OnEnChangeEditname();
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
};
