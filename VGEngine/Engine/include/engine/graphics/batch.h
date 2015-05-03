
#pragma once

#include "engine/graphics/texture.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/game/renderComponent.h"
#include "engine/graphics/shader.h"

#include <vector>

namespace vg
{
	namespace graphics
	{
		/// @todo continue with this later
		/**
			A group of sprites that can be drawn in a single draw call.
			*/
		class Batch
		{
		public:
			Batch(Texture* texture);
			~Batch();
			void add(RenderComponent* drwawable);
			void draw(Shader& shader);

		private:
			Texture* mTexture;                          ///<description>
			VertexBuffer mVertexBuffer;                 ///<description>
			IndexBuffer mIndexBuffer;                   ///<description>
			bool mBuffersOutOfDate;                     ///<description>
			std::vector<RenderComponent*> mDrawables;   ///<description>

		};
	}
}