#pragma once
#include "header.h"

class AudioController
{
public:
	~AudioController();
	void load(const char* filename);
	void play();
	void pause();
protected:
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceID;
};

