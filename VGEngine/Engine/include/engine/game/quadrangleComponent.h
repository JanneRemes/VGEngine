#pragma once
#include "engine/game/renderComponent.h"
#include "../external/glm/vec2.hpp"
namespace vg{
	class QuadrangleComponent :
		public RenderComponent
	{
	public:
		QuadrangleComponent();
		~QuadrangleComponent();

	private:
		std::vector<float> getDefaultVertices();
		std::vector<unsigned short> getDefaultIndices();
		void setTexCoords(glm::vec2 texCoords[4]);
	};
}