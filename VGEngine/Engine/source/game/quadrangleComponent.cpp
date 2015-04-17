#include "engine\game\quadrangleComponent.h"
using namespace vg;
using namespace std;

quadrangleComponent::quadrangleComponent() :RenderComponent(getDefaultVertices(), getDefaultIndices())
{
}


quadrangleComponent::~quadrangleComponent()
{
}
std::vector<float> quadrangleComponent::getDefaultVertices()
{
	std::vector<float> defaultVertices = std::vector < float >
	{
		// Position Vec2
		// Color Vec4
		// TexCoord Vec2

		    //left up
		   -1.0f, 1.0f,
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
			1.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
	};
	return defaultVertices;
}
std::vector<GLuint> quadrangleComponent::getDefaultIndices()
{
	std::vector<GLuint> defaultIndices = std::vector < GLuint >
	{
		0u, 1u, 2u,
		0u, 2u, 3u
	};
	return defaultIndices;
};


