
#ifdef OS_WINDOWS
#include "engine/sound/soundEffect.h"
#include "engine/utility/logger.h"
#include "engine/assets/fileManager.h""

#include <irrKlang.h>

using namespace vg::sound;
using namespace irrklang;


SoundEffect::SoundEffect(const Sound& soundFile)
{
	Sound doge = soundFile;
	
	mSoundPath = "assets/"+doge.getPath();
	data = nullptr;
	player = createIrrKlangDevice();
}

void SoundEffect::play()
{
	
	char *cstr = new char[mSoundPath.length() + 1];
	strcpy(cstr, mSoundPath.c_str());
	ISound *sound = ((ISoundEngine*)player)->play2D(cstr, false, false, true);
	data = static_cast<void *>(sound);
}
bool SoundEffect::isFinishedPlaying()
{
	if (data == nullptr)
		return false;
	return ((ISound *)data)->isFinished();
}

bool SoundEffect::isStartedPlaying()
{
	((ISound *)data)->setIsPaused();
	return false;
}

void SoundEffect::pause()
{
	if (data == nullptr)
		return;
	((ISound *)data)->setIsPaused(true);
}

void SoundEffect::setLoop(bool b)
{
	((ISound *)data)->setIsLooped(b);
}

void SoundEffect::setPosition(float pos)
{
	((ISound *)data)->setPlayPosition(pos);
}

float SoundEffect::getPosition()
{
	
	return ((ISound *)data)->getPlayPosition();
}

float SoundEffect::getLength()
{
	return ((ISound *)data)->getPlayLength();
}

void SoundEffect::stop()
{
	if (((ISound *)data) != nullptr)
		((ISound *)data)->stop();
}

void SoundEffect::destroy()
{
}

SoundEffect::~SoundEffect()
{
	delete ((ISound *)data);
}
#endif