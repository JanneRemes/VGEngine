
#include "engine/graphics/spriteBatch.h"
#include "engine/graphics/drawable.h"
#include "engine/graphics/graphicsDevice.h"

using namespace vg;

void SpriteBatch::append(const Drawable& drawable, uint32_t layer)
{
	drawable.draw(mLayers[layer][drawable.getTexture()]);
}

void SpriteBatch::draw(Shader& shader)
{
	for (auto& layer : mLayers)
	{
		for (auto& group : layer.second)
		{
			mVertexButter.setData(group.second);
			GraphicsDevice::draw(&shader, &mVertexButter);
		}
	}
}
