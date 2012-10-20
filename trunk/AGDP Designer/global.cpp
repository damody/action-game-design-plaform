#include "global.h"

HeroInfo* g_HeroInfo = NULL;

FramesMap*	g_ActiveFramesMap = NULL;
std::wstring	g_FrameName = std::wstring( L"" );
int		g_FrameIndex = -1;

float g_Frame_Scale = 1.0f;
float g_Frame_OffsetX = 100.0f;
float g_Frame_OffsetY = 100.0f;

TextureManager* g_TextureManagerFrame;

HeroInfoMap g_HeroInfoMap;
ObjectInfoMap g_ObjectInfoMap;

LuaMap g_Actions;
LuaMap g_Effects;
KeyMap g_KeyMap('^','8','v','2','<','4','>','6');