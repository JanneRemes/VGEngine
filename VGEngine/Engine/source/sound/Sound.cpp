#include "engine/sound/Sound.h"
using namespace vg;
Sound::Sound(const std::string& path)
	: Asset(path)
{
	
}

bool Sound::load(FileManager *fileManager)
{
	fileManager->readAsset(mPath, &data);
}

bool Sound::unload()
{
	return 0;
}

Sound::~Sound()
{
}
