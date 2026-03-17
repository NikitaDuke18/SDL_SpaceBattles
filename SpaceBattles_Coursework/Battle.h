#pragma once

#include <SDL3/SDL.h>
#include "Player.h"
#include "CometManager.h"

class Battle
{
public:
	// pathMap - отвечает за то что будет у нас, бесконечные волны или определенный уровень который будет прочитан как txt файл
	Battle(const char pathMap, SDL_Renderer* renderer, Player* player, int width, int height, int FPS);
	~Battle();

	void update();
	void draw();
private:
	SDL_Renderer* renderer;
	Player* player;
	CometManager* cometManager;
	int windowWidth;
	int windowHeight;

	// уровень сложности
	int FPS;
	int spawnInSecondsComets;
	int maxCountComets;
};

