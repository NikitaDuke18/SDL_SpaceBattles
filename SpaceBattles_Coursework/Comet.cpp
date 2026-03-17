#include "Comet.h"

Comet::Comet()
{
}

Comet::Comet(SDL_Renderer* renderer, SDL_FRect src, SDL_FRect dest, const char* path, int score)
{
	this->src = src;
	this->dest = dest;
	texture = IMG_LoadTexture(renderer, path);
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	this->score = score;
}

Comet::~Comet()
{
	SDL_DestroyTexture(texture);
}

void Comet::update()
{
	dest.y += 1;
}

void Comet::draw(SDL_Renderer* renderer)
{
	SDL_RenderTexture(renderer, texture, &src, &dest);
}
