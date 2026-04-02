#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>

#include "Battle.h"

enum Scene
{
	MENU,
	CHOOSE_BATTLE,
	SETTINGS,
	MAP_BATTLE,
	BATTLE
};

struct TextItem {
	std::string text;
	SDL_Texture* texture = nullptr;
	SDL_FRect dest;
	bool isHovered = false;
};

class SceneManager
{
public:
	SceneManager(SDL_Renderer* renderer, TTF_Font* font, bool* quit, int width, int height, Scene scene, Battle* battle);
	~SceneManager();

	void setupItems(SDL_Renderer* renderer, TTF_Font* font, int width, int height);

	void update();
	void draw(SDL_Renderer* renderer);

	void changeScene(Scene scene);
	void nextScene();
	void previousScene();
	
	void nextChoice();
	void previousChoice();

	Scene getCurrentScene() { return currentScene;  };

private:
	Scene currentScene;
	Battle* battle;

	TTF_Font* font;
	SDL_Color textColorWhite;
	SDL_Surface* textSurface;
	//SDL_Texture* textTexture;
	SDL_FRect textDest;

	std::vector<TextItem> menuItems = {
		{"PLAY"},
		{"SETTINGS"},
		{"QUIT"}
	};

	std::vector<TextItem> chooseBattleItems = {
		{"INFINITY"},
		{"LEVELS"}
	};

	std::vector<TextItem> settingsItems = {
		{"UP - W"},
		{"DOWN - S"},
		{"LEFT - A"},
		{"RIGHT - D"},
		{"SHOOT - ENTER"},
		{"PAUSE - K"}
	};

	std::vector<TextItem> mapBattleItems = {
		{"LEVELS: "},
		{"1"},
		{"2"},
		{"3"},
		{"4"}
	};

	int currentChoice;

	bool* quit;
};

