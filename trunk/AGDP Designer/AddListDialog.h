#pragma once


// CAddListDialog 對話方塊

class CAddListDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAddListDialog)
	std::wstring m_Text;
public:
	CAddListDialog(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CAddListDialog();

// 對話方塊資料
	enum { IDD = IDD_ADDLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
};
