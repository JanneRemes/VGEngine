#include "engine/game/renderComponent.h"
using namespace vg;
RenderComponent::RenderComponent(std::vector<float> vertices, std::vector<GLuint> indices) :Component()
{
	this->vertices = vertices;
	this->indices = indices;
}
