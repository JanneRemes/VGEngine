
#include "engine/graphics/debugSprite.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/utility/logger.h"

using namespace vg;
using namespace std;
using namespace glm;

DebugSprite::DebugSprite(const string& textureFileName, float x, float y, float rotation)
    : mPosition(x, y), mRotation(rotation)
{
	mTexture = new Texture(textureFileName);
}

DebugSprite::~DebugSprite()
{
	delete mVertexBuffer;
	delete mIndexBuffer;
}

void DebugSprite::initialize()
{
	mVertexBuffer = new VertexBuffer(vector<float>
	{
		// Position Vec2
		// Color Vec4
		// TexCoord Vec2

		//left up
		-1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f,
		0.0f, 1.0f,

		//left down
		-1.0f, -1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f,

		//right down
		1.0f, -1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f,

		//right up
		1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f
	});

	mIndexBuffer = new IndexBuffer(vector<uint>
	{
		0u, 1u, 2u,
		0u, 2u, 3u
	});
}

void DebugSprite::draw(Shader& shader)
{
    if (mTexture->isLoaded())
    {
        shader.useProgram();
        mTexture->bind();
        shader.unUseProgram();
    }
        
    GraphicsDevice::draw(&shader, mVertexBuffer, mIndexBuffer,
        mPosition.x, mPosition.y, mRotation);
	
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