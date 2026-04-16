#define _CRT_SECURE_NO_WARNINGS

#include "SaveLoad.h"

void SaveLoad::savePlayer(Player* player)
{
    SDL_Log("SAVE");

    FILE* file = fopen("data/playerData.txt", "wt");

    if (!file)
    {
        SDL_Log("Cannot create file playerData.txt");
        return;
    }

    fprintf(file, "HP: %i\n", player->getHP());
    fprintf(file, "HP: %i\n", player->getScore());
    fprintf(file, "X: %.f\n", player->getDest().x);
    fprintf(file, "Y: %.f\n", player->getDest().y);

    fclose(file);
}

void SaveLoad::loadPlayer(Player* player)
{
    SDL_Log("LOAD");

    FILE* file = fopen("data/playerData.txt", "r");

    if (!file)
    {
        SDL_Log("Cannot read file playerData.txt");
        return;
    }

    char buffer[100];
    int HP;
    int score;
    float x;
    float y;

    // %*s - skip string and write only numbers
    fscanf_s(file, "%*s %d\n", &HP);
    fscanf_s(file, "%*s %d\n", &score);
    fscanf_s(file, "%*s %f\n", &x);
    fscanf_s(file, "%*s %f\n", &y);

    player->setHP(HP);
    player->setScore(score);
    player->setPosition({ x, y });
    SDL_Log("X: %f, Y: %f", x, y);

    fclose(file);
}

void SaveLoad::deletePlayerTXT()
{
    remove("data/playerData.txt");
}

void SaveLoad::saveMaxScore(Player* player)
{
    FILE* file = fopen("data/score.txt", "r");
    int oldScore = 0;

    if (file)
    {
        fscanf_s(file, "%*s %d", &oldScore);
        fclose(file);
    }

    if (player->getScore() > oldScore)
    {
        file = fopen("data/score.txt", "w");

        if (file)
        {
            fprintf(file, "SCORE: %d\n", player->getScore());
            fclose(file);
        }
    }
}

int SaveLoad::getMaxScore()
{
    FILE* file = fopen("data/score.txt", "r");
    int oldScore = 0;

    if (file)
    {
        fscanf_s(file, "%*s %d", &oldScore);
        fclose(file);
    }

    return oldScore;
}
