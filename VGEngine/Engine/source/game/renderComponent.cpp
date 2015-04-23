#include "engine/game/renderComponent.h"
using namespace vg;
RenderComponent::RenderComponent(std::vector<float> vertices, std::vector<GLuint> indices) :Component()
{
	this->vertices = vertices;
	this->indices = indices;
	mTexture = nullptr;
}
void RenderComponent::setTexture(Texture *texture)
{
	mTexture = texture;
}
Texture *RenderComponent::getTexture()
{
	return mTexture;
}