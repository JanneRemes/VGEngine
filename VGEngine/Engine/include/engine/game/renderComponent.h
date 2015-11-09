
#pragma once

#include "engine/game/component.h"

#include "../external/glm/vec2.hpp"

#include <vector>

namespace vg
{
	//forward declaration
	namespace graphics
	{
		class Texture;
	}

	/**
	Component for rendering gameObject
	*/
	class RenderComponent : public Component
	{
	public:
		/**
		Constructor
		@param vertices vector of vertices for the draw
		@param indices vector of indices for the draw
		*/
		RenderComponent(std::vector<float> vertices, std::vector<unsigned short> indices);
		~RenderComponent() = default;

		/**
		@return Returns the components vertices
		*/
		std::vector<float> *getVertices();

		/**
		@return Returns the components indices
		*/
		std::vector<unsigned short> *getIndices();

		/**
		@return pointer to current texture
		*/
		vg::graphics::Texture *getTexture();

		/**
		@param texCoords new texture coordinates
		*/
		void setTexCoords(glm::vec2 texCoords[4]);
		

	protected:
		vg::graphics::Texture *mTexture;
		std::vector<float> mVertices;
		std::vector<unsigned short> mIndices;
	};
}