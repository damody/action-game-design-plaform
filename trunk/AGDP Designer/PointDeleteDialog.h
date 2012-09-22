#pragma once


// CPointDeleteDialog 對話方塊

class CPointDeleteDialog : public CDialogEx
{
	DECLARE_DYNAMIC( CPointDeleteDialog )
public:
	const int m_MaxID;
	int m_CurID;
public:
	CPointDeleteDialog( int max, CWnd* pParent = NULL ); // 標準建構函式
	virtual ~CPointDeleteDialog();

// 對話方塊資料
	enum { IDD = IDD_POINTSUB };

protected:
	virtual void DoDataExchange( CDataExchange* pDX );  // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangePointid();
};
