#pragma once
#include <stdexcept>
#include <math.h>
#include <ft2build.h>
#include FT_FREETYPE_H

class FT2_Obj 
{ 
	FT_Library library; 
	int h; 
	FT_Face face;

public: 
	void Init(const char * fname, unsigned int h);
	void Free();
	unsigned char* DrawAUnicode(wchar_t ch, int& width, int& height);
};