
#include "../external/lodepng/lodepng.h"
#include "engine\graphics\text.h"
#include "engine\utility\logger.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine\graphics\opengl.h"
#include "engine/game/game.h"
using namespace vg;

text::text(std::string& fontPath, FileManager *manager)
{
	manager->readAsset(fontPath, mCharData);
}

void text::draw(Shader &shader)
{	
	if (!mVertexBufferList.empty())
	for (int i = 0; i < mVertexBufferList.size(); i++)
	{
		shader.useProgram();

		gl::activeTexture(GL_TEXTURE0);
		gl::bindTexture(mTextureList[i]);

		///@todo set transform values to shader
		//GraphicsDevice::draw(&shader, &mVertexBufferList[i], &mIndexBufferList[i], 640.0f, 360.0f, 0.0f, 1.0f);
		GraphicsDevice::draw(&shader, &mVertexBufferList[i], &mIndexBufferList[i]);

		gl::activeTexture();
		gl::bindTexture(0);

		shader.unUseProgram();
	}
}

void text::setText(std::string text)
{
	FT_Error error;
	// Library init
	error = FT_Init_FreeType(&mLibrary);
	mFace = NULL;
	// New face
	error = FT_New_Memory_Face(mLibrary, &mCharData[0], mCharData.size(), 0, &mFace);
	mGlyph = mFace->glyph;
	
	for (int i = 0; i < text.size(); i++)
	{
		//error = FT_Load_Char(mFace, 'X', FT_LOAD_RENDER);
		mGlyph_index = FT_Get_Char_Index(mGlyph->face, text[i]);
		FT_Set_Char_Size(mFace, 0, 16 * 64, 1080, 720);
		FT_Load_Glyph(mFace, mGlyph_index, FT_LOAD_DEFAULT);
		FT_Render_Glyph(mGlyph, FT_RENDER_MODE_NORMAL);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(0, &mTexture);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mGlyph->bitmap.width, mGlyph->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, mGlyph->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	Log("text", "Bitmap x: %i", mGlyph->bitmap_left, "");
	Log("text", "Bitmap y: %i", mGlyph->bitmap_top, "");
	Log("text", "Bitmap width: %i", mGlyph->bitmap.width, "");
	Log("text", "Bitmap height: %i", mGlyph->bitmap.rows, "");

	float sx = 2.0f / 1080.0f;
	float sy = 2.0f / 720.0f;

	float x = mGlyph->bitmap_left * sx;
	float y = mGlyph->bitmap_top * sy;

	float w = mGlyph->bitmap.width * sx;
	float h = mGlyph->bitmap.rows * sy;

	Log("text", "Bitmap x, y, w, h: %f %f %f %f", x, y, w, h, "");

	createBuffer(x, y, w, h);

	mVertexBuffer = new VertexBuffer(mVertexData);
	mIndexBuffer = new IndexBuffer(mIndexData);

	mVertexBufferList.push_back(*mVertexBuffer);
	mIndexBufferList.push_back(*mIndexBuffer);
	mTextureList.push_back(mTexture);

	FT_Done_FreeType(mLibrary);
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

void text::createBuffer(float x, float y, float w, float h)
{
	//vertex x0 y0
	mVertexData.push_back(x);
	mVertexData.push_back(y);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(x);
	mVertexData.push_back(y);

	//vertex x1 y0
	mVertexData.push_back(x);
	mVertexData.push_back(y - h);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(x);
	mVertexData.push_back(y - h);

	//vertex x1 y1
	mVertexData.push_back(x + w);
	mVertexData.push_back(y - h);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(x + w);
	mVertexData.push_back(y - h);

	//vertex x0 y1
	mVertexData.push_back(x + w);
	mVertexData.push_back(y);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(x + w);
	mVertexData.push_back(y);

	// Index data
	mIndexData.push_back(0);
	mIndexData.push_back(1);
	mIndexData.push_back(2);

	mIndexData.push_back(0);
	mIndexData.push_back(2);
	mIndexData.push_back(3);

	///////////////////////////
	
	//vertex x0 y0
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);

	//// Colours and alpha
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	////UV
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);

	////vertex x1 y0
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(-1.0);

	//// Colours and alpha
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	////UV
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(-1.0);

	////vertex x1 y1
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(-1.0);

	//// Colours and alpha
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	////UV
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(-1.0);

	////vertex x0 y1
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(0.0);

	//// Colours and alpha
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	////UV
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(0.0);

	//mIndexData.push_back(0);
	//mIndexData.push_back(1);
	//mIndexData.push_back(2);

	//mIndexData.push_back(0);
	//mIndexData.push_back(2);
	//mIndexData.push_back(3);
}