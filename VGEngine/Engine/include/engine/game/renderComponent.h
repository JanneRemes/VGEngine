#pragma once
#include "engine/game/component.h"
#include <vector>
#include "GLES2/gl2.h"
using namespace std;
namespace vg
{
	class RenderComponent :
		public Component
	{
	public:
		RenderComponent(std::vector<float> vertices,std::vector<GLuint> indices);
		~RenderComponent() = default;
		std::vector<float> *getVertices(){ return &vertices; };
		std::vector<GLuint> *getIndices(){ return &indices; };
	private:
		std::vector<float> vertices;
		std::vector<GLuint> indices;
	};
}