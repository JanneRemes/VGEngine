
#include "engine/graphics/debugSprite.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/utility/logger.h"

#include "../external/glm/gtc/matrix_transform.hpp"
#include "../external/glm/gtx/transform.hpp"

using namespace vg;
using namespace std;

DebugSprite::DebugSprite(const string& textureFileName,
	Vector2<int> position, Vector2<int> size, float rotation, uint layer)
	: mPosition(position), mSize(size), mRotation(rotation), mLayer(layer)
{
	mTexture = new Texture(textureFileName);
	mVertices = defaultVertices;
	mIndices = defaultIndices;
}

DebugSprite::~DebugSprite()
{
	delete mVertexBuffer;
	delete mIndexBuffer;
}

void DebugSprite::initialize()
{
	mVertexBuffer = new VertexBuffer(mVertices);
	mIndexBuffer = new IndexBuffer(mIndices);
}

void DebugSprite::draw(Shader& shader)
{
    if (mTexture->isLoaded())
    {
        shader.useProgram();
        mTexture->bind();
        shader.unUseProgram();
    }
    
	shader.setPosition(mPosition);
	shader.setSize(mSize);
	shader.setRotation(mRotation);
	shader.setLayer(mLayer);

	GraphicsDevice::draw(&shader, mVertexBuffer, mIndexBuffer);
	
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

void DebugSprite::setPosition(Vector2<int> position)
{
	mPosition = position;
}

void DebugSprite::move(Vector2<int> change)
{
	mPosition += change;
}

void DebugSprite::setRotation(float rotation)
{
    mRotation = rotation;
}

void DebugSprite::rotate(float rotation)
{
    setRotation(mRotation + rotation);
}

/// @todo continue with spriteBatch later
/*
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
*/
