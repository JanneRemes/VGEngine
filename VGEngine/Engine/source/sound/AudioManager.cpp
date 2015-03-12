
#include "engine\sound\AudioManager.h"
#include <string>

using namespace vg;

SFXMapping::SFXMapping(size_t id, const Sound& sound)
	: mId(id)
	, mSoundEffect(sound)
{
}

AudioManager::~AudioManager()
{
	for (auto& mapping : mSoundEffectList)
	{
		mapping.mSoundEffect.Stop();
		mapping.mSoundEffect.Destroy();
	}
}

void AudioManager::Stop(const std::string& name)
{
	const size_t id = mStringHash(name);

	for (auto& mapping : mSoundEffectList)
	{
		if (mapping.mId == id)
		{
			mapping.mSoundEffect.Stop();
			return;
		}
	}
}

void AudioManager::Play(const std::string& name)
{
	const size_t id = mStringHash(name);

	for (auto& mapping : mSoundEffectList)
	{
		if (mapping.mId == id)
		{
			mapping.mSoundEffect.Play();
			return;
		}
	}
}

void AudioManager::LoopEnabled(const std::string& name, bool b)
{
	const size_t id = mStringHash(name);

	for (auto& mapping : mSoundEffectList)
	{
		if (mapping.mId == id)
		{
			mapping.mSoundEffect.SetLoop(b);
			return;
		}
	}
}

void AudioManager::addSound(const std::string& name, const Sound& sound)
{
	mSoundEffectList.emplace_back(mStringHash(name), sound);
}
