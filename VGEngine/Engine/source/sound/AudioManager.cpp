
#include "engine\sound\AudioManager.h"
#include <string>
#include "engine\utility\logger.h"
using namespace vg;

SFXMapping::SFXMapping(size_t id, const Sound& sound)
	: mId(id)
	
{
	mSoundEffect = new SoundEffect(sound);
}

AudioManager::~AudioManager()
{
	//for (auto& mapping : mSoundEffectList)
	//{
	//	mapping.mSoundEffect->Stop();
	//	mapping.mSoundEffect->Destroy();
	//}
}

void AudioManager::Stop(const std::string& name)
{
	const size_t id = mStringHash(name);

	SFXMapping* mapping = FindSFXMap(id);
	if (mapping != nullptr)
	{
		mapping->mSoundEffect->Stop();
	}
}

void AudioManager::Pause(const std::string& name)
{
	const size_t id = mStringHash(name);

	SFXMapping* mapping = FindSFXMap(id);
	if (mapping != nullptr)
	{
		mapping->mSoundEffect->Pause();
	}
}

void AudioManager::pauseAll()
{
    auto i = std::begin(mSoundEffectList);
    while (i != std::end(mSoundEffectList))
    {
        (*i).mSoundEffect->Pause();
        i++;
    }
}

void AudioManager::Play(const std::string& name)
{
	const size_t id = mStringHash(name);

	SFXMapping* mapping = FindSFXMap(id);
	if (mapping != nullptr)
	{
		mapping->mSoundEffect->Play();
	}
}

void AudioManager::playAll()
{
    auto i = std::begin(mSoundEffectList);
    while (i != std::end(mSoundEffectList))
    {
        //if (!(*i).mSoundEffect->IsFinishedPlaying())
        {
            (*i).mSoundEffect->Play();
        }
        i++;
    }
}

void AudioManager::LoopEnabled(const std::string& name, bool b)
{
	const size_t id = mStringHash(name);

			SFXMapping* mapping= FindSFXMap(id);
			if (mapping != nullptr)
			{
				mapping->mSoundEffect->SetLoop(b);
			}
}
void AudioManager::SetPosition(const std::string& name, float pos)
{
	const size_t id = mStringHash(name);

	SFXMapping* mapping = FindSFXMap(id);
	if (mapping != nullptr)
	{
		mapping->mSoundEffect->SetPosition(pos);
	}
}

float AudioManager::GetPosition(const std::string& name)
{
	const size_t id = mStringHash(name);

	SFXMapping* mapping = FindSFXMap(id);
	if (mapping != nullptr)
	{
		return mapping->mSoundEffect->GetPosition();
	}
}
float AudioManager::GetLength(const std::string& name)
{
	const size_t id = mStringHash(name);

	SFXMapping* mapping = FindSFXMap(id);
	if (mapping != nullptr)
	{
		return mapping->mSoundEffect->GetLength();
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
	//mSoundEffectList.emplace_back(mStringHash("Instant"), sound);
    if (mSoundEffectList.size() < mMaxSounds)
    {
        const size_t id = ++mInstantID;
        mSoundEffectList.emplace_back(id, sound);

        SFXMapping* mapping = FindSFXMap(id);
        if (mapping != nullptr)
        {
            mapping->mSoundEffect->Play();
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
			if ((*i).mSoundEffect->IsFinishedPlaying())
			{
				int pos = (*i).mSoundEffect->GetPosition();
				int length = (*i).mSoundEffect->GetLength();

				Log("TrackTag", "track im in the end", "");

				(*i).mSoundEffect->Stop();
				(*i).mSoundEffect->Destroy();
				i = mSoundEffectList.erase(i);
			}
			else
		++i;
	}
}

SFXMapping *AudioManager::FindSFXMap(int id)
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