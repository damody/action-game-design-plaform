#include "FTBITMAP.h"
#include <math.h>

void printtext(Bitmap *bitmap)
{
	for(int j=0; j<bitmap->height; j++) {
		for(int i=0; i<bitmap->pitch; i++) {
			for(int k=7; k>=0; k--){
				if(7-k+i*8 == bitmap->width)
					break;
				printf("%c", (bitmap->data[i+j*bitmap->pitch] & 0x1<<k)?'1':'0');
			}
		}
		printf("\n");
	}
	printf("%d\n", bitmap->width);
}

void combinetext(Bitmap *bitmap, Bitmap *font)
{
	int x1 = bitmap->x;
	int y1 = bitmap->y;
	unsigned int width1 = bitmap->width;
	unsigned int height1 = bitmap->height;
	unsigned int pitch1 = bitmap->pitch;
	unsigned char* data1 = bitmap->data;

	int x2 = x1 + width1 + font->x;
	int y2 = font->y;
	unsigned int width2 = font->width;
	unsigned int height2 = font->height;
	unsigned int pitch2 = font->pitch;
	unsigned char* data2 = font->data;

	int x3 = x1;
	if(x1 > x2) {
		x3 = x2;
	}
	unsigned int width3 = width1 + font->x + width2;
	int y3 = y1;
	unsigned int height3 = height1;
	if(y1 > y2) {
		y3 = y2;
		height3 += (y1 - y2);
	}
	if(y1+height1 < y2+height2) {
		height3 += (y2+height2) - (y1+height1);
	}
	unsigned int pitch3 = width3/8;
	if(width3 % 8 != 0) {
		pitch3 += 1;
	}

	int size3 = pitch3 * height3;
	unsigned char *data3 = static_cast<unsigned char*>(calloc(size3, sizeof(unsigned char)));
	int shiftX1 = 0;
	int shiftY1 = (height3+y3) - (height1+y1);
	for(int j=0; j<height1; j++) {
		int nj = j+shiftY1;
		for(int i=0; i<pitch1; i++) {
			int n = shiftX1/8+i+nj*pitch3;
			unsigned char data = data1[i+j*pitch1];
			int shift = shiftX1%8;
			if(shift == 0) {
				data3[n] |= data;
			} else {
				data3[n] |= (0x7f & data>>shift);
				data3[n+1] |= data<<(8-shift);
			}
		}
	}
	int shiftX2 = x2-x3;
	int shiftY2 = (height3+y3) - (height2+y2);
	for(int j=0; j<height2; j++) {
		int nj = j+shiftY2;
		for(int i=0; i<pitch2; i++) {
			int n = shiftX2/8+i+nj*pitch3;
			unsigned char data = data2[i+j*pitch2];
			int shift = shiftX2%8;
			if(shift == 0) {
				data3[n] |= data;
			} else {
				data3[n] |= (0x7f & data>>shift);
				data3[n+1] |= data<<(8-shift);
			}
		}
	}
	free(bitmap->data);

	bitmap->x = x3;
	bitmap->y = y3;
	bitmap->width = width3;
	bitmap->height = height3;
	bitmap->pitch = pitch3;
	bitmap->data = data3;
}

bool rasters(const wchar_t texts, Bitmap& bitmap)
{
	FT_Library library;
	if (FT_Init_FreeType(&library)) {
		return false;
	}

	FT_Face face;
	if(FT_New_Face(library, "unifont.ttf", 0, &face)) {
		FT_Done_FreeType(library);
		return false;
	}

	int pixalWidth = 1024;
	int pixalHeight = 1024;
	if(FT_Set_Pixel_Sizes(face, pixalWidth, pixalHeight)) {
		FT_Done_Face(face);
		FT_Done_FreeType(library);
		return false;
	}

	FT_Select_Charmap(face, FT_ENCODING_UNICODE);

	FT_Matrix     matrix;
	FT_Vector     pen;
	pen.x = 0*64;
	pen.y = 0;

	float angle = -0.0f/180.0f* 3.14f; 
	matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L ); 
	matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L ); 
	matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L ); 
	matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );

	FT_Set_Transform( face, &matrix, &pen );

		unsigned int ucode = texts;
		FT_UInt glyph_index = FT_Get_Char_Index(face, ucode);
		if(!glyph_index) {
			return false;
		}

		if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT)) {
			return false;
		}
		if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP) {
			if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO)) {
				return false;
			}
		}

		Bitmap font = {    face->glyph->bitmap_left,
			face->glyph->bitmap_top - face->glyph->bitmap.rows,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			face->glyph->bitmap.pitch,
			face->glyph->bitmap.buffer
		};

		unsigned char *array = static_cast<unsigned char*>(calloc(1, sizeof(unsigned char)));
		Bitmap bitmapTemp = {0, 0, 0, 0, 0, array};

		unsigned char *buffer;

		if((face->glyph->bitmap.width + 0.0f) / face->glyph->bitmap.pitch > 1.0f)
		{
			buffer = static_cast<unsigned char*>(calloc((face->glyph->bitmap.pitch+1)*face->glyph->bitmap.rows, sizeof(unsigned char)));
			memcpy(buffer, face->glyph->bitmap.buffer, (face->glyph->bitmap.pitch+1)*face->glyph->bitmap.rows*sizeof(unsigned char));
		}
		else
		{
			buffer = static_cast<unsigned char*>(calloc(face->glyph->bitmap.pitch*face->glyph->bitmap.rows, sizeof(unsigned char)));
			memcpy(buffer, face->glyph->bitmap.buffer, face->glyph->bitmap.pitch*face->glyph->bitmap.rows*sizeof(unsigned char));
		}

		font.data = buffer;

		//combinetext(&bitmapTemp, &font);

		bitmap = font;

	FT_Done_Face(face);
	FT_Done_FreeType(library);

	return true;
}