
#include "engine/game/renderComponent.h"
#include "engine/graphics/texture.h"
#include "engine/assets/assetManager.h"
#include "engine/game/game.h"
#include "engine/utility/logger.h"

using namespace vg;
using namespace vg::graphics;
using namespace std;

RenderComponent::RenderComponent()
:mShape(Rectangle), mVertices(getDefaultVertices()), mIndices(getDefaultIndices())
{
	mTexture = nullptr;
}

RenderComponent::RenderComponent(std::string textureName, Shape shape)
: mShape(shape), mVertices(getDefaultVertices()), mIndices(getDefaultIndices())
{
	core::AssetManager* am = Game::getInstance()->getAssetManager();
	if ((am->get<vg::graphics::Texture>(textureName)) == nullptr)
		am->load<vg::graphics::Texture>(textureName);
	mTexture = am->get<vg::graphics::Texture>(textureName);
}

RenderComponent::RenderComponent(Shape shape)
: mShape(shape), mVertices(getDefaultVertices()), mIndices(getDefaultIndices())
{
	mTexture = nullptr;
}

vector<float>* RenderComponent::getVertices()
{
	return &mVertices;
}

vector<unsigned short>* RenderComponent::getIndices()
{
	return &mIndices;
}

Texture* RenderComponent::getTexture()
{
	return mTexture;
}

void RenderComponent::setTexCoords(glm::vec2 texCoords[4])
{
	for (int i = 0; i < 4; i++)
	{
		mVertices[i * 8 + 6] = texCoords[i].x;
		mVertices[i * 8 + 7] = texCoords[i].y;
	}
}

void RenderComponent::setColor(vg::Color color)
{
	for (int i = 2; i < mVertices.size(); i += 8)
	{
		mVertices[i] = color.red / 255.0f;
		mVertices[i + 1] = color.green / 255.0f;
		mVertices[i + 2] = color.blue / 255.0f;
		mVertices[i + 3] = color.alpha / 255.0f;
	}
}


//private

std::vector<float> RenderComponent::getDefaultVertices()
{
	std::vector<float> result;
	switch (mShape)
	{
	case(Triangle) :
		result = std::vector<float>
		{
			// Position Vec2
			// Color Vec4
			// TexCoord Vec2

			//Triangle up
			0.5f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f,

			//left down
			0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 0.0f,

			//right down
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f,
		};
		break;

	case(Rectangle) :
		result = std::vector <float>
		{
			// Position Vec2
			// Color Vec4
			// TexCoord Vec2

			//left up
			0.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f,

			//left down
			0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 0.0f,

			//right down
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f,

			//right up
			1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f
		};
		break;

	default :
		Log("vgengine", "Indvalid RenderComponent shape!", "");
		break;
	}
	return result;
}

std::vector<unsigned short> RenderComponent::getDefaultIndices()
{
	std::vector<unsigned short> result;

	switch (mShape)
	{
	case(Triangle) :
		result = std::vector<unsigned short>
		{
			0u, 1u, 2u
		};
		break;

	case(Rectangle) :
		result = std::vector <unsigned short>
		{
			0u, 1u, 2u,
			0u, 2u, 3u
		};
		break;

	default:
		Log("vgengine", "Indvalid RenderComponent shape!", "");
		break;
	}
	return result;
};