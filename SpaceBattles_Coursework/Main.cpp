#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Game.h"

Game* game;

SDL_AppResult SDL_AppInit(void** state, int argc, char* argv[]) 
{
	game = new Game();
	return game->SDL_AppInit();
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	return game->SDL_AppEvent(event);
}

SDL_AppResult SDL_AppIterate(void* state)
{
	return game->SDL_AppIterate();
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	game->SDL_AppQuit();
}