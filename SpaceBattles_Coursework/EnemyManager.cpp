#include "EnemyManager.h"

EnemyManager::EnemyManager(SDL_Renderer* renderer, CollisionManager* collisionManager, UI* ui, int width, int height, Player* player)
{
	this->renderer = renderer;
	this->collisionManager = collisionManager;
	this->ui = ui;
	this->width = width;
	this->height = height;
	this->player = player;

	greeny = nullptr;
	oranges = nullptr;
	brotherGreeny = nullptr;
	voidBoss = nullptr;
	boss = nullptr;

	currentBoss = 0;
}

EnemyManager::~EnemyManager()
{
	if (greeny)
	{
		delete greeny;
		greeny = nullptr;
	}
	
	if (oranges)
	{
		delete oranges;
		oranges = nullptr;
	}
	
	if (brotherGreeny)
	{
		delete brotherGreeny;
		brotherGreeny = nullptr;
	}

	if (voidBoss)
	{
		delete voidBoss;
		voidBoss = nullptr;
	}

	if (boss)
	{
		delete boss;
		boss = nullptr;
	}
}

void EnemyManager::setup()
{
	currentBoss = 0;
	if (greeny) 
	{ 
		delete greeny;
		greeny = nullptr;
	}

	if (oranges)
	{
		delete oranges;
		oranges = nullptr;
	}

	if (brotherGreeny)
	{
		delete brotherGreeny;
		brotherGreeny = nullptr;
	}

	if (voidBoss)
	{
		delete voidBoss;
		voidBoss = nullptr;
	}

	if (boss)
	{
		delete boss;
		boss = nullptr;
	}
}

void EnemyManager::update()
{
	if (greeny) greeny->update();
	if (oranges) oranges->update();
	if (brotherGreeny) brotherGreeny->update();
	if (voidBoss) voidBoss->update();
	if (boss) boss->update();
}

void EnemyManager::draw()
{
	if (greeny) greeny->draw();
	if (oranges) oranges->draw();
	if (brotherGreeny) brotherGreeny->draw();
	if (voidBoss) voidBoss->draw();
	if (boss) boss->draw();
}

void EnemyManager::checkCollision()
{
	if (greeny)
	{
		// Bubbles and Player
		for (int i = 0; i < greeny->getSizeBubbles(); i++)
		{
			if (greeny->getBubbles(i) != nullptr)
			{
				SDL_FRect bubbleDest = greeny->getBubbles(i)->dest;
				SDL_FRect playerDest = player->getDest();
				
				if (collisionManager->checkCollisionRect(bubbleDest, playerDest))
				{
					player->lostHP(1);
					greeny->destroyBubblesIndex(i);
				}
			}
		}

		// Player Bullets and Greeny
		for (int i = 0; i < player->getBulletsSize(); i++)
		{
			if (player->bulletExists(i))
			{
				SDL_FRect bulletDest = player->getBulletDest(i);
				SDL_FRect greenyDest = greeny->getDest();

				if (collisionManager->checkCollisionRect(bulletDest, greenyDest))
				{
					greeny->lostHP(player->getBullet(i)->getDamage());
					player->deleteBullet(i);

					SDL_Log("GREENY HP: %i", greeny->getHP());

					if (greeny->getHP() <= 0)
					{
						delete greeny;
						greeny = nullptr;
						break;
					}
				}
			}
		}
	}

	if (oranges)
	{
		// Hands and Player
		for (int i = 0; i < oranges->getSizeHands(); i++)
		{
			if (oranges->getHands(i) != nullptr)
			{
				SDL_FRect orangesDest = oranges->getHands(i)->dest;
				SDL_FRect playerDest = player->getDest();

				if (collisionManager->checkCollisionRect(orangesDest, playerDest))
				{
					player->lostHP(1);
					oranges->destroyHandsIndex(i);
				}
			}
		}
		
		// Player Bullets and Oranges
		for (int i = 0; i < player->getBulletsSize(); i++)
		{
			if (player->bulletExists(i))
			{
				SDL_FRect bulletDest = player->getBulletDest(i);
				SDL_FRect orangesDest = oranges->getDest();

				if (collisionManager->checkCollisionRect(bulletDest, orangesDest))
				{
					oranges->lostHP(player->getBullet(i)->getDamage());
					player->deleteBullet(i);

					SDL_Log("ORANGES HP: %i", oranges->getHP());

					if (oranges->getHP() <= 0)
					{
						delete oranges;
						oranges = nullptr;
						break;
					}
				}
			}
		}
	}

	if (brotherGreeny)
	{
		// HandBomb and Player
		for (int i = 0; i < brotherGreeny->getSizeHandBombs(); i++)
		{
			if (brotherGreeny->getHandBomb(i) != nullptr)
			{
				SDL_FRect destHandBomb = brotherGreeny->getHandBomb(i)->dest;
				SDL_FRect playerDest = player->getDest();

				if (collisionManager->checkCollisionRect(destHandBomb, playerDest))
				{
					player->lostHP(brotherGreeny->getHandBomb(i)->damage); // 1 or 2
					brotherGreeny->destroyHandBombIndex(i);
				}
			}
		}

		// Player Bullets and Greeny
		for (int i = 0; i < player->getBulletsSize(); i++)
		{
			if (player->bulletExists(i))
			{
				SDL_FRect bulletDest = player->getBulletDest(i);
				SDL_FRect brotherGreenyDest = brotherGreeny->getDest();

				if (collisionManager->checkCollisionRect(bulletDest, brotherGreenyDest))
				{
					brotherGreeny->lostHP(player->getBullet(i)->getDamage());
					player->deleteBullet(i);

					if (brotherGreeny->getHP() <= 0)
					{
						delete brotherGreeny;
						brotherGreeny = nullptr;
						break;
					}
				}
			}
		}
	}

	if (voidBoss)
	{
		// Ray and Player
		Ray* ray = voidBoss->getRay();
		if (ray)
		{
			SDL_FRect rayDest = ray->dest;
			SDL_FRect playerDest = player->getDest();
			int rayDamage = ray->damage;

			if (collisionManager->checkCollisionRect(rayDest, playerDest) && ray->attack)
			{
				player->lostHP(rayDamage);
			}
		}

		// Player Bullets and Void
		for (int i = 0; i < player->getBulletsSize(); i++)
		{
			if (player->bulletExists(i))
			{
				SDL_FRect bulletDest = player->getBulletDest(i);
				SDL_FRect voidBossDest = voidBoss->getDest();

				if (collisionManager->checkCollisionRect(bulletDest, voidBossDest))
				{
					voidBoss->lostHP(player->getBullet(i)->getDamage());
					player->deleteBullet(i);

					if (voidBoss->getHP() <= 0)
					{
						delete voidBoss;
						voidBoss = nullptr;
						break;
					}
				}
			}
		}
	}

	if (boss)
	{
		// Blaster and Player
		for (int i = 0; i < boss->getSizeBlasters(); i++)
		{
			if (boss->getBlaster(i) != nullptr)
			{
				SDL_FRect blasterDest = boss->getBlaster(i)->dest;
				SDL_FRect playerDest = player->getDest();

				if (collisionManager->checkCollisionRect(blasterDest, playerDest))
				{
					player->lostHP(boss->getBlaster(i)->damage);
					boss->deleteBlasterIndex(i);
				}
			}
		}

		// Player Bullets and Boss
		for (int i = 0; i < player->getBulletsSize(); i++)
		{
			if (player->bulletExists(i))
			{
				SDL_FRect bulletDest = player->getBulletDest(i);
				SDL_FRect bossDest = boss->getDest();

				if (collisionManager->checkCollisionRect(bulletDest, bossDest))
				{
					boss->lostHP(player->getBullet(i)->getDamage());
					player->deleteBullet(i);

					if (boss->getHP() <= 0)
					{
						delete boss;
						boss = nullptr;
						break;
					}
				}
			}
		}
	}
}

bool EnemyManager::createEnemy()
{
	if (!greeny && !oranges && !brotherGreeny && !voidBoss && !boss)
	{
		switch (currentBoss)
		{
		case 0:
			if (!greeny)
			{
				greeny = new Greeny(renderer, width, height);
				currentBoss++;
				return true;
			}
			break;
		case 1:
			if (!oranges)
			{
				oranges = new Oranges(renderer, ui, width, height);
				currentBoss++;
			}
			return true;
			break;
		case 2:
			if (!brotherGreeny)
			{
				brotherGreeny = new BrotherGreeny(renderer, width, height);
				currentBoss++;
			}
			return true;
			break;
		case 3:
			if (!voidBoss)
			{
				voidBoss = new Void(renderer, width, height, ui);
				currentBoss++;
			}
			return true;
			break;
		case 4:
			if (!boss)
			{
				boss = new Boss(renderer, width, height);
				currentBoss++;
			}
			return true;
			break;
		default:
			if (currentBoss > 4)
			{
				currentBoss = 0;
			}
			break;
		}
	}

	return false;
}
