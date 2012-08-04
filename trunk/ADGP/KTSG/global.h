#pragma once
#include <d3d11.h>
#include "DX11/TextureManager.h"
#include "DX11/WaveSound.h"
#include "game/HeroManager.h"
#include "game/ObjectManager.h"
#include "game/HeroInfoManager.h"
#include "game/ObjectInfoManager.h"
#include "game/BGManager.h"


extern TextureManager g_TextureManager;
extern HeroInfoMG     g_HeroInfoMG;
extern HeroManager    g_HeroMG;
extern ObjectInfoMG   g_ObjectInfoMG;
extern ObjectMG	      g_ObjectMG;
extern BGManager      g_BGManager;
extern ID3D11Device*  g_d3dDevice;

extern WavSound g_WavePlayer;
extern int g_Time;
