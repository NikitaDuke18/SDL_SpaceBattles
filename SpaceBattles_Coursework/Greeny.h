#pragma once

#include "Entity.h"

struct Bubbles
{
	SDL_Texture* texture;
	SDL_FRect dest;
	int scale = 4;

	void update()
	{
		dest.y += 1;
	}

	void draw(SDL_Renderer* renderer)
	{
		SDL_RenderTexture(renderer, texture,NULL, &dest);
	}
};

class Greeny : public Entity
{
public:
	Greeny(SDL_Renderer* renderer, int width, int height);
	~Greeny();

	void setup();

	void update();
	void draw();

	void lostHP(int damage);

	void createBubbles();
	void destroyBubbles();
	void destroyBubblesIndex(int index);

	int getSizeBubbles() { return sizeBubbles; };
	Bubbles* getBubbles(int index) { return bubbles[index]; };

	int getHP() { return HP; };
private:
	SDL_Renderer* renderer;
	int width;
	int height;
	int HP;
	const int sizeBubbles = 10;
	Bubbles* bubbles[10];
	Uint64 lastTime;
	Uint64 accumulator; 
	Uint64 timeSpawn;
};