#pragma once
#include <vector>
#include "engine\sound\SoundEffect.h"

namespace vg
{
	class SFXMapping
	{
	public:
		SFXMapping(size_t id, const Sound& sound);
	
		size_t mId;
		SoundEffect *mSoundEffect;
	};

	class AudioManager
	{
	public:
		~AudioManager();

		void addSound(const std::string& name, const Sound& sound);
		void Stop(const std::string& name);
		void Play(const std::string& name);
		void Pause(const std::string& name);
		void SetPitch(const std::string& name, int pitch);
		void SetVolume(const std::string& name, float vol);
		void LoopEnabled(const std::string& name, bool b);
		SFXMapping *FindSFXMap(int id);

	private:
		std::hash<std::string> mStringHash;
		std::vector<SFXMapping> mSoundEffectList;
	};
}
