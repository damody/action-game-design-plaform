#pragma once


// CPointDeleteDialog ��ܤ��

class CPointDeleteDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPointDeleteDialog)

public:
	CPointDeleteDialog(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CPointDeleteDialog();

// ��ܤ�����
	enum { IDD = IDD_POINTSUB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
};
