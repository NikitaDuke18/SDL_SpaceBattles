#pragma once

#include <SDL3/SDL.h>
#include "Player.h"

class InputHandler
{
public:
	InputHandler(Player* player);
	~InputHandler();

	void keyDown();
	void keyUp();

private:
	Player* player = nullptr;

};

