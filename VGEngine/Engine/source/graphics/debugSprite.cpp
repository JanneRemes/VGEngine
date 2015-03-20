
#include "engine/graphics/debugSprite.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/utility/logger.h"

using namespace vg;
using namespace std;

DebugSprite::DebugSprite(/*const Texture& texture*/)
    //:mTexture(texture)
{

}

DebugSprite::~DebugSprite()
{

}

void DebugSprite::draw(Shader& shader)
{
    VertexBuffer vertexBuffer(getVertices());
    IndexBuffer indexBuffer(getIndices());
    GraphicsDevice::draw(shader, vertexBuffer, indexBuffer);

    if (glGetError() != GL_NO_ERROR)
        Log("DRAW", "gl error", "");

    
}


/*
Texture* DebugSprite::getTexture()
{
    return &mTexture;
}
*/

std::vector<float> DebugSprite::getVertices()
{
    float result[] =
    {
        // Position Vec2
        // Color Vec4
        // TexCoord Vec2

        //left up
        -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f,
    
        //left down
        -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f,
    
        //right down
        1.0f, -1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f,
    
        //right up
        1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f
    
    };
    return vector<float>(result, result + sizeof(result) / sizeof(float));
}

std::vector<uint> DebugSprite::getIndices()
{
    uint result[] =
    {
        0u, 1u, 2u,
        0u, 2u, 3u

    };
    return vector<uint>(result, result + sizeof(result) / sizeof(uint));
}