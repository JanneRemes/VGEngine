
#include "engine/sound/sound.h"
#include "engine/assets/fileManager.h"

using namespace vg::sound;

Sound::Sound(const std::string& path)
	: Asset(path)
{
	
}

bool Sound::load(vg::core::FileManager *fileManager)
{
	fileManager->readAsset(mPath, &data);
	return true;
}

bool Sound::unload()
{
	return 0;
}

Sound::~Sound()
{
}
