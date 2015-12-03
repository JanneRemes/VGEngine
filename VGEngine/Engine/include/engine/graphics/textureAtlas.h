#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include "engine\graphics\texture.h"
#include "engine\assets\asset.h"

namespace vg
{
	namespace graphics
	{
		class TextureAtlas
		{

		public:
	
			TextureAtlas();
			~TextureAtlas();
			bool unload();
			void bind() const;
			void unbind() const;
			void setSmoothing(bool enable) const;
			void pushTexture(vg::graphics::Texture* texture);
			void arrangeTextureAtlas();

		private:

			int getLargest();
			int getWidest();
			int getHighest();

			uint32_t mWidth = 2048;											///< Texture atlas width
			uint32_t mHeight = 2048;										///< Texture atlas height
			uint32_t mAtlasId = 0;											///< Texture atlas id
			std::vector<unsigned char> atlasPixels;							///< Texture atlas pixel data vector
			std::vector<Texture*>textureVector;								///< A vector for the texture pixel data for sorting
			std::vector<uint32_t>atlasIds;
		};
	}
}