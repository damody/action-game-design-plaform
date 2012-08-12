#include "dxut/DXUT.h"
#include "DXUTUI.h"
#include "ConvStr.h"


DXUTUI* g_ktsg_ui;

//void CALLBACK KTSGOnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
void CALLBACK KTSGOnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );
bool CALLBACK KTSGIsD3D11DeviceAcceptable( const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo,
				    DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext );

HRESULT CALLBACK KTSGOnD3D11ResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,
					 const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	g_ktsg_ui->m_DialogResourceManager.OnD3D11ResizedSwapChain( pd3dDevice, pBackBufferSurfaceDesc ) ;
	g_ktsg_ui->m_D3DSettingsDlg.OnD3D11ResizedSwapChain( pd3dDevice, pBackBufferSurfaceDesc ) ;
	return true;
}


DXUTUI::DXUTUI()
{
	m_CmdStateSet.clear();
	g_ktsg_ui = this;
	m_NextUIid = 1;
	m_CmdStateSet.clear();

	// Disable gamma correction on this sample
	DXUTSetIsInGammaCorrectMode( false );
	DXUTSetCallbackD3D11SwapChainResized( KTSGOnD3D11ResizedSwapChain );
	DXUTSetCallbackD3D11DeviceAcceptable( KTSGIsD3D11DeviceAcceptable );
	// 	//DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
	// 	//DXUTSetCallbackMsgProc( MsgProc );
	// 	DXUTSetCallbackKeyboard( KTSGOnKeyboard );
	//	DXUTSetCallbackFrameMove( OnFrameMove );
	// 	DXUTSetCallbackD3D11DeviceCreated( OnD3D11CreateDevice );
	// 	DXUTSetCallbackD3D11FrameRender( OnD3D11FrameRender );
	// 	DXUTSetCallbackD3D11SwapChainReleasing( OnD3D11ReleasingSwapChain );
	// 	DXUTSetCallbackD3D11DeviceDestroyed( OnD3D11DestroyDevice );

	DXUTInit( true, true );                 // Use this line instead to try to create a hardware device

	DXUTSetCursorSettings( true, true );    // Show the cursor and clip it when in full screen
}

DXUTUI::~DXUTUI(void)
{
	DXUTGetExitCode();
}

void DXUTUI::SetWindow( HWND hWndFocus, bool bHandleMessages /*= TRUE*/ )
{
	DXUTSetWindow(hWndFocus, hWndFocus, hWndFocus, bHandleMessages);
}

void DXUTUI::CreateDevice( int winWidth, int winHeight)
{
	DXUTCreateDevice(D3D_FEATURE_LEVEL_11_0, true, winWidth, winHeight);
	m_DialogResourceManager.OnD3D11CreateDevice( DXUTGetD3D11Device(), DXUTGetD3D11DeviceContext() );
	m_D3DSettingsDlg.OnD3D11CreateDevice( DXUTGetD3D11Device() );
}

bool DXUTUI::InitDXUT()
{
	DXUTInit( true, true );
	m_D3DSettingsDlg.Init( &m_DialogResourceManager );
	return true;
}

void DXUTUI::UpdataUI(float dt)
{
	//DXUTRender3DEnvironment();
	DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"HUD / Stats" );
	for (int i=0; i<m_DialogSet.size(); i++)
		m_DialogSet[i].Updata(dt);
	DXUT_EndPerfEvent();
}

void DXUTUI::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_DialogResourceManager.MsgProc(hWnd, uMsg, wParam, lParam);
	m_D3DSettingsDlg.MsgProc(hWnd, uMsg, wParam, lParam);
	for (int i=0; i<m_DialogSet.size(); i++)
		m_DialogSet[i].GetDialog()->MsgProc(hWnd, uMsg, wParam, lParam);
}

void DXUTUI::OpenUI( int id )
{
	for (int i=0; i<m_DialogSet.size(); i++)
	{
		if (m_DialogSet[i].GetID()==id)
		{
			m_DialogSet[i].open();
			return;
		}
	}
}

void DXUTUI::CloseUI( int id )
{
	for (int i=0; i<m_DialogSet.size(); i++)
	{
		if (m_DialogSet[i].GetID()==id)
		{
			m_DialogSet[i].close();
			return;
		}
	}
}

void DXUTUI::SetStatic( int id, const char* text )
{
	wchar_t* wtext;
	wtext = new wchar_t[128];
	ConvStr::CharToWchar(wtext, text);
	SetStatic(id, wtext);
	delete[] wtext;
}

void DXUTUI::SetStatic( int id, const wchar_t* text )
{
	CommandType type;
	for (int i=0; i<m_DialogSet.size(); i++)
	{
		type = m_DialogSet[i].CmdIdIsExist(id);
		if (type!=COMMAND_NULL)
		{
			if (!m_DialogSet[i].GetIsOpen())
				return;
			switch(type)
			{
			case COMMAND_BUTTON:
				m_DialogSet[i].GetDialog()->GetButton(id)->SetText(text);
				break;
			case COMMAND_TEXT:
				m_DialogSet[i].GetDialog()->GetStatic(id)->SetText(text);
				break;
			}
			break;
		}
	}
}


int DXUTUI::GetComboBoxSel( int id )
{
	for (int i=0; i<m_DialogSet.size(); i++)
	{
		if (m_DialogSet[i].CmdIdIsExist(id)!=COMMAND_NULL)
		{
			return m_DialogSet[i].GetDialog()->GetComboBox(id)->GetSelectedIndex();	
		}
	}
	return -1;
}

void DXUTUI::UpdataCmdState()
{
	for (int i=0; i<m_CmdStateSet.size(); i++)
	{
		if (m_CmdStateSet[i].type == COMMAND_BUTTON)
			m_CmdStateSet[i].state = -1;
	}
}

void DXUTUI::ChengeCmdState( int id )
{
	CmdState newstate;
	for (int i=0; i<m_DialogSet.size(); i++)
	{
		if (m_DialogSet[i].CmdIdIsExist(id)!=COMMAND_NULL)
		{
			if (!m_DialogSet[i].GetIsOpen())
				return;
			newstate.id = id;
			newstate.type = m_DialogSet[i].GetCmdType(id);
			switch(newstate.type)
			{
			case COMMAND_BUTTON:
				newstate.state = 1;
				break;
			case COMMAND_COMBO_BOX:
				newstate.state = GetComboBoxSel(id);
				break;
			}
			m_CmdStateSet.push_back(newstate);
			break;
		}
	}
}

void DXUTUI::ClearCmdState()
{
	m_CmdStateSet.clear();
}

void DXUTUI::CloseAllUI()
{
	for (int i=0; i<m_DialogSet.size(); i++)
	{
		m_DialogSet[i].close();
	}
}

int DXUTUI::GetCurrencyUI()
{
	for (int i=0; i<m_DialogSet.size(); i++)
	{
		if (m_DialogSet[i].GetIsOpen())
			return i;
	}
}

int DXUTUI::GetSliderNum( int id )
{
	for (int i=0; i<m_DialogSet.size(); i++)
	{
		if (m_DialogSet[i].CmdIdIsExist(id)!=COMMAND_NULL)
		{
			return m_DialogSet[i].GetDialog()->GetSlider(id)->GetValue();
		}
	}
	return -1;
}

bool CALLBACK KTSGIsD3D11DeviceAcceptable( const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo, DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
	return true;
}

void CALLBACK KTSGOnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{
	g_ktsg_ui->ChengeCmdState(nControlID);
}

void UIDialog::close()
{
	m_uidig->SetVisible(false);
	m_isopen = false;
}

void UIDialog::open()
{
	m_uidig->SetVisible(true);
	m_isopen = true;
}

void UIDialog::Updata(float dt)
{
	if (m_isopen)
		m_uidig->OnRender(dt);
}

CommandType UIDialog::CmdIdIsExist( int id )
{
	for (int i=0; i<m_comset.size(); i++)
	{
		if (id == m_comset[i].id)
			return m_comset[i].type;
	}
	return COMMAND_NULL;
}

CommandType UIDialog::GetCmdType( int id )
{
	for (int i=0; i<m_comset.size(); i++)
	{
		if (m_comset[i].id == id)
			return m_comset[i].type;
	}
	return COMMAND_NULL;
}

void UIDialog::SetCmd( int no, int id, const char* text, CommandType type, float px, float py, int w, int h )
{
	m_comset[no].id = id;
	strcpy_s(m_comset[no].text, 128, text);
	m_comset[no].type = (CommandType)type;
	m_comset[no].px = px;
	m_comset[no].py = py;
	m_comset[no].w = w;
	m_comset[no].h = h;
}
