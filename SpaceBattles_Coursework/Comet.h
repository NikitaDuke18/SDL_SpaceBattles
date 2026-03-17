#pragma once

#include "Entity.h"

class Comet : public Entity
{
public:
	Comet();
	Comet(SDL_Renderer* renderer, SDL_FRect src, SDL_FRect dest, const char* path, int score);
	~Comet();

	void update();
	void draw(SDL_Renderer* renderer);

private:
	int score;

};

