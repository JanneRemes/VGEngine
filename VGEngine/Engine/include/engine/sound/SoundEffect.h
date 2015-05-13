
#pragma once

#include "engine/assets/fileManager.h"
#include "engine/sound/Sound.h"
#include "engine/android_native_app_glue.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <SLES/OpenSLES_Android.h>
#include <SLES/OpenSLES.h>
#include "engine/utility/logger.h"

namespace vg 
{
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
            void Play();

            /**
            Stop sound
            */
            void Stop();

            /**
            Pause sound
            */
            void Pause();

            /**
            Enable or disable sound looping
            @param bool set true to enable looping
            */
            void SetLoop(bool b);

            /**
            Destroys sound
            */
            void Destroy();

            /**
            Set track position
            @param pos new position in track
            */
            void SetPosition(float pos);

            /**
            Get current track position
            @param pos get current track position
            */
            float GetPosition();

            /**
            Get current track position
            @param length get total length of the track
            */
            float GetLength();

            /**
            Checks if track has finished playing
            @param bool
            */
            bool IsFinishedPlaying();

            /**
            Checks if track has started playing
            @param bool
            */
            bool IsStartedPlaying();
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
