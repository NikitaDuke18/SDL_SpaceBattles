#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "Player.h"

struct Items
{
	SDL_Texture* textureImg;
	SDL_Texture* textureText;
	SDL_FRect destImg;
	SDL_FRect destText;
	std::string text;

	void draw(SDL_Renderer* renderer)
	{
		SDL_RenderTexture(renderer, textureImg, NULL, &destImg);
		SDL_RenderTexture(renderer, textureText, NULL, &destText);
	}
};

class UI
{
public:
	UI(SDL_Renderer* renderer, int width, int height, TTF_Font* font, Player* player);
	~UI();

	void initialize(SDL_Renderer* renderer, int width, int height, TTF_Font* font);
	void setup();
	
	void update();
	void draw(SDL_Renderer* renderer);

	void updateHP();
	void updateScore();
private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Surface* textSurface;

	Items health;
	Items bomb;

	SDL_Texture* bar;
	SDL_FRect barDest;

	SDL_Texture* score;
	SDL_FRect scoreDest;

	SDL_Color textColorWhite;

	Player* player;

	int scale;
};