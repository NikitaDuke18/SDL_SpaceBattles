#include "Audio.h"

Audio::Audio(const char* path)
{
	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
	if (!mixer)
	{
		SDL_Log("Couldn't create mixer on default device: %s", SDL_GetError());
	}

	audio = MIX_LoadAudio(mixer, path, false);

	track = MIX_CreateTrack(mixer);

	if (!track)
	{
		SDL_Log("Couldn't create a mixer track: %s", SDL_GetError());
	}

	MIX_SetTrackAudio(track, audio);
}

Audio::~Audio()
{
	MIX_DestroyTrack(track);
	MIX_DestroyMixer(mixer);
	MIX_DestroyAudio(audio);
	SDL_DestroyProperties(options);
}

void Audio::loadAudio(const char* path)
{
	MIX_DestroyTrack(track);
	MIX_DestroyAudio(audio);

	audio = MIX_LoadAudio(mixer, path, false);

	if (!audio)
	{
		SDL_Log("Couldn't read a audio track: %s", SDL_GetError());
	}

	track = MIX_CreateTrack(mixer);

	if (!track)
	{
		SDL_Log("Couldn't create a mixer track: %s", SDL_GetError());
	}

	MIX_SetTrackAudio(track, audio);
}

void Audio::loop()
{
	options = SDL_CreateProperties();
	if (!options)
	{
		SDL_Log("Couldn't create play options: %s", SDL_GetError());
	}
	SDL_SetNumberProperty(options, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
}

void Audio::pause()
{
	MIX_TrackPaused(track);
}

void Audio::play()
{
	if (options != NULL)
	{
		MIX_PlayTrack(track, options);
	}
	else
	{
		MIX_PlayTrack(track, 0);
	}
}

void Audio::stop()
{
	MIX_StopTrack(track, 0);
}
