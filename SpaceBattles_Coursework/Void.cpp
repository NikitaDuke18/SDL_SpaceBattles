#include "Void.h"

Void::Void(SDL_Renderer* renderer, int width, int height, UI* ui)
{
	this->renderer = renderer;
	this->width = width;
	this->height = height;
	this->ui = ui;

	this->scale = 5;
	this->texture = IMG_LoadTexture(renderer, "assets/entity/enemy/boss/Void.png");
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	this->dest = { 0, 0, this->scale * 14.0F, this->scale * 13.0F };
	this->dest.x -= this->dest.w;

	this->speed = 2;
	this->positionAttack = SDL_rand(width - dest.w);
	this->changePosition = false;
	this->HP = 40;
	this->dir = RIGHT;
	this->angle = 0;
}

Void::~Void()
{
	if (ray)
	{
		delete ray;
	}
}

void Void::setup()
{
	this->scale = 5;
	this->dest = { 0, 0, this->scale * 14.0F, this->scale * 13.0F };
	this->dest.x -= this->dest.w;

	this->speed = 2;
	this->positionAttack = SDL_rand(width - dest.w);
	this->changePosition = false;
	this->HP = 40;
	this->dir = RIGHT;
	this->angle = 0;
}

void Void::update()
{
	if (ray)
	{
		ray->update(speed);

		if (speed != 0)
		{
			delete ray;
			ray = nullptr;
			positionAttack = SDL_rand(width);
			changePosition = true;
		}
	}
	
	switch (dir)
	{
	case LEFT:
		dest.x -= speed;
		break;
	case RIGHT:
		dest.x += speed;
		break;
	case NONE:
		break;
	default:
		break;
	}

	if (dest.x > width)
	{
		dest.x = width;
		dest.y = ui->getBarDest().y - dest.h;
		angle = 180;
		dir = LEFT;
		changePosition = false;
	}
	else if (dest.x + dest.w < 0)
	{
		dest.x = 0 - dest.w;
		dest.y = 0;
		angle = 0;
		dir = RIGHT;
		changePosition = false;
	}

	if (!changePosition)
	{
		if (dest.x >= positionAttack && dir == RIGHT)
		{
			createRay();
			changePosition = true;
		}
		if (dest.x <= positionAttack && dir == LEFT)
		{
			createRay();
			changePosition = true;
		}
	}
}

void Void::draw()
{
	if (ray)
	{
		ray->draw(renderer);
	}

	SDL_RenderTextureRotated(renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}

void Void::lostHP(int damage)
{
	this->HP -= damage;
}

void Void::createRay()
{
	ray = new Ray();
	if (dir == RIGHT)
	{
		ray->dest = { dest.x, dest.y + dest.h, dest.w, height * 1.0F };
	}
	else if (dir == LEFT)
	{
		ray->dest = { dest.x, 0, dest.w, dest.y };
	}
}