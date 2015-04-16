
#include "engine/graphics/debugSprite.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/utility/logger.h"

#include "../external/glm/gtc/matrix_transform.hpp"
#include "../external/glm/gtx/transform.hpp"

using namespace vg;
using namespace std;

DebugSprite::DebugSprite(const string& textureFileName, float x, float y, float rotation)
    : mPosition(x, y), mRotation(rotation)
{
	mTexture = new Texture(textureFileName);
    mVertices = defaultVertices;
    mIndices = defaultIndices;
    updateVertices();
}

DebugSprite::~DebugSprite()
{
	//delete mVertexBuffer;
	//delete mIndexBuffer;
}

void DebugSprite::initialize()
{
	//mVertexBuffer = new VertexBuffer(mVertices);
	//mIndexBuffer = new IndexBuffer(mIndices);
}

void DebugSprite::draw(Shader& shader)
{
    VertexBuffer vBuffer(mVertices);
    IndexBuffer iBuffer(mIndices);

    if (mTexture->isLoaded())
    {
        shader.useProgram();
        mTexture->bind();
        shader.unUseProgram();
    }
        
    GraphicsDevice::draw(&shader, &vBuffer, &iBuffer);
	
    if (mTexture->isLoaded())
    {
        shader.useProgram();
        mTexture->unbind();
        shader.unUseProgram();
    }
}

Texture* DebugSprite::getTexture()
{
    return mTexture;
}

void DebugSprite::setPosition(float x, float y)
{
    mPosition.x = x;
    mPosition.y = y;
    updateVertices();
}

void DebugSprite::move(float x, float y)
{
    setPosition(mPosition.x + x, mPosition.y + y);
}

void DebugSprite::setRotation(float rotation)
{
    mRotation = rotation;
    updateVertices();
}

void DebugSprite::rotate(float rotation)
{
    setRotation(mRotation + rotation);
}

/*
void DebugSprite::setScale(float scale)
{
    setScale(mScale + scale);
    updateVertices();
}

void DebugSprite::scale(float scale)
{
    setScale(mScale + scale);
}
*/

void DebugSprite::updateVertices()
{
    /// @todo get current vertex element size
    glm::mat4 transform = glm::translate(glm::vec3(mPosition, 1.0f))
        * glm::inverse(glm::rotate(mRotation, glm::vec3(0.0f, 0.0f, 1.0f)));
    
    for (int i = 0; i < defaultVertices.size(); i += 8)
    {
        glm::vec4 position(mVertices[i], mVertices[i + 1], 0.0f, 1.0f);
        position = transform * position;
        mVertices[i] = position.x;
        mVertices[i + 1] = position.y;
    }
}
