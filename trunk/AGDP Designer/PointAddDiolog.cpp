// PointAddDiolog.cpp : 實作檔
//

#include "stdafx.h"
#include "AGDP Designer.h"
#include "PointAddDiolog.h"
#include "afxdialogex.h"


// CPointAddDiolog 對話方塊

IMPLEMENT_DYNAMIC(CPointAddDiolog, CDialogEx)

CPointAddDiolog::CPointAddDiolog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPointAddDiolog::IDD, pParent)
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
END_MESSAGE_MAP()


// CPointAddDiolog 訊息處理常式
