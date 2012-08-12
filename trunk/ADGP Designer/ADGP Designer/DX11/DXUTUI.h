#pragma once

#include <vector>
#include <map>
//#include "SDKmisc.h"
//#include "SDKMesh.h"
#include <D3DX11tex.h>
#include <D3DX11.h>
#include <D3DX11core.h>
#include <D3DX11async.h>

#include "dxut/DXUT.h"
#include "dxut/DXUTcamera.h"
#include "dxut/DXUTgui.h"
#include "dxut/DXUTsettingsdlg.h"



enum CommandType
{
	COMMAND_NULL=0,
	COMMAND_BUTTON,
	COMMAND_TEXT,
	COMMAND_COMBO_BOX,
	COMMAND_SLIDER
};

struct CmdState
{
	int id;
	CommandType type;
	int state;		//-1=no event
};
// 		--		cmd1={cid=id編號(數字), ctext=控制項的字, ctype=控制項類型(數字), cpx=控制項x座標, cpy=控制項y座標, 
// 			--		cw=控制項寬度, ch=控制項長度}
struct KTSGCommand
{
	int id;			//command id
	char text[128];		//command static text
	CommandType type;	//type
	float px,py;		//x,y coordinate
	int w,h;		//command width, height
};

class UIDialog
{
private:
	bool m_isopen;
	int m_id;
	std::vector<KTSGCommand>	m_comset;
	CDXUTDialog*	m_uidig;
public:
	UIDialog(){m_uidig=NULL; m_isopen=true;}
	~UIDialog(){if (m_uidig) delete m_uidig;}

	void init(){m_uidig = new CDXUTDialog;}

	void SetID(int id){m_id = id;}
	void SetCmd(int no, int id, const char* text, CommandType type, float px, float py, int w, int h);	//'no' is number of cmd in this dialog

	int GetID(){return m_id;}
	CDXUTDialog* GetDialog(){return m_uidig;}
	CommandType GetCmdType(int id);
	bool GetIsOpen(){return m_isopen;}
	CommandType CmdIdIsExist(int id);

	void ResizeCmdState(int num){m_comset.resize(num);}
	void close();
	void open();
	void Updata(float dt);
};

class DXUTUI
{
public:
	int	m_NextUIid;
	std::vector<CmdState>		m_CmdStateSet;
	std::vector<UIDialog>		m_DialogSet;
	CDXUTDialogResourceManager	m_DialogResourceManager;    // Manager for shared resources of dialogs
	CD3DSettingsDlg			m_D3DSettingsDlg;           // Device settings dialog
	//CDXUTDialog                 m_SampleUI;                 // Dialog for sample specific controls
	//CDXUTTextHelper*            m_pTxtHelper;


	DXUTUI();
	~DXUTUI(void);

	//init fun, must call when app start
	void SetWindow(HWND hWndFocus, bool bHandleMessages = TRUE);
	void CreateDevice(int winWidth, int winHeight);
	ID3D11Device* GetDevice(){ return DXUTGetD3D11Device();}
	ID3D11DeviceContext* GetDeviceContext(){ return DXUTGetD3D11DeviceContext();}
	IDXGISwapChain* GetSwapChaine(){ return DXUTGetDXGISwapChain();}
	bool InitDXUT();

	void UpdataUI(float dt);
	void MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void UpdataCmdState();

	void OpenUI(int id);
	void CloseUI(int id);
	void CloseAllUI();
	int GetCurrencyUI();		//return a UI's id that is open
	void SetStatic(int id, const char* text);
	void SetStatic(int id, const wchar_t* text);
	int GetComboBoxSel(int id);
	int GetSliderNum(int id);
	void ChengeCmdState(int id);
	void ClearCmdState();
	std::vector<CmdState> GetCmdState(){return m_CmdStateSet;}

	void AddNewUI(const char* path);
	void AddNewUI(const wchar_t* path);
};
