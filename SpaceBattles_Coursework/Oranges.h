#pragma once

#include "Entity.h"
//#include "Player.h"
#include "UI.h"

struct Hands
{
	SDL_Texture* texture;
	SDL_FRect dest;	
	DIRECTION dir = NONE;
	int scale = 3;
	int speed = 2;

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

class Oranges : public Entity
{
public:
	Oranges(SDL_Renderer* renderer, UI* ui, int width, int height);
	~Oranges();

	void setup();

	void update();
	void draw();

	void lostHP(int damage);
	void createHands();
	void checkHandsOut();
	void destroyHandsIndex(int index);

	int getHP();
	int getSizeHands() { return sizeHands; };
	Hands* getHands(int index) { return hands[index]; };
private:
	SDL_Renderer* renderer;
	UI* ui;
	DIRECTION direction;
	int width;
	int height;
	int HP;
	float angle = 0;

	int sizeHands = 10;
	Hands* hands[10];

	Uint64 lastTime;
	Uint64 accumulator;
	Uint64 timeSpawn;
};