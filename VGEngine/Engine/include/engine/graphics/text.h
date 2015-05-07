
#pragma once

#include "engine/assets/fileManager.h"
#include "engine/graphics/shader.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"
#include "engine\utility\Vector2.h"

#include <GLES2/gl2.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace vg
{
	namespace graphics
	{
		/**
		Class used for showing text on screen, utilizes freetype
		*/
		class Text
		{
		public:

			~Text(){};
			Text(std::string& fontPath, FileManager *manager, int fontsize = 12);
			void draw(Shader *shader);
			void setText(std::string text);
			void setFontSize(int size);
			
			/**
			Origin in lower left corner of the text
			*/
			void setPosition(int x, int y);
			vg::Vector2<int> getPosition();

			/**
			Colour values ranging from 0 - 255
			*/
			void setColour(int r, int g, int b);

			//std::vector<float> getVertexData() { return mVertexData; };
			//std::vector<uint32_t> getIndexData() { return mIndexData; };

		private:

			std::vector<float> mVertexData;		///< <description>
			std::vector<uint32_t> mIndexData;	///< <description>

			void createBuffer();

			GLuint mTexture;
			VertexBuffer *mVertexBuffer;
			IndexBuffer *mIndexBuffer;

			std::vector<FT_Byte> mCharData;
			Vector2<int> mPosition;

			std::string mText;

			FT_UInt  mGlyph_index;
			FT_Library mLibrary;
			FT_Face mFace;
			FT_GlyphSlot mGlyph;
			FT_UInt mFontSize;
		};
	}
}