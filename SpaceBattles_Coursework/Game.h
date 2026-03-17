#pragma once

#include <SDL3/SDL.h>
#include "Battle.h"
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

	void update();
	void draw();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	int width;
	int height;

	// FPS
	const int FPS = 120;
	const double frameDuraction = 1.0 / FPS;
	Uint64 freq;
	Uint64 last;
	int frameCount;
	Uint64 fpsTimer;
	Uint64 now;
	double delta;
	double fpsElapsed;

	Battle* battle = nullptr;
	InputHandler* inputHandler = nullptr;
	Player* player = nullptr;
};

