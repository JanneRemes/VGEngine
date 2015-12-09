
#pragma once

#include "engine/utility/vec2f.h"

#include <vector>

namespace vg
{
	namespace graphics
	{
		/**
		Contains values needed for rendering a character.
		*/
		class Character
		{
		public:
			Character();
			~Character();

		private:
			std::vector<float> mVertices;	///< vertices for two triangles
			Vec2f mTexCoords;				///< upper left corner in the Font texture
			float mWidth;					///< width in texture coordinates
			float mHeight;					///< height in texture coordinates
		};
	}
}