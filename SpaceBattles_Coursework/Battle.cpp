#include "Battle.h"

Battle::Battle(const char pathMap, SDL_Renderer* renderer, Player* player, int width, int height, int FPS)
{
	this->renderer = renderer;
	this->player = player;
	this->windowWidth = width;
	this->windowHeight = height;
	this->FPS = FPS;

	if (pathMap == NULL)
	{
		// Infinity game
		// FPS = 1 seconds
		spawnInSecondsComets = this->FPS; 
		maxCountComets = 6;
	}

	cometManager = new CometManager(renderer, maxCountComets, spawnInSecondsComets, windowWidth, windowHeight);
}

Battle::~Battle()
{
	delete cometManager;
}

void Battle::update()
{
	cometManager->update();
	player->update();
}

void Battle::draw()
{
	cometManager->draw();
	player->draw(renderer);
}
