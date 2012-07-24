
// zip_interfaceDlg.h : 標頭檔
//

#pragma once
#include "afxmenubutton.h"
#include "afxwin.h"
#include "ZipFolder.h"
#include "afxcmn.h"



class ZipMaping
{
public:
	void NewMaping(HTREEITEM TI, ZipFolder* ZF)
	{
		ItemToFolder IF;
		IF.TI = TI;
		IF.ZF = ZF;
		FolderList.push_back(IF);
	}
	ZipFolder* GetMaping(HTREEITEM TI)
	{
		for(int i = 0; i < FolderList.size(); i++)
		{
			if(FolderList[i].TI == TI) return FolderList[i].ZF;
		}
		return 0;
	}
private:
	struct ItemToFolder
	{
		HTREEITEM TI;
		ZipFolder* ZF;
	};

	std::vector<ItemToFolder> FolderList;
};

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
	void ShowFolderDataToListBox(ZipFolder* ZF, CListBox* LB)
	{
		LB->ResetContent();
		for(int i = 0; i < ZF->m_ZipDatas.size(); i++)
		{
			t_CS = ZF->m_ZipDatas[i]->m_Name.c_str();
			t_CS+= "\t";
			if(ZF->m_ZipDatas[i]->IsCompressed())
			{
				t_CS += " true ";
			}else
			{
				t_CS += " false ";
			}
			char buffer[11];
			memcpy(buffer, &*(ZF->m_ZipDatas[i]->GetData().end()-11), 10);
			buffer[10] = 0;
			t_CS += buffer; //顯示最後一個char看看對不對...
			LB->AddString(t_CS);
		}
	}
	void ShowZipFolderToListBox(ZipFolder* ZF, CListBox* LB)
	{
		LB->ResetContent();
		for(int i = 0; i < ZF->m_ZipDatas.size(); i++)
		{
			t_CS = ZF->m_ZipDatas[i]->m_Name.c_str();
			LB->AddString(t_CS);
		}
		for(int i =0; i < ZF->m_ZipFolders.size(); i++)
		{
			t_CS = ZF->m_ZipFolders[i].m_Name.c_str();
			t_CS = '+' + t_CS;
			LB->AddString(t_CS);
		}
	}
	void MakeFolderTree(ZipFolder* ZF, CTreeCtrl* TC)
	{
		TC->DeleteAllItems();
		HTREEITEM t_TI;
		HTREEITEM TI = TC->InsertItem(CString(ZF->m_Name.c_str()));
		m_ZMap.NewMaping(TI, ZF);
		for(int i = 0; i < ZF->m_ZipFolders.size(); i++)
		{
			t_CS = ZF->m_ZipFolders[i].m_Name.c_str();
			t_TI = TC->InsertItem(t_CS, TI);
			m_ZMap.NewMaping(t_TI, &ZF->m_ZipFolders[i]);
			MakeFolderTree(&ZF->m_ZipFolders[i], TC, &t_TI);
		}
		/*for(int i =0; i < ZF->m_ZipDatas.size(); i++)
		{
			t_CS = ZF->m_ZipDatas[i]->m_Name.c_str();
			t_TI = TC->InsertItem(t_CS);
		}*/
	}
	void MakeFolderTree(ZipFolder* ZF, CTreeCtrl* TC, HTREEITEM* TI)
	{
		HTREEITEM t_TI;
		for(int i = 0; i < ZF->m_ZipFolders.size(); i++)
		{
			t_CS = ZF->m_ZipFolders[i].m_Name.c_str();
			t_TI = TC->InsertItem(t_CS, *TI);
			m_ZMap.NewMaping(t_TI, &ZF->m_ZipFolders[i]);
			MakeFolderTree(&ZF->m_ZipFolders[i], TC, &t_TI);
		}
		/*for(int i =0; i < ZF->m_ZipDatas.size(); i++)
		{
			t_CS = ZF->m_ZipDatas[i]->m_Name.c_str();
			TC->InsertItem(t_CS, *TI);
		}*/
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
	ZipFolder*	m_FocusFolder;

	CString		t_CS;
	CTreeCtrl	m_TreeCtrlFolderData;
	ZipMaping	m_ZMap;
//	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
