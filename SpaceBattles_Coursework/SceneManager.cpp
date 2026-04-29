#include "SceneManager.h"

SceneManager::SceneManager(SDL_Renderer* renderer, TTF_Font* font, bool* quit, int width, int height, Scene scene, Battle* battle)
{
	this->width = width;
	this->height = height;

	this->quit = quit;
	this->font = font;
	textColorWhite = { 255, 255, 255, 255 };

	this->currentChoice = 0;
	setupItems(renderer, font, width, height);
	
	this->currentScene = scene;
	this->battle = battle;

	this->music = new Audio("assets/musics/title--1-.mp3");
	this->music->loop();
	this->music->play();
}

SceneManager::~SceneManager()
{
	for (TextItem& item : menuItems)
	{
		SDL_DestroyTexture(item.texture);
	}

	for (TextItem& item : chooseBattleItems)
	{
		SDL_DestroyTexture(item.texture);
	}

	for (TextItem& item : settingsItems)
	{
		SDL_DestroyTexture(item.texture);
	}

	for (TextItem& item : mapBattleItems)
	{
		SDL_DestroyTexture(item.texture);
	}

	maxScoreRecord.destroyTexture();

	delete music;
	music = nullptr;
}

void SceneManager::setupItems(SDL_Renderer* renderer, TTF_Font* font, int width, int height)
{
	this->width = width;
	this->height = height;

	float startY;
	float startX;

	// MENU
	startY = 200.0f;
	for (TextItem& item : menuItems) {
		textSurface = TTF_RenderText_Blended(font, item.text.c_str(), 0, textColorWhite);
		item.texture = SDL_CreateTextureFromSurface(renderer, textSurface);

		item.dest = { (width - textSurface->w) / 2.0f, startY, (float)textSurface->w, (float)textSurface->h};

		startY += item.dest.h + 20.0f;
		SDL_DestroySurface(textSurface);
	}

	menuItems[currentChoice].isHovered = true;

	// CHOOSE BATTLE
	startX = 200.0f; 
	for (TextItem& item : chooseBattleItems) {
		textSurface = TTF_RenderText_Blended(font, item.text.c_str(), 0, textColorWhite);
		item.texture = SDL_CreateTextureFromSurface(renderer, textSurface);

		item.dest = { startX, (height - textSurface->h) / 2.0f, (float)textSurface->w, (float)textSurface->h };

		startX += item.dest.w + 50.0f;
		SDL_DestroySurface(textSurface);
	}

	chooseBattleItems[currentChoice].isHovered = true;

	// SETTINGS 
	startX = 50.0f;
	startY = 50.0f;
	for (TextItem& item : settingsItems)
	{
		textSurface = TTF_RenderText_Blended(font, item.text.c_str(), 0, textColorWhite);
		item.texture = SDL_CreateTextureFromSurface(renderer, textSurface);

		item.dest = { startX, startY, (float)textSurface->w, (float)textSurface->h };

		startY += item.dest.h + 50.0f;
		SDL_DestroySurface(textSurface);
	}

	// MAP
	startX = 0.0f;
	startY = 0.0f;
	for (TextItem& item : mapBattleItems)
	{
		textSurface = TTF_RenderText_Blended(font, item.text.c_str(), 0, textColorWhite);
		item.texture = SDL_CreateTextureFromSurface(renderer, textSurface);

		item.dest = { (width - textSurface->w + startX) / 2.0f, (height - textSurface->h) / 2.0f, (float)textSurface->w, (float)textSurface->h };

		startX += item.dest.w + 20.0f;
		SDL_DestroySurface(textSurface);
	}

	SaveLoad saveLoad; 
	int score = saveLoad.getMaxScore();
	maxScoreRecord.text = "YOUR MAX RECORD: " + std::to_string(score);
	maxScoreRecord.initialize(renderer, font, textColorWhite);
	maxScoreRecord.dest.x = maxScoreRecord.dest.w / 4;
	maxScoreRecord.dest.y = height - maxScoreRecord.dest.h * 2;
}

void SceneManager::update()
{
	switch (currentScene)
	{
	case MENU:
		break;
	case SETTINGS:
		break;
	case CHOOSE_BATTLE:
		break;
	case MAP_BATTLE:
		break;
	case BATTLE:
		battle->update();
		break;
	default:
		break;
	}
}

void SceneManager::draw(SDL_Renderer* renderer)
{
	switch (currentScene)
	{
	case MENU:
		for (TextItem& item : menuItems) {
			if (item.isHovered)
			{
				SDL_SetTextureColorMod(item.texture, 255, 255, 0);
			}
			else
			{
				SDL_SetTextureColorMod(item.texture, 255, 255, 255);
			}

			SDL_RenderTexture(renderer, item.texture, NULL, &item.dest);
		}

		SDL_RenderTexture(renderer, maxScoreRecord.texture, NULL, &maxScoreRecord.dest);
		
		break;
	case SETTINGS:
		for (TextItem& item : settingsItems) {
			SDL_RenderTexture(renderer, item.texture, NULL, &item.dest);
		}

		break;
	case CHOOSE_BATTLE:
		for (TextItem& item : chooseBattleItems) {
			if (item.isHovered)
			{
				SDL_SetTextureColorMod(item.texture, 255, 255, 0);
			}
			else
			{
				SDL_SetTextureColorMod(item.texture, 255, 255, 255);
			}

			SDL_RenderTexture(renderer, item.texture, NULL, &item.dest);
		}

		break;
	case MAP_BATTLE: {
		TextItem& item = mapBattleItems[0];
		TextItem& level = mapBattleItems[currentChoice];
	
		level.dest.x = mapBattleItems[1].dest.x;
		level.dest.y = mapBattleItems[1].dest.y;

		SDL_SetTextureColorMod(level.texture, 255, 255, 0);

		SDL_RenderTexture(renderer, item.texture, NULL, &item.dest);
		SDL_RenderTexture(renderer, level.texture, NULL, &level.dest);
		break;
	}
	case BATTLE:
		battle->draw();
		break;
	default:
		break;
	}
}

void SceneManager::updateScoreUI(SDL_Renderer* renderer)
{
	SaveLoad saveLoad;
	int score = saveLoad.getMaxScore();
	maxScoreRecord.text = "YOUR MAX RECORD: " + std::to_string(score);
	maxScoreRecord.initialize(renderer, font, textColorWhite);
	maxScoreRecord.dest.x = maxScoreRecord.dest.w / 4;
	maxScoreRecord.dest.y = height - maxScoreRecord.dest.h * 2;
}

void SceneManager::changeScene(Scene scene)
{
	this->currentScene = scene;

	switch (currentScene)
	{
	case MENU:
		currentChoice = 0;
		menuItems[currentChoice].isHovered = true;
		music->loadAudio("assets/musics/title--1-.mp3");
		music->play();
		break;
	case CHOOSE_BATTLE:
		break;
	case SETTINGS:
		break;
	case MAP_BATTLE:
		break;
	case BATTLE:
		break;
	default:
		break;
	}
}

void SceneManager::nextScene()
{
	switch (currentScene)
	{
	case MENU:
		switch (currentChoice)
		{
		case 0:
			currentScene = CHOOSE_BATTLE;
			menuItems[currentChoice].isHovered = false;
			currentChoice = 0;
			chooseBattleItems[currentChoice].isHovered = true;
			break;
		case 1:
			currentScene = SETTINGS;
			menuItems[currentChoice].isHovered = false;
			currentChoice = 0;
			break;
		case 2:
			*quit = true;
			break;
		default:
			break;
		}
		break;
	case CHOOSE_BATTLE:
		switch (currentChoice)
		{
		case 0:
			currentScene = BATTLE;
			battle->setup(NULL);
			music->loadAudio("assets/musics/missionobjective--1-.mp3");
			music->play();
			break;
		case 1:
			currentScene = MAP_BATTLE;
			break;
		default:
			break;
		}

		chooseBattleItems[currentChoice].isHovered = false;
		currentChoice = 1;
		break;
	case SETTINGS:
		break;
	case MAP_BATTLE:
		break;
	case BATTLE:
		break;
	default:
		break;
	}
}

void SceneManager::previousScene()
{
	switch (currentScene)
	{
	case CHOOSE_BATTLE:
		currentScene = MENU;
		chooseBattleItems[currentChoice].isHovered = false;
		currentChoice = 0;
		menuItems[currentChoice].isHovered = true;
		break;
	case SETTINGS:
		currentScene = MENU;
		currentChoice = 0;
		menuItems[currentChoice].isHovered = true;
		break;
	case MAP_BATTLE:
		currentScene = CHOOSE_BATTLE;
		currentChoice = 0;
		chooseBattleItems[currentChoice].isHovered = true;
		break;
	case BATTLE:
		break;
	default:
		break;
	}
}

void SceneManager::nextChoice()
{
	switch (currentScene)
	{
	case MENU:
		menuItems[currentChoice].isHovered = false;

		currentChoice -= 1;

		if (currentChoice < 0)
		{
			currentChoice = menuItems.size() - 1;
		}

		menuItems[currentChoice].isHovered = true;
		break;
	case CHOOSE_BATTLE:
		chooseBattleItems[currentChoice].isHovered = false;

		currentChoice -= 1;

		if (currentChoice < 0)
		{
			currentChoice = chooseBattleItems.size() - 1;
		}

		chooseBattleItems[currentChoice].isHovered = true;
		break;
	case SETTINGS:
		break;
	case MAP_BATTLE:
		currentChoice -= 1;

		if (currentChoice < 1)
		{
			currentChoice = mapBattleItems.size() - 1;
		}
		break;
	case BATTLE:
		break;
	default:
		break;
	}
}

void SceneManager::previousChoice()
{
	switch (currentScene)
	{
	case MENU:
		menuItems[currentChoice].isHovered = false;

		currentChoice += 1;

		if (currentChoice >= menuItems.size())
		{
			currentChoice = 0;
		}

		menuItems[currentChoice].isHovered = true;
		break;
	case CHOOSE_BATTLE:
		chooseBattleItems[currentChoice].isHovered = false;

		currentChoice += 1;

		if (currentChoice >= chooseBattleItems.size())
		{
			currentChoice = 0;
		}

		chooseBattleItems[currentChoice].isHovered = true;
		break;
	case SETTINGS:
		break;
	case MAP_BATTLE:
		currentChoice += 1;

		if (currentChoice >= mapBattleItems.size())
		{
			currentChoice = 1;
		}
		break;
	case BATTLE:
		break;
	default:
		break;
	}
}