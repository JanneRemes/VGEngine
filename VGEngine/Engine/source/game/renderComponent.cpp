#include "engine/game/renderComponent.h"
using namespace vg;
RenderComponent::RenderComponent(std::vector<GLfloat> vertices, std::vector<GLuint> indices) :Component()
{
	this->vertices = vertices;
	this->indices = indices;
}