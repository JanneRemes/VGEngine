#include "engine/sound/SoundEffect.h"

using namespace vg;
SoundEffect::SoundEffect(const Sound& soundFile)
{
	mIsFinished = false;
	mIsStarted = false;
	// For error checking
	SLresult result;
	
	// Create engine, realize it, get interface
	result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
	result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
	result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &Engine);

	// Get data from SoundEffectData
	int mFd = soundFile.data.fd;
	off_t mStart = soundFile.data.start;
	off_t mLength = soundFile.data.length;

	// Data location
	SLDataLocator_AndroidFD loc_fd = { SL_DATALOCATOR_ANDROIDFD, mFd, mStart, mLength };
	// Data format
	SLDataFormat_MIME format_mime = { SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED };
	// Data source
	SLDataSource audioSource = { &loc_fd, &format_mime };

	// Outputmix
	const SLInterfaceID outputInterfaces[1] = { SL_IID_PLAYBACKRATE };
	const SLboolean outputRequired[1] = {SL_BOOLEAN_FALSE};
	result = (*Engine)->CreateOutputMix(Engine, &outputObject, 1, outputInterfaces, outputRequired);
	result = (*outputObject)->Realize(outputObject, SL_BOOLEAN_FALSE);

	SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, outputObject };
	SLDataSink audioSink = { &loc_outmix, NULL };
	
	// create audio player
	const SLInterfaceID interfaces[3] = { SL_IID_VOLUME, SL_IID_SEEK, SL_IID_PLAYBACKRATE };
	const SLboolean required[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
	result = (*Engine)->CreateAudioPlayer(Engine, &PlayerObject, &audioSource, &audioSink, 3, interfaces, required);

	// Realize player
	result = (*PlayerObject)->Realize(PlayerObject, SL_BOOLEAN_FALSE);
	if (result != SL_RESULT_SUCCESS)
		Log("debug","Player realize failed","");

	// Get play interface
	result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_PLAY, &PlayerPlay);
	if (result != SL_RESULT_SUCCESS)
		Log("debug", "play interface failed","");

	// Get volume interface
	result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_VOLUME, &PlayerVolume);
	if (result != SL_RESULT_SUCCESS)
		Log("debug", "volume interface failed","");

	// get seek interface
	result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_SEEK, &Seek);

	// get playbackrate interface
	result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_PLAYBACKRATE, &RateObject);
	if (result != SL_RESULT_SUCCESS)
		Log("debug", "Playback rate interface failed","");
}

void SoundEffect::Play()
{	
	(*PlayerPlay)->SetPlayState(PlayerPlay, SL_PLAYSTATE_PLAYING);
	mIsStarted = true;
}

bool SoundEffect::IsFinishedPlaying()
{
	SLmillisecond position = 0;
	SLmillisecond length = 0;
	(*PlayerPlay)->GetPosition(PlayerPlay, &position);
	(*PlayerPlay)->GetDuration(PlayerPlay, &length);
	
	(*PlayerPlay)->GetPlayState(PlayerPlay, &mState);
	
	if (mState == SL_PLAYSTATE_PAUSED)
	{
		mIsFinished = true;
		return true;
	}
	else
		mIsFinished = false;
		return false;
}

bool SoundEffect::IsStartedPlaying()
{
	return mIsStarted;
}

void SoundEffect::Pause()
{
	(*PlayerPlay)->SetPlayState(PlayerPlay, SL_PLAYSTATE_PAUSED);
}
void SoundEffect::SetLoop(bool b)
{
	if (true)
	(*Seek)->SetLoop(Seek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
	else
	(*Seek)->SetLoop(Seek, SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN);
}

void SoundEffect::SetPosition(float pos)
{
	(*Seek)->SetPosition(Seek, pos, SL_SEEKMODE_ACCURATE);
}
float SoundEffect::GetPosition()
{
	SLmillisecond position;
	(*PlayerPlay)->GetPosition(PlayerPlay, &position);
	return position;
}
float SoundEffect::GetLength()
{
	SLmillisecond length;
	(*PlayerPlay)->GetDuration(PlayerPlay, &length);
	return length;
}
void SoundEffect::Stop()
{
	(*PlayerPlay)->SetPlayState(PlayerPlay, SL_PLAYSTATE_STOPPED);
}
void SoundEffect::Destroy()
{
		if (PlayerObject != NULL)
		{
			(*PlayerObject)->Destroy(PlayerObject);
			PlayerObject = NULL;
			PlayerPlay = NULL;
			PlayerVolume = NULL;
			maxVolumeLevel = NULL;
			Seek = NULL;
		}
		if (outputObject != NULL)
		{
			(*outputObject)->Destroy(outputObject);
			outputObject = NULL;

		}
		if (engineObject != NULL)
		{
			(*engineObject)->Destroy(engineObject);
			Engine = NULL;
		}
}
SoundEffect::~SoundEffect()
{
}
