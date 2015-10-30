#ifdef OS_WINDOWS
#include <engine/sound/soundEffect.h>
#include <engine/utility/logger.h>
#include <engine/assets/fileManager.h>
#include <xaudio2.h>
using namespace vg::sound;

SoundEffect::SoundEffect(const Sound& soundFile)
{


}

void SoundEffect::play()
{

}
bool SoundEffect::isFinishedPlaying()
{
	return false;
}

bool SoundEffect::isStartedPlaying()
{
	return false;
}

void SoundEffect::pause()
{
}

void SoundEffect::setLoop(bool b)
{
}

void SoundEffect::setPosition(float pos)
{
}

float SoundEffect::getPosition()
{
	return 0;
}

float SoundEffect::getLength()
{
	return 0;
}

void SoundEffect::stop()
{
}

void SoundEffect::destroy()
{
}

SoundEffect::~SoundEffect()
{
}
#endif