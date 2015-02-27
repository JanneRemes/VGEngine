#include "engine\graphics\text.h"
#include <vector>
using namespace vg;

text::text(unsigned char bitmap) : mBitmap(bitmap)
{
	
}

void text::initialize(std::string& fontPath,FileManager *manager)
{
	std::vector<unsigned char> charData;
	manager->readAsset(fontPath, charData);

	const unsigned char* data = (const unsigned char*)&charData[0];

	//stbtt_BakeFontBitmap(data, 0, 32.0, mBitmap, 512, 512, 32, 96, cdata);
}

void text::print()
{

}