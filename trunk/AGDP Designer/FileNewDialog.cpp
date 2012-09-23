// FileNewDialog.cpp : ��@��
//

#include "stdafx.h"
#include "AGDP Designer.h"
#include "FileNewDialog.h"
#include "afxdialogex.h"


// CFileNewDialog ��ܤ��

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


// CFileNewDialog �T���B�z�`��


void CFileNewDialog::OnBnClickedCreatehero()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	m_Type = 0;
	m_Name = CString( "John Jon" );
	( ( CEdit* )GetDlgItem( IDC_EDITNAME ) )-> SetWindowText( m_Name );
}


void CFileNewDialog::OnBnClickedCreateobject()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	m_Type = 1;
	m_Name = CString( "Something" );
	( ( CEdit* )GetDlgItem( IDC_EDITNAME ) )-> SetWindowText( m_Name );
}


void CFileNewDialog::OnBnClickedCreatebg()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	m_Type = 2;
	m_Name = CString( "Wonderland" );
	( ( CEdit* )GetDlgItem( IDC_EDITNAME ) )-> SetWindowText( m_Name );
}


void CFileNewDialog::OnEnChangeEditname()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C
	// TODO:  �b���[�J����i���B�z�`���{���X
	GetDlgItem( IDC_EDITNAME )-> GetWindowText( m_Name );
}


int CFileNewDialog::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( CDialogEx::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}

	// TODO:  �b���[�J�S�O�إߪ��{���X
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
