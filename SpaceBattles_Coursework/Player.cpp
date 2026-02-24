#include "Player.h"

Player::Player(SDL_Renderer* renderer)
{
	texture = IMG_LoadTexture(renderer, "assets/entity/player/player_atlas.png");
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	src = {0, 0, 8, 16};
	dest = { 0, 0, src.w * 4, src.h * 4  };
	speed = 1;
}

Player::~Player()
{
	SDL_DestroyTexture(texture);

}

void Player::update()
{
	if (up) {
		dest.y -= speed;
	}
	if (down) {
		dest.y += speed;
	}
	if (left) {
		dest.x -= speed;
	}
	if (right) {
		dest.x += speed;
	}
}

void Player::draw(SDL_Renderer* renderer)
{
	SDL_RenderTexture(renderer, texture, &src, &dest);
}
