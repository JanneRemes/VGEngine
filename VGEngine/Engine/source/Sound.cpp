#include "engine\Sound.h"
using namespace vg;
Sound::Sound(const std::string& path)
	: Asset(path)
{
	
}

bool Sound::load(FileManager& fileManager)
{
	// Load sound file to SoundEffectData
	fileManager.readAsset(mPath, &data);
}

bool Sound::unload()
{
	return 0;
}

Sound::~Sound()
{
}
