#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

struct Text
{
	SDL_Texture* texture;
	std::string text;
	SDL_FRect dest;

	void initialize(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color)
	{
		SDL_Surface* surface;

		surface = TTF_RenderText_Blended(font, text.c_str(), 0, color);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		dest.w = texture->w;
		dest.h = texture->h;

		SDL_DestroySurface(surface);
	}

	void initialize(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_FPoint point)
	{
		initialize(renderer, font, color);
		this->dest.x = point.x;
		this->dest.y = point.y;
	}

	void destroyTexture()
	{
		if (texture)
		{
			SDL_DestroyTexture(texture);
		}
	}
};