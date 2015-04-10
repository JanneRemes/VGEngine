#pragma once
#include "engine/game/renderComponent.h"
#include "GLES2/gl2.h"
namespace vg{
	class TriangleComponent :
		public RenderComponent
	{
	public:
		TriangleComponent();
		~TriangleComponent();
	private:
		std::vector<GLfloat> getDefaultVertices();
		std::vector<GLuint> getDefaultIndices();
	};

}