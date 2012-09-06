#pragma once

#include <d3d11.h>
#include "DX11/TextureManager.h"
#include <game/HeroInfo.h>
#include <game/Frameinfo.h>
#include <string>

extern HeroInfo* g_HeroInfo;

extern std::string g_FrameName;
extern int	g_FrameIndex;
extern FramesMap* g_ActiveFramesMap;

extern float g_Frame_Scale;
extern float g_Frame_OffsetX;
extern float g_Frame_OffsetY;

extern TextureManager* g_TextureMG_Frame;

int LoadTexture( std::string path );