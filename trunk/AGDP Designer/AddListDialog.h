#pragma once


// CAddListDialog ��ܤ��

class CAddListDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAddListDialog)
	std::wstring m_Text;
public:
	CAddListDialog(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CAddListDialog();

// ��ܤ�����
	enum { IDD = IDD_ADDLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
};
