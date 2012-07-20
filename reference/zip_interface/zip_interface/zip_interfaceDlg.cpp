
// zip_interfaceDlg.cpp : ��@��
//

#include "stdafx.h"
#include "zip_interface.h"
#include "zip_interfaceDlg.h"
#include "afxdialogex.h"
#include "ConvStr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ܤ�����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
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


// Czip_interfaceDlg ��ܤ��




Czip_interfaceDlg::Czip_interfaceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Czip_interfaceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Czip_interfaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBoxInput);
	DDX_Control(pDX, IDC_LIST2, m_ListBoxOutput);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox_CompressMethod);
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
END_MESSAGE_MAP()


// Czip_interfaceDlg �T���B�z�`��

BOOL Czip_interfaceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
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

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w
	CMenu menu;
	menu.LoadMenu(IDR_MAIN_MENU);
	SetMenu(&menu);
	menu.Detach();

	m_ComboBox_CompressMethod.AddString(L"0  NO_COMPRESS");
	m_ComboBox_CompressMethod.AddString(L"1  BEST_SPEED");
	m_ComboBox_CompressMethod.AddString(L"2");
	m_ComboBox_CompressMethod.AddString(L"3");
	m_ComboBox_CompressMethod.AddString(L"4");
	m_ComboBox_CompressMethod.AddString(L"5");
	m_ComboBox_CompressMethod.AddString(L"6  NORMAL");
	m_ComboBox_CompressMethod.AddString(L"7");
	m_ComboBox_CompressMethod.AddString(L"8");
	m_ComboBox_CompressMethod.AddString(L"9  BEST_COMPRESSION");
	m_ComboBox_CompressMethod.SetCurSel(1);
	m_ZipFolder = new ZipFolder();
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
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

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void Czip_interfaceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR Czip_interfaceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Czip_interfaceDlg::OnFileSave()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
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
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
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
			ShowZipFolderToListBox(m_ZipFolder, &m_ListBoxInput);
		}
	}
}


void Czip_interfaceDlg::OnZipdataAdd()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
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
			ShowZipFolderToListBox(m_ZipFolder, &m_ListBoxInput);
		}
	}
}

void Czip_interfaceDlg::OnBnClickedButton1()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	for(int i = 0; i < m_ZipFolder->m_ZipDatas.size(); i++)
	{
		m_ZipFolder->m_ZipDatas[i]->CompressData(CompressLevel(m_ComboBox_CompressMethod.GetCurSel()));
	}
	SeeListBox2();
}

void Czip_interfaceDlg::OnBnClickedButton2()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	for(int i = 0; i < m_ZipFolder->m_ZipDatas.size(); i++)
	{
		m_ZipFolder->m_ZipDatas[i]->UncompressData();
	}
	SeeListBox1();
	ZipFolder ZF;
	ZF.m_Name = "Info";
	m_ZipFolder->m_ZipFolders.push_back(ZF);
}

