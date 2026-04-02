#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <string>

#include "Text.h"
#include "UI.h"
#include "CollisionManager.h"
#include "Player.h"
#include "CometManager.h"

class Battle
{
public:
	// pathMap - отвечает за то что будет у нас, бесконечные волны или определенный уровень который будет прочитан как txt файл
	Battle(const char pathMap, SDL_Renderer* renderer, TTF_Font* font, Player* player, int width, int height, int FPS);
	~Battle();

	void setup(const char pathMap);

	void update();
	void draw();

	void collision();

	bool getGameOver() { return gameOver; };
	void setGameOver(bool gameOver) { this->gameOver = gameOver; };

private:
	SDL_Renderer* renderer;
	TTF_Font* font;

	CollisionManager* collisionManager;
	Player* player;
	CometManager* cometManager;
	UI* ui;

	// Text
	Text gameOverText;
	Text commandText;
	SDL_Color colorWhite;

	int windowWidth;
	int windowHeight;

	// уровень сложности
	int FPS;
	int spawnInSecondsComets;
	int maxCountComets;

	std::vector<SDL_FRect> stars;
	int starsCount;

	bool gameOver;
};