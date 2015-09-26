
#include "engine/graphics/texture.h"
#include "engine/assets/fileManager.h"
#include "../external/lodepng/lodepng.h"
#include "engine/utility/logger.h"
#include "engine/graphics/opengl.h"
#if defined (OS_ANDROID)
#include <GLES2/gl2.h>
#endif

#include <string>
#include <vector>

using namespace vg::graphics;

Texture::Texture(const std::string& path)
	: Asset(path)
{
}

bool Texture::load(core::FileManager *fileManager)
{
	std::vector<unsigned char> rawBytes;

	if (fileManager->readAsset(mPath, rawBytes) == false)
	{
		Log("vgengine", "Failed to load texture asset '%s'.", mPath.c_str());
		return false;
	}

	std::vector<unsigned char> pixels;
	uint32_t error = lodepng::decode(pixels, mWidth, mHeight, rawBytes);
	if (error != 0)
	{
		Log("vgengine", "LodePNG: '%s'.", lodepng_error_text(error));
		return false;
	}

	// reflects the pixels over x-axis
	int widthInChars = mWidth * 4;
	unsigned char* imagePtr = &pixels[0];
	unsigned char* top = nullptr;
	unsigned char* bottom = nullptr;
	unsigned char temp = 0;

	for (int h = 0; h < mWidth / 2; h++)
	{
		top = imagePtr + h * widthInChars;
		bottom = imagePtr + (mHeight - h - 1) * widthInChars;
		for (int w = 0; w < widthInChars; w++)
		{
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}


	gl::genTextures(&mId);
	gl::activeTexture();
	gl::bindTexture(mId);
	gl::texImage2D(mWidth, mHeight, pixels);
	//gl::texParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
	//gl::texParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	gl::texParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gl::texParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	gl::texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gl::texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//gl::texParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//gl::texParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	gl::bindTexture(0);

	mIsLoaded = true;
	return true;
}

bool Texture::unload()
{
	if (mId != 0)
	{
		glDeleteTextures(1, &mId);
	}

	mIsLoaded = false;
}

void Texture::bind() const
{
	gl::activeTexture();
	gl::bindTexture(mId);
}

void Texture::unbind() const
{
	gl::activeTexture();
	gl::bindTexture(0u);
}

void Texture::setSmoothing(bool enableSmoothing) const
{
	gl::activeTexture();
	gl::bindTexture(mId);
	gl::texParameteri(GL_TEXTURE_MAG_FILTER, enableSmoothing ? GL_LINEAR : GL_NEAREST);
	gl::texParameteri(GL_TEXTURE_MIN_FILTER, enableSmoothing ? GL_LINEAR : GL_NEAREST);
	gl::bindTexture(0);
}

uint32_t Texture::getId() const
{
	return mId;
}

uint32_t Texture::getWidth() const
{
	return mWidth;
}

uint32_t Texture::getHeight() const
{
	return mHeight;
}
