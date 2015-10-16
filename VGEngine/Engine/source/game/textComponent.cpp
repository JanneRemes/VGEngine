
#include "engine/game/textComponent.h"
#include "engine/game/game.h"
#include <engine/assets/fileManager.h>
#include "engine/graphics/graphics.h"
#include "engine/graphics/opengl.h"

using namespace vg;
using namespace vg::graphics;
using namespace std;

TextComponent::TextComponent(string fontPath, unsigned int fontSize)
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

    mFontSize = fontSize;
	mVertexBuffer = new VertexBuffer(defaultVertices);
	mIndexBuffer = new IndexBuffer(defaultIndices);
    fm->readAsset(fontPath, mCharData);
	initializeFace();
}

TextComponent::~TextComponent()
{
    delete mVertexBuffer;
    delete mIndexBuffer;
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

unsigned int TextComponent::getTextureId()
{
	return mTexture;
}

FT_GlyphSlot*  TextComponent::getGlyph()
{
	return &mGlyph;
}

FT_Face* TextComponent::getFace()
{
	return &mFace;
}

VertexBuffer* TextComponent::getVertexBuffer()
{
	return mVertexBuffer;
}

IndexBuffer* TextComponent::getIndexBuffer()
{
	return mIndexBuffer;
}

void TextComponent::initializeFace()
{
	FT_Error error;
	FT_Library library;
	error = FT_Init_FreeType(&library);

	Vector2<int> resolution = Graphics::getResolution();

	// New face
	error = FT_New_Memory_Face(library, &mCharData[0], mCharData.size(), 0, &mFace);
	mGlyph = mFace->glyph;
	FT_Set_Char_Size(mFace, 0, mFontSize * 64, resolution.getX(), resolution.getY());

	gl::genTextures(&mTexture);

	gl::activeTexture();
	gl::bindTexture(mTexture);

	gl::texParameteri(getGL_TEXTURE_WRAP_S(), getGL_CLAMP_TO_EDGE());
	gl::texParameteri(getGL_TEXTURE_WRAP_T(), getGL_CLAMP_TO_EDGE());
	gl::texParameteri(getGL_TEXTURE_MIN_FILTER(), getGL_LINEAR());
	gl::texParameteri(getGL_TEXTURE_MAG_FILTER(), getGL_LINEAR());

	gl::bindTexture(0);
}

void TextComponent::setColour(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
{
	vector<float> vertexData = defaultVertices;

	for (int i = 2; i < vertexData.size(); i += 8)
	{
		vertexData[i] = red / 255.0f;
		vertexData[i + 1] = green / 255.0f;
		vertexData[i + 2] = blue / 255.0f;
		vertexData[i + 3] = alpha / 255.0f;
	}
	delete mVertexBuffer;
	mVertexBuffer = new VertexBuffer(vertexData);
}
