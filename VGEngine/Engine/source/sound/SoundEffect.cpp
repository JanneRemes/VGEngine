#include "engine/sound/SoundEffect.h"

using namespace vg;
SoundEffect::SoundEffect(const Sound& soundFile)
{	
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
	LOGA("Sound data: %i %i %i", mStart, mLength, mFd);

	// Data location
	SLDataLocator_AndroidFD loc_fd = { SL_DATALOCATOR_ANDROIDFD, mFd, mStart, mLength };
	// Data format
	SLDataFormat_MIME format_mime = { SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED };
	// Data source
	SLDataSource audioSource = { &loc_fd, &format_mime };
	
	// Outputmix
	const SLInterfaceID outputInterfaces = SL_IID_VOLUME;
	const SLboolean outputRequired = SL_BOOLEAN_TRUE;
	result = (*Engine)->CreateOutputMix(Engine, &outputObject, 0, &outputInterfaces, &outputRequired);
	result = (*outputObject)->Realize(outputObject, SL_BOOLEAN_FALSE);

	SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, outputObject };
	SLDataSink audioSink = { &loc_outmix, NULL };

	// create audio player
	const SLInterfaceID interfaces[2] = {  SL_IID_VOLUME, SL_IID_SEEK };
	const SLboolean required[2] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
	result = (*Engine)->CreateAudioPlayer(Engine, &PlayerObject, &audioSource, &audioSink, 2, interfaces, required);

	if (result == SL_RESULT_SUCCESS)
		LOGA("Player creation success");
	else if (result == SL_RESULT_CONTENT_NOT_FOUND)
	LOGA("SL_RESULT_CONTENT_NOT_FOUND");
	else if (result == SL_RESULT_PRECONDITIONS_VIOLATED)
		LOGA("SL_RESULT_PRECONDITIONS_VIOLATED");

	// Realize player
	result = (*PlayerObject)->Realize(PlayerObject, SL_BOOLEAN_FALSE);
	if (result != SL_RESULT_SUCCESS)
		LOGA("Player realize failed");

	// Get play interface
	result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_PLAY, &PlayerPlay);
	if (result != SL_RESULT_SUCCESS)
		LOGA("play interface failed");

	// Get volume interface
	result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_VOLUME, &PlayerVolume);
	if (result != SL_RESULT_SUCCESS)
		LOGA("volume interface failed");

	// get seek interface
	result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_SEEK, &Seek);
}

void SoundEffect::setVolume(float volume)
{
	SLmillibel vol = volume;
	(*PlayerVolume)->SetVolumeLevel(PlayerVolume, vol);
}

void SoundEffect::Play()
{
	(*PlayerPlay)->SetPlayState(PlayerPlay, SL_PLAYSTATE_PLAYING);
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
