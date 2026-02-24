#include "Game.h"

Game::Game()
{
	width = 800;
	height = 640;
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
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	player->update();
	player->draw(renderer);

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;
}

void Game::SDL_AppQuit()
{
	delete player;
	delete inputHandler;
}
