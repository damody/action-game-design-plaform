#pragma once


// CPointDeleteDialog 對話方塊

class CPointDeleteDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPointDeleteDialog)

public:
	CPointDeleteDialog(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CPointDeleteDialog();

// 對話方塊資料
	enum { IDD = IDD_POINTSUB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
};
