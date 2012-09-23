#include "StdGame.h"
#include "global.h"
TextureManager	g_TextureManager;
HeroInfoManager	g_HeroInfoManager;
HeroManager	g_HeroManager;
ObjectInfoManager	g_ObjectInfoManager;
ObjectManager	g_ObjectManager;
BackgroundManager	g_BackgroundManager;
EffectManager*  g_EffectManager;
TextManager     g_TextManager;
ID3D11Device*	g_d3dDevice;
ID3D11DeviceContext* g_DeviceContext;
WavPlayer	g_WavPlayer;
TextGeneratorDX11 g_TextGenarator;
float		g_TimeSpeed = 1.f / 60.f;
int		g_Time = 0;
Camera_Sptr	g_Camera;

//test
bool g_TestViewEffect;