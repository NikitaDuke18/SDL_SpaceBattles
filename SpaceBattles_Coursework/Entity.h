#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

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

protected:
	SDL_Texture* texture;
	SDL_FRect src;
	SDL_FRect dest;
	int scale;
	int speed;
};

