#pragma once

#include "Entity.h"

/*
* 1 - пуля наносит 1 урон
* 2 - пуля наносит 5 урона
* 3 - пуля наносит 15 урона
*/
enum BulletType
{
	BULLET_1, 
	BULLET_2,
	BULLET_3
};

class Bullet : public Entity
{
public:
	Bullet(SDL_Renderer* renderer, SDL_FPoint position, BulletType type);
	~Bullet();

	void initializeBullet(SDL_Renderer* renderer, BulletType type);

	void update() override;
	void draw(SDL_Renderer* renderer) override;

	int getDamage() { return damage; };

private:
	int damage;
};

