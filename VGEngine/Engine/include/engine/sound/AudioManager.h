#pragma once
#include <vector>
#include "engine\sound\SoundEffect.h"

namespace vg
{
	/**
	<class description>
	*/
	class SFXMapping
	{
	public:
		/**
		<description>
		@param id <description>
		@param sound <description>
		*/
		SFXMapping(size_t id, const Sound& sound);
	
		size_t mId;					///< <description>
		SoundEffect *mSoundEffect;	///< <description>
	};

	/**
	<class description>
	*/
	class AudioManager
	{
	public:
		AudioManager() { mInstantID = 0; };
		~AudioManager();

		/**
		<description>
		@param name <description>
		@param sound <description>
		*/
		void addSound(const std::string& name, const Sound& sound);

		/**
		<Add sound without ID, plays it instantly and then deletes>
		@param sound <description>
		*/
		void addSound(const Sound& sound);

		/**
		<description>
		@param name <description>
		*/
		void Stop(const std::string& name);

		/**
		<description>
		@param name <description>
		*/
		void Play(const std::string& name);

		/**
		<description>
		@param name <description>
		*/
		void Pause(const std::string& name);

		/**
		Set looping enabled or disabled for track
		@param name <description>
		@param b <description>
		*/
		void LoopEnabled(const std::string& name, bool b);

		/**
		Set the playing position in track
		@param name <description>
		@param pos <description>
		*/
		void SetPosition(const std::string& name, float pos);

		/**
		@return Returns playing position of track in milliseconds
		*/
		float GetPosition(const std::string& name);

		/**
		@return Returns track length in milliseconds
		*/
		float GetLength(const std::string& name);

		void update();

		/**
		<description>
		@param id <description>
		*/
		SFXMapping *FindSFXMap(int id);
	private:
		size_t mInstantID;
		std::hash<std::string> mStringHash;			///< <description>
		std::vector<SFXMapping> mSoundEffectList;	///< <description>
	};
}
