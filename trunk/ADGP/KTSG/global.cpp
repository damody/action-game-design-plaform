#include "StdGame.h"
#include "global.h"
TextureManager	g_TextureManager;
HeroInfoMG	g_HeroInfoMG;
HeroManager	g_HeroMG;
ObjectInfoMG	g_ObjectInfoMG;
ObjectMG	g_ObjectMG;
BGManager	g_BGManager;
EffectManager*  g_EffectMG;
TextManager     g_TextMG;
ID3D11Device*	g_d3dDevice;
ID3D11DeviceContext* g_DeviceContext;
WavPlayer	g_WavPlayer;	
TextGeneratorDX11 g_TextGenarator;
int		g_Time;
Camera_Sptr	g_Camera;

//test
bool g_TestViewEffect;