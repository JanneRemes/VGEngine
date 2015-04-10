#pragma once


#include <GLES2/gl2.h>
#include "engine\assets\fileManager.h"
#include <vector>
#include "engine\graphics\shader.h"
#include "engine\graphics\vertexBuffer.h"
#include "engine\graphics\indexBuffer.h"
namespace vg
{
	/**
	Class used for showing text on screen, utilizes freetype
	*/
	class text
	{
	public:
	
		~text(){};
		text(std::string& fontPath, FileManager *manager);
		void initialize();
		void draw(Shader &slimshady);

		//std::vector<float> getVertexData() { return mVertexData; };
		//std::vector<uint32_t> getIndexData() { return mIndexData; };

	private:
	
		std::vector<float> mVertexData;		///< <description>
		std::vector<uint32_t> mIndexData;	///< <description>

		GLuint mTexture;

		VertexBuffer *mVertexBuffer;
		IndexBuffer *mIndexBuffer;
		
	};
}