#pragma once

#include "Entity.h"
#include "UI.h"

struct Ray
{
	SDL_FRect dest;
	SDL_Color color = {0, 0, 0, 0};
	int damage = 2;
	bool attack = false;

	Uint64 lastTime;
	Uint64 accumulator;
	Uint64 timeChangeColor = 1000000; // 1000000000 = 1 sec

	void update(int& speed)
	{
		attack = false;
		speed = 0;

		Uint64 currentTime = SDL_GetTicksNS();

		accumulator += currentTime - lastTime;

		lastTime = currentTime;

		if (accumulator > timeChangeColor)
		{
			if (color.g < 255 && color.r < 255)
			{
				color.g += 5;
			}
			else if (color.g == 255 && color.r < 255)
			{
				color.r += 5;
			}
			else if (color.g > 0)
			{
				color.g -= 5;

				if (color.g < 5)
				{
					attack = true;
				}
			}
			else
			{
				accumulator = 0;
				speed = 2;
			}

			if (color.a < 255)
			{
				color.a += 1;
			}
		}
	}

	void draw(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &dest);
	}
};

class Void : public Entity
{
public:
	Void(SDL_Renderer* renderer, int width, int height, UI* ui);
	~Void();

	void setup();

	void update();
	void draw();

	void lostHP(int damage);
	void createRay();

	int getHP() { return HP; };
	Ray* getRay() { return ray; };
private:
	SDL_Renderer* renderer;
	UI* ui;
	int width;
	int height;
	DIRECTION dir;
	float angle;
	int positionAttack;
	bool changePosition;
	int HP;

	Ray* ray;

	Uint64 lastTime;
	Uint64 accumulator;
	Uint64 timeSpawn;
};