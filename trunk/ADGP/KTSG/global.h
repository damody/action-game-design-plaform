#pragma once
#include "ball/BallptrManager.h"
#include "DX11/TextureManager.h"
#include "game/BGManager.h"
#include "game/HeroManager.h"
#include "game/ObjectManager.h"
#include "game/HeroInfoManager.h"
#include "game/ObjectInfoManager.h"

#include <d3d11.h>
extern TextureManager g_TextureManager;
extern HeroInfoMG     g_HeroInfoMG;
extern HeroManager    g_HeroMG;
extern ObjectInfoMG   g_ObjectInfoMG;
extern ObjectMG	      g_ObjectMG;
extern BGManager      g_BGManger;
extern ID3D11Device*  g_d3dDevice;
extern int g_Time;

extern BallptrManager g_BallptrManager;
extern BallptrManager g_EnemyBallptrManager;