#include "InputHandler.h"

InputHandler::InputHandler(Player* player)
{
	this->player = player;
}

InputHandler::~InputHandler()
{
}

void InputHandler::keyDown()
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
}

void InputHandler::keyUp()
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
}
