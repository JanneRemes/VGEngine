
#include "engine/game/textRenderSystem.h"
#include "engine/game/textComponent.h"
#include "engine/game/game.h"
#include "engine/graphics/shader.h"
#include "engine/graphics/opengl.h"
#include "engine/graphics/graphics.h"
#include "engine/game/renderSystem.h"

using namespace vg;
using namespace vg::graphics;
using namespace std;

TextRenderSystem::TextRenderSystem()
{

}

TextRenderSystem::~TextRenderSystem()
{

}

void TextRenderSystem::update(std::vector<GameObject*> *gameObjects,float deltaTime)
{
    Shader* shader = Game::getInstance()->getGraphics()->getShader();
	shader->useProgram();
	shader->setUniform("unifNoTexture", false);
	shader->setUniform("unifFontTexture", true);

    for (auto i = gameObjects->begin(); i != gameObjects->end(); i++)
    {
        TextComponent* text = (*i)->getComponent<TextComponent>();
		TransformComponent* transform = (*i)->getComponent<TransformComponent>();
        if (text != nullptr && transform != nullptr)
        {
			gl::bindTexture(text->getTextureId());

			string textString = text->getText();
			FT_GlyphSlot* glyph = text->getGlyph();
			float x = transform->getWorldPosition().getX();
			float y = transform->getWorldPosition().getY();
			float base = y;

			for (int i = 0; i < textString.size(); i++)
			{
				FT_UInt index = FT_Get_Char_Index((*glyph)->face, textString[i]);
				FT_Load_Glyph(*text->getFace(), index, FT_RENDER_MODE_NORMAL);
				FT_Render_Glyph(*glyph, FT_RENDER_MODE_NORMAL);
				gl::texImage2DAlpha((*glyph)->bitmap.width, (*glyph)->bitmap.rows, (*glyph)->bitmap.buffer);

				y = base - (*glyph)->bitmap_top;

				RenderSystem::updateProjection(shader);
				shader->setUniform("unifModel", RenderSystem::modelTransform(Vector2<float>(x, y), transform->getOrigin(),
					Vector2<float>((*glyph)->bitmap.width, (*glyph)->bitmap.rows), 0.0f));
				shader->setUniform("unifLayer", transform->getLayer());
				Graphics::draw(shader, text->getVertexBuffer(), text->getIndexBuffer());
				
				x += ((*glyph)->advance.x >> 6);
			}
			gl::bindTexture(0u);
        }
    }
	shader->setUniform("unifFontTexture", false);
	shader->unUseProgram();
}