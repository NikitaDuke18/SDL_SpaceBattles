#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <string>

#include "Text.h"
//#include "UI.h"
//#include "CollisionManager.h"
#include "CometManager.h"
#include "EnemyManager.h"
//#include "Player.h"
#include "SaveLoad.h"

class Battle
{
public:
	// pathMap - отвечает за то что будет у нас, бесконечные волны или определенный уровень который будет прочитан как txt файл
	Battle(const char pathMap, SDL_Renderer* renderer, TTF_Font* font_48, TTF_Font* font_32, Player* player, SaveLoad* saveLoad, int width, int height, int FPS);
	~Battle();

	void setup(const char pathMap);

	void update();
	void draw();

	void collision();

	void changePause() { pause = !pause; };
	bool getPause() { return pause; };

	bool getGameOver() { return gameOver; };
	void setGameOver(bool gameOver) { this->gameOver = gameOver; };

private:
	SDL_Renderer* renderer;
	TTF_Font* font_48;
	TTF_Font* font_32;

	CollisionManager* collisionManager;
	CometManager* cometManager;
	EnemyManager* enemyManager;
	Player* player;
	UI* ui;
	SaveLoad* saveLoad;

	// Text
	Text gameOverText;
	Text commandText;
	Text pauseText;
	Text pauseCommandText;
	SDL_Color colorWhite;

	int windowWidth;
	int windowHeight;

	// уровень сложности
	int FPS;
	int spawnInSecondsComets;
	int maxCountComets;

	std::vector<SDL_FRect> stars;
	int starsCount;

	int scoreToSpawnBoss;

	bool pause;
	bool gameOver;
};