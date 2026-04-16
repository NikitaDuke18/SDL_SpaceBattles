#pragma once

#include <SDL3/SDL.h>
#include "SceneManager.h"
//#include "Battle.h"
//#include "Player.h"
#include "SaveLoad.h"

class InputHandler
{
public:
	InputHandler(SDL_Renderer* renderer, SceneManager* sceneManager, Battle* battle, Player* player, SaveLoad* saveLoad);
	~InputHandler();

	void keyDown();
	void keyUp();

private:
	SDL_Renderer* renderer;
	SceneManager* sceneManager;
	Battle* battle;
	Player* player = nullptr;
	SaveLoad* saveLoad;

	Uint64 lastKeyPressTime;
	Uint64 delayMS;

	int updateCount;
	bool enterDown = false;
	bool* quit;
};

