#pragma once
#include "engine/game/renderComponent.h"
#include "GLES2/gl2.h"
namespace vg{
	class quadrangleComponent :
		public RenderComponent
	{
	public:
		quadrangleComponent();
		~quadrangleComponent();

	private:
		std::vector<float> getDefaultVertices();
		std::vector<GLuint> getDefaultIndices();
	};
}