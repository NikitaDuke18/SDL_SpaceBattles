#pragma once

#include "Entity.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	bool checkCollisionRect(SDL_FRect entity1, SDL_FRect entity2);

private:


};