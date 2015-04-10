#include "engine\game\triangleComponent.h"

using namespace vg;
TriangleComponent::TriangleComponent() :RenderComponent(getDefaultVertices(),getDefaultIndices())
{

}


TriangleComponent::~TriangleComponent()
{
}
std::vector<GLfloat> TriangleComponent::getDefaultVertices()
{
	std::vector<GLfloat> defaultVertices();
	defaultVertices.push_back();
	return ;
}
std::vector<GLuint> TriangleComponent::getDefaultIndices()
{
	std::vector<GLuint> defaultIndices();
	return ;
}