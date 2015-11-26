
#pragma once

#include "engine/game/component.h"
#include "engine/utility/vec2f.h"
#include "engine/game/transformComponent.h"

#include <vector>
#include <string>

namespace vg
{
	//forward declaration
	namespace graphics
	{
		class Font;
	}

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

		/**
		@param texCoords new texture coordinates
		*/
		void setTexCoords(Vec2f leftTop, Vec2f rightBottom);

		/**
		@return current font
		*/
		graphics::Font* getFont();

    private:

        /**
        Default vertices
        */
		std::vector<float> defaultVertices;

        /**
        Default indices
        */
		std::vector<unsigned short> defaultIndices;

		std::vector<float> mVertices;			///< vertices for drawing
		std::vector<unsigned short> mIndices;	///< indices for drawing
        std::string mText;				        ///< <String to render>
		graphics::Font* mFont;					///< current font
    };
}
