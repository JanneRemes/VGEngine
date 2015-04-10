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
	std::vector<GLfloat> defaultVertices = std::vector<GLfloat>
	{
		// Position Vec2
		// Color Vec4
		// TexCoord Vec2

		//Triangle up
			0.0f, 1.0f,
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
	};
	return defaultVertices;
}
std::vector<GLuint> TriangleComponent::getDefaultIndices()
{
	std::vector<GLuint> defaultIndices = std::vector<GLuint>
	{
		//up
		0,
		//left
		1,
		//right
		2,
	};
	return defaultIndices;
}