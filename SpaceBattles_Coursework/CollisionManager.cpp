#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

bool CollisionManager::checkCollisionRect(SDL_FRect entity1, SDL_FRect entity2)
{
	if (entity1.x + entity1.w > entity2.x &&
		entity1.x < entity2.x + entity2.w &&
		entity1.y + entity1.h > entity2.y &&
		entity1.y < entity2.y + entity2.h)
	{
		return true;
	}
	return false;
}
