#pragma once
#include "engine\assets\fileManager.h"
#include "engine/sound/Sound.h"
#include "engine/android_native_app_glue.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <SLES\OpenSLES_Android.h>
#include <SLES\OpenSLES.h>

#include <android/log.h>

#define LOGA(...) ((void)__android_log_print(ANDROID_LOG_INFO, "SoundEffect", __VA_ARGS__))
namespace vg 
{

class SoundEffect
{
public:
	SoundEffect(Sound soundFile);
	~SoundEffect();
	
	void Play();
	void Stop();
	void Pause();

	void AddToQueue(android_app* app);
	void setVolume(float volume);
	
private:
	// Interfaces
	SLPlayItf PlayerPlay;
	SLVolumeItf PlayerVolume;
	SLmillibel maxVolumeLevel;
	SLSeekItf Seek;

	// Buffer
	SLAndroidSimpleBufferQueueItf BufferQueue;
	short *nextBuffer;
	unsigned nextSize;

};

}
