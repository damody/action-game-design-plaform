// AddListDialog.cpp : ��@��
//

#include "stdafx.h"
#include "AGDP Designer.h"
#include "AddListDialog.h"
#include "afxdialogex.h"


// CAddListDialog ��ܤ��

IMPLEMENT_DYNAMIC(CAddListDialog, CDialogEx)

CAddListDialog::CAddListDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddListDialog::IDD, pParent)
{

}

CAddListDialog::~CAddListDialog()
{
}

void CAddListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	CString str;
	GetDlgItem( IDC_ADDSTR )-> GetWindowText( str );
	m_Text = std::wstring(str.GetBuffer(0));
}


BEGIN_MESSAGE_MAP(CAddListDialog, CDialogEx)
END_MESSAGE_MAP()


// CAddListDialog �T���B�z�`��
