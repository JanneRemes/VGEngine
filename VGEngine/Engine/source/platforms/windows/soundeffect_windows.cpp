
#ifdef OS_WINDOWS
#include "engine/sound/soundEffect.h"
#include "engine/utility/logger.h"
#include "engine/assets/fileManager.h""

#include <irrKlang.h>

using namespace vg::sound;
using namespace irrklang;

ISound *mySound = nullptr;

SoundEffect::SoundEffect(const Sound& soundFile)
{
	Sound doge = soundFile;
	
	mSoundPath = "assets/"+doge.getPath();
	mySound = nullptr;
}

void SoundEffect::play()
{
	ISoundEngine* engine = createIrrKlangDevice();
	char *cstr = new char[mSoundPath.length() + 1];
	strcpy(cstr, mSoundPath.c_str());
	mySound = engine->play2D(cstr,false,false,true);
}
bool SoundEffect::isFinishedPlaying()
{
	return mySound->isFinished();
}

bool SoundEffect::isStartedPlaying()
{
	mySound->setIsPaused();
	return false;
}

void SoundEffect::pause()
{
	mySound->setIsPaused(true);
}

void SoundEffect::setLoop(bool b)
{
	mySound->setIsLooped(b);
}

void SoundEffect::setPosition(float pos)
{
	mySound->setPlayPosition(pos);
}

float SoundEffect::getPosition()
{
	
	return mySound->getPlayPosition();
}

float SoundEffect::getLength()
{
	return mySound->getPlayLength();
}

void SoundEffect::stop()
{
	if (mySound != nullptr)
	mySound->stop();
}

void SoundEffect::destroy()
{
}

SoundEffect::~SoundEffect()
{
	delete mySound;
}
#endif