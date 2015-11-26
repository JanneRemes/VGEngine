
#include "engine/game/textComponent.h"
#include "engine/game/game.h"
#include "engine/assets/assetManager.h"
#include "engine/graphics/opengl.h"
#include "engine/graphics/font.h"
#include "engine/utility/string.h"

using namespace vg;
using namespace vg::graphics;
using namespace std;

TextComponent::TextComponent(string fontPath, unsigned int fontSize, string text)
	: Component(), mText(text)
{
	core::AssetManager* assetManager = Game::getInstance()->getAssetManager();
	mFont = assetManager->get<Font>(toStringi(fontSize) + fontPath);
	if (mFont == nullptr)
	{
		assetManager->load<Font>(toStringi(fontSize) + fontPath);
		mFont = assetManager->get<Font>(toStringi(fontSize) + fontPath);
	}

	float defaultVerticesArray[] =
	{
		// Position Vec2
		// Color Vec4
		// TexCoord Vec2

		//left up
		0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f,

		//left down
		0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f,

		//right down
		1.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f,

		//right up
		1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f
	};
	defaultVertices = std::vector<float>(defaultVerticesArray, defaultVerticesArray + sizeof(defaultVerticesArray) / sizeof(defaultVerticesArray[0]));


	unsigned short defaultIndicesArray[] =
	{
		0u, 1u, 2u,
		0u, 2u, 3u
	};
	defaultIndices = std::vector<unsigned short>(defaultIndicesArray, defaultIndicesArray + sizeof(defaultIndicesArray) / sizeof(defaultIndicesArray[0]));

	mVertices = defaultVertices;
	mIndices = defaultIndices;
}

TextComponent::~TextComponent()
{
}

void TextComponent::setText(string text)
{
    mText = text;
}

string TextComponent::getText()
{
	return mText;
}

void TextComponent::setFontSize(unsigned int fontSize)
{
	string oldPath = mFont->getPath();
	string newPath = toStringi(fontSize) + removeDigits(oldPath);

	core::AssetManager* assetManager = Game::getInstance()->getAssetManager();
	mFont = assetManager->get<Font>(newPath);
	if (mFont == nullptr)
	{
		assetManager->load<Font>(newPath);
		mFont = assetManager->get<Font>(newPath);
	}
}

std::vector<float>* TextComponent::getVertices()
{
	return &mVertices;
}

std::vector<unsigned short>* TextComponent::getIndices()
{
	return &mIndices;
}

graphics::Font* TextComponent::getFont()
{
	return mFont;
}

void TextComponent::setColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
{
	for (int i = 2; i < mVertices.size(); i += 8)
	{
		mVertices[i] = red / 255.0f;
		mVertices[i + 1] = green / 255.0f;
		mVertices[i + 2] = blue / 255.0f;
		mVertices[i + 3] = alpha / 255.0f;
	}
}

void TextComponent::setTexCoords(Vec2f leftTop, Vec2f rightBottom)
{
	glm::vec2 tc[4];
	tc[0] = glm::vec2(leftTop.x, leftTop.y);
	tc[1] = glm::vec2(leftTop.x, rightBottom.y);
	tc[2] = glm::vec2(rightBottom.x, rightBottom.y);
	tc[3] = glm::vec2(rightBottom.x, leftTop.y);
	for (int i = 0; i < 4; i++)
	{
		mVertices[i * 8 + 6] = tc[i].x;
		mVertices[i * 8 + 7] = tc[i].y;
	}
}

