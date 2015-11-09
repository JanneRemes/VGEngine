
#include "engine/game/renderComponent.h"
#include "engine/graphics/texture.h"

using namespace vg;
using namespace vg::graphics;
using namespace std;

RenderComponent::RenderComponent(vector<float> vertices, vector<unsigned short> indices) 
: Component(), mVertices(vertices), mIndices(indices)
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