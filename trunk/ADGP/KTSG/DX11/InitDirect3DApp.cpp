#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include "InitDirect3DApp.h"
#include "InputState.h"
#include "WaveSound.h"
#include "ui/CmdDef.h"
#include "game/HeroInfo.h"

InitDirect3DApp* InitDirect3DApp::dxAppInstance = NULL;

InitDirect3DApp::InitDirect3DApp()
: D3DApp(), m_Heroes_Width(0), m_Heroes_Height(0), m_Buffer_Heroes(0),
            m_Background_Width(0), m_Background_Height(0), m_Buffer_Background(0), m_Background(0),
	    m_SettingKeyID(-1), m_LastGameProcess(1), m_GameProcess(1), m_Last2GameProcess(1)
{
	dxAppInstance = this;
}

InitDirect3DApp::~InitDirect3DApp()
{
	if( m_DeviceContext )
		m_DeviceContext->ClearState();
}

void InitDirect3DApp::initApp()
{
	D3DApp::initApp();
	InitTexture();
	LoadResource();
	LoadBlend();
	LoadHero();
	buildPointFX();
	OnResize();
	// Set blend
	float BlendFactor[4] = {0,0,0,0};
	m_DeviceContext->OMSetBlendState(m_pBlendState_BLEND, BlendFactor, 0xffffffff);
	//m_DeviceContext->OMSetDepthStencilState(m_pDepthStencil_ZWriteOFF, 0);
	buildPoint();
	//init Camera
	m_Camera = Camera_Sptr(new Camera(0,0,0,0,0,45));
	

}


void InitDirect3DApp::UpdateScene(float dt)
{
	m_DXUT_UI->UpdataUI(dt);
	m_SwapChain->Present(0, 0);
	D3DApp::DrawScene(); // clear window
	PrintInfo();
	UpdateInput();

	//*test camera
	TestCamera();
	UpdateCamera();
	

	
	static float timp_count = 0;
	timp_count+=dt;
	if (timp_count > 1/60.0f)
	{
		//Hero Update
		for(std::vector<Hero_RawPtr>::iterator it = m_Heroes.begin();it != m_Heroes.end(); it++)
		{
			(*it)->Update(dt);
		}
		//Background Update
		if(m_Background != NULL)
		{
			m_Background->Update(dt);
		}
		timp_count -= 1/60.0f;
	}
	
	UpdateUI();
	buildPoint();
}

void InitDirect3DApp::OnResize()
{
	D3DApp::OnResize();
	
	if (m_Heroes_Width!=NULL && m_Heroes_Height!=NULL)
	{
		m_Heroes_Width->SetFloat((float)mClientWidth);
		m_Heroes_Height->SetFloat((float)mClientHeight);
	}

	if (m_Background_Width!=NULL && m_Background_Height!=NULL)
	{
		m_Background_Width->SetFloat((float)mClientWidth);
		m_Background_Height->SetFloat((float)mClientHeight);
	}
	
}

void InitDirect3DApp::DrawScene()
{
	// clear color
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, m_ClearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL,  1.0f, 0);
	m_DeviceContext->ClearRenderTargetView(RTVView1, m_ClearColor);
	m_DeviceContext->ClearRenderTargetView(RTVView2, m_ClearColor);
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
	
	//Draw Hero
	UINT offset = 0;
	UINT stride2 = sizeof(ClipVertex);
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_DeviceContext->IASetInputLayout(m_PLayout_Heroes);
	m_DeviceContext->IASetVertexBuffers(0, 1, &m_Buffer_Heroes, &stride2, &offset);
	for (DrawVertexGroups::iterator it = m_DrawVertexGroups.begin();it != m_DrawVertexGroups.end();++it)
	{
		if (it->texture.get())
		{
			m_PMap_Heroes->SetResource(*(it->texture));
			m_PTech_Heroes->GetPassByIndex(0)->Apply(0, m_DeviceContext);
			m_DeviceContext->Draw(it->VertexCount, it->StartVertexLocation);
		}
	}
	
	//Draw Background
	if (m_Background != NULL)
	{
		offset = 0;
		stride2 = sizeof(BGVertex);
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		m_DeviceContext->IASetInputLayout(m_PLayout_Background);
		m_DeviceContext->IASetVertexBuffers(0, 1, &m_Buffer_Background, &stride2, &offset);
		for (DrawVertexGroups::iterator it = m_Background->m_DrawVertexGroups.begin();it != m_Background->m_DrawVertexGroups.end();++it)
		{
			if (it->texture.get())
			{
				m_PMap_Heroes->SetResource(*(it->texture));
				m_PTech_Heroes->GetPassByIndex(0)->Apply(0, m_DeviceContext);
				m_DeviceContext->Draw(it->VertexCount, it->StartVertexLocation);
			}
		}
	}
	
}

void InitDirect3DApp::buildPointFX()
{
	ID3D10Blob* pCode;
	ID3D10Blob* pError;
	HRESULT hr = 0;
	hr=D3DX11CompileFromFile(_T("shader\\Hero.fx"), NULL, NULL, NULL, 
		"fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );
	if(FAILED(hr))
	{
		if( pError )
		{
			MessageBoxA(0, (char*)pError->GetBufferPointer(), 0, 0);
			ReleaseCOM(pError);
		}
		DXTrace(__FILE__, __LINE__, hr, _T("D3DX11CreateEffectFromFile"), TRUE);
	} 
	HR(D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Heroes));
	m_PTech_Heroes = m_Effect_Heroes->GetTechniqueByName("PointTech");
	m_Heroes_Width = m_Effect_Heroes->GetVariableByName("width")->AsScalar();
	m_Heroes_Height =m_Effect_Heroes->GetVariableByName("height")->AsScalar();
	m_Heroes_cLootAt = m_Effect_Heroes->GetVariableByName("cLookAt");
	m_Heroes_cPos = m_Effect_Heroes->GetVariableByName("cPolarCoord");
	m_PMap_Heroes =m_Effect_Heroes->GetVariableByName("gMap")->AsShaderResource();

	D3DX11_PASS_DESC PassDesc;
	m_PTech_Heroes->GetPassByIndex(0)->GetDesc(&PassDesc);
	HR(m_d3dDevice->CreateInputLayout(VertexDesc_HeroVertex, 4, PassDesc.pIAInputSignature,PassDesc.IAInputSignatureSize, &m_PLayout_Heroes));

	hr = 0;
	hr=D3DX11CompileFromFile(_T("shader\\Background.fx"), NULL, NULL, NULL, 
		"fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );
	if(FAILED(hr))
	{
		if( pError )
		{
			MessageBoxA(0, (char*)pError->GetBufferPointer(), 0, 0);
			ReleaseCOM(pError);
		}
		DXTrace(__FILE__, __LINE__, hr, _T("D3DX11CreateEffectFromFile"), TRUE);
	} 
	HR(D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Background));
	m_PTech_Background = m_Effect_Background->GetTechniqueByName("PointTech");
	m_Background_Width = m_Effect_Background->GetVariableByName("sceneW")->AsScalar();
	m_Background_Height =m_Effect_Background->GetVariableByName("sceneH")->AsScalar();
	m_Background_cLootAt = m_Effect_Background->GetVariableByName("cLookAt");
	m_Background_cPos = m_Effect_Background->GetVariableByName("cPolarCoord");
	m_PMap_Background =m_Effect_Background->GetVariableByName("gMap")->AsShaderResource();

	D3DX11_PASS_DESC PassDescBG;
	m_PTech_Background->GetPassByIndex(0)->GetDesc(&PassDescBG);
	HR(m_d3dDevice->CreateInputLayout(VertexDesc_BGVertex, 4, PassDescBG.pIAInputSignature,PassDescBG.IAInputSignatureSize, &m_PLayout_Background));

	m_vbd.Usage = D3D11_USAGE_IMMUTABLE;
	m_vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_vbd.CPUAccessFlags = 0;
	m_vbd.MiscFlags = 0;
}



void InitDirect3DApp::buildPoint()
{
	ReleaseCOM(m_Buffer_Heroes);
	// set heroes
	std::stable_sort(m_Heroes.begin(),m_Heroes.end(),SortHero);
	m_HeroVertex.clear();
	m_DrawVertexGroups.clear();
	int vertexCount = 0, count = 0;
	if(!m_Heroes.empty())
	{
		for(std::vector<Hero_RawPtr>::iterator it=m_Heroes.begin();it != m_Heroes.end();)
		{
			DrawVertexGroup dvg={};
			dvg.texture = (*it)->GetTexture();
			vertexCount = 0;
			dvg.StartVertexLocation = count;
			do 
			{
			  //save vertex points
			  m_HeroVertex.push_back((*it)->GetPic());
			  it++;
			  ++vertexCount;
			  ++count;
			} while (it!=m_Heroes.end() && dvg.texture == (*it)->GetTexture());
			dvg.VertexCount = vertexCount;
			//save dvg
			m_DrawVertexGroups.push_back(dvg);
		}
		if (vertexCount>0)
		{
			m_vbd.ByteWidth = (UINT)(sizeof(ClipVertex) * m_HeroVertex.size());
			m_vbd.StructureByteStride=sizeof(ClipVertex);
			D3D11_SUBRESOURCE_DATA vinitData;
			vinitData.pSysMem = &m_HeroVertex[0];
			HR(m_d3dDevice->CreateBuffer(&m_vbd, &vinitData, &m_Buffer_Heroes));
		}
	}

	if(m_Background != NULL){
		m_Background->BuildPoint();
		m_vbd.ByteWidth = (UINT)(sizeof(BGVertex) * m_Background->m_BGVerteices.size());
		m_vbd.StructureByteStride=sizeof(BGVertex);
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &m_HeroVertex[0];
		HR(m_d3dDevice->CreateBuffer(&m_vbd, &vinitData, &m_Buffer_Background));
	}

}

void InitDirect3DApp::LoadResource()
{
	m_Lua.InputLuaFile("resource.lua");
	// load wav file
	WavSoundS::instance().Initialize(m_hMainWnd);
	WavSoundS::instance().SetVolume(-2000);
	for (int i=1;;++i)
	{
		if (m_Lua.HasValue("wav/%d/1", i))
		{
			int idx = m_Lua.GetLua<int>("wav/%d/1", i);
			const char* file = m_Lua.GetLua<const char*>("wav/%d/2", i);
			int mutiplay = m_Lua.GetLua<int>("wav/%d/3", i);
			assert(file != 0);
			bool res = WavSoundS::instance().CreatSound(file, idx, mutiplay);
			assert(res);
		}
		else
			break;
	}
}

void InitDirect3DApp::LoadBlend()
{
	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
	depth_stencil_desc.DepthEnable = TRUE;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;

	depth_stencil_desc.StencilEnable = FALSE;
	depth_stencil_desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depth_stencil_desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	// 秨币zbuffer write
	if ( D3D_OK != m_d3dDevice->CreateDepthStencilState(&depth_stencil_desc, &m_pDepthStencil_ZWriteON) )
		return ;

	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	// 闽超zbuffer write
	if ( D3D_OK != m_d3dDevice->CreateDepthStencilState(&depth_stencil_desc, &m_pDepthStencil_ZWriteOFF) )
		return ;
	m_DeviceContext->OMSetDepthStencilState(m_pDepthStencil_ZWriteON, 0);
	CD3D11_BLEND_DESCX blend_state_desc(
		FALSE,
		FALSE,
		TRUE,
		D3D11_BLEND_ONE,
		D3D11_BLEND_ONE,
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_ONE,
		D3D11_BLEND_ONE,
		D3D11_BLEND_OP_ADD,
		D3D11_COLOR_WRITE_ENABLE_ALL);
	// ADD睼︹家Α
	if ( D3D_OK != m_d3dDevice->CreateBlendState(&blend_state_desc, &m_pBlendState_ADD) )
		return;
	blend_state_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA ;
	blend_state_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	blend_state_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blend_state_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;

	// Alpha Blend睼︹家Α
	if ( D3D_OK != m_d3dDevice->CreateBlendState(&blend_state_desc, &m_pBlendState_BLEND) )
		return ;
}

void InitDirect3DApp::LoadHero()
{
	//Test
	LuaCell_Sptr davis = LuaCell_Sptr(new LuaCell);
	davis->InputLuaFile("davis.lua");
	HeroInfo_Sptr temp = HeroInfo_Sptr(new HeroInfo);
	temp->LoadHeroData(davis);
	g_HeroInfoMG.AddHeroInfo(temp->m_Name,temp);
	//test bg
	LuaCell_Sptr ft = LuaCell_Sptr(new LuaCell);
	ft->InputLuaFile("bg.lua");
	BackGround_RawPtr tempBG = BackGround_RawPtr(new BackGround());
	if(!tempBG->CheckDataVaild(ft)){
		std::cout<<"BG Data Fail"<<std::endl;
	}
	tempBG->LoadData(ft);

	//player init
	int key[8] = {KEY_UP,KEY_DOWN,KEY_RIGHT,KEY_LEFT,KEY_Q,KEY_W,KEY_E,KEY_R};
	m_Player.SetCtrlKey(key);

	m_Player.SetHero("Davis");
	m_Player.SetTeam(0);

	for(int i=0 ; i<10 ; i++){
		for (int j=0 ; j<10 ; j++)
		{
			m_Heroes.push_back(m_Player.CreateHero(Vector3(-500+j*100,0,i*100)));
		}
			
	}
	
	
}


int InitDirect3DApp::UpdateInput()
{
	m_Player.UpdateInput();
	return 0;
}

int InitDirect3DApp::UpdateUI()
{
	switch(m_GameProcess)
	{
	case UI_PAGE_MAIN_MENU:
		DealMainMenu();
		break;
	case UI_PAGE_OPTION:
		DealOptionPage();
		break;
	case UI_PAGE_TOWER_SETTING:
		DealTowerSettingPage();
		break;
	case UI_PAGE_GAME_PLAY:
		DealGamePlayPage();
		break;
	}
	m_DXUT_UI->ClearCmdState();
	return 0;
}

void InitDirect3DApp::PrintInfo()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.
	static int frameCnt = 0;
	static float t_base = 0.0f;
	frameCnt++;
	// Compute averages over one second period.
	if( (m_Timer.getGameTime() - t_base) >= 1.0f )
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;
		std::wcout << L"FPS: " << fps << L" Balls: " << g_BallptrManager.Ballptrs().size()
			 << "\t"<< g_EnemyBallptrManager.Ballptrs().size() << L"\n";
		std::wcout << m_FrameStats;
		// Reset for next average.
		frameCnt = 0;
		t_base  += 1.0f;
	}
}


void InitDirect3DApp::InitTexture()
{
	ID3D11Texture2D* tex1, *tex2, *tesres;
	// Create the depth/stencil buffer and view.
	D3D11_TEXTURE2D_DESC depthStencilDesc0;
	depthStencilDesc0.Width     = mClientWidth;
	depthStencilDesc0.Height    = mClientHeight;
	depthStencilDesc0.MipLevels = 1;
	depthStencilDesc0.ArraySize = 1;
	depthStencilDesc0.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
	depthStencilDesc0.SampleDesc.Count   = 1; // multisampling must match
	depthStencilDesc0.SampleDesc.Quality = 0; // swap chain values.
	depthStencilDesc0.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc0.BindFlags      = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	depthStencilDesc0.CPUAccessFlags = 0; 
	depthStencilDesc0.MiscFlags      = 0;
	HR(m_d3dDevice->CreateTexture2D(&depthStencilDesc0, 0, &tex1));
	HR(m_d3dDevice->CreateShaderResourceView(tex1, 0, &SRVView1));
	HR(m_d3dDevice->CreateRenderTargetView(tex1, 0, &RTVView1));

	HR(m_d3dDevice->CreateTexture2D(&depthStencilDesc0, 0, &tex2));
	HR(m_d3dDevice->CreateShaderResourceView(tex2, 0, &SRVView2));
	HR(m_d3dDevice->CreateRenderTargetView(tex2, 0, &RTVView2));

	HR(m_d3dDevice->CreateTexture2D(&depthStencilDesc0, 0, &tesres));
	HR(m_d3dDevice->CreateShaderResourceView(tesres, 0, &SRVViewRes));
	HR(m_d3dDevice->CreateRenderTargetView(tesres, 0, &RTVViewRes));

	Screen_Vertex svQuad[4];
	svQuad[0].pos = D3DXVECTOR4( -1.0f, 1.0f, 0.5f, 1.0f );
	svQuad[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	svQuad[1].pos = D3DXVECTOR4( 1.0f, 1.0f, 0.5f, 1.0f );
	svQuad[1].tex = D3DXVECTOR2( 1.0f, 0.0f );
	svQuad[2].pos = D3DXVECTOR4( -1.0f, -1.0f, 0.5f, 1.0f );
	svQuad[2].tex = D3DXVECTOR2( 0.0f, 1.0f );
	svQuad[3].pos = D3DXVECTOR4( 1.0f, -1.0f, 0.5f, 1.0f );
	svQuad[3].tex = D3DXVECTOR2( 1.0f, 1.0f );

	ID3D11Texture2D* tex12;

	D3D11_TEXTURE2D_DESC depthStencilDesc1;
	depthStencilDesc1.Width     = mClientWidth;
	depthStencilDesc1.Height    = mClientHeight;
	depthStencilDesc1.MipLevels = 1;
	depthStencilDesc1.ArraySize = 1;
	depthStencilDesc1.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc1.SampleDesc.Count   = 1; // multisampling must match
	depthStencilDesc1.SampleDesc.Quality = 0; // swap chain values.
	depthStencilDesc1.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc1.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc1.CPUAccessFlags = 0; 
	depthStencilDesc1.MiscFlags      = 0;
	HR(m_d3dDevice->CreateTexture2D(&depthStencilDesc1, 0, &tex12));
	HR(m_d3dDevice->CreateDepthStencilView(tex12, 0, &m_DepthStencilView2));
}

void InitDirect3DApp::DealMainMenu()
{
	std::vector<CmdState> cmdstate = m_DXUT_UI->GetCmdState();

	for (size_t i=0; i<cmdstate.size(); i++)
	{
		switch(cmdstate[i].id)
		{
		case IDC_MAIN_MENU_STARTGAME:
			ChangeUI(UI_PAGE_GAME_PLAY);
			break;
		case IDC_MAIN_MENU_OPTION:
			ChangeUI(UI_PAGE_OPTION);
			break;
		case IDC_MAIN_MENU_EXIT:
			exit(0);
			break;
		}
	}
}

void InitDirect3DApp::DealOptionPage()
{
	int val;
	std::vector<CmdState> cmdstate = m_DXUT_UI->GetCmdState();

// 	if (m_SettingKeyID>=0)
// 		SetCtrlKey();		//砞﹚北龄矪瞶ㄧ计

	for (size_t i=0; i<cmdstate.size(); i++)
	{
		switch(cmdstate[i].id)
		{
		case IDC_OPTION_MENU_VOLUME:
			val = m_DXUT_UI->GetSliderNum(cmdstate[i].id)-7000;
			WavSoundS::instance().SetVolume(val);
			break;
		case IDC_OPTION_MENU_KEY_UP:
			m_SettingKeyID = 0;
			m_SettingKeyTextID = IDC_OPTION_MENU_KEY_UP-1;
			break;
		case IDC_OPTION_MENU_KEY_DOWN:
			m_SettingKeyID = 1;
			m_SettingKeyTextID = IDC_OPTION_MENU_KEY_DOWN-1;
			break;
		case IDC_OPTIOT_MENU_KEY_LEFT:
			m_SettingKeyID = 2;
			m_SettingKeyTextID = IDC_OPTIOT_MENU_KEY_LEFT-1;
			break;
		case IDC_OPTIOT_MENU_KEY_RIGHT:
			m_SettingKeyID = 3;
			m_SettingKeyTextID = IDC_OPTIOT_MENU_KEY_RIGHT-1;
			break;
		case IDC_OPTIOT_MENU_KEY_SKILL:
			m_SettingKeyID = 4;
			m_SettingKeyTextID = IDC_OPTIOT_MENU_KEY_SKILL-1;
			break;
		case IDC_OPTIOT_MENU_KEY_TIME:
			m_SettingKeyID = 5;
			m_SettingKeyTextID = IDC_OPTIOT_MENU_KEY_TIME-1;
			break;
		case IDC_OPTIOT_MENU_KEY_EXIT:
			GoBackUI();
			break;
		}
	}
}

void InitDirect3DApp::DealTowerSettingPage()
{
	int tid;
	std::vector<CmdState> cmdstate = m_DXUT_UI->GetCmdState();
	for (size_t i=0; i<cmdstate.size(); i++)
	{
		switch(cmdstate[i].id)
		{
		case IDC_TOWER_SETTING_TOWERCOMBO:
			ReflashTowerState();
			break;
		case IDC_TOWER_SETTING_LVUP:
			tid = m_DXUT_UI->GetComboBoxSel(IDC_TOWER_SETTING_TOWERCOMBO);
			
			ReflashTowerState();
			break;
		case IDC_TOWER_SETTING_SELL:
			tid = m_DXUT_UI->GetComboBoxSel(IDC_TOWER_SETTING_TOWERCOMBO);
			
			ReflashTowerState();
			break;
		case IDC_TOWER_SETTING_TOWERSEL:
			break;
		case IDC_TOWER_SETTING_BUY:
			tid = m_DXUT_UI->GetComboBoxSel(IDC_TOWER_SETTING_TOWERCOMBO);
			ReflashTowerState();
			break;
		case IDC_TOWER_SETTING_OPTION:
			ChangeUI(UI_PAGE_OPTION);
			break;
		case IDC_TOWER_SETTING_BACK:
			GoBackUI();
			break;
		case IDC_TOWER_SETTING_EXIT:
			exit(0);
			break;
		}
	}
}

void InitDirect3DApp::DealGamePlayPage()
{
	std::vector<CmdState> cmdstate = m_DXUT_UI->GetCmdState();
	for (size_t i=0; i<cmdstate.size(); i++)
	{
		switch(cmdstate[i].id)
		{
		case IDC_PLAY_PAGE_MENU:
			ChangeUI(UI_PAGE_TOWER_SETTING);
			break;
		}
	}

}

void InitDirect3DApp::ChangeUI( int i )
{
	if (i!=m_GameProcess)
	{
		m_Last2GameProcess = m_LastGameProcess;
		m_LastGameProcess = m_GameProcess;
		m_GameProcess=i;
		m_DXUT_UI->CloseAllUI();
		m_DXUT_UI->OpenUI(i);
	}
}

void InitDirect3DApp::GoBackUI()
{
	if (m_LastGameProcess!=m_GameProcess)
	{
		m_GameProcess=m_LastGameProcess;
		m_LastGameProcess=m_Last2GameProcess;
		m_DXUT_UI->CloseAllUI();
		m_DXUT_UI->OpenUI(m_GameProcess);
	}
}

void InitDirect3DApp::ReflashTowerState()
{
	
}

void InitDirect3DApp::TestCamera()
{
	if (InputStateS::instance().isKeyDown(KEY_Z))
	{
		m_Camera->Zoom(-10);
		//m_Camera->SurroundX(-10);
		//m_Camera->MoveX(-1);
	}
	if (InputStateS::instance().isKeyDown(KEY_X))
	{
		//m_Camera->SurroundX(10);
		m_Camera->Zoom(10); 
		//m_Camera->MoveX(1);
	}
	if (InputStateS::instance().isKeyDown(KEY_4))
	{
		//m_Camera->Zoom(-1);
		//m_Camera->SurroundX(-10);
		m_Camera->MoveX(-10);
	}
	if (InputStateS::instance().isKeyDown(KEY_6))
	{
		//m_Camera->SurroundX(10);
		//m_Camera->Zoom(1); 
		m_Camera->MoveX(10); 
	}
	if (InputStateS::instance().isKeyDown(KEY_2))
	{
		//m_Camera->Zoom(-1);
		//m_Camera->SurroundX(-10);
		m_Camera->MoveY(-10);
	}
	if (InputStateS::instance().isKeyDown(KEY_8))
	{
		//m_Camera->SurroundX(10);
		//m_Camera->Zoom(1); 
		m_Camera->MoveY(10); 
	}
	if (InputStateS::instance().isKeyDown(KEY_K))
	{
		//m_Camera->Zoom(-1);
		m_Camera->SurroundX(-10);
		//m_Camera->MoveX(-1);
	}
	if (InputStateS::instance().isKeyDown(KEY_I))
	{
		m_Camera->SurroundX(10);
		//m_Camera->Zoom(1);
		//m_Camera->MoveX(1);
	}
	if (InputStateS::instance().isKeyDown(KEY_J))
	{
		//m_Camera->Zoom(-1);
		m_Camera->SurroundY(-10);
		//m_Camera->MoveX(-1);
	}
	if (InputStateS::instance().isKeyDown(KEY_L))
	{
		m_Camera->SurroundY(10);
		//m_Camera->Zoom(1);
		//m_Camera->MoveX(1);
	}
}

void InitDirect3DApp::UpdateCamera()
{
	m_Heroes_cLootAt->SetRawValue(m_Camera->GetLookAt(), 0, sizeof(float)*3);
	m_Heroes_cPos->SetRawValue((void*)m_Camera->GetCPos(), 0, sizeof(float)*3);
	m_Background_cLootAt->SetRawValue(m_Camera->GetLookAt(), 0, sizeof(float)*3);
	m_Background_cPos->SetRawValue((void*)m_Camera->GetCPos(), 0, sizeof(float)*3);
}
