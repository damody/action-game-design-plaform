#pragma once
#include <vector>
// CActionListDialog ��ܤ��

class CListDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CListDialog)
	
public:
	CListDialog(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CListDialog();

	std::wstring m_Select;
	std::vector<std::wstring> m_List;

	void AddList(std::wstring& str);
	void SetTitle(std::wstring& title);
	BOOL OnInitDialog();
// ��ܤ�����
	enum { IDD = IDD_LIST };

protected:
	std::wstring m_Title;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddlist();
};