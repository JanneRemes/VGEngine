
#include "engine/graphics/text.h"
#include "../external/lodepng/lodepng.h"
#include "engine/utility/logger.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/graphics/opengl.h"
#include "engine/game/game.h"

using namespace vg::graphics;

Text::Text(std::string& fontPath, FileManager *manager)
{
	// Library init
	FT_Error error;
	error = FT_Init_FreeType(&mLibrary);
	mFace = NULL;

	manager->readAsset(fontPath, mCharData);

	Vector2<int> resolution(Game::getInstance()->getGraphics()->getContext()->getWidth(),
		Game::getInstance()->getGraphics()->getContext()->getHeight());

	// New face
	error = FT_New_Memory_Face(mLibrary, &mCharData[0], mCharData.size(), 0, &mFace);
	mGlyph = mFace->glyph;
	FT_Set_Char_Size(mFace, 0, 16 * 64, resolution.getX(), resolution.getY());

	gl::genTextures(&mTexture);

	gl::activeTexture();
	gl::bindTexture(mTexture);

	gl::texParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gl::texParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	gl::texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gl::texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gl::bindTexture(0);

	Log("text", "Bitmap x: %i", mGlyph->bitmap_left, "");
	Log("text", "Bitmap y: %i", mGlyph->bitmap_top, "");
	Log("text", "Bitmap width: %i", mGlyph->bitmap.width, "");
	Log("text", "Bitmap height: %i", mGlyph->bitmap.rows, "");

	float sx = 2.0f / 1280.0f;
	float sy = 2.0f / 720.0f;

	float x = mGlyph->bitmap_left / sx;
	float y = mGlyph->bitmap_top / sy;

	float w = mGlyph->bitmap.width / sx;
	float h = mGlyph->bitmap.rows / sy;


	float tempX = mGlyph->bitmap_left;
	float tempY = mGlyph->bitmap_top;
	float tempW = mGlyph->bitmap.width;
	float tempH = mGlyph->bitmap.rows;

	Log("text", "Bitmap x, y, w, h: %f %f %f %f", x, y, w, h, "");

	createBuffer(x, y, w, h);

	mVertexBuffer = new VertexBuffer(mVertexData);
	mIndexBuffer = new IndexBuffer(mIndexData);
}

void Text::draw(std::string text, Shader* shader)
{
	Vector2<int> startPosition(0, 0);

	shader->useProgram();

	gl::activeTexture();
	gl::bindTexture(mTexture);


	float sx = Game::getInstance()->getGraphics()->getScreenWidth();
	float sy = Game::getInstance()->getGraphics()->getScreenHeight();
	for (int i = 0; i < text.size(); i++)
	{
		mGlyph_index = FT_Get_Char_Index(mGlyph->face, text[i]);
		FT_Load_Glyph(mFace, mGlyph_index, FT_LOAD_DEFAULT);
		FT_Render_Glyph(mGlyph, FT_RENDER_MODE_NORMAL);

		gl::texImage2D(mGlyph->bitmap.width, mGlyph->bitmap.rows, mGlyph->bitmap.buffer, GL_ALPHA);

		Log("text", "ADVANCE: %d", sx);
		shader->setPosition(Vector2<int>(100 /*+(mGlyph->advance.x >> 6)*sx*/+70*i, 100));
		shader->setSize(Vector2<int>(mGlyph->bitmap.width, mGlyph->bitmap.rows));
		GraphicsDevice::draw(shader, mVertexBuffer, mIndexBuffer);
	}
		gl::bindTexture(0);

		shader->unUseProgram();
	
}

void Text::initializeBuffer(char *text)
{
	float sx = 2 / 1280;
	float sy = 2 / 720;

	const char *p;
	for (p = text; *p; p++)
	{
		if (FT_Load_Char(mFace, *p, FT_LOAD_RENDER))
			continue;

		gl::texImage2D(mGlyph->bitmap.width, mGlyph->bitmap.rows, mGlyph->bitmap.buffer, GL_RGBA);

		float x = mGlyph->bitmap_left;
		float y = mGlyph->bitmap_top;

		float w = mGlyph->bitmap.width;
		float h = mGlyph->bitmap.rows;

		createBuffer(x, y, w, h);

		x += (mGlyph->advance.x * 64) * sx;
		y += (mGlyph->advance.y * 64) * sy;
	}
}

void Text::createBuffer(float x, float y, float w, float h)
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
	mVertexData.push_back(1.0);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);

	//vertex x1 y1
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

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

	// Index data
	mIndexData.push_back(0);
	mIndexData.push_back(1);
	mIndexData.push_back(2);

	mIndexData.push_back(0);
	mIndexData.push_back(2);
	mIndexData.push_back(3);

	///////////////////////////

	//// left up
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);

	//// Colours and alpha
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	////UV
	//mVertexData.push_back(x);
	//mVertexData.push_back(y - h);

	//// left down
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);

	//// Colours and alpha
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	////UV
	//mVertexData.push_back(x);
	//mVertexData.push_back(y);

	//// right down
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	//// Colours and alpha
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	////UV
	//mVertexData.push_back(x + w);
	//mVertexData.push_back(y);

	//// right up
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(0.0);

	//// Colours and alpha
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(0.0);
	//mVertexData.push_back(1.0);
	//mVertexData.push_back(1.0);

	////UV
	//mVertexData.push_back(x + w);
	//mVertexData.push_back(y - h);

	//mIndexData.push_back(0);
	//mIndexData.push_back(1);
	//mIndexData.push_back(2);

	//mIndexData.push_back(0);
	//mIndexData.push_back(2);
	//mIndexData.push_back(3);


	////left up
	//	0.0f, 0.0f,//-1.0f, 1.0f,
	//	0.5f, 0.5f, 0.5f, 1.0f,
	//	0.0f, 1.0f,

	//	//left down
	//	0.0f, 1.0f,//-1.0f, -1.0f,
	//	1.0f, 0.0f, 0.0f, 1.0f,
	//	0.0f, 0.0f,

	//	//right down
	//	1.0f, 1.0f,//1.0f, -1.0f,
	//	0.0f, 0.0f, 1.0f, 1.0f,
	//	1.0f, 0.0f,

	//	//right up
	//	1.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, 1.0f
}