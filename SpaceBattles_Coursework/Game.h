#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

//#include "Battle.h"
#include "InputHandler.h"
#include "Player.h"
//#include "SceneManager.h"
#include "UI.h"
#include "SaveLoad.h"

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

	TTF_Font* font_48;
	TTF_Font* font_32;

	int width;
	int height;
	bool* quit;

	// FPS
	const int FPS = 120;
	//const double frameDuraction = 1.0 / FPS;
	Uint64 frameDurationNS = 1000000000 / FPS;
	Uint64 freq;
	Uint64 last;
	int frameCount;
	Uint64 fpsTimer;
	Uint64 now;
	Uint64 accumulator = 0;
	double delta;
	double fpsElapsed;

	SaveLoad* saveLoad = nullptr;
	Battle* battle = nullptr;
	InputHandler* inputHandler = nullptr;
	Player* player = nullptr;

	SceneManager* sceneManager;
};

	