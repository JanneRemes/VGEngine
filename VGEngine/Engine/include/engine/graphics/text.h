#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GLES2/gl2.h>
#include "engine\assets\fileManager.h"
#include <vector>
#include "engine\graphics\shader.h"
#include "engine\graphics\vertexBuffer.h"
#include "engine\graphics\indexBuffer.h"
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
		void initialize();

		//void draw(Shader &slimshady);


		///**
		//<description>
		//@return vector<float>
		//*/
		//std::vector<float> getVertexData() { return mVertexData; };

		///**
		//<description>
		//@return vector<uint32_t>
		//*/
		//std::vector<uint32_t> getIndexData() { return mIndexData; };

	private:
		/*const unsigned char *mBuffer;	///< <description>
		unsigned char mBitmap[800*600]; ///< <description>
		const char *mFontPath;			///< <description>
		std::string mOutData;			///< <description>
		GLuint ftex;					///< <description>
		stbtt_bakedchar mData[96];		///< <description>
		void convertTriangles();		///< <description>
		
		std::vector<float> mVertexData;		///< <description>
		std::vector<uint32_t> mIndexData;	///< <description>

		VertexBuffer *mVertexBuffer;
		IndexBuffer *mIndexBuffer;*/
		
	};
}