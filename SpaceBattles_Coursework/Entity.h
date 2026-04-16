#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

class Entity
{
public:
	virtual ~Entity() = default;

	virtual void update();
	virtual void draw(SDL_Renderer* renderer);

	SDL_FRect getDest();
	void setDest(SDL_FRect* rect);

	int getScale() { return scale; };
	void setScale(int scale) { this->scale = scale; };

	int getSpeed();
	void setSpeed(int speed);

	void setPosition(SDL_FPoint position) { dest.x = position.x; dest.y = position.y; };

protected:
	SDL_Texture* texture;
	SDL_FRect src;
	SDL_FRect dest;
	int scale;
	int speed;
};

