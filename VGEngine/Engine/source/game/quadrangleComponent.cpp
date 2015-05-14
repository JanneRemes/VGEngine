
#include <engine/game/quadrangleComponent.h>

using namespace vg;
using namespace std;

QuadrangleComponent::QuadrangleComponent() :RenderComponent(getDefaultVertices(), getDefaultIndices())
{
}


QuadrangleComponent::~QuadrangleComponent()
{
}

std::vector<float> QuadrangleComponent::getDefaultVertices()
{
	std::vector<float> defaultVertices = std::vector < float >
    {
        // Position Vec2
        // Color Vec4
        // TexCoord Vec2

        //left up
        0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f,

        //left down
        0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f,

        //right down
        1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f,

        //right up
        1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f
    };
	return defaultVertices;
}

std::vector<GLuint> QuadrangleComponent::getDefaultIndices()
{
	std::vector<GLuint> defaultIndices = std::vector < GLuint >
	{
		0u, 1u, 2u,
		0u, 2u, 3u
	};
	return defaultIndices;
};
