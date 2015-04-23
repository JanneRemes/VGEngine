#pragma once
#include "engine/game/component.h"
#include <vector>
#include "GLES2/gl2.h"
using namespace std;
namespace vg
{
	/**
	Component for rendering gameObject
	*/
	class RenderComponent :
		public Component
	{
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
	private:
		std::vector<float> vertices; ///< List of vertices
		std::vector<GLuint> indices; ///< List of indices
	};
}