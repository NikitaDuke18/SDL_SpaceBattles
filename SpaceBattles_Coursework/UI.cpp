#include "UI.h"

UI::UI(SDL_Renderer* renderer, int width, int height, TTF_Font* font, Player* player)
{
	this->renderer = renderer;
	scale = 5;
	textColorWhite = { 255, 255, 255, 255 };
	this->font = font;
	this->player = player;

	initialize(renderer, width, height, font);
}

UI::~UI()
{
	// BAR
	SDL_DestroyTexture(bar);
	
	// SCORE
	SDL_DestroyTexture(score);

	// HEALTH
	SDL_DestroyTexture(health.textureImg);
	SDL_DestroyTexture(health.textureText);

	// BOMB
	SDL_DestroyTexture(bomb.textureImg);
	SDL_DestroyTexture(bomb.textureText);
}

void UI::initialize(SDL_Renderer* renderer, int width, int height, TTF_Font* font)
{
	// BAR
	bar = IMG_LoadTexture(renderer, "assets/ui/bar.png");
	SDL_SetTextureScaleMode(bar, SDL_SCALEMODE_NEAREST);
	barDest.w = width;
	barDest.h = 22 * scale;
	barDest.x = 0;
	barDest.y = height - barDest.h;

	// SCORE
	textSurface = TTF_RenderText_Blended(font, ("SCORE: " + std::to_string(player->getScore())).c_str(), 0, textColorWhite);
	score = SDL_CreateTextureFromSurface(renderer, textSurface);
	scoreDest = { 10, 10, (float)score->w, (float)score->h};

	SDL_DestroySurface(textSurface);

	// HEALTH
	health.textureImg = IMG_LoadTexture(renderer, "assets/ui/health.png");
	SDL_SetTextureScaleMode(health.textureImg, SDL_SCALEMODE_NEAREST);

	health.text = std::to_string(player->getHP());
	textSurface = TTF_RenderText_Blended(font, health.text.c_str(), 0, textColorWhite);
	health.textureText = SDL_CreateTextureFromSurface(renderer, textSurface);

	health.destImg = {barDest.x + 60, barDest.y + 35, (float)8 * scale, (float)7 * scale};
	health.destText = { health.destImg.x + 60, health.destImg.y, (float)health.textureText->w, (float)health.textureText->h };

	SDL_DestroySurface(textSurface);

	// BOMB
	bomb.textureImg = IMG_LoadTexture(renderer, "assets/ui/bomb.png");
	SDL_SetTextureScaleMode(bomb.textureImg, SDL_SCALEMODE_NEAREST);

	bomb.text = std::to_string(player->getBomb());
	textSurface = TTF_RenderText_Blended(font, bomb.text.c_str(), 0, textColorWhite);
	bomb.textureText = SDL_CreateTextureFromSurface(renderer, textSurface);

	bomb.destImg = { barDest.w - 160, barDest.y + 40, (float)6 * scale, (float)7 * scale };
	bomb.destText = { bomb.destImg.x + 60, bomb.destImg.y - 5, (float)bomb.textureText->w, (float)bomb.textureText->h };
}

void UI::setup()
{
	updateHP();
	updateScore();
}

void UI::update()
{

}

void UI::draw(SDL_Renderer* renderer)
{
	// BAR
	SDL_RenderTexture(renderer, bar, NULL, &barDest);
	
	// SCORE
	SDL_RenderTexture(renderer, score, NULL, &scoreDest);

	// HEALTH
	health.draw(renderer);

	// BOMB
	bomb.draw(renderer);
}

void UI::updateHP()
{
	if (health.textureText)
	{
		SDL_DestroyTexture(health.textureText);
	}

	health.text = std::to_string(player->getHP());
	textSurface = TTF_RenderText_Blended(font, health.text.c_str(), 0, textColorWhite);
	health.textureText = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_DestroySurface(textSurface);
}

void UI::updateScore()
{
	if (score)
	{
		SDL_DestroyTexture(score);
	}

	textSurface = TTF_RenderText_Blended(font, ("SCORE: " +  std::to_string(player->getScore())).c_str(), 0, textColorWhite);
	score = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_DestroySurface(textSurface);
}
