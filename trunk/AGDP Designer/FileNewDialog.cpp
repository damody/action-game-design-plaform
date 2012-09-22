// FileNewDialog.cpp : 實作檔
//

#include "stdafx.h"
#include "AGDP Designer.h"
#include "FileNewDialog.h"
#include "afxdialogex.h"


// CFileNewDialog 對話方塊

IMPLEMENT_DYNAMIC( CFileNewDialog, CDialogEx )

CFileNewDialog::CFileNewDialog( CWnd* pParent /*=NULL*/ )
	: CDialogEx( CFileNewDialog::IDD, pParent ), m_Type( 0 )
{
}

CFileNewDialog::~CFileNewDialog()
{
}

void CFileNewDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}


BEGIN_MESSAGE_MAP( CFileNewDialog, CDialogEx )
	ON_BN_CLICKED( IDC_CREATEHERO, &CFileNewDialog::OnBnClickedCreatehero )
	ON_BN_CLICKED( IDC_CREATEOBJECT, &CFileNewDialog::OnBnClickedCreateobject )
	ON_BN_CLICKED( IDC_CREATEBG, &CFileNewDialog::OnBnClickedCreatebg )
	ON_EN_CHANGE( IDC_EDITNAME, &CFileNewDialog::OnEnChangeEditname )
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CFileNewDialog 訊息處理常式


void CFileNewDialog::OnBnClickedCreatehero()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_Type = 0;
	m_Name = CString( "John Jon" );
	( ( CEdit* )GetDlgItem( IDC_EDITNAME ) )-> SetWindowText( m_Name );
}


void CFileNewDialog::OnBnClickedCreateobject()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_Type = 1;
	m_Name = CString( "Something" );
	( ( CEdit* )GetDlgItem( IDC_EDITNAME ) )-> SetWindowText( m_Name );
}


void CFileNewDialog::OnBnClickedCreatebg()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_Type = 2;
	m_Name = CString( "Wonderland" );
	( ( CEdit* )GetDlgItem( IDC_EDITNAME ) )-> SetWindowText( m_Name );
}


void CFileNewDialog::OnEnChangeEditname()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。
	// TODO:  在此加入控制項告知處理常式程式碼
	GetDlgItem( IDC_EDITNAME )-> GetWindowText( m_Name );
}


int CFileNewDialog::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CDialogEx::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	// TODO:  在此加入特別建立的程式碼
	return 0;
}

BOOL CFileNewDialog::OnInitDialog()
{
	BOOL reasult = CDialog::OnInitDialog();
	( ( CButton* )GetDlgItem( IDC_CREATEHERO ) )->SetCheck( TRUE );
	m_Name = CString( "John Jon" );
	( ( CEdit* )GetDlgItem( IDC_EDITNAME ) )-> SetWindowText( m_Name );
	return reasult;
}
