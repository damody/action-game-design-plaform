#pragma once


// CPointAddDiolog ��ܤ��

class CPointAddDiolog : public CDialogEx
{
	DECLARE_DYNAMIC( CPointAddDiolog )
public:
	float x, y;
public:
	CPointAddDiolog( CWnd* pParent = NULL ); // �зǫغc�禡
	virtual ~CPointAddDiolog();

// ��ܤ�����
	enum { IDD = IDD_POINTADD };

protected:
	virtual void DoDataExchange( CDataExchange* pDX );  // DDX/DDV �䴩
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeXvaule();
	afx_msg void OnEnChangeYvalue();
};
