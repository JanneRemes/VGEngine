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
	std::vector<GLfloat> defaultVertices = std::vector<GLfloat>();
	//defaultVertices.push_back();
	return defaultVertices;
}
std::vector<GLuint> TriangleComponent::getDefaultIndices()
{
	std::vector<GLuint> defaultIndices = std::vector<GLuint>();
	return defaultIndices;
}