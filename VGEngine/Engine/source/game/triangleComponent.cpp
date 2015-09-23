#include "engine\game\triangleComponent.h"

using namespace vg;
using namespace std;
TriangleComponent::TriangleComponent() :RenderComponent(getDefaultVertices(),getDefaultIndices())
{

}


TriangleComponent::~TriangleComponent()
{
}
std::vector<float> TriangleComponent::getDefaultVertices()
{
	std::vector<float> defaultVertices = std::vector<float>
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
std::vector<GLushort> TriangleComponent::getDefaultIndices()
{
	std::vector<GLushort> defaultIndices = std::vector<GLushort>
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
