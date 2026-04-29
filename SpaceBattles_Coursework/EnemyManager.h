#pragma once

//#include "Player.h"

#include "Greeny.h"
#include "Oranges.h"
#include "BrotherGreeny.h"
#include "Void.h"
#include "Boss.h"

#include "CollisionManager.h"
#include "Audio.h"
//#include "UI.h"

class EnemyManager
{
public:
	EnemyManager(SDL_Renderer* renderer, CollisionManager* collisionManager, UI* ui, int width, int height, Player* player);
	~EnemyManager();

	void setup();

	void update();
	void draw();

	void checkCollision();
	bool createEnemy();

private:
	SDL_Renderer* renderer;
	CollisionManager* collisionManager;
	UI* ui;
	Audio* soundFX;
	std::string soundsEnemy[3] = {"assets/sounds/alien-talk-1.wav", "assets/sounds/alien-talk-2.wav", "assets/sounds/alien-talk-3.wav"};

	Player* player;

	int width;
	int height;

	// ENEMY
	Greeny* greeny;
	Oranges* oranges;
	BrotherGreeny* brotherGreeny;
	Void* voidBoss;
	Boss* boss;

	int currentBoss;
};