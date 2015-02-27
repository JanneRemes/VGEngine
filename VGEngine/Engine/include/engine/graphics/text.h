#pragma once
#define STB_TRUETYPE_IMPLEMENTATION
#include "engine\graphics\stb_truetype.h"
#include <GLES2/gl2.h>
#include "engine\assets\fileManager.h"

namespace vg
{
	class text
	{
	public:
		text(unsigned char bitmap);
		~text(){};

		void initialize(std::string& fontPath,FileManager *manager);
		void print();

	private:
		const unsigned char *mBuffer;
		unsigned char mBitmap;
		const char *mFontPath;
		const unsigned char *mData;
		std::string mOutData;
		GLuint ftex;
		//stbtt_bakedchar mData[96];
		
	};
}