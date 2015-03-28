
#include "engine/graphics/debugSprite.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/utility/logger.h"

using namespace vg;
using namespace std;

DebugSprite::DebugSprite(const string& textureFileName)
{
	mTexture = new Texture(textureFileName);
    //mVertexBuffer = new VertexBuffer(getVertices());
    //mIndexBuffer = new IndexBuffer(getIndices());
}

DebugSprite::~DebugSprite()
{

}

void DebugSprite::draw(Shader& shader)
{
    VertexBuffer vertexBuffer(getVertices());
    IndexBuffer indexBuffer(getIndices());

	if (mTexture->isLoaded())
		mTexture->bind();

	shader.useProgram();
	
    GraphicsDevice::draw(shader, vertexBuffer, indexBuffer);
	
	if (mTexture->isLoaded())
		mTexture->unbind();
	shader.unUseProgram();
}

Texture* DebugSprite::getTexture()
{
    return mTexture;
}

std::vector<float> DebugSprite::getVertices()
{
    float result[] =
    {
        // Position Vec2
        // Color Vec4
        // TexCoord Vec2

        //left up
        -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f, 1.0f,
        0.0f, 1.0f,
    
        //left down
        -0.5f, -0.5f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f,
    
        //right down
        0.5f, -0.5f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f,
    
        //right up
        0.5f, 0.5f,
        1.0f, 1.0f, 0.0f, 1.0f,
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