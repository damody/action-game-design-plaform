// PointAddDiolog.cpp : ��@��
//

#include "stdafx.h"
#include "AGDP Designer.h"
#include "PointAddDiolog.h"
#include "afxdialogex.h"


// CPointAddDiolog ��ܤ��

IMPLEMENT_DYNAMIC(CPointAddDiolog, CDialogEx)

CPointAddDiolog::CPointAddDiolog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPointAddDiolog::IDD, pParent),x(0.0f),y(0.0f)
{

}

CPointAddDiolog::~CPointAddDiolog()
{
}

void CPointAddDiolog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPointAddDiolog, CDialogEx)
	ON_EN_CHANGE(IDC_Xvalue, &CPointAddDiolog::OnEnChangeXvaule)
	ON_EN_CHANGE(IDC_Yvalue, &CPointAddDiolog::OnEnChangeYvalue)
END_MESSAGE_MAP()


// CPointAddDiolog �T���B�z�`��


void CPointAddDiolog::OnEnChangeXvaule()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X

	CString str;
	GetDlgItem(IDC_Xvalue)-> GetWindowText(str);
	if (!str.IsEmpty())
	{
		wchar_t r = str.Right(1).GetBuffer(0)[0];
		if (r == '-' && str.GetLength()==1)
		{
			x = _wtof(str.GetBuffer(0));
		}else if(r >= '0' && r <= '9'){
			x = _wtof(str.GetBuffer(0));

		}else if(r =='.' && str.Find('.')==str.GetLength()-1){
			x = _wtof(str.GetBuffer(0));
		}else{
			AfxMessageBox(_T("Not A Number"));
			str.Delete(str.GetLength()-1);
			
			if (str.IsEmpty())
			{
				x = 0;
				GetDlgItem(IDC_Xvalue)-> SetWindowText(_T("0"));
			}else{
				GetDlgItem(IDC_Xvalue)-> SetWindowText(str);
			}
		}
	}else{
		x = 0;
	}
	
}


void CPointAddDiolog::OnEnChangeYvalue()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	CString str;
	GetDlgItem(IDC_Yvalue)-> GetWindowText(str);
	if (!str.IsEmpty())
	{
		wchar_t r = str.Right(1).GetBuffer(0)[0];
		if (r == '-' && str.GetLength()==1)
		{
			y = _wtof(str.GetBuffer(0));
		}else if(r >= '0' && r <= '9'){
			y = _wtof(str.GetBuffer(0));
		}else if(r =='.' && str.Find('.')==str.GetLength()-1){
			y = _wtof(str.GetBuffer(0));
		}else{
			AfxMessageBox(_T("Not A Number"));
			str.Delete(str.GetLength()-1);

			if (str.IsEmpty())
			{
				y = 0;
				GetDlgItem(IDC_Yvalue)-> SetWindowText(_T("0"));
			}else{
				GetDlgItem(IDC_Yvalue)-> SetWindowText(str);
			}
		}
	}else{
		y = 0;
	}
}

BOOL CPointAddDiolog::OnInitDialog()
{
	BOOL reasult = CDialog::OnInitDialog();
	((CEdit*)GetDlgItem(IDC_Xvalue))-> SetWindowText(_T("0"));
	((CEdit*)GetDlgItem(IDC_Yvalue))-> SetWindowText(_T("0"));
	return reasult;
}
