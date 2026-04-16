#include "BrotherGreeny.h"

BrotherGreeny::BrotherGreeny(SDL_Renderer* renderer, int width, int height)
{
	this->renderer = renderer;
	this->width = width;
	this->height = height;

	this->texture = IMG_LoadTexture(renderer, "assets/entity/enemy/boss/BrotherGreeny.png");
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

	this->scale = 5;
	this->dest = {0.0F - 10 * this->scale, 0.0F - 14 * this->scale, 10.0F * this->scale, 10.0F * this->scale};
	this->HP = 35;
	this->speed = 3;

	sizeHandBombs = 20;
	handBombs = new HandBomb*[sizeHandBombs];
	for (int i = 0; i < sizeHandBombs; i++)
	{
		handBombs[i] = nullptr;
	}
	direction = UP_LEFT;
	changeDir = false;

	lastTime = SDL_GetTicksNS();
	accumulator = 0;
	timeSpawn = 2000000000;
}

BrotherGreeny::~BrotherGreeny()
{
	for (int i = 0; i < sizeHandBombs; i++)
	{
		if (handBombs[i])
		{
			SDL_DestroyTexture(handBombs[i]->texture);
			delete handBombs[i];
			handBombs[i] = nullptr;
		}
	}
	delete[] handBombs;
}

void BrotherGreeny::setup()
{
	this->scale = 5;
	this->dest = { 0.0F - 10 * this->scale, 0.0F - 14 * this->scale, 10.0F * this->scale, 10.0F * this->scale };
	this->HP = 35;
	this->speed = 2;

	sizeHandBombs = 20;
	handBombs = new HandBomb * [sizeHandBombs];
	for (int i = 0; i < sizeHandBombs; i++)
	{
		handBombs[i] = nullptr;
	}

	lastTime = SDL_GetTicksNS();
	accumulator = 0;
	timeSpawn = 2000000000;
}

void BrotherGreeny::update()
{
	for (int i = 0; i < sizeHandBombs; i++)
	{
		if (handBombs[i])
		{
			handBombs[i]->update();
		}
	}

	switch (direction)
	{
	case UP_LEFT:
		if ((dest.y <= 0 || dest.x <= 0) && speed < 0)
		{
			speed *= -1;
		}

		if (dest.y > height / 2)
		{
			direction = UP_RIGHT;
			dest.y = height / 2;

			break;
			// speed = 0;
		}

		dest.y += speed;
		dest.x += speed;
		break;
	case UP_RIGHT:
		if (dest.y <= 0 || dest.x + dest.w >= width)
		{
			speed *= -1;
		}

		if (dest.y > height / 2)
		{
			direction = DOWN_RIGHT;
			dest.y = height / 2;

			break;
			//speed = 0;
		}

		dest.y -= speed;
		dest.x += speed;
		break;
	case DOWN_RIGHT:
		if (dest.y + dest.h >= height || dest.x <= 0)
		{
			speed *= -1;
		}

		if (dest.y < height / 2)
		{
			direction = DOWN_LEFT;
			dest.y = height / 2;

			break;
		}

		dest.y -= speed;
		dest.x -= speed;
		break;
	case DOWN_LEFT:
		if (dest.y + dest.h >= height || dest.x + dest.w >= width)
		{
			speed *= -1;
		}

		if (dest.y < height / 2)
		{
			direction = UP_LEFT;
			dest.y = height / 2;

			break;
		}

		dest.y += speed;
		dest.x -= speed;
		break;
	default:
		break;
	}

	spawnHandBomb();
	checkHandBombOut();
}

void BrotherGreeny::draw()
{
	for (int i = 0; i < sizeHandBombs; i++)
	{
		if (handBombs[i])
		{
			handBombs[i]->draw(renderer);
		}
	}
	SDL_RenderTexture(renderer, texture, NULL, &dest);
}

void BrotherGreeny::lostHP(int damage)
{
	this->HP -= damage;
}

void BrotherGreeny::spawnHandBomb()
{
	Uint64 currentTime = SDL_GetTicksNS();

	accumulator += currentTime - lastTime;

	lastTime = currentTime;

	if (accumulator >= timeSpawn)
	{
		int count = 0;
		for (int i = 0; i < sizeHandBombs && count < 4; i++)
		{
			if (!handBombs[i])
			{
				count++;
				handBombs[i] = new HandBomb();

				if (count % 2 == 0)
				{
					handBombs[i]->texture = IMG_LoadTexture(renderer, "assets/entity/bullets/enemy/red_hand.png");
					handBombs[i]->damage = 2;
				}
				else
				{
					handBombs[i]->texture = IMG_LoadTexture(renderer, "assets/entity/bullets/enemy/green_hand.png");
					handBombs[i]->damage = 1;
				}

				handBombs[i]->dest = { dest.x, dest.y, 5.0F * handBombs[i]->scale, 5.0F * handBombs[i]->scale };
				handBombs[i]->dest.x = dest.x + handBombs[i]->dest.w / 2;
				handBombs[i]->dest.y = dest.y + handBombs[i]->dest.h / 2;

				switch (count)
				{
				case 1:
					handBombs[i]->dir = DOWN;

					break;
				case 2:
					handBombs[i]->dir = LEFT;

					break;
				case 3:
					handBombs[i]->dir = UP;

					break;
				case 4:
					handBombs[i]->dir = RIGHT;

					break;
				default:
					break;
				}
			}
		}

		accumulator -= timeSpawn;
	}
}

void BrotherGreeny::checkHandBombOut()
{
	for (int i = 0; i < sizeHandBombs; i++)
	{
		if (handBombs[i])
		{
			if (handBombs[i]->dest.x > width || handBombs[i]->dest.x + width < 0 ||
				handBombs[i]->dest.y > height || handBombs[i]->dest.y + height < 0)
			{
				SDL_DestroyTexture(handBombs[i]->texture);
				delete handBombs[i];
				handBombs[i] = nullptr;
			}
		}
	}
}

void BrotherGreeny::destroyHandBombIndex(int index)
{
	if (handBombs[index])
	{
		SDL_DestroyTexture(handBombs[index]->texture);
		delete handBombs[index];
		handBombs[index] = nullptr;
	}
}