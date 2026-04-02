#include "Battle.h"

Battle::Battle(const char pathMap, SDL_Renderer* renderer, TTF_Font* font, Player* player, int width, int height, int FPS)
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

	// TEXT
	colorWhite = { 255, 255, 255, 255 };
	gameOverText.text = "GAME OVER";
	gameOverText.initialize(renderer, font, colorWhite);
	gameOverText.dest.x = width / 2 - gameOverText.dest.w / 2;
	gameOverText.dest.y = height / 2 - gameOverText.dest.h - 50;

	commandText.text = "Press \"SPACE\" to MENU";
	commandText.initialize(renderer, font, colorWhite);
	commandText.dest.x = width / 2 - commandText.dest.w / 2;
	commandText.dest.y = height / 2 - commandText.dest.h + 25;

	starsCount = 20;
	for (int i = 0; i < starsCount; i++)
	{
		stars.push_back({ (float)SDL_rand(width), (float)SDL_rand(height), 4, 4 });
	}

	this->collisionManager = new CollisionManager();
	cometManager = new CometManager(renderer, maxCountComets, spawnInSecondsComets, windowWidth, windowHeight);
	ui = new UI(renderer, width, height, font, player);

	gameOver = false;
}

Battle::~Battle()
{
	delete collisionManager;
	delete cometManager;
	delete ui;

	gameOverText.destroyTexture();
	commandText.destroyTexture();
}

void Battle::setup(const char pathMap)
{
	gameOver = false;

	if (pathMap == NULL)
	{
		// Infinity game
		// FPS = 1 seconds
		spawnInSecondsComets = this->FPS;
		maxCountComets = 6;
	}

	player->setup();
	cometManager->setup();
	ui->setup();
}

void Battle::update()
{
	if (!gameOver)
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
		player->update();

		collision();
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
	player->draw(renderer);
	ui->draw(renderer);

	if (gameOver)
	{
		SDL_RenderTexture(renderer, gameOverText.texture, NULL, &gameOverText.dest);
		SDL_RenderTexture(renderer, commandText.texture, NULL, &commandText.dest);
	}
}

void Battle::collision()
{
	int cometsSize = cometManager->getSize();
	for (int i = 0; i < cometsSize; i++)
	{
		if (cometManager->cometExists(i))
		{
			if (collisionManager->checkCollisionRect(player->getDest(), cometManager->getCometDest(i)))
			{
				if (player->lostHP(1))
				{
					gameOver = true;
				}
				cometManager->deleteComet(i);

				ui->updateHP();
			}
		}
	}

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
						player->deleteBullet(i);
						cometManager->deleteComet(j);

						ui->updateScore();
						break;
					}
				}
			}
		}
	}
}