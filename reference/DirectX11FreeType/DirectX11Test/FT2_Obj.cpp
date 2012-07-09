#include "FT2_Obj.h"
#include FT_GLYPH_H

void draw_bitmap( FT_Bitmap*  bitmap, FT_Int x, FT_Int y, unsigned char* image, FT_Int w, FT_Int h);

void FT2_Obj::Init(const char * fname, unsigned int h) 
{ 
            this->h=h;

            if (FT_Init_FreeType( &library ))  
                        throw std::runtime_error("FT_Init_FreeType failed");

            if (FT_New_Face( library, fname, 0, &face ))  
                        throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");

            //FT_Set_Char_Size( face,h<< 6, h << 6, 96, 96); 
			FT_Set_Pixel_Sizes(face, 24, 24);
			FT_Select_Charmap(face, FT_ENCODING_UNICODE);
            FT_Matrix     matrix;              /* transformation matrix */ 
            FT_Vector     pen;
			pen.x = 0;
			pen.y = 0;

            float angle = -0.0f/180.0f* 3.14f; 
            matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L ); 
            matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L ); 
            matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L ); 
            matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );

            FT_Set_Transform( face, &matrix, &pen ); 
}

unsigned char* FT2_Obj::DrawAUnicode(wchar_t ch, int& w, int& h) 
{ 
            /*if(FT_Load_Glyph( face, FT_Get_Char_Index( face, ch ), FT_LOAD_DEFAULT )) 
                        throw std::runtime_error("FT_Load_Glyph failed");

			FT_Glyph glyph; 
			if(FT_Get_Glyph( face->glyph, &glyph )) 
				throw std::runtime_error("FT_Get_Glyph failed");

			FT_Render_Glyph( face->glyph,   FT_RENDER_MODE_NORMAL  );  
			FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 ); 
			FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

			FT_Bitmap& bitmap=bitmap_glyph->bitmap;

			int width =  bitmap.width; 
			int height =  bitmap.rows;

			w = width;
			h = height;

            unsigned char* expanded_data = new unsigned char[ 3 * width * height];

            for(int j=0; j<height; j++) 
			{
				for(int i=0; i<width; i++) 
                {
					expanded_data[3*(i+(height-j-1)*width)]=  
                    expanded_data[3*(i+(height-j-1)*width)+1] =  
                    expanded_data[3*(i+(height-j-1)*width)+2] = 
                    (i>=bitmap.width || j>=bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width*j];
                }
            }
			return expanded_data;*/

	FT_Error error;

	error = FT_Load_Char(face, ch, FT_LOAD_RENDER); 

	if (error) 
		throw std::runtime_error("Load char failed.");

	FT_Bitmap *source = &face->glyph->bitmap;  

	int width = (face->glyph->metrics.width / 64); 
	int height = (face->glyph->metrics.height / 64); 
	int pixelDepth = 8;    
	int size = width * height;

	unsigned char* expanded_data = new unsigned char[width * height];

	for(int i=0;i<width*height;i++)
	{
		expanded_data[i] = 0;
	}

	w = width;
	h = height;

	draw_bitmap(source, face->glyph->bitmap_left, h - face->glyph->bitmap_top, expanded_data, w, h);

	return expanded_data;
}

void FT2_Obj::Free() 
{ 
            FT_Done_Face(face); 
            FT_Done_FreeType(library); 
}

void draw_bitmap( FT_Bitmap*  bitmap, FT_Int x, FT_Int y, unsigned char* image, FT_Int w, FT_Int h)
{
	FT_Int  i, j, p, q;
	FT_Int  x_max = x + bitmap->width;
	FT_Int  y_max = y + bitmap->rows;

	printf("%d, %d, %d, %d, %d, %d\n", x, y, bitmap->width, bitmap->rows, w, h);

	for ( i = x, p = 0; i < x_max; i++, p++ )
	{
		for ( j = y, q = 0; j < y_max; j++, q++ )
		{
			if ( i < 0      || j < 0       ||
				i >= w || j >= h )
				continue;

			image[j*w+i] |= bitmap->buffer[q * bitmap->width + p];
		}
	}
}