#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include "InitDirect3DApp.h"
#include "InputState.h"
#include "WaveSound.h"
#include "ui/CmdDef.h"
#include "game/HeroInfo.h"

InitDirect3DApp* InitDirect3DApp::dxAppInstance = NULL;

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance)
: D3DApp(hInstance), m_Heroes_Width(0), m_Heroes_Height(0), m_Buffer_Heroes(0) , m_SettingKeyID(-1), m_LastGameProcess(1), m_GameProcess(1), m_Last2GameProcess(1)
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

	//init control key
	m_CtrlKey.resize(CTRL_KEY_MAX);
	m_CtrlKey[0] = DEFAULT_CTRL_KEY_UP;
	m_CtrlKey[1] = DEFAULT_CTRL_KEY_DOWN;
	m_CtrlKey[2] = DEFAULT_CTRL_KEY_LEFT;
	m_CtrlKey[3] = DEFAULT_CTRL_KEY_RIGHT;
	m_CtrlKey[4] = DEFAULT_CTRL_KEY_SKILL;
	m_CtrlKey[5] = DEFAULT_CTRL_KEY_TIMECHENGE;
}


void InitDirect3DApp::UpdateScene(float dt)
{
	m_DXUT_UI->UpdataUI(dt);
	m_SwapChain->Present(0, 0);
	D3DApp::DrawScene(); // clear window
	PrintInfo();
	UpdateInput();
	static float timp_count = dt;
	if (timp_count > 1/60.0f)
	{
		for(std::vector<Hero_RawPtr>::iterator it = m_Heroes.begin();it != m_Heroes.end(); it++)
		{
			(*it)->Update(dt);
		}
		timp_count = 0;
	}
	timp_count+=dt;
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
	
}

void InitDirect3DApp::DrawScene()
{
	// clear color
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, m_ClearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL,  1.0f, 0);
	m_DeviceContext->ClearRenderTargetView(RTVView1, m_ClearColor);
	m_DeviceContext->ClearRenderTargetView(RTVView2, m_ClearColor);
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

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
}

void InitDirect3DApp::buildPointFX()
{
	ID3D10Blob* pCode;
	ID3D10Blob* pError;
	HRESULT hr = 0;
	hr=D3DX11CompileFromFile(_T("shader\\bullet.fx"), NULL, NULL, NULL, 
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
	m_PMap_Heroes =m_Effect_Heroes->GetVariableByName("gMap")->AsShaderResource();

	D3DX11_PASS_DESC PassDesc;
	m_PTech_Heroes->GetPassByIndex(0)->GetDesc(&PassDesc);
	HR(m_d3dDevice->CreateInputLayout(VertexDesc_BulletVertex, 4, PassDesc.pIAInputSignature,PassDesc.IAInputSignatureSize, &m_PLayout_Heroes));

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
	// 開啟zbuffer write
	if ( D3D_OK != m_d3dDevice->CreateDepthStencilState(&depth_stencil_desc, &m_pDepthStencil_ZWriteON) )
		return ;

	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	// 關閉zbuffer write
	if ( D3D_OK != m_d3dDevice->CreateDepthStencilState(&depth_stencil_desc, &m_pDepthStencil_ZWriteOFF) )
		return ;

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
	// ADD混色模式
	if ( D3D_OK != m_d3dDevice->CreateBlendState(&blend_state_desc, &m_pBlendState_ADD) )
		return;
	blend_state_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA ;
	blend_state_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	blend_state_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blend_state_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;

	// Alpha Blend混色模式
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

	Hero_RawPtr TestHero = Hero_RawPtr(new Hero("Davis"));
	TestHero->Position(Vector3(200,200,0));
	m_Heroes.push_back(TestHero);
}


int InitDirect3DApp::UpdateInput()
{
	
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

void InitDirect3DApp::SetCtrlKey()
{
	if (InputStateS::instance().isKeyPress(KEY_A))
	{
		m_CtrlKey[m_SettingKeyID] = KEY_A;
		m_SettingKeyID=-1;
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "A");
	}
	else if (InputStateS::instance().isKeyPress(KEY_B))
	{
		m_CtrlKey[m_SettingKeyID] = KEY_B;
		m_SettingKeyID=-1;
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "B");
	}
	else if (InputStateS::instance().isKeyPress(KEY_C))
	{
		m_CtrlKey[m_SettingKeyID] = KEY_C;
		m_SettingKeyID=-1;
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "C");
	}
	else if (InputStateS::instance().isKeyPress(KEY_D))
	{
		m_CtrlKey[m_SettingKeyID] = KEY_D;
		m_SettingKeyID=-1;
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "D");
	}
	else if (InputStateS::instance().isKeyPress(KEY_E))
	{
		m_CtrlKey[m_SettingKeyID] = KEY_E;
		m_SettingKeyID=-1;
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "E");
	}
	else if (InputStateS::instance().isKeyPress(KEY_F)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_F; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "F");
	}
	else if (InputStateS::instance().isKeyPress(KEY_G)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_G; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "G");
	}
	else if (InputStateS::instance().isKeyPress(KEY_H)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_H; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "H");
	}
	else if (InputStateS::instance().isKeyPress(KEY_I)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_I; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "I");
	}
	else if (InputStateS::instance().isKeyPress(KEY_J)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_J; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "J");
	}
	else if (InputStateS::instance().isKeyPress(KEY_K)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_K; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "K");
	}
	else if (InputStateS::instance().isKeyPress(KEY_L)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_L; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "L");
	}
	else if (InputStateS::instance().isKeyPress(KEY_M)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_M; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "M");
	}
	else if (InputStateS::instance().isKeyPress(KEY_N)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_N; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "N");
	}
	else if (InputStateS::instance().isKeyPress(KEY_O)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_O; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "O");
	}
	else if (InputStateS::instance().isKeyPress(KEY_P)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_P; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "P");
	}
	else if (InputStateS::instance().isKeyPress(KEY_Q)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_Q; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Q");
	}
	else if (InputStateS::instance().isKeyPress(KEY_R)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_R; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "R");
	}
	else if (InputStateS::instance().isKeyPress(KEY_S)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_S; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "S");
	}
	else if (InputStateS::instance().isKeyPress(KEY_T)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_T; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "T");
	}
	else if (InputStateS::instance().isKeyPress(KEY_U)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_U; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "U");
	}
	else if (InputStateS::instance().isKeyPress(KEY_V)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_V; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "V");
	}
	else if (InputStateS::instance().isKeyPress(KEY_W)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_W; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "W");
	}
	else if (InputStateS::instance().isKeyPress(KEY_X)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_X; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "X");
	}
	else if (InputStateS::instance().isKeyPress(KEY_Y)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_Y; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Y");
	}
	else if (InputStateS::instance().isKeyPress(KEY_Z)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_Z; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Z");
	}
	//===============================================================================0~9===================================================================
	//===============================================================================0~9===================================================================
	else if (InputStateS::instance().isKeyPress(KEY_0)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_0; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "0");
	}
	else if (InputStateS::instance().isKeyPress(KEY_1)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_1; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "1");
	}
	else if (InputStateS::instance().isKeyPress(KEY_2)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_2; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "2");
	}
	else if (InputStateS::instance().isKeyPress(KEY_3)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_3; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "3");
	}
	else if (InputStateS::instance().isKeyPress(KEY_4)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_4; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "4");
	}
	else if (InputStateS::instance().isKeyPress(KEY_5)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_5; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "5");
	}
	else if (InputStateS::instance().isKeyPress(KEY_6)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_6; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "6");
	}
	else if (InputStateS::instance().isKeyPress(KEY_7)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_7; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "7");
	}
	else if (InputStateS::instance().isKeyPress(KEY_8)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_8; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "8");
	}
	else if (InputStateS::instance().isKeyPress(KEY_9)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_9; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "9");
	}
	//===============================================================================numpad===================================================================
	//===============================================================================numpad===================================================================
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD0)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD0; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num0");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD1)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD1; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num1");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD2)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD2; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num2");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD3)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD3; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num3");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD4)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD4; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num4");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD5)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD5; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num5");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD6)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD6; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num6");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD7)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD7; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num7");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD8)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD8; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num8");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD9)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD9; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num9");
	}
	//===============================================================================方向鍵===================================================================
	//===============================================================================方向鍵===================================================================
	else if (InputStateS::instance().isKeyPress(KEY_UP)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_UP; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Up");
	}
	else if (InputStateS::instance().isKeyPress(KEY_DOWN)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_DOWN; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Down");
	}
	else if (InputStateS::instance().isKeyPress(KEY_LEFT)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_LEFT; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Left");
	}
	else if (InputStateS::instance().isKeyPress(KEY_RIGHT)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_RIGHT; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Right");
	}
	/*if (m_SettingKeyID==-1)
		m_TestHero.m_CtrlKeys = m_CtrlKey;*/
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

	if (m_SettingKeyID>=0)
		SetCtrlKey();		//設定控制按鍵的處理函數

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
