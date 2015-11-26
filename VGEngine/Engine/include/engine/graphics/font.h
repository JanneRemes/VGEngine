
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
			@param fileManager used for reading assets
			@return result
			*/
			bool load(core::FileManager *fileManager);

			/**
			Deletes the loaded texture
			@return result
			*/
			bool unload();

			/**
			@return fontSize
			*/
			unsigned int getFontSize();
			
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

			/**
			@param character in the font texture
			@return character size
			*/
			Vec2f getSize(char character);

			/**
			@param character in the font texture
			@return character width
			*/
			float getWidth(char character);

			/**
			@param character in the font texture
			@return character height
			*/
			float getHeight(char character);

			/**
			@param character in the font texture
			@return horizontal advance to next character
			*/
			float getAdvance(char character);
			
			/**
			@param character in the font texture
			@return character offset
			*/
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

			float mAdvance[128];		///< horizontal advance for each character 
			float mWidth[128];			///< for each character
			float mHeight[128];			///< for each character
			float mTex_x1[128];			///< for each character
			float mTex_x2[128];			///< for each character
			float mTex_y1[128];			///< for each character
			float mTex_y2[128];			///< for each character	
			float mOffset_x[128];		///< for each character
			float mOffset_y[128];		///< for each character

			unsigned int mTexture;		///< texture id
			unsigned int mFontSize;		///< <Fontsize for text>
		};
	}
}