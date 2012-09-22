#pragma once


// CPointAddDiolog 對話方塊

class CPointAddDiolog : public CDialogEx
{
	DECLARE_DYNAMIC( CPointAddDiolog )
public:
	float x, y;
public:
	CPointAddDiolog( CWnd* pParent = NULL ); // 標準建構函式
	virtual ~CPointAddDiolog();

// 對話方塊資料
	enum { IDD = IDD_POINTADD };

protected:
	virtual void DoDataExchange( CDataExchange* pDX );  // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeXvaule();
	afx_msg void OnEnChangeYvalue();
};
