#pragma once

#include <SDL3_mixer/SDL_mixer.h>

class Audio
{
public:
	Audio(const char* path);
	~Audio();

	void loadAudio(const char* path);

	void loop();
	void pause();
	void play();
	void stop();

private:
	MIX_Mixer* mixer = NULL;
	MIX_Audio* audio = NULL;
	MIX_Track* track = NULL;
	SDL_PropertiesID options = 0;
};

