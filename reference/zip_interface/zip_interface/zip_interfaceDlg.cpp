
// zip_interfaceDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "zip_interface.h"
#include "zip_interfaceDlg.h"
#include "afxdialogex.h"
#include "ConvStr.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Czip_interfaceDlg 對話方塊




Czip_interfaceDlg::Czip_interfaceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Czip_interfaceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;
}

void Czip_interfaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBoxInput);
	DDX_Control(pDX, IDC_LIST2, m_ListBoxOutput);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox_CompressMethod);
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrlFolderData);
}

BEGIN_MESSAGE_MAP(Czip_interfaceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_SAVE32771, &Czip_interfaceDlg::OnFileSave)
	ON_COMMAND(ID_FILE_LOAD, &Czip_interfaceDlg::OnFileLoad)
	ON_COMMAND(ID_ZIPDATA_ADD, &Czip_interfaceDlg::OnZipdataAdd)
	ON_BN_CLICKED(IDC_BUTTON2, &Czip_interfaceDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Czip_interfaceDlg::OnBnClickedButton1)
//	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &Czip_interfaceDlg::OnTvnSelchangedTree1)
END_MESSAGE_MAP()


// Czip_interfaceDlg 訊息處理常式

BOOL Czip_interfaceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(TRUE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	CMenu menu;
	menu.LoadMenu(IDR_MAIN_MENU);
	SetMenu(&menu);
	menu.Detach();

	m_ComboBox_CompressMethod.AddString(L"00  NO_COMPRESS");
	m_ComboBox_CompressMethod.AddString(L"01  BEST_SPEED");
	m_ComboBox_CompressMethod.AddString(L"02");
	m_ComboBox_CompressMethod.AddString(L"03");
	m_ComboBox_CompressMethod.AddString(L"04");
	m_ComboBox_CompressMethod.AddString(L"05");
	m_ComboBox_CompressMethod.AddString(L"06  NORMAL");
	m_ComboBox_CompressMethod.AddString(L"07");
	m_ComboBox_CompressMethod.AddString(L"08");
	m_ComboBox_CompressMethod.AddString(L"09  BEST_COMPRESSION");

	m_ComboBox_CompressMethod.AddString(L"10");
	m_ComboBox_CompressMethod.AddString(L"11 CL_ZLIB_1_BAST_SPEED");
	m_ComboBox_CompressMethod.AddString(L"12 CL_ZLIB_2");
	m_ComboBox_CompressMethod.AddString(L"13 CL_ZLIB_3");
	m_ComboBox_CompressMethod.AddString(L"14 CL_ZLIB_4");
	m_ComboBox_CompressMethod.AddString(L"15 CL_ZLIB_5");
	m_ComboBox_CompressMethod.AddString(L"16 CL_ZLIB_6_NORMAL");
	m_ComboBox_CompressMethod.AddString(L"17 CL_ZLIB_7");
	m_ComboBox_CompressMethod.AddString(L"18 CL_ZLIB_8");
	m_ComboBox_CompressMethod.AddString(L"19 CL_ZLIB_9_BEST_COMPRESSION");

	m_ComboBox_CompressMethod.AddString(L"20 CL_LZMA_0_BAST_SPEED");
	m_ComboBox_CompressMethod.AddString(L"21 CL_LZMA_1");
	m_ComboBox_CompressMethod.AddString(L"22 CL_LZMA_2");
	m_ComboBox_CompressMethod.AddString(L"23 CL_LZMA_3");
	m_ComboBox_CompressMethod.AddString(L"24 CL_LZMA_4");
	m_ComboBox_CompressMethod.AddString(L"25 CL_LZMA_5_NORMAL");
	m_ComboBox_CompressMethod.AddString(L"26 CL_LZMA_6");
	m_ComboBox_CompressMethod.AddString(L"27 CL_LZMA_7");
	m_ComboBox_CompressMethod.AddString(L"28 CL_LZMA_8");
	m_ComboBox_CompressMethod.AddString(L"29 CL_LZMA_9_BAST_COMPRESSION");

	m_ComboBox_CompressMethod.AddString(L"30 CL_LZO_1x_1");
	m_ComboBox_CompressMethod.SetCurSel(11);
	m_ZipFolder = new ZipFolder();
	m_FocusFolder = m_ZipFolder;
	//HTREEITEM FQ = m_TreeCtrlFolderData.InsertItem(L"FQ");
	//m_TreeCtrlFolderData.InsertItem(L"Fuuck", FQ);
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void Czip_interfaceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void Czip_interfaceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR Czip_interfaceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Czip_interfaceDlg::OnFileSave()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CFileDialog dlg(FALSE);
	dlg.m_ofn.lpstrFilter	= L"bsz Files (*.bsz)\0*.bsz\0All Files (*.*)\0*.*\0\0";
	dlg.m_ofn.lpstrTitle	= L"Save BSZ File";

	CString filename;

	if(dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		if (filename.GetLength()>1)
		{
			if (filename.Right(4) != ".bsz")
				filename += ".bsz";
			m_ZipFolder->WriteToDisk(ConvStr::GetStr(filename.GetString()));
		}
	}
}


void Czip_interfaceDlg::OnFileLoad()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrFilter	=L"bsz Files (*.bsz)\0*.bsz\0All Files (*.*)\0*.*\0\0";
	dlg.m_ofn.lpstrTitle	=L"Open BSZ File";
	
	CString filename;

	if(dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		if (filename.GetLength()>1)
		{
			m_ZipFolder = new ZipFolder();
			m_ZipFolder->ReadFromDisk(ConvStr::GetStr(filename.GetString()));
			ShowFolderDataToListBox(m_ZipFolder, &m_ListBoxInput);
			
			MakeFolderTree(m_ZipFolder, &m_TreeCtrlFolderData);
		}
	}
}


void Czip_interfaceDlg::OnZipdataAdd()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrFilter	=L"All Files (*.*)\0*.*\0\0";
	dlg.m_ofn.lpstrTitle	=L"Load File";

	CString filename;

	if(dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		if (filename.GetLength()>1)
		{
			m_ZipFolder->AddZipDataFromDisk(ConvStr::GetStr(filename.GetString()));
			//m_ListBoxInput.AddString(CString(m_ZipFolder->m_ZipDatas.back()->m_Name.c_str()));
			//ShowZipFolderToListBox(m_ZipFolder, &m_ListBoxInput);
			ShowFolderDataToListBox(m_ZipFolder, &m_ListBoxInput);
		}
	}
}

void Czip_interfaceDlg::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	for(int i = 0; i < m_ZipFolder->m_ZipDatas.size(); i++)
	{
		m_ZipFolder->m_ZipDatas[i]->CompressData(CompressLevel(m_ComboBox_CompressMethod.GetCurSel()));
	}
	//SeeListBox2();
	ShowFolderDataToListBox(m_ZipFolder, &m_ListBoxInput);
}

void Czip_interfaceDlg::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	for(int i = 0; i < m_ZipFolder->m_ZipDatas.size(); i++)
	{
		m_ZipFolder->m_ZipDatas[i]->UncompressData();
	}
	ShowFolderDataToListBox(m_ZipFolder, &m_ListBoxInput);
	//m_FocusFolder = m_ZMap.GetMaping(m_TreeCtrlFolderData.GetSelectedItem());
	//m_FocusFolder->m_ZipFolders.push_back(ZipFolder());
	//SeeListBox1();
	//m_ZipFolder->m_ZipFolders[0].AddZipDataFromDisk("ConvStr.h");
	/*ZipFolder ZF;
	ZF.m_Name = "Texture";
	m_ZipFolder->m_ZipFolders.push_back(ZF);*/
}



//void Czip_interfaceDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
//	// TODO: 在此加入控制項告知處理常式程式碼
//
//	*pResult = 0;
//}
