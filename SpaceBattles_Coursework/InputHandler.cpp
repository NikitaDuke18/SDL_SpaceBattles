#include "InputHandler.h"

InputHandler::InputHandler(SDL_Renderer* renderer, Battle* battle, Player* player)
{
	this->renderer = renderer;
	this->battle = battle;
	this->player = player;
	this->updateCount = 0;
}

InputHandler::~InputHandler()
{
}

void InputHandler::keyDown()
{
	if (!battle->getGameOver())
	{
		const bool* keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_SCANCODE_W]) {
			player->setUp(true);
		}
		if (keys[SDL_SCANCODE_S]) {
			player->setDown(true);
		}
		if (keys[SDL_SCANCODE_A]) {
			player->setLeft(true);
		}
		if (keys[SDL_SCANCODE_D]) {
			player->setRight(true);
		}

		if (keys[SDL_SCANCODE_RETURN])
		{
			updateCount++;
			enterDown = true;
		}
	}
	
}

void InputHandler::keyUp()
{
	if (!battle->getGameOver())
	{
		const bool* keys = SDL_GetKeyboardState(NULL);

		if (!keys[SDL_SCANCODE_W]) {
			player->setUp(false);
		}
		if (!keys[SDL_SCANCODE_S]) {
			player->setDown(false);
		}
		if (!keys[SDL_SCANCODE_A]) {
			player->setLeft(false);
		}
		if (!keys[SDL_SCANCODE_D]) {
			player->setRight(false);
		}

		if (!keys[SDL_SCANCODE_RETURN] && enterDown)
		{
			if (updateCount >= 10)
			{
				player->shoot(renderer, updateCount / 120);
				updateCount = 0;
			}
			enterDown = false;
		}
	}
}