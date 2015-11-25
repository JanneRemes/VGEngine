
#include "engine/game/textComponent.h"
#include "engine/game/game.h"
#include "engine/assets/fileManager.h"
#include "engine/graphics/opengl.h"
#include "engine/graphics/screen.h"

using namespace vg;
using namespace vg::graphics;
using namespace std;

TextComponent::TextComponent(string fontPath, unsigned int fontSize, string text)
	: Component(), mText(text), mFontSize(fontSize)
{
	core::FileManager* fm = Game::getInstance()->getFileManager();
	float defaultVerticesArray[] =
	{
		// Position Vec2
		// Color Vec4
		// TexCoord Vec2

		//left up
		0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f,

		//left down
		0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f,

		//right down
		1.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f,

		//right up
		1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f
	};
	defaultVertices = std::vector<float>(defaultVerticesArray, defaultVerticesArray + sizeof(defaultVerticesArray) / sizeof(defaultVerticesArray[0]));


	unsigned short defaultIndicesArray[] =
	{
		0u, 1u, 2u,
		0u, 2u, 3u
	};
	defaultIndices = std::vector<unsigned short>(defaultIndicesArray, defaultIndicesArray + sizeof(defaultIndicesArray) / sizeof(defaultIndicesArray[0]));

	mVertices = defaultVertices;
	mIndices = defaultIndices;
    fm->readAsset(fontPath, mCharData);
	initializeFace();
}

TextComponent::~TextComponent()
{
	FT_Done_Face(mFace);
	FT_Done_FreeType(mLibrary);
}

void TextComponent::setText(string text)
{
    mText = text;
}

string TextComponent::getText()
{
	return mText;
}

void TextComponent::setFontSize(unsigned int fontSize)
{
    mFontSize = fontSize;
	initializeFace();
}

unsigned int TextComponent::getFontSize()
{
	return mFontSize;
}

void TextComponent::bindTexture()
{
	gl::bindTexture(mTexture);
}

void TextComponent::unBindTexture()
{
	gl::bindTexture(0u);
}

FT_GlyphSlot*  TextComponent::getGlyph()
{
	return &mGlyph;
}

FT_Face* TextComponent::getFace()
{
	return &mFace;
}

std::vector<float>* TextComponent::getVertices()
{
	return &mVertices;
}

std::vector<unsigned short>* TextComponent::getIndices()
{
	return &mIndices;
}

void TextComponent::initializeFace()
{
	FT_Error error;
	error = FT_Init_FreeType(&mLibrary);

	// New face
	error = FT_New_Memory_Face(mLibrary, &mCharData[0], mCharData.size(), 0, &mFace);
	mGlyph = mFace->glyph;
	FT_Set_Char_Size(mFace,	/* handle to face object */
		0,					/* char_width in 1/64th of points */
		mFontSize * 64,		/* char_height in 1/64th of points */
		300,				/* horizontal device resolution in dpi */
		300);				/* vertical device resolution in dpi */

	gl::genTextures(&mTexture);

	gl::activeTexture();
	gl::bindTexture(mTexture);

	gl::texParameteri(gl::getGL_TEXTURE_WRAP_S(), gl::getGL_CLAMP_TO_EDGE());
	gl::texParameteri(gl::getGL_TEXTURE_WRAP_T(), gl::getGL_CLAMP_TO_EDGE());
	gl::texParameteri(gl::getGL_TEXTURE_MIN_FILTER(), gl::getGL_LINEAR());
	gl::texParameteri(gl::getGL_TEXTURE_MAG_FILTER(), gl::getGL_LINEAR());

	gl::bindTexture(0);
}

void TextComponent::setColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
{
	for (int i = 2; i < mVertices.size(); i += 8)
	{
		mVertices[i] = red / 255.0f;
		mVertices[i + 1] = green / 255.0f;
		mVertices[i + 2] = blue / 255.0f;
		mVertices[i + 3] = alpha / 255.0f;
	}
}

void TextComponent::setTexCoords(Vec2f leftTop, Vec2f rightBottom)
{
	glm::vec2 tc[4];
	tc[0] = glm::vec2(leftTop.x, leftTop.y);
	tc[1] = glm::vec2(leftTop.x, rightBottom.y);
	tc[2] = glm::vec2(rightBottom.x, rightBottom.y);
	tc[3] = glm::vec2(rightBottom.x, leftTop.y);
	for (int i = 0; i < 4; i++)
	{
		mVertices[i * 8 + 6] = tc[i].x;
		mVertices[i * 8 + 7] = tc[i].y;
	}
}

