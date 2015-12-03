#include <algorithm>
#include "engine\graphics\textureAtlas.h"
#include "engine\assets\asset.h"
#include "engine/assets/fileManager.h"
#include "../external/lodepng/lodepng.h"
#include "engine/utility/logger.h"
#include "engine/graphics/opengl.h"

using namespace vg::graphics;
using namespace vg::graphics::gl;
using namespace vg::core;


TextureAtlas::TextureAtlas()
{
}
bool TextureAtlas::unload()
{
	if (mAtlasId != 0)
	{
		deleteTextures(&mAtlasId);
	}

	return true;
}

void TextureAtlas::bind() const
{
	gl::activeTexture();
	gl::bindTexture(mAtlasId);
}

void TextureAtlas::unbind() const
{
	gl::activeTexture();
	gl::bindTexture(0u);
}

void TextureAtlas::setSmoothing(bool enableSmoothing) const
{
	gl::activeTexture();
	gl::bindTexture(mAtlasId);
	gl::texParameteri(getGL_TEXTURE_MAG_FILTER(), enableSmoothing ? getGL_LINEAR() : getGL_NEAREST());
	gl::texParameteri(getGL_TEXTURE_MIN_FILTER(), enableSmoothing ? getGL_LINEAR() : getGL_NEAREST());
	gl::bindTexture(0);
}

void TextureAtlas::pushTexture(vg::graphics::Texture* texture)
{
	textureVector.push_back(texture);
}

int TextureAtlas::getLargest()
{
	int largest;

	return largest;
}

int TextureAtlas::getWidest()
{
	int widest;

	return widest;
}

int TextureAtlas::getHighest()
{
	int highest;

	return highest;
}

void TextureAtlas::arrangeTextureAtlas()
{
	enum TexturePlacement
	{
		TOPDOWN,
		LEFTRIGHT,
		FULL
	};

	TexturePlacement order = LEFTRIGHT;
	atlasIds.push_back(mAtlasId);

	//indices to help navigating through the atlas' axis
	uint32_t atlasXIndex = 0;	
	uint32_t atlasYIndex = 0;

	//indices to help navigating through the textures own space on its atlas
	uint32_t heightIndex = 0;
	uint32_t widthIndex = 0;

	//indices to mark the corner of 
	uint32_t cornerXIndex = 0;
	uint32_t cornerYIndex = 0;

	std::vector<unsigned char>textureData;

	for (unsigned int i = 0; i < textureVector.size(); i++)
	{
		textureData = textureVector[i]->getDataVector();

		for (unsigned int j = 0; j < textureData.size(); i++)
		{
			atlasPixels[widthIndex + mHeight * heightIndex] = textureData[j];
			widthIndex++;

			if (widthIndex > textureVector[i]->getWidth())
			{
				widthIndex = atlasXIndex;
				heightIndex++;
			}
		}

		switch (order)
		{
		case (LEFTRIGHT) :
			atlasXIndex = atlasXIndex + textureVector[i]->getWidth() + 1;
			widthIndex = atlasXIndex;
			heightIndex = atlasYIndex;
			break;

		case(TOPDOWN) :
			atlasYIndex = atlasYIndex + textureVector[i]->getHeight() + 1;
			widthIndex = atlasXIndex;
			heightIndex = atlasYIndex;
			break;

		case(FULL) :

			gl::genTextures(&atlasIds.back());
			gl::activeTexture();
			gl::bindTexture(atlasIds.back());
			gl::texImage2DRGBA(mWidth, mHeight, atlasPixels);
			gl::texParameteri(getGL_TEXTURE_WRAP_S(), getGL_CLAMP_TO_EDGE());
			gl::texParameteri(getGL_TEXTURE_WRAP_T(), getGL_CLAMP_TO_EDGE());
			gl::texParameteri(getGL_TEXTURE_MAG_FILTER(), getGL_LINEAR());
			gl::texParameteri(getGL_TEXTURE_MIN_FILTER(), getGL_LINEAR());

			gl::bindTexture(0);

			break;
		}
		
	}
	
	textureVector.clear();
}



