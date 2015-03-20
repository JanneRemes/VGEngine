#pragma once

#include "../external/stb_truetype.h"
#include <GLES2/gl2.h>
#include "engine\assets\fileManager.h"

namespace vg
{
	/**
	Class used for showing text on screen, utilizes STB_TRUETYPE
	*/
	class text
	{
	public:
		/**
		<description>
		*/
		~text(){};

		/**
		<description>
		@param fontPath
		@param manager
		*/
		text(std::string& fontPath, FileManager *manager);

		/**
		<description>
		@param x
		@param y
		@param text
		*/
		void print(float x, float y, char* text);

	private:
		const unsigned char *mBuffer;	///< <description>
		unsigned char mBitmap[512*512]; ///< <description>
		const char *mFontPath;			///< <description>
		std::string mOutData;			///< <description>
		GLuint ftex;					///< <description>
		stbtt_bakedchar mData[96];		///< <description>
		void convertTriangles();		///< <description>
		
	};
}