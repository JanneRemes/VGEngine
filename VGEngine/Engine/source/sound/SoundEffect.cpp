
#include "engine/sound/SoundEffect.h"

using namespace vg;
SoundEffect::SoundEffect(Sound soundFile)
{
	LOGA("Im in soundeffect.cpp");
	
	// Audio player
	
	SLObjectItf engineObject = NULL;
	SLObjectItf PlayerObject = NULL;
	SLObjectItf outputObject = NULL;
	
	static SLEngineItf Engine;
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
	const SLInterfaceID outputInterfaces[1] = { SL_IID_VOLUME };
	const SLboolean outputRequired[1] = { SL_BOOLEAN_TRUE };
	result = (*Engine)->CreateOutputMix(Engine, &outputObject, 0, outputInterfaces, outputRequired);
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

	/*
	// Realize bufferqueue
	result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_BUFFERQUEUE, &BufferQueue);
	if (result != SL_RESULT_SUCCESS)
		LOGA("bufferqueue interface failed");
		*/

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

	// looping
	result = (*Seek)->SetLoop(Seek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);

	result = (*PlayerPlay)->SetPlayState(PlayerPlay, SL_PLAYSTATE_PLAYING);
	if (result != SL_RESULT_SUCCESS)
		LOGA("SetPlayState failed");
	else
		LOGA("SetPlayState success");

	LOGA("Im out of soundeffect.cpp");
}


void SoundEffect::AddToQueue(android_app* app)
{
	// Loading file to buffer
	SLresult result;

	std::string buffer;
	vg::FileManager f(app);

	if (f.readAsset("test_loop.wav", buffer))
		LOGA("Success loading the asset");

	const char *tempBuf = buffer.c_str();
	int fileSize = buffer.length();

	nextBuffer = (short *)tempBuf;
	nextSize = sizeof(tempBuf);

	LOGA("->Enqueue");
	result = (*BufferQueue)->Enqueue(BufferQueue, nextBuffer, nextSize);

	if (result == SL_RESULT_SUCCESS)
		LOGA("Adding to queue worked");
	else if (result == SL_RESULT_BUFFER_INSUFFICIENT)
		LOGA("Buffer insufficient");
	else if (result == SL_RESULT_PARAMETER_INVALID)
		LOGA("Invalid parameters");

	LOGA("Out of AddToQueue");
}


void SoundEffect::setVolume(float volume)
{
	SLmillibel vol = volume;
	(*PlayerVolume)->SetVolumeLevel(PlayerVolume, vol);
}

void SoundEffect::Play()
{

}

void SoundEffect::Pause()
{
	(*PlayerPlay)->SetPlayState(PlayerPlay, SL_PLAYSTATE_PAUSED);
}

void SoundEffect::Stop()
{
	(*PlayerPlay)->SetPlayState(PlayerPlay, SL_PLAYSTATE_STOPPED);
}


SoundEffect::~SoundEffect()
{
}
