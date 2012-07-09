#pragma  once
#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct Bitmap_ {
	int             x;
	int             y;
	unsigned int    width;
	unsigned int    height;
	unsigned int    pitch;
	unsigned char*  data;

} Bitmap;

void printtext(Bitmap *bitmap);
void combinetext(Bitmap *bitmap, Bitmap *font);
bool rasters(const wchar_t texts, Bitmap& bitmap);