#pragma once

#include <SDL3/SDL.h>
#include "Battle.h"
#include "Player.h"

class InputHandler
{
public:
	InputHandler(SDL_Renderer* renderer, Battle* battle, Player* player);
	~InputHandler();

	void keyDown();
	void keyUp();

private:
	SDL_Renderer* renderer;
	Battle* battle;
	Player* player = nullptr;
	
	int updateCount;
	bool enterDown = false;
};

