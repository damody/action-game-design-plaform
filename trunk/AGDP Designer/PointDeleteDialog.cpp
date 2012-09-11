// PointDeleteDialog.cpp : 實作檔
//

#include "stdafx.h"
#include "AGDP Designer.h"
#include "PointDeleteDialog.h"
#include "afxdialogex.h"


// CPointDeleteDialog 對話方塊

IMPLEMENT_DYNAMIC(CPointDeleteDialog, CDialogEx)

CPointDeleteDialog::CPointDeleteDialog( int max,CWnd* pParent /*= NULL*/ )
: CDialogEx(CPointDeleteDialog::IDD, pParent),m_MaxID(max),m_CurID(0)
{

}

CPointDeleteDialog::~CPointDeleteDialog()
{
}

void CPointDeleteDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPointDeleteDialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_POINTID, &CPointDeleteDialog::OnCbnSelchangePointid)
END_MESSAGE_MAP()


// CPointDeleteDialog 訊息處理常式


void CPointDeleteDialog::OnCbnSelchangePointid()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_CurID = ((CComboBox*)GetDlgItem(IDC_POINTID))->GetCurSel();
}

BOOL CPointDeleteDialog::OnInitDialog()
{
	BOOL reasult = CDialog::OnInitDialog();
	CComboBox* cb = (CComboBox*)GetDlgItem(IDC_POINTID);
	for (int i=0 ; i<m_MaxID ; i++)
	{
		char buff[1000];
		sprintf(buff,"%d",i);
		cb->AddString(CString(buff));
	}
	cb->SetCurSel(0);
	return reasult;
}
