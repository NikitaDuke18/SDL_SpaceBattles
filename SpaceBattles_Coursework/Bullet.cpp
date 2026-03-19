#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* renderer, SDL_FPoint position, BulletType type)
{
	scale = 4;
	initializeBullet(renderer, type);
	dest.x = position.x;
	dest.y = position.y;
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
}

Bullet::~Bullet()
{
	SDL_DestroyTexture(texture);
	SDL_Log("Bullet destroy");
}

void Bullet::initializeBullet(SDL_Renderer* renderer, BulletType type)
{
	switch (type)
	{
	case BULLET_1:
		texture = IMG_LoadTexture(renderer, "assets/entity/bullets/default/bullet_1.png");
		src = { 0, 0, 2, 3 };
		dest.w = src.w * scale;
		dest.h = src.h * scale;
		damage = 1;
		break;
	case BULLET_2:
		texture = IMG_LoadTexture(renderer, "assets/entity/bullets/default/bullet_2.png");
		src = { 0, 0, 4, 4 };
		dest.w = src.w * scale;
		dest.h = src.h * scale;
		damage = 5;
		break;
	case BULLET_3:
		texture = IMG_LoadTexture(renderer, "assets/entity/bullets/default/bullet_3.png");
		src = { 0, 0, 8, 8 };
		dest.w = src.w * scale;
		dest.h = src.h * scale;
		damage = 15;
		break;
	default:
		break;
	}
}

void Bullet::update()
{
	dest.y -= 1;
}

void Bullet::draw(SDL_Renderer* renderer)
{
	SDL_RenderTexture(renderer, texture, &src, &dest);
}
