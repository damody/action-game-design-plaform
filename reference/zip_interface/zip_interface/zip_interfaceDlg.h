
// zip_interfaceDlg.h : 標頭檔
//

#pragma once
#include "afxmenubutton.h"
#include "afxwin.h"
#include "ZipFolder.h"


// Czip_interfaceDlg 對話方塊
class Czip_interfaceDlg : public CDialogEx
{
// 建構
public:
	Czip_interfaceDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_ZIP_INTERFACE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援
	void SeeListBox1() {
		m_ListBoxInput.ResetContent();
		for (int i = 0; i < m_ZipFolder->m_ZipDatas.size(); i++)
		{
			CString SSt;
			if(m_ZipFolder->m_ZipDatas[i]->IsCompressed())
			{
				SSt = "IsZip ";
			}else
			{
				SSt = "UnZip ";
			}
			SSt += "OringinalSize:";
			SSt += m_ZipFolder->m_ZipDatas[i]->GetData().size() + " ";
			;
			SSt += CString(("Path:" + m_ZipFolder->m_ZipDatas[i]->m_Name).c_str());
			m_ListBoxInput.AddString(SSt);
		}
	}
	void SeeListBox2() {
		m_ListBoxOutput.ResetContent();
		for (int i = 0; i < m_ZipFolder->m_ZipDatas.size(); i++)
		{
			CString SSt;
			if(m_ZipFolder->m_ZipDatas[i]->IsCompressed())
			{
				SSt = "IsZip ";
			}else
			{
				SSt = "UnZip ";
			}
			SSt += "OringinalSize:";
			SSt += m_ZipFolder->m_ZipDatas[i]->GetData().size() + " ";
			;
			SSt += CString(("Path:" + m_ZipFolder->m_ZipDatas[i]->m_Name).c_str());
			m_ListBoxOutput.AddString(SSt);
		}
	}
	void ShowZipFolderToListBox(ZipFolder* ZF, CListBox* CB)
	{
		CB->ResetContent();
		for(int i = 0; i < ZF->m_ZipDatas.size(); i++)
		{
			t_CS = ZF->m_ZipDatas[i]->m_Name.c_str();
			CB->AddString(t_CS);
		}
		for(int i =0; i < ZF->m_ZipFolders.size(); i++)
		{
			t_CS = ZF->m_ZipFolders[i].m_Name.c_str();
			t_CS = '+' + t_CS;
			CB->AddString(t_CS);
		}
	}
// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMFCMenuButton menu1;
	afx_msg void OnBnClickedMfcmenubutton2();
	afx_msg void OnFileSave();
	afx_msg void OnFileLoad();
	afx_msg void OnZipdataAdd();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CListBox	m_ListBoxInput;
	CListBox	m_ListBoxOutput;
	CComboBox	m_ComboBox_CompressMethod;

	ZipFolder*	m_ZipFolder;
	ZipFolder*	m_curFolder;
	CString		t_CS;
};
