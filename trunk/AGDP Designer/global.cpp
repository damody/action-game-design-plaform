#include "global.h"

HeroInfo* g_HeroInfo = NULL;

FramesMap*	g_ActiveFramesMap = NULL;
std::string	g_FrameName = std::string( "" );
int		g_FrameIndex = -1;

float g_Frame_Scale = 1.0f;
float g_Frame_OffsetX = 100.0f;
float g_Frame_OffsetY = 100.0f;

TextureManager* g_TextureManagerPicture;
TextureManager* g_TextureManagerFrame;

int LoadTexture( std::string path )
{
	int id = -1;

	if ( g_TextureManagerFrame != NULL )
	{
		id = g_TextureManagerFrame->AddTexture( path );
	}

	return id;
}
