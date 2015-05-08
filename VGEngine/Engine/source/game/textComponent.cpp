
#include "engine/game/textComponent.h"
#include "engine/game/game.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/graphics/opengl.h"

using namespace vg;
using namespace vg::graphics;
using namespace std;

TextComponent::TextComponent(std::string& fontPath, FileManager *manager)
{
    mFontSize = 12;

    // Library initialize
    FT_Error error;
	FT_Library library;
    error = FT_Init_FreeType(&library);
    mFace = NULL;

    manager->readAsset(fontPath, mCharData);

    Vector2<int> resolution(Game::getInstance()->getGraphics()->getContext()->getWidth(),
        Game::getInstance()->getGraphics()->getContext()->getHeight());

    // New face
    error = FT_New_Memory_Face(library, &mCharData[0], mCharData.size(), 0, &mFace);
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

    mVertexBuffer = new VertexBuffer(defaultVertices);
    mIndexBuffer = new IndexBuffer(defaultIndices);
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

void TextComponent::setFontSize(uint fontSize)
{
    mFontSize = fontSize;
}

GLuint TextComponent::getTextureId()
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
