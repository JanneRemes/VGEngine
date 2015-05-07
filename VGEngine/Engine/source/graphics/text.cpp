
#include "engine/graphics/text.h"
#include "../external/lodepng/lodepng.h"
#include "engine/utility/logger.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/graphics/opengl.h"
#include "engine/game/game.h"

using namespace vg::graphics;

Text::Text(std::string& fontPath, FileManager *manager, int fontsize)
{
	mPosition.setX(200.0f);
	mPosition.setY(200.0f);

	mFontSize = fontsize;

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
	FT_Set_Char_Size(mFace, 0, mFontSize * 64, resolution.getX(), resolution.getY());

	gl::genTextures(&mTexture);

	gl::activeTexture();
	gl::bindTexture(mTexture);

	gl::texParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gl::texParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	gl::texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gl::texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gl::bindTexture(0);

	createBuffer();

	mVertexBuffer = new VertexBuffer(mVertexData);
	mIndexBuffer = new IndexBuffer(mIndexData);
}

void Text::draw(Shader* shader)
{
	float x = mPosition.getX();
	float y = mPosition.getY();

	float basey = y;

	shader->useProgram();

	gl::activeTexture();
	gl::bindTexture(mTexture);
	Vector2<int> resolution(Game::getInstance()->getGraphics()->getContext()->getWidth(),
		Game::getInstance()->getGraphics()->getContext()->getHeight());

	for (int i = 0; i < mText.size(); i++)
	{
		mGlyph_index = FT_Get_Char_Index(mGlyph->face, mText[i]);
		FT_Load_Glyph(mFace, mGlyph_index, FT_LOAD_DEFAULT);
		FT_Render_Glyph(mGlyph, FT_RENDER_MODE_NORMAL);

		gl::texImage2D(mGlyph->bitmap.width, mGlyph->bitmap.rows, mGlyph->bitmap.buffer, GL_ALPHA);
		
		y = basey - mGlyph->bitmap_top;
		shader->setPosition(Vector2<int>(x, y ));
		shader->setSize(Vector2<int>(mGlyph->bitmap.width, mGlyph->bitmap.rows));
		GraphicsDevice::draw(shader, mVertexBuffer, mIndexBuffer);
		x += (mGlyph->advance.x >> 6 );
	}
		gl::bindTexture(0);

		shader->unUseProgram();	
}

void Text::setText(std::string text)
{
	mText = text;
}

void Text::setPosition(int x, int y)
{
	mPosition.setX(x);
	mPosition.setY(y);
}

vg::Vector2<int> Text::getPosition()
{
	return mPosition;
}

void Text::setColour(int r, int g, int b)
{
	for (int i = 2; i < mVertexData.size(); i += 8)
	{
		mVertexData[i] = r / 255.0f;
		mVertexData[i + 1] = g / 255.0f;
		mVertexData[i + 2] = b / 255.0f;
	}
}

void Text::setFontSize(int size)
{
	Vector2<int> resolution(Game::getInstance()->getGraphics()->getContext()->getWidth(),
		Game::getInstance()->getGraphics()->getContext()->getHeight());

	mFontSize = size;
	FT_Set_Char_Size(mFace, 0, mFontSize * 64, resolution.getX(), resolution.getY());
}

void Text::createBuffer()
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
}