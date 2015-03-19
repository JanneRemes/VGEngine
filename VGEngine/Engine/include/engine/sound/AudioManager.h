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

		/**
		Set looping enabled or disabled for track
		*/
		void LoopEnabled(const std::string& name, bool b);

		/**
		Set the playing position in track
		*/
		void SetPosition(const std::string& name, float pos);

		/**
		Get playing position of track in milliseconds
		*/
		float GetPosition(const std::string& name);

		/**
		Get track length in milliseconds
		*/
		float GetLength(const std::string& name);

		SFXMapping *FindSFXMap(int id);
	private:
		std::hash<std::string> mStringHash;
		std::vector<SFXMapping> mSoundEffectList;
	};
}
