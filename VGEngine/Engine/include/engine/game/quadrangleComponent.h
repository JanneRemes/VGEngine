#pragma once
#include "engine/game/renderComponent.h"
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
	};
}