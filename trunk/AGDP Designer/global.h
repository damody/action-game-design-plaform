#pragma once

#include <d3d11.h>
#include "DX11/TextureManager.h"
#include <game/HeroInfo.h>
#include <game/ObjectInfo.h>
#include <game/Frameinfo.h>
#include <game/LuaMap.h>
#include <string>

extern HeroInfo* g_HeroInfo;

extern std::wstring g_FrameName;
extern int	g_FrameIndex;
extern FramesMap* g_ActiveFramesMap;

extern float g_Frame_Scale;
extern float g_Frame_OffsetX;
extern float g_Frame_OffsetY;

extern TextureManager* g_TextureManagerFrame;

extern HeroInfoMap g_HeroInfoMap;
extern ObjectInfoMap g_ObjectInfoMap;

extern LuaMap g_Actions;
extern KeyMap g_KeyMap;	
