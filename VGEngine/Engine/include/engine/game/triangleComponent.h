#pragma once
#include "engine/game/renderComponent.h"
namespace vg{

	/**
	Component for drawing triangle shapes
	*/
	class TriangleComponent :
		public RenderComponent
	{
	public:

		/**
		Constructor that also sets default vertices and indices for a triangle shape by using renderComponent
		*/
		TriangleComponent();
		~TriangleComponent();
		
	private:

		/**
		@return Returns the default vertices that are needed for a triangle
		*/
		std::vector<float> getDefaultVertices();

		/**
		@return Returns the default indices that are needed for a triangle
		*/
		std::vector<unsigned short> getDefaultIndices();
	};

}