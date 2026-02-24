#pragma once

#include <SDL3/SDL.h>
#include "InputHandler.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();

	SDL_AppResult SDL_AppInit();
	SDL_AppResult SDL_AppEvent(SDL_Event* event);
	SDL_AppResult SDL_AppIterate();
	void SDL_AppQuit();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	int width;
	int height;

	InputHandler* inputHandler = nullptr;
	Player* player = nullptr;
};

