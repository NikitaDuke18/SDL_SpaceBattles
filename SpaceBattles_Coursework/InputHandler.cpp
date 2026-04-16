#include "InputHandler.h"

InputHandler::InputHandler(SDL_Renderer* renderer, SceneManager* sceneManager, Battle* battle, Player* player, SaveLoad* saveLoad)
{
	this->renderer = renderer;
	this->sceneManager = sceneManager;
	this->battle = battle;
	this->player = player;
	this->saveLoad = saveLoad;

	lastKeyPressTime = 0;
	delayMS = 200;

	this->updateCount = 0;
}

InputHandler::~InputHandler()
{
}

void InputHandler::keyDown()
{

	const bool* keys = SDL_GetKeyboardState(NULL);

	Uint64 currentTime = SDL_GetTicks();

	switch (sceneManager->getCurrentScene())
	{
	case MENU:
		if (keys[SDL_SCANCODE_UP])
		{
			if (currentTime > lastKeyPressTime + delayMS) {
				sceneManager->nextChoice();
				lastKeyPressTime = currentTime;
			}
		}
		else if (keys[SDL_SCANCODE_DOWN])
		{
			if (currentTime > lastKeyPressTime + delayMS) {
				sceneManager->previousChoice();
				lastKeyPressTime = currentTime;
			}
		}

		if (keys[SDL_SCANCODE_RETURN])
		{
			if (currentTime > lastKeyPressTime + delayMS) {
				sceneManager->nextScene();
				lastKeyPressTime = currentTime;
			}
		}
		break;
	case SETTINGS:
		if (keys[SDL_SCANCODE_ESCAPE])
		{
			if (currentTime > lastKeyPressTime + delayMS) {
				sceneManager->previousScene();
				lastKeyPressTime = currentTime;
			}
		}
		break;
	case CHOOSE_BATTLE:
		if (keys[SDL_SCANCODE_LEFT])
		{
			if (currentTime > lastKeyPressTime + delayMS) {
				sceneManager->nextChoice();
				lastKeyPressTime = currentTime;
			}
		}
		else if (keys[SDL_SCANCODE_RIGHT])
		{
			if (currentTime > lastKeyPressTime + delayMS) {
				sceneManager->previousChoice();
				lastKeyPressTime = currentTime;
			}
		}

		if (keys[SDL_SCANCODE_RETURN])
		{

			if (currentTime > lastKeyPressTime + delayMS) {
				sceneManager->nextScene();
				lastKeyPressTime = currentTime;
			}
		}

		if (keys[SDL_SCANCODE_ESCAPE])
		{
			if (currentTime > lastKeyPressTime + delayMS) {
				sceneManager->previousScene();
				lastKeyPressTime = currentTime;
			}
		}
		break;
	case MAP_BATTLE:
		if (keys[SDL_SCANCODE_LEFT])
		{
			if (currentTime > lastKeyPressTime + delayMS) {
				sceneManager->nextChoice();
				lastKeyPressTime = currentTime;
			}
		}
		else if (keys[SDL_SCANCODE_RIGHT])
		{
			if (currentTime > lastKeyPressTime + delayMS) {
				sceneManager->previousChoice();
				lastKeyPressTime = currentTime;
			}
		}

		if (keys[SDL_SCANCODE_RETURN])
		{

			if (currentTime > lastKeyPressTime + delayMS) {
				SDL_Log("LEVELS: WILL BE CREATED");
				lastKeyPressTime = currentTime;
			}
		}

		if (keys[SDL_SCANCODE_ESCAPE])
		{
			if (currentTime > lastKeyPressTime + delayMS) {
				sceneManager->previousScene();
				lastKeyPressTime = currentTime;
			}
		}
		break;
	case BATTLE:
		if (!battle->getGameOver())
		{
			if (!battle->getPause())
			{
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
			else
			{
				if (keys[SDL_SCANCODE_ESCAPE])
				{
					saveLoad->savePlayer(player);
					sceneManager->changeScene(MENU);
				}
			}

			if (keys[SDL_SCANCODE_K])
			{
				battle->changePause();
				SDL_Delay(200);
			}
		}
		else
		{
			if (keys[SDL_SCANCODE_SPACE])
			{
				saveLoad->deletePlayerTXT();
				saveLoad->saveMaxScore(player);
				sceneManager->changeScene(MENU);
			}
		}
		break;
	default:
		break;
	}
}

void InputHandler::keyUp()
{
	if (!battle->getGameOver())
	{
		const bool* keys = SDL_GetKeyboardState(NULL);

		if (!battle->getPause())
		{
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
}