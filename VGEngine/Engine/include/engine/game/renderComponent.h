#pragma once
#include "engine/game/component.h"
#include <vector>
#include "GLES2/gl2.h"
#include "engine/graphics/texture.h"
using namespace std;
namespace vg
{
	/**
	Component for rendering gameObject
	*/
	class RenderComponent :
		public Component
	{
		friend class Factory;
	public:
		/**
		Constructor
		@param vertices vector of vertices for the draw
		@param indices vector of indices for the draw
		*/
		RenderComponent(std::vector<float> vertices,std::vector<GLuint> indices);
		~RenderComponent() = default;

		/**
		@return Returns the components vertices
		*/
		std::vector<float> *getVertices(){ return &vertices; };

		/**
		@return Returns the components indices
		*/
		std::vector<GLuint> *getIndices(){ return &indices; };

		/**
		@return pointer to current texture
		*/
		vg::graphics::Texture *getTexture();

	private:
		void setTexture(vg::graphics::Texture *texture);

		vg::graphics::Texture *mTexture;
		std::vector<float> vertices;
		std::vector<GLuint> indices;
	};
}