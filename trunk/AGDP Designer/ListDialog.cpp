// ActionListDialog.cpp : 實作檔
//

#include "stdafx.h"
#include "AGDP Designer.h"
#include "ListDialog.h"
#include "AddListDialog.h"
#include "afxdialogex.h"
#include "global.h"

// CActionListDialog 對話方塊

IMPLEMENT_DYNAMIC(CListDialog, CDialogEx)

CListDialog::CListDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CListDialog::IDD, pParent)
{
		m_Title = std::wstring(L"List");
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
	ON_BN_CLICKED(IDC_ADDLIST, &CListDialog::OnBnClickedAddlist)
END_MESSAGE_MAP()

BOOL CListDialog::OnInitDialog()
{
	SetWindowText(CString(m_Title.c_str()));
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

void CListDialog::OnBnClickedAddlist()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CAddListDialog dialog;
	if (dialog.DoModal()==IDOK)
	{
		CComboBox* cb = ( CComboBox* )GetDlgItem( IDC_CB_LIST );
		cb->AddString( CString( dialog.m_Text.c_str() ) );
		cb->SetCurSel(cb->FindString(0,CString( dialog.m_Text.c_str() )));
	}
}

void CListDialog::SetTitle( std::wstring& title )
{
		m_Title = title;
}
