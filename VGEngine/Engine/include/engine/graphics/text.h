
#pragma once

#include "engine/assets/fileManager.h"
#include "engine/graphics/shader.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"

#include <GLES2/gl2.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace vg
{
	/**
	Class used for showing text on screen, utilizes freetype
	*/
	class Text
	{
	public:

		~Text(){};
		Text(std::string& fontPath, FileManager *manager);
		void initializeBuffer(char *text);
		void draw(Shader *shader);

		//std::vector<float> getVertexData() { return mVertexData; };
		//std::vector<uint32_t> getIndexData() { return mIndexData; };

	private:

		std::vector<float> mVertexData;		///< <description>
		std::vector<uint32_t> mIndexData;	///< <description>

		void createBuffer(float x, float y, float w, float h);

		GLuint mTexture;
		VertexBuffer *mVertexBuffer;
		IndexBuffer *mIndexBuffer;

		std::vector<FT_Byte> mCharData;

		FT_UInt  mGlyph_index;
		FT_Library mLibrary;
		FT_Face mFace;
		FT_GlyphSlot mGlyph;
	};
}