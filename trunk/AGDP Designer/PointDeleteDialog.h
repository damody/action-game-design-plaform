#pragma once


// CPointDeleteDialog ��ܤ��

class CPointDeleteDialog : public CDialogEx
{
	DECLARE_DYNAMIC( CPointDeleteDialog )
public:
	const int m_MaxID;
	int m_CurID;
public:
	CPointDeleteDialog( int max, CWnd* pParent = NULL ); // �зǫغc�禡
	virtual ~CPointDeleteDialog();

// ��ܤ�����
	enum { IDD = IDD_POINTSUB };

protected:
	virtual void DoDataExchange( CDataExchange* pDX );  // DDX/DDV �䴩
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangePointid();
};
