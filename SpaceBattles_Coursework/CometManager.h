#pragma once

#include "Comet.h"

enum CometType
{
	COMET_1,
	COMET_2,
	COMET_3,
	COMET_4,
	COMET_5,
	COMET_COUNT
};

class CometManager
{
public:
	CometManager(SDL_Renderer* renderer, const int maxCountComets, const int iterateSpawnInSeconds, int windowWidth, int windowHeight);
	~CometManager();

	void setup();

	void update();
	void draw();

	void createRandomComet();
	void deleteComet(int id);

	void spawnComet(int iterateSpawnInSeconds);
	bool checkCometsOut(int id);
	bool cometExists(int id);

	int getSize() { return size; };
	void setSize(int size) { this->size = size; };

	Comet* getComet(int id) { return comets[id]; };
	SDL_FRect getCometDest(int id) { return comets[id]->getDest(); };
private:
	SDL_Renderer* renderer;
	Comet** comets;
	int size;
	int windowWidth;
	int windowHeight;

	int iterateSpawnInSeconds;

	int updateCount = 0;
};

