
#pragma once

#include "engine/game/system.h"

namespace vg
{
    class TextRenderSystem : public System
    {
    public:
        TextRenderSystem();
        ~TextRenderSystem();
        void update(std::vector<GameObject*> *gameObjects);

    private:

    };
}