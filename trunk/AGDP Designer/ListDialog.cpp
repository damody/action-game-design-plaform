// ActionListDialog.cpp : 實作檔
//

#include "stdafx.h"
#include "AGDP Designer.h"
#include "ListDialog.h"
#include "afxdialogex.h"
#include "global.h"

// CActionListDialog 對話方塊

IMPLEMENT_DYNAMIC(CListDialog, CDialogEx)

CListDialog::CListDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CListDialog::IDD, pParent)
{

}

CListDialog::~CListDialog()
{
}

void CListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	CComboBox* cb = ( CComboBox* )GetDlgItem( IDC_CB_LIST );

	if (cb->GetCount()!=0){
		CString str;
		int sel = cb->GetCurSel();
		int n = cb->GetLBTextLen( sel );
		cb->GetLBText( sel, str.GetBuffer(n) );
		m_Select = std::wstring(str);
	};

}

void CListDialog::AddList( std::wstring& str )
{
	m_List.push_back(str);
}

BEGIN_MESSAGE_MAP(CListDialog, CDialogEx)
END_MESSAGE_MAP()

BOOL CListDialog::OnInitDialog()
{
	
	CComboBox* cb = ( CComboBox* )GetDlgItem( IDC_CB_LIST );

	for ( int i = 0 ; i < (int)m_List.size() ; i++ )
	{
		cb->AddString( CString( m_List[i].c_str() ) );
	}

	cb->SetCurSel( 0 );
	BOOL reasult = CDialog::OnInitDialog();
	return reasult;
}





// CActionListDialog 訊息處理常式


