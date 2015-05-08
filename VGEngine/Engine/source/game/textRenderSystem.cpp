
#include "engine/game/textRenderSystem.h"
#include "engine/game/textComponent.h"
#include "engine/game/game.h"
#include "engine/graphics/shader.h"

using namespace vg;
using namespace vg::graphics;

TextRenderSystem::TextRenderSystem()
{

}

TextRenderSystem::~TextRenderSystem()
{

}

void TextRenderSystem::update(std::vector<GameObject*> *gameObjects)
{
    Shader* shader = Game::getInstance()->getGraphics()->getShader();

    for (auto i = gameObjects->begin(); i != gameObjects->end(); i++)
    {
        TextComponent* text = (*i)->getComponent<TextComponent>();
        if (text != nullptr)
        {
            text->draw(shader);
        }
    }
}