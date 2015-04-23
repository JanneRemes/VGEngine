#pragma once
#include "engine/game/renderComponent.h"
#include "GLES2/gl2.h"
namespace vg{
	class QuadrangleComponent :
		public RenderComponent
	{
	public:
		QuadrangleComponent();
		~QuadrangleComponent();

	private:
		std::vector<float> getDefaultVertices();
		std::vector<GLuint> getDefaultIndices();
	};
}