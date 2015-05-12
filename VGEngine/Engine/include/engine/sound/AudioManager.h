#pragma once
#include <vector>
#include "engine\sound\SoundEffect.h"

namespace vg
{
	/**
	Storage for SoundEffects
	*/
	class SFXMapping
	{
	public:
		SFXMapping(size_t id, const Sound& sound);
	
		size_t mId;					///< ID for finding sounds 
		SoundEffect *mSoundEffect;	///< SoundEffect
	};

	/**
	Manager for playing all the sounds
	*/
	class AudioManager
	{
	public:
		AudioManager() { mInstantID = 0; };
		~AudioManager();

		/**
		Add ID and sound to the playlist
		@param name ID for finding this sound
		@param sound Soundfile to add
        @return true if there was room to add sound
		*/
		bool addSound(const std::string& name, const Sound& sound);

		/**
		Add sound without ID, plays it instantly and then deletes
		@param sound Soundfile to add
        @return true if there was room to add sound
		*/
		bool addSound(const Sound& sound);

		/**
		Stop playing the soundfile
		@param name ID for sound
		*/
		void Stop(const std::string& name);

		/**
		Start playing the soundfile
		@param name ID for sound
		*/
		void Play(const std::string& name);
        
        /**
        Plays all the soundfiles
        */
        void playAll();

		/**
		Pause playing the soundfile
		@param name ID for sound
		*/
		void Pause(const std::string& name);

        /**
		Pause all soundfiles currently playing
        */
        void pauseAll();

		/**
		Set looping enabled or disabled for track
		@param name ID for sound
		@param b
		*/
		void LoopEnabled(const std::string& name, bool b);

		/**
		Set the playing position in track
		@param name ID for sound
		@param pos
		*/
		void SetPosition(const std::string& name, float pos);

		/**
		@param name ID for sound
		@return Returns playing position of track in milliseconds
		*/
		float GetPosition(const std::string& name);

		/**
		@param name ID for sound
		@return Returns track length in milliseconds
		*/
		float GetLength(const std::string& name);

		/**
		Checks if soundfile has finished playing and destroys it
		*/
		void update();

		/**
		Find soundfile by ID
		@param id soundfile ID
		*/
		SFXMapping *FindSFXMap(int id);
	private:
		size_t mInstantID;
		std::hash<std::string> mStringHash;			///< ID hash
		std::vector<SFXMapping> mSoundEffectList;	///< Playlist for soundfiles
        const int mMaxSounds = 15;					///< Maximum number of soundfiles to play at same time
	};
}
