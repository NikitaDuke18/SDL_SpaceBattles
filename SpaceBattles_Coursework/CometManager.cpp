#include "CometManager.h"

CometManager::CometManager(SDL_Renderer* renderer, const int maxCountComets, const int iterateSpawnInSeconds, int windowWidth, int windowHeight)
{
	this->renderer = renderer;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	this->size = maxCountComets;
	this->comets = new Comet*[this->size];

	for (int i = 0; i < this->size; i++)
	{
		comets[i] = nullptr;
	}

	this->iterateSpawnInSeconds = iterateSpawnInSeconds;
}

CometManager::~CometManager()
{
	// Delete comets
	for (int i = 0; i < size; i++)
	{
		if (comets[i])
		{
			delete comets[i];
			comets[i] = nullptr;
		}
	}
	delete[] comets;
}

void CometManager::setup()
{
	for (int i = 0; i < size; i++)
	{
		if (comets[i])
		{
			delete comets[i];
			comets[i] = nullptr;
		}
	}
}

void CometManager::update()
{
	spawnComet(iterateSpawnInSeconds);

	for (int i = 0; i < size; i++)
	{
		if (comets[i] != nullptr)
		{
			comets[i]->update();

			if (checkCometsOut(i))
			{
				delete comets[i];
				comets[i] = nullptr;
			}
		}
	}
}

void CometManager::draw()
{
	for (int i = 0; i < size; i++)
	{
		if (comets[i])
		{
			comets[i]->draw(renderer);
		}
	}
}

void CometManager::createRandomComet()
{
	int findIdToCreate = -1;

	// »щем где можно создать комету
	for (int i = 0; i < size; i++)
	{
		if (!comets[i])
		{
			findIdToCreate = i;
			break;
		}
	}

	if (findIdToCreate != -1)
	{
		int choice = SDL_rand(COMET_COUNT);
		SDL_FRect src;
		SDL_FRect dest;
		int scale = 4;

		switch (choice)
		{
		case COMET_1:
			src = { 0, 0, 6, 5 };
			dest = { SDL_rand(windowWidth - src.w * scale) * 1.0F, 0 - SDL_rand(windowHeight) - src.h * scale, src.w * scale, src.h * scale };

			comets[findIdToCreate] = new Comet(renderer, src, dest, "assets/entity/comets/comet_1.png", 2);
			break;
		case COMET_2:
			src = { 0, 0, 7, 7 };
			dest = { SDL_rand(windowWidth - src.w * scale) * 1.0F, 0 - SDL_rand(windowHeight) - src.h * scale, src.w * scale, src.h * scale };

			comets[findIdToCreate] = new Comet(renderer, src, dest, "assets/entity/comets/comet_2.png", 2);
			break;
		case COMET_3:
			src = { 0, 0, 11, 9 };
			dest = { SDL_rand(windowWidth - src.w * scale) * 1.0F, 0 - SDL_rand(windowHeight) - src.h * scale, src.w * scale, src.h * scale };

			comets[findIdToCreate] = new Comet(renderer, src, dest, "assets/entity/comets/comet_3.png", 1);
			break;
		case COMET_4:
			src = { 0, 0, 12, 12 };
			dest = { SDL_rand(windowWidth - src.w * scale) * 1.0F, 0 - SDL_rand(windowHeight) - src.h * scale, src.w * scale, src.h * scale };

			comets[findIdToCreate] = new Comet(renderer, src, dest, "assets/entity/comets/comet_4.png", 1);
			break;
		case COMET_5:
			src = { 0, 0, 16, 8 };
			dest = { SDL_rand(windowWidth - src.w * scale) * 1.0F, 0 - SDL_rand(windowHeight) - src.h * scale, src.w * scale, src.h * scale };

			comets[findIdToCreate] = new Comet(renderer, src, dest, "assets/entity/comets/comet_5.png", 1);
			break;
		default:
			SDL_Log("Error: Problem with createRandomComet() in CometManager");
			break;
		}
	}
}

void CometManager::deleteComet(int id)
{
	if (comets[id])
	{
		delete comets[id];
		comets[id] = nullptr;
	}
}

void CometManager::spawnComet(int iterateSpawnInSeconds)
{
	updateCount++;

	if (updateCount >= iterateSpawnInSeconds)
	{
		createRandomComet();
		updateCount = 0;
	}
}

bool CometManager::checkCometsOut(int id)
{
	if (comets[id]->getDest().y > 800 + comets[id]->getDest().h) {
		return true;
	}

	return false;
}

bool CometManager::cometExists(int id)
{
	if (comets[id])
	{
		return true;
	}
	return false;
}