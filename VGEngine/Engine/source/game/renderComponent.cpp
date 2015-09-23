
#include "engine/game/renderComponent.h"

using namespace vg;

RenderComponent::RenderComponent(std::vector<float> vertices, std::vector<GLushort> indices) :Component()
{
	this->vertices = vertices;
	this->indices = indices;
	mTexture = nullptr;
}

void RenderComponent::setTexture(vg::graphics::Texture *texture)
{
	mTexture = texture;
}

vg::graphics::Texture *RenderComponent::getTexture()
{
	return mTexture;
}