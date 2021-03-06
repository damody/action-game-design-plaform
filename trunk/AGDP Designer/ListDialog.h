#pragma once
#include <vector>
// CActionListDialog 對話方塊

class CListDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CListDialog)
	
public:
	CListDialog(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CListDialog();

	std::wstring m_Select;
	std::vector<std::wstring> m_List;

	void AddList(std::wstring& str);
	void SetTitle(std::wstring& title);
	BOOL OnInitDialog();
// 對話方塊資料
	enum { IDD = IDD_LIST };

protected:
	std::wstring m_Title;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddlist();
};
