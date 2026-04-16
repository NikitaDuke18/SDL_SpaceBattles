#include "Greeny.h"

Greeny::Greeny(SDL_Renderer* renderer, int width, int height)
{
	this->renderer = renderer;
	this->width = width;
	this->height = height;

	texture = IMG_LoadTexture(renderer, "assets/entity/enemy/boss/Greeny.png");
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

	scale = 5; // Boss
	dest = {width / 2.0F - texture->w / 2, (float)0 - (texture->h * scale * 2), 14.0F * scale, 14.0F * scale};
	speed = 4;
	HP = 30;

	for (int i = 0; i < sizeBubbles; i++)
	{
		bubbles[i] = nullptr;
	}

	timeSpawn = 1500000000;
	accumulator = 0;
}

Greeny::~Greeny()
{
	for (int i = 0; i < sizeBubbles; i++)
	{
		if (bubbles[i])
		{
			SDL_DestroyTexture(bubbles[i]->texture);
			delete bubbles[i];
			bubbles[i] = nullptr;
		}
	}

	SDL_DestroyTexture(texture);
}

void Greeny::setup()
{
	dest.x = width / 2.0F - texture->w / 2;
	dest.y = (float)0 - (texture->h * scale * 2);
	HP = 30;
	speed = 3;

	for (int i = 0; i < sizeBubbles; i++)
	{
		if (bubbles[i])
		{
			SDL_DestroyTexture(bubbles[i]->texture);
			delete bubbles[i];
			bubbles[i] = nullptr;
		}
	}

	accumulator = 0;
}

void Greeny::update()
{
	for (int i = 0; i < sizeBubbles; i++)
	{
		if (bubbles[i])
		{
			bubbles[i]->update();
		}
	}

	if (dest.y < 75)
	{
		dest.y += 1;
		lastTime = SDL_GetTicksNS();
	}
	else
	{
		if (dest.x > 800 - dest.w || dest.x < 0)
		{
			speed *= -1;
		}

		dest.x += speed;

		createBubbles();
	}

	destroyBubbles();
}

void Greeny::draw()
{
	for (int i = 0; i < sizeBubbles; i++)
	{
		if (bubbles[i])
		{
			bubbles[i]->draw(renderer);
		}
	}

	SDL_RenderTexture(renderer, texture, NULL, &dest);
}

void Greeny::lostHP(int damage)
{
	this->HP -= damage;
}

void Greeny::createBubbles()
{
	Uint64 currentTime = SDL_GetTicksNS();

	Uint64 deltaTime = currentTime - lastTime;

	accumulator += deltaTime;

	lastTime = currentTime;

	if (accumulator >= timeSpawn)
	{
		for (int i = 0; i < sizeBubbles; i++)
		{
			if (!bubbles[i])
			{
				bubbles[i] = new Bubbles();
				bubbles[i]->texture = IMG_LoadTexture(renderer, "assets/entity/bullets/enemy/bubble.png");
				SDL_SetTextureScaleMode(bubbles[i]->texture, SDL_SCALEMODE_NEAREST);
				bubbles[i]->dest = { dest.x + (float)SDL_rand(dest.w), dest.h, 4.0F * bubbles[i]->scale, 8.0F * bubbles[i]->scale};
				break;
			}
		}

		accumulator -= timeSpawn;
	}
}

void Greeny::destroyBubbles()
{
	for (int i = 0; i < sizeBubbles; i++)
	{
		if (bubbles[i])
		{
			if (bubbles[i]->dest.y >= height)
			{
				SDL_DestroyTexture(bubbles[i]->texture);
				delete bubbles[i];
				bubbles[i] = nullptr;

				//SDL_Log("ENEMY DESTROY");
			}
		}
	}
}

void Greeny::destroyBubblesIndex(int index)
{
	if (bubbles[index])
	{
		SDL_DestroyTexture(bubbles[index]->texture);
		delete bubbles[index];
		bubbles[index] = nullptr;
	}
}