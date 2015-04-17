
#include "../external/lodepng/lodepng.h"
#include "engine\graphics\text.h"
#include "engine\utility\logger.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine\graphics\opengl.h"
using namespace vg;

text::text(std::string& fontPath, FileManager *manager)
{
	std::vector<FT_Byte> charData;
	manager->readAsset(fontPath, charData);
	
	FT_Error error;
	FT_Library library;
	error = FT_Init_FreeType(&library);
	if (error)
	{
		Log("FTYPE", "Freetype init fail %x", error, "");
	}

	mFace = NULL;
	error = FT_New_Memory_Face(library, &charData[0], charData.size(), 0, &mFace);
	if (error != 0)
	{
		Log("FTYPE", "Freetype new memory face error %x", error, "");
	}
	error = FT_Set_Pixel_Sizes(mFace, 0, 10);
	error = FT_Load_Char(mFace, 'X', FT_LOAD_RENDER);

	mGlyph = mFace->glyph;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gl::genTextures(&mTexture);
	gl::activeTexture();
	gl::bindTexture(mTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mGlyph->bitmap.width, mGlyph->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, mGlyph->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//gl::bindTexture(0);

	//Log("text", "Bitmap width: %i", face->glyph->bitmap.width, "");
	//Log("text", "Bitmap height: %i", face->glyph->bitmap.rows, "");
	//Log("text", "Bitmap buffer: %p", face->glyph->bitmap.buffer, "");
	
	float x = mGlyph->bitmap_left ;
	float y = mGlyph->bitmap_top ;

	float w = mGlyph->bitmap.width ;
	float h = mGlyph->bitmap.rows ;

	createBuffer(x, y, w, h);

	mVertexBuffer = new VertexBuffer(mVertexData);
	mIndexBuffer = new IndexBuffer(mIndexData);
}

void text::initializeBuffer(char *text)
{
	float sx = 2 / 1280;
	float sy = 2 / 720;

	const char *p;
	for (p = text; *p; p++)
	{
		if (FT_Load_Char(mFace, *p, FT_LOAD_RENDER))
			continue;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mGlyph->bitmap.width, mGlyph->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, mGlyph->bitmap.buffer);

		float x = mGlyph->bitmap_left;
		float y = mGlyph->bitmap_top;

		float w = mGlyph->bitmap.width;
		float h = mGlyph->bitmap.rows;

		createBuffer(x, y, w, h);

		x += (mGlyph->advance.x * 64) * sx;
		y += (mGlyph->advance.y * 64) * sy;
	}
}

void text::draw(Shader &slimshady)
{	
	slimshady.useProgram();

	gl::activeTexture(mTexture);
	gl::bindTexture(mTexture);

	GraphicsDevice::draw(&slimshady, mVertexBuffer, mIndexBuffer, 0.0f, 0.0f, 0.0f, 1.0f);

	gl::activeTexture();
	gl::bindTexture(0);

	slimshady.unUseProgram();
}

void text::createBuffer(float x, float y, float w, float h)
{
	//vertex x0 y0
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);

	//vertex x1 y0
	mVertexData.push_back(0.0);
	mVertexData.push_back(-1.0);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(0.0);
	mVertexData.push_back(-1.0);

	//vertex x1 y1
	mVertexData.push_back(1.0);
	mVertexData.push_back(-1.0);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(1.0);
	mVertexData.push_back(-1.0);

	//vertex x0 y1
	mVertexData.push_back(1.0);
	mVertexData.push_back(0.0);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(1.0);
	mVertexData.push_back(0.0);

	mIndexData.push_back(0);
	mIndexData.push_back(1);
	mIndexData.push_back(2);

	mIndexData.push_back(0);
	mIndexData.push_back(2);
	mIndexData.push_back(3);

	////vertex x0 y0
	//mVertexData.push_back(x);
	//mVertexData.push_back(-y);

	//// Colours and alpha
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	////UV
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);

	////vertex x1 y0
	//mVertexData.push_back(x);
	//mVertexData.push_back(-y - h);

	//// Colours and alpha
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	////UV
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(0.0);

	////vertex x1 y1
	//mVertexData.push_back(x + w);
	//mVertexData.push_back(-y - h);

	//// Colours and alpha
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	////UV
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);

	////vertex x0 y1
	//mVertexData.push_back(x + w);
	//mVertexData.push_back(-y);

	//// Colours and alpha
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	////UV
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	//// Index data
	//mIndexData.push_back(0);
	//mIndexData.push_back(1);
	//mIndexData.push_back(2);

	//mIndexData.push_back(0);
	//mIndexData.push_back(2);
	//mIndexData.push_back(3);
}