
#include "engine\graphics\text.h"
#include "engine\utility\logger.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine\graphics\opengl.h"
using namespace vg;


text::text(std::string& fontPath, FileManager *manager)
{

}


void text::initialize()
{
	FT_Library lib;
	FT_Init_FreeType(&lib);
}


//void text::draw(Shader &slimshady)
//{
//	/*slimshady.useProgram();
//
//	gl::activeTexture(ftex);
//	gl::bindTexture(ftex);
//
//	GraphicsDevice::draw(&slimshady, mVertexBuffer, mIndexBuffer);
//	slimshady.unUseProgram();
//
//	gl::activeTexture();
//	gl::bindTexture(0);*/
//}