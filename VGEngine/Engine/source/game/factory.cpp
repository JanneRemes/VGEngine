#include "engine\game\factory.h"

using namespace vg;
Factory::Factory(AssetManager *assetManager,FileManager *fileManager)
{
	mAssetManager = assetManager;
	mFileManager = fileManager;
}


Factory::~Factory()
{
}
