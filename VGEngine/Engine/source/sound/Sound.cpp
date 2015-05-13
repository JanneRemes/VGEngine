
#include "engine/sound/Sound.h"

using namespace vg::sound;

Sound::Sound(const std::string& path)
	: Asset(path)
{
	
}

bool Sound::load(vg::core::FileManager *fileManager)
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
