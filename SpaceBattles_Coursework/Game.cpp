#include "Game.h"

Game::Game()
{
	width = 800; // 800
	height = 640; // 640

	// FPS
	freq = SDL_GetPerformanceFrequency();
	last = SDL_GetTicksNS();
	frameCount = 0;
	//fpsTimer = SDL_GetPerformanceCounter();
	fpsTimer = SDL_GetTicksNS();
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

	if (!TTF_Init())
	{
		SDL_Log("Couldn't initialize ttf: %s", SDL_GetError());
	}

	if (!SDL_CreateWindowAndRenderer("Space battles", width, height, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!MIX_Init())
	{
		SDL_Log("Couldn't init SDL_mixer library: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	font_48 = TTF_OpenFont("assets/fonts/waltographUI.ttf", 48);

	if (!font_48)
	{
		SDL_Log("Error load font_48: %s", SDL_GetError());
	}

	font_32 = TTF_OpenFont("assets/fonts/waltographUI.ttf", 32);

	if (!font_32)
	{
		SDL_Log("Error load font_24: %s", SDL_GetError());
	}

	quit = new bool(false);

	saveLoad = new SaveLoad();
	player = new Player(renderer, SDL_FPoint{ width / 2.0F, height / 2.0F }, width, height);
	battle = new Battle(NULL, renderer, font_48, font_32, player, saveLoad, width, height, FPS);

	sceneManager = new SceneManager(renderer, font_48, quit, width, height, MENU, battle);

	inputHandler = new InputHandler(renderer, sceneManager, battle, player, saveLoad);

	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::SDL_AppEvent(SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::SDL_AppIterate()
{
	/*now = SDL_GetPerformanceCounter();

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
	}*/


	now = SDL_GetTicksNS();

	accumulator += now - last;

	last = now;

	bool shouldDraw = false;
	while (accumulator >= frameDurationNS)
	{
		accumulator -= frameDurationNS;
		shouldDraw = true;
	}

	if (shouldDraw)
	{
		update();
		draw();
		frameCount++;
		shouldDraw = false;
	}

	if (now - fpsTimer >= 1000000000)
	{
		SDL_Log("FPS: %i", frameCount);
		frameCount = 0;
		fpsTimer = now;
	}

	if (*quit)
	{
		return SDL_APP_SUCCESS;
	}

	return SDL_APP_CONTINUE;
}

void Game::SDL_AppQuit()
{
	delete quit;
	delete player;
	delete battle;
	delete inputHandler;
	delete sceneManager;

	// Close font
	TTF_CloseFont(font_48);
	TTF_CloseFont(font_32);

	TTF_Quit();
	MIX_Quit();
	SDL_Quit();
}

void Game::update()
{
	inputHandler->keyDown();
	inputHandler->keyUp();

	sceneManager->update();
}

void Game::draw()
{
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);	

	sceneManager->draw(renderer);

	SDL_RenderPresent(renderer);
}
