
#include "engine/graphics/debugSprite.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/utility/logger.h"

using namespace vg;
using namespace std;

DebugSprite::DebugSprite(const string& textureFileName)
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
		mTexture->bind();

	shader.useProgram();
	
    GraphicsDevice::draw(&shader, mVertexBuffer, mIndexBuffer);
	
	if (mTexture->isLoaded())
		mTexture->unbind();
	shader.unUseProgram();
}

Texture* DebugSprite::getTexture()
{
    return mTexture;
}