// PointDeleteDialog.cpp : 實作檔
//

#include "stdafx.h"
#include "AGDP Designer.h"
#include "PointDeleteDialog.h"
#include "afxdialogex.h"


// CPointDeleteDialog 對話方塊

IMPLEMENT_DYNAMIC(CPointDeleteDialog, CDialogEx)

CPointDeleteDialog::CPointDeleteDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPointDeleteDialog::IDD, pParent)
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
END_MESSAGE_MAP()


// CPointDeleteDialog 訊息處理常式
