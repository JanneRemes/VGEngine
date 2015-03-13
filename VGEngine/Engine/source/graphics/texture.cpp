
#include "engine/graphics/texture.h"
#include "engine/assets/fileManager.h"
#include "../../external/lodepng/lodepng.h"
//#include "engine/logger.h"
#include <string>
#include <vector>
#include "engine/android_native_app_glue.h"
using namespace vg;

Texture::Texture(const std::string& path)
	: Asset(path)
{
}

bool Texture::load(FileManager& fileManager)
{
	std::vector<unsigned char> rawBytes;

	if (fileManager.readAsset(mPath, rawBytes) == false)
	{
		// Log("ERROR", "Failed to load texture asset '%s'.", mPath.c_str());
		return false;
	}

	std::vector<unsigned char> pixels;
	uint32_t error = lodepng::decode(pixels, mWidth, mHeight, rawBytes);

	if (error != 0)
	{
		// Log("ERROR", "LodePNG: '%s'.", lodepng_error_text(error));
		return false;
	}

	glGenTextures(1, &mId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels.at(0));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

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
	//gl::ActiveTexture(gl::TEXTURE0);
	//gl::BindTexture(gl::TEXTURE_2D, m_Id);
}

void Texture::unbind() const
{
	//gl::ActiveTexture(gl::TEXTURE0);
	//gl::BindTexture(gl::TEXTURE_2D, 0);
}

void Texture::setSmoothing(bool enableSmoothing) const
{
	//gl::ActiveTexture(gl::TEXTURE0);
	//gl::BindTexture(gl::TEXTURE_2D, m_Id);
	//gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, b ? gl::LINEAR : gl::NEAREST);
	//gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, b ? gl::LINEAR : gl::NEAREST);
	//gl::BindTexture(gl::TEXTURE_2D, 0);
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
