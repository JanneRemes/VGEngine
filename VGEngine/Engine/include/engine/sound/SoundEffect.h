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

	/**
	<class description>
	*/
class SoundEffect
{
public:

	/**
	<description>
	@param soundFile <description>
	*/
	SoundEffect(const Sound& soundFile);
	~SoundEffect();
	
	/**
	<description>
	*/
	void Play();

	/**
	<description>
	*/
	void Stop();

	/**
	<description>
	*/
	void Pause();

	/**
	<description>
	@param b <description>
	*/
	void SetLoop(bool b);

	/**
	<description>
	*/
	void Destroy();

	/**
	<description>
	@param pos <description>
	*/
	void SetPosition(float pos);

	/**
	<description>
	*/
	float GetPosition();

	/**
	<description>
	*/
	float GetLength();
private:

	SLEngineItf Engine;				///< <description>

	SLObjectItf engineObject;		///< <description>
	SLObjectItf PlayerObject;		///< <description>
	SLObjectItf outputObject;		///< <description>

	// Interfaces
	SLPlayItf PlayerPlay;			///< <description>
	SLVolumeItf PlayerVolume;		///< <description>
	SLmillibel maxVolumeLevel;		///< <description>
	SLSeekItf Seek;					///< <description>
	SLPlaybackRateItf RateObject;	///< <description>
};
}
