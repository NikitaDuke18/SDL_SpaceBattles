#include "Boss.h"

Boss::Boss(SDL_Renderer* renderer, int width, int height)
{
	this->renderer = renderer;
	this->width = width;
	this->height = height;

	this->scale = 5;
	this->texture = IMG_LoadTexture(renderer, "assets/entity/enemy/boss/FinalBoss.png");
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	this->dest = {0, 0, 30.0F * this->scale, 23.0F * this->scale};
	this->dest.x = width / 2 - this->dest.w / 2;
	this->dest.y = 0 - this->dest.h * 2;
	this->speed = 1;
	this->HP = 50;
	this->changePosition = false;

	sizeBlasters = 21;
	blasters = new Blaster*[sizeBlasters];
	for (int i = 0; i < sizeBlasters; i++)
	{
		blasters[i] = nullptr;
	}

	lastTime = SDL_GetTicksNS();
	accumulator = 0;
	timeSpawn = 2000000000;
}

Boss::~Boss()
{
	for (int i = 0; i < sizeBlasters; i++)
	{
		if (blasters[i])
		{
			SDL_DestroyTexture(blasters[i]->texture);
			delete blasters[i];
			blasters[i] = nullptr;
		}
	}
	delete[] blasters;
}

void Boss::setup()
{
	sizeBlasters = 21;
	blasters = new Blaster * [sizeBlasters];
	for (int i = 0; i < sizeBlasters; i++)
	{
		blasters[i] = nullptr;
	}

	lastTime = SDL_GetTicksNS();
	accumulator = 0;
	timeSpawn = 2000000000;
}

void Boss::update()
{
	for (int i = 0; i < sizeBlasters; i++)
	{
		if (blasters[i])
		{
			blasters[i]->update();
		}
	}

	if (dest.y < 0)
	{
		dest.y += speed;
	}
	else
	{
		if (!changePosition)
		{
			createBlaster();
		}
		else
		{
			Uint64 currentTime = SDL_GetTicksNS();

			accumulator += currentTime - lastTime;

			lastTime = currentTime;

			if (accumulator >= 1500000000)
			{
				dest.x = SDL_rand(width - dest.w);
				dest.y = SDL_rand(height / 3);

				changePosition = false;
				accumulator = 0;
			}
		}
	}

	checkOutBlaster();
}

void Boss::draw()
{
	for (int i = 0; i < sizeBlasters; i++)
	{
		if (blasters[i])
		{
			blasters[i]->draw(renderer);
		}
	}

	SDL_RenderTexture(renderer, texture, NULL, &dest);
}

void Boss::lostHP(int damage)
{
	this->HP -= damage;
}

void Boss::createBlaster()
{
	Uint64 currentTime = SDL_GetTicksNS();

	accumulator += currentTime - lastTime;

	lastTime = currentTime;

	if (accumulator >= timeSpawn)
	{
		int count = 0;
		for (int i = 0; i < sizeBlasters && count < 3; i++)
		{
			if (!blasters[i])
			{
				blasters[i] = new Blaster();
				blasters[i]->texture = IMG_LoadTexture(renderer, "assets/entity/bullets/enemy/blaster_1.png");
				SDL_SetTextureScaleMode(blasters[i]->texture, SDL_SCALEMODE_NEAREST);
				blasters[i]->dest = { dest.x, dest.y, 6.0F * blasters[i]->scale, 11.0F * blasters[i]->scale };
				blasters[i]->dest.x = dest.x + dest.w / 2 - blasters[i]->dest.w / 2;
				blasters[i]->dest.y = dest.y + dest.h / 2 - blasters[i]->dest.h - 10;
				blasters[i]->damage = 1;

				if (count == 0)
				{
					blasters[i]->angle = 0;
				}
				else if (count == 1)
				{
					blasters[i]->angle = 45;
				}
				else if (count == 2)
				{
					blasters[i]->angle = -45;
				}

				count++;
			}
		}

		changePosition = true;
		accumulator = 0;
	}
}

void Boss::checkOutBlaster()
{
	for (int i = 0; i < sizeBlasters; i++)
	{
		if (blasters[i])
		{
			if (blasters[i]->dest.x + blasters[i]->dest.w < 0 ||
				blasters[i]->dest.x > width ||
				blasters[i]->dest.y + blasters[i]->dest.h < 0 ||
				blasters[i]->dest.y > height)
			{
				SDL_DestroyTexture(blasters[i]->texture);
				delete blasters[i];
				blasters[i] = nullptr;
				SDL_Log("Delete");
			}
		}
	}
}

void Boss::deleteBlasterIndex(int index)
{
	if (blasters[index])
	{
		SDL_DestroyTexture(blasters[index]->texture);
		delete blasters[index];
		blasters[index] = nullptr;
	}
}
