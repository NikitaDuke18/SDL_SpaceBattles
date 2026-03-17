#include "Game.h"

Game::Game()
{
	width = 800; // 800
	height = 640; // 640

	// FPS
	freq = SDL_GetPerformanceFrequency();
	last = SDL_GetPerformanceCounter();
	frameCount = 0;
	fpsTimer = SDL_GetPerformanceCounter();
}

Game::~Game()
{
}

SDL_AppResult Game::SDL_AppInit()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize sdl: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer("Space battles", width, height, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	player = new Player(renderer);
	battle = new Battle(NULL, renderer, player, width, height, FPS);
	inputHandler = new InputHandler(player);

	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::SDL_AppEvent(SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}

	inputHandler->keyDown();
	inputHandler->keyUp();

	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::SDL_AppIterate()
{
	now = SDL_GetPerformanceCounter();
	delta = (double)(now - last) / freq;

	if (delta >= frameDuraction) {
		update();
		draw();
		last = now;
		frameCount++;
	}

	fpsElapsed = (double)(now - fpsTimer) / freq;
	if (fpsElapsed >= 1.0) {
		SDL_Log("FPS: %i", frameCount);
		frameCount = 0;
		fpsTimer = now;
	}

	return SDL_APP_CONTINUE;
}

void Game::SDL_AppQuit()
{
	delete player;
	delete inputHandler;
}

void Game::update()
{
	battle->update();
}

void Game::draw()
{
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	battle->draw();

	SDL_RenderPresent(renderer);
}
