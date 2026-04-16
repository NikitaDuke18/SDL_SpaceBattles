#include "Oranges.h"

Oranges::Oranges(SDL_Renderer* renderer, UI* ui, int width, int height)
{
	this->renderer = renderer;
	this->ui = ui;
	this->width = width;
	this->height = height;

	this->texture = IMG_LoadTexture(renderer, "assets/entity/enemy/boss/Oranges.png");
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	
	this->direction = DOWN;
	this->scale = 5;
	this->speed = 3;
	this->dest = { 0, 0, 14.0F * scale, 12.0F * scale};
	this->HP = 20;

	for (int i = 0; i < sizeHands; i++)
	{
		hands[i] = nullptr;
	}

	this->lastTime = SDL_GetTicksNS();
	this->timeSpawn = 1000000000;
	this->accumulator = 0;
}

Oranges::~Oranges()
{
	for (int i = 0; i < sizeHands; i++)
	{
		if (hands[i])
		{
			SDL_DestroyTexture(hands[i]->texture);
			hands[i] = nullptr;
		}
	}

	SDL_DestroyTexture(this->texture);
}

void Oranges::setup()
{
	this->scale = 5;
	this->speed = 3;
	this->dest = { 0 - 14.0F * scale * 2, 0, 14.0F * scale, 12.0F * scale };
	this->HP = 20;

	for (int i = 0; i < sizeHands; i++)
	{
		hands[i] = nullptr;
	}

	this->timeSpawn = 1000000000;
	this->lastTime = SDL_GetTicksNS();
	this->accumulator = 0;
}

void Oranges::update()
{
	for (int i = 0; i < sizeHands; i++)
	{
		if (hands[i])
		{
			hands[i]->update();
		}
	}

	switch (direction)
	{
	case UP:
		dest.x -= speed;
		break;
	case DOWN:
		dest.x += speed;
		break;
	case LEFT:
		dest.y += speed;
		break;
	case RIGHT:
		dest.y -= speed;
		break;
	case NONE:
		break;
	default:
		break;
	}

	if (dest.x > width - dest.w)
	{
		direction = LEFT;
		angle += 90;
		dest.x = width - dest.w;
	}
	else if (dest.y > height - dest.h - ui->getBarDest().h)
	{
		direction = UP;
		angle += 90;
		dest.y = height - dest.h - ui->getBarDest().h;
	}
	else if (dest.x < 0)
	{
		direction = RIGHT;
		angle += 90;
		dest.x = 0;
	}
	else if (dest.y < 0)
	{
		direction = DOWN;
		angle += 90;
		dest.y = 0;
	}

	if (angle >= 360)
	{
		angle = 0;
	}

	createHands();
	checkHandsOut();
}

void Oranges::draw()
{
	for (int i = 0; i < sizeHands; i++)
	{
		if (hands[i])
		{
			hands[i]->draw(renderer);
		}
	}

	SDL_RenderTextureRotated(renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}

void Oranges::lostHP(int damage)
{
	this->HP -= damage;
}

void Oranges::createHands()
{
	Uint64 currentTime = SDL_GetTicksNS();

	accumulator += currentTime - lastTime;

	lastTime = currentTime;

	if (accumulator >= timeSpawn)
	{
		for (int i = 0; i < sizeHands; i++)
		{
			if (!hands[i])
			{
				hands[i] = new Hands();
				hands[i]->texture = IMG_LoadTexture(renderer, "assets/entity/bullets/enemy/hands.png");
				SDL_SetTextureScaleMode(hands[i]->texture, SDL_SCALEMODE_NEAREST);
				hands[i]->dest = { dest.x + hands[i]->dest.w / 2, dest.y + hands[i]->dest.h / 2, 14.0F * hands[i]->scale, 6.0F * hands[i]->scale};

				switch (direction)
				{
				case UP:
					hands[i]->dir = UP;
					break;
				case DOWN:
					hands[i]->dir = DOWN;
					break;
				case LEFT:
					hands[i]->dir = LEFT;
					break;
				case RIGHT:
					hands[i]->dir = RIGHT;
					break;
				case NONE:
					break;
				default:
					break;
				}

				break;
			}
		}

		accumulator -= timeSpawn;
	}
}

void Oranges::checkHandsOut()
{
	for (int i = 0; i < sizeHands; i++)
	{
		if (hands[i])
		{
			if (hands[i]->dest.x + hands[i]->dest.w < 0 ||
				hands[i]->dest.x > width ||
				hands[i]->dest.y + hands[i]->dest.h < 0 ||
				hands[i]->dest.y > height)
			{
				SDL_DestroyTexture(hands[i]->texture);
				delete hands[i];
				hands[i] = nullptr;
			}
		}
	}
}

void Oranges::destroyHandsIndex(int index)
{
	if (hands[index])
	{
		SDL_DestroyTexture(hands[index]->texture);
		delete hands[index];
		hands[index] = nullptr;
	}
}

int Oranges::getHP()
{
	return HP;
}
