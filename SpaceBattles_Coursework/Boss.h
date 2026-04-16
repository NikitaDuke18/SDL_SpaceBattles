#pragma once

#include "Entity.h"

struct Blaster
{
	SDL_Texture* texture;
	SDL_FRect dest;
	int scale = 4;
	int speed = 2;
	int damage;
	float angle; // 45

	void update()
	{
		if (angle > 0)
		{
			dest.x -= speed;
			
		}
		else if (angle < 0)
		{
			dest.x += speed;
		}

		dest.y += speed;
	}

	void draw(SDL_Renderer* renderer)
	{
		SDL_RenderTextureRotated(renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
	}
};

class Boss : public Entity
{
public:
	Boss(SDL_Renderer* renderer, int width, int height);
	~Boss();

	void setup();

	void update();
	void draw();

	void lostHP(int damage);

	void createBlaster();
	void checkOutBlaster();
	void deleteBlasterIndex(int index);

	int getSizeBlasters() { return sizeBlasters; };
	int getHP() { return HP; };
	Blaster* getBlaster(int index) { return blasters[index]; };
private:
	SDL_Renderer* renderer;
	int width;
	int height;
	int HP;
	bool changePosition;

	int sizeBlasters;
	Blaster** blasters;

	Uint64 lastTime;
	Uint64 accumulator;
	Uint64 timeSpawn;
};