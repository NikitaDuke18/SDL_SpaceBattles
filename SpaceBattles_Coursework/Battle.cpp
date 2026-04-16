#include "Battle.h"

Battle::Battle(const char pathMap, SDL_Renderer* renderer, TTF_Font* font_48, TTF_Font* font_32, Player* player, SaveLoad* saveLoad, int width, int height, int FPS)
{
	this->renderer = renderer;
	this->font_48 = font_48;
	this->font_32 = font_32;

	this->player = player;
	this->saveLoad = saveLoad;
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

	// TEXT
	colorWhite = { 255, 255, 255, 255 };
	gameOverText.text = "GAME OVER";
	gameOverText.initialize(renderer, font_48, colorWhite);
	gameOverText.dest.x = width / 2 - gameOverText.dest.w / 2;
	gameOverText.dest.y = height / 2 - gameOverText.dest.h - 50;

	commandText.text = "Press \"SPACE\" to MENU";
	commandText.initialize(renderer, font_32, colorWhite);
	commandText.dest.x = width / 2 - commandText.dest.w / 2;
	commandText.dest.y = height / 2 - commandText.dest.h + 25;

	pauseText.text = "PAUSE";
	pauseText.initialize(renderer, font_48, colorWhite);
	pauseText.dest.x = width / 2 - pauseText.dest.w / 2;
	pauseText.dest.y = height / 2 - pauseText.dest.h - 50;

	pauseCommandText.text = "Press \"K\" - UNPAUSE OR \"ESC\" - MENU";
	pauseCommandText.initialize(renderer, font_32, colorWhite);
	pauseCommandText.dest.x = width / 2 - pauseCommandText.dest.w / 2;
	pauseCommandText.dest.y = height / 2 - pauseCommandText.dest.h + 25;

	starsCount = 20;
	for (int i = 0; i < starsCount; i++)
	{
		stars.push_back({ (float)SDL_rand(width), (float)SDL_rand(height), 4, 4 });
	}

	scoreToSpawnBoss = 0;

	this->collisionManager = new CollisionManager();
	cometManager = new CometManager(renderer, maxCountComets, spawnInSecondsComets, windowWidth, windowHeight);
	ui = new UI(renderer, width, height, font_48, player);
	enemyManager = new EnemyManager(renderer, collisionManager, ui, width, height, player);

	pause = false;
	gameOver = false;
}

Battle::~Battle()
{
	delete collisionManager;
	delete cometManager;
	delete ui;

	gameOverText.destroyTexture();
	commandText.destroyTexture();
	pauseText.destroyTexture();
	pauseCommandText.destroyTexture();
}

void Battle::setup(const char pathMap)
{
	pause = false;
	gameOver = false;
	scoreToSpawnBoss = 0;

	if (pathMap == NULL)
	{
		// Infinity game
		// FPS = 1 seconds
		spawnInSecondsComets = this->FPS;
		maxCountComets = 6;
	}

	player->setup();
	cometManager->setup();
	enemyManager->setup();
	ui->setup();

	// LOAD
	saveLoad->loadPlayer(player);
	ui->updateScore();
	// TEST
	//enemyManager->createEnemy();
}

void Battle::update()
{
	if (!gameOver)
	{
		if (!pause)
		{
			for (int i = 0; i < starsCount; i++)
			{
				stars[i].y += 1;

				if (stars[i].y > windowHeight)
				{
					stars[i] = { (float)SDL_rand(windowWidth), (float)0 - SDL_rand(windowWidth), 4, 4 };
				}
			}

			cometManager->update();
			enemyManager->update();

			player->update();

			collision();
		}
	}
}

void Battle::draw()
{
	for (int i = 0; i < starsCount; i++)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &stars[i]);
	}

	cometManager->draw();
	enemyManager->draw();
	player->draw(renderer);
	ui->draw(renderer);

	if (pause)
	{
		SDL_RenderTexture(renderer, pauseText.texture, NULL, &pauseText.dest);
		SDL_RenderTexture(renderer, pauseCommandText.texture, NULL, &pauseCommandText.dest);
	}

	if (gameOver)
	{
		SDL_RenderTexture(renderer, gameOverText.texture, NULL, &gameOverText.dest);
		SDL_RenderTexture(renderer, commandText.texture, NULL, &commandText.dest);
	}
}

void Battle::collision()
{
	// Comets and Player
	int cometsSize = cometManager->getSize();
	for (int i = 0; i < cometsSize; i++)
	{
		if (cometManager->cometExists(i))
		{
			if (collisionManager->checkCollisionRect(player->getDest(), cometManager->getCometDest(i)))
			{
				player->lostHP(1);
				cometManager->deleteComet(i);
			}
		}
	}

	// Bullets and Comets
	int bulletSize = player->getBulletsSize();
	for (int i = 0; i < bulletSize; i++)
	{
		if (player->bulletExists(i))
		{
			for (int j = 0; j < cometsSize; j++)
			{
				if (cometManager->cometExists(j))
				{
					if (collisionManager->checkCollisionRect(player->getBulletDest(i), cometManager->getCometDest(j)))
					{
						player->addScore(cometManager->getComet(j)->getScore());
						scoreToSpawnBoss += cometManager->getComet(j)->getScore();
						SDL_Log("SCORE TO SPAWN: %i", scoreToSpawnBoss);

						player->deleteBullet(i);
						cometManager->deleteComet(j);

						ui->updateScore();

						if (scoreToSpawnBoss >= 20)
						{
							if (enemyManager->createEnemy()) { scoreToSpawnBoss -= 20; }
						}

						break;
					}
				}
			}
		}
	}

	// EnemyManager
	enemyManager->checkCollision();

	// GAME OVER
	if (player->getHP() <= 0)
	{
		gameOver = true;
	}
	ui->updateHP();
}