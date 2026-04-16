#pragma once

#include "Entity.h"

enum Diagonal
{
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};

struct HandBomb
{
	SDL_Texture* texture;
	SDL_FRect dest;
	DIRECTION dir = NONE;
	int scale = 3;
	int speed = 2;
	int damage;

	void update()
	{
		switch (dir)
		{
		case UP:
			dest.y -= speed;
			break;
		case DOWN:
			dest.y += speed;
			break;
		case LEFT:
			dest.x -= speed;
			break;
		case RIGHT:
			dest.x += speed;
			break;
		case NONE:
			break;
		default:
			break;
		}
	}

	void draw(SDL_Renderer* renderer)
	{
		SDL_RenderTexture(renderer, texture, NULL, &dest);
	}
};

class BrotherGreeny : public Entity
{
public:
	BrotherGreeny(SDL_Renderer* renderer, int width, int height);
	~BrotherGreeny();

	void setup();

	void update();
	void draw();

	void lostHP(int damage);
	void spawnHandBomb();
	void checkHandBombOut();
	void destroyHandBombIndex(int index);

	int getHP() { return HP; };
	int getSizeHandBombs() { return sizeHandBombs; };
	HandBomb* getHandBomb(int index) { return handBombs[index]; };
private:
	SDL_Renderer* renderer;
	int width;
	int height;

	int HP;
	int angle;

	int sizeHandBombs;
	HandBomb** handBombs;

	Diagonal direction;
	bool changeDir;

	Uint64 lastTime;
	Uint64 accumulator;
	Uint64 timeSpawn;
};

