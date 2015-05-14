
#include <engine/sound/AudioManager.h>
#include <engine/utility/logger.h>
#include <string>

using namespace vg::sound;

SFXMapping::SFXMapping(size_t id, const Sound& sound)
	: mId(id)
	
{
	mSoundEffect = new SoundEffect(sound);
}

AudioManager::~AudioManager()
{
	for (auto& mapping : mSoundEffectList)
	{
		mapping.mSoundEffect->stop();
		mapping.mSoundEffect->destroy();
	}
}

void AudioManager::stop(const std::string& name)
{
	const size_t id = mStringHash(name);

	SFXMapping* mapping = findSFXMap(id);
	if (mapping != nullptr)
	{
		mapping->mSoundEffect->stop();
	}
}

void AudioManager::pause(const std::string& name)
{
	const size_t id = mStringHash(name);

	SFXMapping* mapping = findSFXMap(id);
	if (mapping != nullptr)
	{
		mapping->mSoundEffect->pause();
	}
}

void AudioManager::pauseAll()
{
    auto i = std::begin(mSoundEffectList);
    while (i != std::end(mSoundEffectList))
    {
        (*i).mSoundEffect->pause();
        i++;
    }
}

void AudioManager::play(const std::string& name)
{
	const size_t id = mStringHash(name);

	SFXMapping* mapping = findSFXMap(id);
	if (mapping != nullptr)
	{
		mapping->mSoundEffect->play();
	}
}

void AudioManager::playAll()
{
    auto i = std::begin(mSoundEffectList);
    while (i != std::end(mSoundEffectList))
    {
        {
            (*i).mSoundEffect->play();
        }
        i++;
    }
}

void AudioManager::loopEnabled(const std::string& name, bool b)
{
	const size_t id = mStringHash(name);

			SFXMapping* mapping= findSFXMap(id);
			if (mapping != nullptr)
			{
				mapping->mSoundEffect->setLoop(b);
			}
}
void AudioManager::setPosition(const std::string& name, float pos)
{
	const size_t id = mStringHash(name);

	SFXMapping* mapping = findSFXMap(id);
	if (mapping != nullptr)
	{
		mapping->mSoundEffect->setPosition(pos);
	}
}

float AudioManager::getPosition(const std::string& name)
{
	const size_t id = mStringHash(name);

	SFXMapping* mapping = findSFXMap(id);
	if (mapping != nullptr)
	{
		return mapping->mSoundEffect->getPosition();
	}
}
float AudioManager::getLength(const std::string& name)
{
	const size_t id = mStringHash(name);

	SFXMapping* mapping = findSFXMap(id);
	if (mapping != nullptr)
	{
		return mapping->mSoundEffect->getLength();
	}
}
bool AudioManager::addSound(const std::string& name, const Sound& sound)
{
    if (mSoundEffectList.size() < mMaxSounds)
    {
        mSoundEffectList.emplace_back(mStringHash(name), sound);
        return true;
    }
    Log("ERROR", "Max number of sounds playing!", "");
    return false;
}

bool AudioManager::addSound(const Sound& sound)
{
    if (mSoundEffectList.size() < mMaxSounds)
    {
        const size_t id = ++mInstantID;
        mSoundEffectList.emplace_back(id, sound);

        SFXMapping* mapping = findSFXMap(id);
        if (mapping != nullptr)
        {
            mapping->mSoundEffect->play();
        }
        return true;
    }
    Log("ERROR", "Max number of sounds playing!", "");
    return false;
}

void AudioManager::update()
{
	auto i = std::begin(mSoundEffectList);
	while (i != std::end(mSoundEffectList))
	{
			if ((*i).mSoundEffect->isFinishedPlaying())
			{
				(*i).mSoundEffect->stop();
				(*i).mSoundEffect->destroy();
				i = mSoundEffectList.erase(i);
			}
			else
		++i;
	}
}

SFXMapping *AudioManager::findSFXMap(int id)
{
	for (auto& mapping : mSoundEffectList)
	{
		if (mapping.mId == id)
		{
			return &mapping;
		}
	}
	return nullptr;
}