
#pragma once

#include "engine/game/component.h"
#include "engine/utility/color.h"

#include "../external/glm/vec2.hpp"

#include <vector>
#include <string>

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

		enum Shape
		{
			Triangle,
			Rectangle
		};
		
		/**
		Default constructor. Shape is a Rectangle without texture.
		*/
		RenderComponent();

		/**
		@param textureName path to texture
		@param shape to be rendered
		*/
		RenderComponent(std::string textureName, Shape shape = Rectangle);

		/**
		@param shape to be rendered
		*/
		RenderComponent(Shape shape);
		
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

		/**
		Color values ranging from 0 - 255
		*/
		void setColor(vg::Color color);
		
	private:
		std::vector<float> getDefaultVertices();
		std::vector<unsigned short> getDefaultIndices();

		Shape mShape;							///< shape to be rendered
		vg::graphics::Texture *mTexture;		///< pointer to texture
		std::vector<float> mVertices;			///< vertex data
		std::vector<unsigned short> mIndices;	///< index data
	};
}