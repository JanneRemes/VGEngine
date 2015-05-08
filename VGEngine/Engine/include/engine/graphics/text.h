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
			/**
			Initializes freetype library and creates new font face
			@param Path to where font file is located
			@param Filemanager to load in the fontfile
			@param Fontsize, optional and 12 if not set
			*/
			Text(std::string& fontPath, FileManager *manager, int fontsize = 12);
            ~Text();
            
			/**
			Draws the previously set string 
			Text position (0, 200) by default
			@param Shader to use for drawing
			*/
            void draw(Shader *shader);

			/**
			Changes the string to render
			@param String to render
			*/
			void setText(std::string text);

			/**
			Changes font size
			@param New font size int
			*/
			void setFontSize(int size);
			
			/**
			New position for text
			Origin in lower left corner of the text
			@param int x
			@param int y
			*/
			void setPosition(int x, int y);
			vg::Vector2<int> getPosition();

			/**
			Colour values ranging from 0 - 255
			*/
			void setColour(int r, int g, int b);

		private:

			std::vector<float> mVertexData;		///< <Vertex data for buffer>
			std::vector<uint32_t> mIndexData;	///< <Index data for buffer>

			void createBuffer();				///< <Creates vertex and index data>

			GLuint mTexture;					///< <Font texture ID>
			VertexBuffer *mVertexBuffer;		///< <Vertex buffer for drawing>
			IndexBuffer *mIndexBuffer;			///< <Index buffer for drawing>

			std::vector<FT_Byte> mCharData;		///< <Vector where fontfile is saved>
			Vector2<int> mPosition;				///< <Text position>

			std::string mText;					///< <String to render>

			FT_UInt mGlyph_index;				///< <Glyph index for each char>
			FT_Library mLibrary;				///< <Freetype library>
			FT_Face mFace;						///< <Face that includes the loaded font>
			FT_GlyphSlot mGlyph;				///< <Slot where each glyph is saved>
			FT_UInt mFontSize;					///< <Fontsize for text>
		};
	}
}