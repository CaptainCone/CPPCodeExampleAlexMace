#include "AudioController.h"

AudioController::~AudioController()
{
	SDL_FreeWAV(wavBuffer);
	SDL_CloseAudioDevice(deviceID);
}

void AudioController::load(const char* filename)
{
	//if (wavBuffer)
		//SDL_FreeWAV(wavBuffer);

	SDL_LoadWAV(filename,&wavSpec,&wavBuffer,&wavLength);
	deviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

void AudioController::play()
{
	SDL_QueueAudio(deviceID, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceID,0);
}

void AudioController::pause()
{
	SDL_PauseAudioDevice(deviceID, 1);
}