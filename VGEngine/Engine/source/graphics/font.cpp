
#include "engine/graphics/font.h"
#include "engine/assets/fileManager.h"
#include "engine/graphics/opengl.h"
#include "engine/utility/logger.h"
#include "engine/utility/string.h"

using namespace vg;
using namespace vg::graphics;
using namespace std;

Font::Font(const std::string& path)
	: Asset(path), mFontSize(toInt(path))
{
}

Font::~Font()
{

}

bool Font::load(core::FileManager* fileManager)
{
	string str = removeDigits(mPath);
	fileManager->readAsset(removeDigits(mPath), mCharData);
	gl::genTextures(&mTexture);
	FT_Error error;
	FT_Face face;					        
	FT_Library library;					
	error = FT_Init_FreeType(&library);

	error = FT_New_Memory_Face(library, &mCharData[0], mCharData.size(), 0, &face);
	mGlyph = face->glyph;
	FT_Set_Char_Size(face,	/* handle to face object */
		mFontSize * 64,		/* char_width in 1/64th of points */
		mFontSize * 64,		/* char_height in 1/64th of points */
		300,				/* horizontal device resolution in dpi */
		300);				/* vertical device resolution in dpi */

	int segment_size_x = 0, segment_size_y = 0;
	int num_segments_x = 16;
	int num_segments_y = 8;
	FT_GlyphSlot slot;
	FT_Bitmap bmp;
	int glyph_width, glyph_height;

	int c, j, i;
	for (c = 0; c < 128; c++)
	{
		error = FT_Load_Char(face, c, FT_LOAD_RENDER);
		if (error)
			Log("vgengine", "Freetype error: %d", error);

		slot = face->glyph;
		bmp = slot->bitmap;

		glyph_width = nextp2(bmp.width);
		glyph_height = nextp2(bmp.rows);

		if (glyph_width > segment_size_x)
			segment_size_x = glyph_width;

		if (glyph_height > segment_size_y)
			segment_size_y = glyph_height;
	}

	int font_tex_width = nextp2(num_segments_x * segment_size_x);
	int font_tex_height = nextp2(num_segments_y * segment_size_y);

	int bitmap_offset_x = 0, bitmap_offset_y = 0;
	
	unsigned char* font_texture_data = (unsigned char*)malloc(sizeof(unsigned char)* 2 * font_tex_width * font_tex_height);
	memset((void*)font_texture_data, 0, sizeof(unsigned char)* 2 * font_tex_width * font_tex_height);

	for (c = 0; c < 128; c++) 
	{
		error = FT_Load_Char(face, c, FT_LOAD_RENDER);
		if (error)
			Log("vgengine", "Freetype error: %d", error);

		slot = face->glyph;
		bmp = slot->bitmap;

		glyph_width = bmp.width;
		glyph_height = bmp.rows;

		div_t temp = div(c, num_segments_x);

		bitmap_offset_x = segment_size_x * temp.rem;
		bitmap_offset_y = segment_size_y * temp.quot;

		for (j = 0; j < glyph_height; j++) 
		{
			for (i = 0; i < glyph_width; i++) 
			{
				font_texture_data[2 * ((bitmap_offset_x + i) + (j + bitmap_offset_y) * font_tex_width) + 0] =
					font_texture_data[2 * ((bitmap_offset_x + i) + (j + bitmap_offset_y) * font_tex_width) + 1] =
					(i >= bmp.width || j >= bmp.rows) ? 0 : bmp.buffer[i + bmp.width * j];
			}
		}

		advance[c] = (float)(slot->advance.x >> 6);
		tex_x1[c] = (float)bitmap_offset_x / (float)font_tex_width;
		tex_x2[c] = (float)(bitmap_offset_x + bmp.width) / (float)font_tex_width;
		tex_y1[c] = (float)bitmap_offset_y / (float)font_tex_height;
		tex_y2[c] = (float)(bitmap_offset_y + bmp.rows) / (float)font_tex_height;
		width[c] = bmp.width;
		height[c] = bmp.rows;
		offset_x[c] = (float)slot->bitmap_left;
		int offy = ((-1 * face->glyph->metrics.height) >> 6) + slot->bitmap.rows - slot->bitmap_top;
		offset_y[c] = static_cast<float>(offy);
	}

	gl::bindTexture(mTexture);
	gl::texParameteri(gl::getGL_TEXTURE_MIN_FILTER(), gl::getGL_LINEAR());
	gl::texParameteri(gl::getGL_TEXTURE_MAG_FILTER(), gl::getGL_LINEAR());
	gl::texImage2DLuminanceAlpha(font_tex_width, font_tex_height, font_texture_data);
	
	free(font_texture_data);
	FT_Done_Face(face);
	FT_Done_FreeType(library);

	return true;
}

bool Font::unload()
{
	return true;
}

Vec2f Font::getTexCoord1(char character)
{
	return Vec2f(tex_x1[character], tex_y1[character]);
}

Vec2f Font::getTexCoord2(char character)
{
	return Vec2f(tex_x2[character], tex_y2[character]);
}

unsigned int Font::getFontSize()
{
	return mFontSize;
}

Vec2f Font::getSize(char character)
{
	return Vec2f(width[character], height[character]);
}

float Font::getWidth(char character)
{
	return width[character];
}

float Font::getHeight(char character)
{
	return height[character];
}

float Font::getAdvance(char character)
{
	return advance[character];
}

Vec2f Font::getOffset(char character)
{
	return Vec2f(offset_x[character], offset_y[character]);
}

void Font::bind()
{
	gl::activeTexture();
	gl::bindTexture(mTexture);
}

void Font::unbind()
{
	gl::activeTexture();
	gl::bindTexture(0u);
}

int Font::nextp2(int x)
{
	int val = 1;
	while (val < x) val <<= 1;
	return val;
}
