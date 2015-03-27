
#pragma once

#include "engine/graphics/texture.h"
#include "engine/graphics/shader.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"

#include <vector>

namespace vg
{
    class DebugSprite
    {
    public:
        DebugSprite(/*const Texture& texture*/);
        ~DebugSprite();

        void draw(Shader& shader);
        //Texture* getTexture();
        std::vector<float> getVertices();
        std::vector<uint> getIndices();

    private:
        //Texture mTexture;
        //VertexBuffer* mVertexBuffer;
        //IndexBuffer* mIndexBuffer;
    };
}