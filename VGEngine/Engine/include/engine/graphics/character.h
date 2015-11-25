
#pragma once

#include "engine/utility/vec2f.h"

#include <vector>

namespace vg
{
	namespace graphics
	{
		class Character
		{
		public:
			Character();
			~Character();

		private:
			std::vector<float> mVertices;
			Vec2f mTexCoords;
			float mWidth;
			float mHeight;
		};
	}
}