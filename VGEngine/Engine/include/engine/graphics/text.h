#pragma once

#include "../../external/stb_truetype.h"
#include <GLES2/gl2.h>
#include "engine\assets\fileManager.h"

namespace vg
{
	class text
	{
	public:
		~text(){};

		text(std::string& fontPath, FileManager *manager);
		void print(float x, float y, char* text);

	private:
		const unsigned char *mBuffer;
		unsigned char mBitmap[512*512];
		const char *mFontPath;
		std::string mOutData;
		GLuint ftex;
		stbtt_bakedchar mData[96];
		void convertTriangles();
		
	};
}