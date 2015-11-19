
#pragma once

#include "engine/game/component.h"
#include "engine/utility/vec2f.h"
#include "engine/assets/fileManager.h"
#include "engine/graphics/shader.h"
#include "engine/game/transformComponent.h"

#include <vector>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace vg
{
	/**
	Class used for showing text on screen, utilizes freetype
	*/
    class TextComponent : public Component
    {
    public:
		/**
		Initializes freetype library and creates new font face
		@param fontPath to where font file is located
		@param fontSize, optional and 12 if not set
		@param text to be displayed
		*/
		TextComponent(std::string fontPath, unsigned int fontSize = 12, std::string text = "");
        
		/**
		Deletes vertex and indexBuffers
		*/
		~TextComponent();
        
		//void draw(graphics::Shader* shader, TransformComponent* transform);

		/**
		Changes the string to render
		@param String to render
		*/
        void setText(std::string text);

		/**
		@return current text value 
		*/
		std::string getText();

		/**
		Changes font size
		@param New font size int
		*/
        void setFontSize(unsigned int fontSize);

		/**
		@return font size
		*/
		unsigned int getFontSize();

		/**
		Binds texture id
		*/
		void bindTexture();

		/**
		Unbinds texture id
		*/
		void unBindTexture();

		/**
		@return current glyph generated by FreeType
		*/
		FT_GlyphSlot* getGlyph();

		/**
		@ return face generated by FreeType
		*/
		FT_Face* getFace();

		/**
		@return current vertices
		*/
		std::vector<float>* getVertices();

		/**
		@return current indices
		*/
		std::vector<unsigned short>* getIndices();

		/**
		Color values ranging from 0 - 255
		*/
		void setColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha = 255);

    private:

		/**
		Generate face from font using FreeType
		*/
		void initializeFace();

        /**
        Default vertices
        */
		std::vector<float> defaultVertices;

        /**
        Default indices
        */
		std::vector<unsigned short> defaultIndices;

        unsigned int mTexture;				    ///< <Font texture ID>
		std::vector<float> mVertices;			///< vertices for drawing
		std::vector<unsigned short> mIndices;	///< indices for drawing

        std::vector<FT_Byte> mCharData;	        ///< <Vector where fontfile is saved>
        std::string mText;				        ///< <String to render>
        FT_Face mFace;					        ///< <Face that includes the loaded font>
        FT_GlyphSlot mGlyph;			        ///< <Slot where each glyph is saved>
        FT_UInt mFontSize;				        ///< <Fontsize for text>
    };
}
