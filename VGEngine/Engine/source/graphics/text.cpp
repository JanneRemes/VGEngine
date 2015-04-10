#include <ft2build.h>
#include FT_FREETYPE_H

#include "../external/lodepng/lodepng.h"
#include "engine\graphics\text.h"
#include "engine\utility\logger.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine\graphics\opengl.h"
using namespace vg;


text::text(std::string& fontPath, FileManager *manager)
{
	//std::vector<FT_Byte> charData;

	std::vector<unsigned char> charData;
	manager->readAsset(fontPath, charData);

	//FT_Library library;
	//FT_Face face;

	//FT_Init_FreeType(&library);
	//FT_New_Memory_Face(library, &charData[0], charData.size(), 0, &face);

	//								   // TODOOO
	//FT_Set_Char_Size(face, 0, 16 * 64, 1080, 720);
	//FT_Set_Pixel_Sizes(face, 0, 48);
	//
	//FT_ULong charcode;
	//FT_UInt glyph_index = FT_Get_Char_Index(face, charcode);

	//FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);

	//FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

	uint mWidth;
	uint mHeight;
	std::vector<unsigned char> rawBytes;

	uint32_t error = lodepng::decode(charData, mWidth, mHeight, rawBytes);


	//glGenTextures(1, &mTexture);
	//gl::activeTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, mTexture);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, &charData);

	//gl::bindTexture(0);

	gl::genTextures(&mTexture);
	gl::activeTexture();
	gl::bindTexture(mTexture);
	gl::texImage2D(mWidth, mHeight, charData);
	gl::texParameteriMag(GL_NEAREST);
	gl::texParameteriMin(GL_NEAREST);
	gl::bindTexture(0);


	//Log("text", "Bitmap width: %i", face->glyph->bitmap.width, "");
	//Log("text", "Bitmap height: %i", face->glyph->bitmap.rows, "");
	//Log("text", "Bitmap buffer: %p", face->glyph->bitmap.buffer, "");


	//vertex x0 y0
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);

	//vertex x1 y0
	mVertexData.push_back(0.0);
	mVertexData.push_back(-1.0);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(0.0);
	mVertexData.push_back(-1.0);

	//vertex x1 y1
	mVertexData.push_back(1.0);
	mVertexData.push_back(-1.0);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(1.0);
	mVertexData.push_back(-1.0);

	//vertex x0 y1
	mVertexData.push_back(1.0);
	mVertexData.push_back(0.0);

	// Colours and alpha
	mVertexData.push_back(0.0);
	mVertexData.push_back(0.0);
	mVertexData.push_back(1.0);
	mVertexData.push_back(1.0);

	//UV
	mVertexData.push_back(1.0);
	mVertexData.push_back(0.0);


	// Index data
	mIndexData.push_back(0);
	mIndexData.push_back(1);
	mIndexData.push_back(2);

	mIndexData.push_back(0);
	mIndexData.push_back(2);
	mIndexData.push_back(3);

	mVertexBuffer = new VertexBuffer(mVertexData);
	mIndexBuffer = new IndexBuffer(mIndexData);

}


void text::initialize()
{
	

}


void text::draw(Shader &slimshady)
{
	slimshady.useProgram();

	gl::activeTexture(mTexture);
	gl::bindTexture(mTexture);

	GraphicsDevice::draw(&slimshady, mVertexBuffer, mIndexBuffer);

	gl::activeTexture();
	gl::bindTexture(0);

	slimshady.unUseProgram();
}