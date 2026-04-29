#pragma once

#include <cstdio>
#include <cstring>
#include "Player.h"

class SaveLoad
{
public:
	//void savePlayer(Player* player);
	//void loadPlayer(Player* player);
	//void deletePlayerTXT();

	void saveMaxScore(Player* player);
	int getMaxScore();
private:

};

