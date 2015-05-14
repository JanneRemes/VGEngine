
#pragma once

#include <engine/sound/Sound.h>

#include <SLES/OpenSLES_Android.h>
#include <SLES/OpenSLES.h>

#include <string>

namespace vg 
{
	class FileManager;
	class AssetManager;

    namespace sound
    {
        /**
        Plays soundfiles
        */
        class SoundEffect
        {
        public:

            /**
            Create new SoundEffect
            @param soundFile sound to play
            */
            SoundEffect(const Sound& soundFile);
            ~SoundEffect();

            /**
            Play sound
            */
            void play();

            /**
            Stop sound
            */
            void stop();

            /**
            Pause sound
            */
            void pause();

            /**
            Enable or disable sound looping
            @param bool set true to enable looping
            */
            void setLoop(bool b);

            /**
            Destroys sound
            */
            void destroy();

            /**
            Set track position
            @param pos new position in track
            */
            void setPosition(float pos);

            /**
            Get current track position
            @param pos get current track position
            */
            float getPosition();

            /**
            Get current track position
            @param length get total length of the track
            */
            float getLength();

            /**
            Checks if track has finished playing
            @param bool
            */
            bool isFinishedPlaying();

            /**
            Checks if track has started playing
            @param bool
            */
            bool isStartedPlaying();

        private:
            // Engine
            SLEngineItf Engine;				///< <description>

            // Objects
            SLObjectItf engineObject;		///< <description>
            SLObjectItf PlayerObject;		///< <description>
            SLObjectItf outputObject;		///< <description>

            // Interfaces
            SLPlayItf PlayerPlay;			///< <description>
            SLVolumeItf PlayerVolume;		///< <description>
            SLmillibel maxVolumeLevel;		///< <description>
            SLSeekItf Seek;					///< <description>
            SLPlaybackRateItf RateObject;	///< <description>

            bool mIsFinished;				///< <description>
            bool mIsStarted;				///< <description>

            SLuint32 mState;				///< Playing state of the sound
        };
    }
}
