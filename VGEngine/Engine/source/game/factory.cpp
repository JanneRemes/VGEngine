
#include "engine\game\factory.h"

using namespace vg;
using namespace std;

Factory::Factory(core::AssetManager *assetManager, core::FileManager *fileManager)
{
	mAssetManager = assetManager;
	mFileManager = fileManager;
}


Factory::~Factory()
{
}

TextComponent* Factory::create(string fontPath, uint fontSize)
{
    return new TextComponent(fontPath, mFileManager, fontSize);
}
