
#pragma once

#include "engine/game/renderComponent.h"

#include <string>

namespace vg
{
	class QuadrangleComponent : public RenderComponent
	{
	public:
		/**
		Default rectangle render component without texture
		*/
		QuadrangleComponent();

		/**
		Rectangle render component with texture
		@param textureName texture file path
		*/
		QuadrangleComponent(std::string textureName);

		~QuadrangleComponent();

		/**
		Color values ranging from 0 - 255
		*/
		void setColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha = 255);

	private:
		std::vector<float> getDefaultVertices();
		std::vector<unsigned short> getDefaultIndices();
	};
}