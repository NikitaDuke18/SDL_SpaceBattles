#include "Entity.h"

void Entity::update()
{
}

void Entity::draw(SDL_Renderer* renderer)
{
}

SDL_FRect Entity::getDest()
{
	return dest;
}

void Entity::setDest(SDL_FRect* rect)
{
	this->dest = dest;
}

int Entity::getSpeed()
{
	return speed;
}

void Entity::setSpeed(int speed)
{
	this->speed = speed;
}
