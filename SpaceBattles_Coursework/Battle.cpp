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

	this->collisionManager = new CollisionManager();
	cometManager = new CometManager(renderer, maxCountComets, spawnInSecondsComets, windowWidth, windowHeight);

	gameOver = false;
}

Battle::~Battle()
{
	delete collisionManager;
	delete cometManager;
}

void Battle::update()
{
	if (!gameOver)
	{
		cometManager->update();
		player->update();

		collision();
	}
	
}

void Battle::draw()
{
	cometManager->draw();
	player->draw(renderer);
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
						player->deleteBullet(i);
						cometManager->deleteComet(j);
						break;
					}
				}
			}
		}
	}
}