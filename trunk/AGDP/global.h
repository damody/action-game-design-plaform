#pragma once
#include <d3d11.h>
#include "DX11/TextureManager.h"
#include "DX11/WaveSound.h"
#include "DX11/TextGeneratorDX11.h"
#include "DX11/TextManager.h"

#include "game/HeroManager.h"
#include "game/ObjectManager.h"
#include "game/HeroInfoManager.h"
#include "game/ObjectInfoManager.h"
#include "game/BGManager.h"
#include "game/Effect.h"
#include "DX11/Camera.h"

extern TextureManager	g_TextureManager;
extern HeroInfoMG	g_HeroInfoMG;
extern HeroManager	g_HeroMG;
extern ObjectInfoMG	g_ObjectInfoMG;
extern ObjectMG		g_ObjectMG;
extern BGManager	g_BGManager;
extern EffectManager*	g_EffectMG;
extern TextManager	g_TextMG;

extern ID3D11Device*	g_d3dDevice;
extern ID3D11DeviceContext*	g_DeviceContext;
extern WavPlayer	g_WavPlayer;
extern TextGeneratorDX11	g_TextGenarator;

extern float		g_TimeSpeed;
extern int		g_Time;
extern Camera_Sptr	g_Camera;

//HolyK
extern bool g_TestViewEffect;//觀看2048*2048 Effect用的bool
//HolyK