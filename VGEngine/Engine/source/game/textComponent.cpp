
#include "engine/game/textComponent.h"
#include "engine/game/game.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/graphics/opengl.h"

using namespace vg;
using namespace vg::graphics;
using namespace std;

TextComponent::TextComponent(std::string& fontPath, FileManager *manager)
{
    mPosition.setX(0.0f);
    mPosition.setY(200.0f);
    mFontSize = 12;

    // Library initialize
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

    mVertexBuffer = new VertexBuffer(defaultVertices);
    mIndexBuffer = new IndexBuffer(defaultIndices);
}

TextComponent::~TextComponent()
{
    delete mVertexBuffer;
    delete mIndexBuffer;
}

void TextComponent::draw(Shader* shader)
{
    shader->useProgram();

    float x = mPosition.getX();
    float y = mPosition.getY();

    float basey = y;

    gl::activeTexture();
    gl::bindTexture(mTexture);
    Vector2<int> resolution(Game::getInstance()->getGraphics()->getContext()->getWidth(),
        Game::getInstance()->getGraphics()->getContext()->getHeight());

    for (int i = 0; i < mText.size(); i++)
    {
        mGlyph_index = FT_Get_Char_Index(mGlyph->face, mText[i]);
        FT_Load_Glyph(mFace, mGlyph_index, FT_RENDER_MODE_NORMAL);
        FT_Render_Glyph(mGlyph, FT_RENDER_MODE_NORMAL);

        gl::texImage2D(mGlyph->bitmap.width, mGlyph->bitmap.rows, mGlyph->bitmap.buffer, GL_ALPHA);

        y = basey - mGlyph->bitmap_top;
        shader->setPosition(Vector2<int>(x, y));
        shader->setSize(Vector2<int>(mGlyph->bitmap.width, mGlyph->bitmap.rows));
        GraphicsDevice::draw(shader, mVertexBuffer, mIndexBuffer);
        x += (mGlyph->advance.x >> 6);
    }

    gl::bindTexture(0);
    shader->unUseProgram();
}

void TextComponent::setText(string text)
{
    mText = text;
}

void TextComponent::setFontSize(uint fontSize)
{
    mFontSize = fontSize;
}

void TextComponent::setPosition(Vector2<int> position)
{
    mPosition = position;
}
