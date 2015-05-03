
#pragma once

#include <map>
#include <vector>
#include <stdint.h>
#include "engine/graphics/vertexBuffer.h"

namespace vg
{
	namespace graphics
	{
		class Texture;
		class Drawable;
		class Shader;

		class SpriteBatch
		{
		public:
			void append(const Drawable& drawable, uint32_t layer = 0);
			void draw(Shader& shader);
		private:
			std::map<uint32_t, std::map<const Texture*, std::vector<float>>> mLayers;
			VertexBuffer mVertexButter;
		};
	}
}
