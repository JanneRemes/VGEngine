
#pragma once

#include "engine/assets/asset.h"
#include "engine/utility/vec2f.h"

#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace vg
{
	namespace graphics
	{
		class Font : public core::Asset
		{
		public:

			Font(const std::string& path);

			~Font();

			/**
			<description>
			@param fileManager <description>
			@return <description>
			*/
			bool load(core::FileManager *fileManager);

			/**
			Deletes the loaded texture
			@return <description>
			*/
			bool unload();

			/**
			@param character in the font texture
			@return upper left corner texture coordinates
			*/
			Vec2f getTexCoord1(char character);

			/**
			@param character in the font texture
			@return lower right corner texture coordinates
			*/
			Vec2f getTexCoord2(char character);

			Vec2f getSize(char character);
			float getWidth(char character);
			float getHeight(char character);
			float getAdvance(char character);
			Vec2f getOffset(char character);

			/**
			Binds the font texture
			*/
			void bind();

			/**
			Unbinds the font texture
			*/
			void unbind();

		private:
			static inline int nextp2(int x);

			unsigned int mTexture;
			float advance[128];
			float width[128];
			float height[128];
			float tex_x1[128];
			float tex_x2[128];
			float tex_y1[128];
			float tex_y2[128];
			float offset_x[128];
			float offset_y[128];

			std::vector<FT_Byte> mCharData;	        ///< <Vector where fontfile is saved>
			FT_GlyphSlot mGlyph;			        ///< <Slot where each glyph is saved>
			FT_UInt mFontSize;				        ///< <Fontsize for text>
		};
	}
}