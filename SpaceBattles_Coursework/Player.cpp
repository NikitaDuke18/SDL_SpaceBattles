#include "Player.h"

Player::Player(SDL_Renderer* renderer)
{
	texture = IMG_LoadTexture(renderer, "assets/entity/player/player_atlas.png");
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	src = {0, 0, 8, 16};
	scale = 4;
	dest = { 0, 0, src.w * scale, src.h * scale };
	speed = 4;
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

	animationPlay();
}

void Player::draw(SDL_Renderer* renderer)
{
	SDL_RenderTexture(renderer, texture, &src, &dest);
}

void Player::animationPlay()
{
	if (left)
	{
		src.x = 0; // firstTexture
	}
	else if (right)
	{
		src.x = 8; // second Texture
	}
	else if (up || down)
	{
		src.x = 16; // third Texture
	}
}
