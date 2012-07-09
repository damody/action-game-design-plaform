#pragma once
#include "ball/BallptrManager.h"
#include "DX11/TextureManager.h"
#include "HeroInfoManager.h"
#include <d3d11.h>
extern TextureManager g_TextureManager;
extern HeroInfoMG     g_HeroInfoMG;
extern BallptrManager g_BallptrManager;
extern BallptrManager g_EnemyBallptrManager;
extern ID3D11Device* g_d3dDevice;

