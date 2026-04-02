#pragma once

#include "Entity.h"
#include "Bullet.h"

class Player : public Entity
{
public:
	Player(SDL_Renderer* renderer, SDL_FPoint position, int width, int height);
	~Player() override;

	void setup();

	void update() override;
	void draw(SDL_Renderer* renderer) override;

	void animationPlay();
	bool lostHP(int damage);
	void addScore(int score);

	void shoot(SDL_Renderer* renderer, int seconds);
	void deleteBullet(int index);
	bool checkBulletOut(int index);
	bool bulletExists(int index);

	bool getUp() { return up; };
	void setUp(bool up) { this->up = up; };

	bool getDown() { return down; };
	void setDown(bool down) { this->down = down; };

	bool getLeft() { return left; };
	void setLeft(bool left) { this->left = left; };

	bool getRight() { return right; };
	void setRight(bool right) { this->right = right; };

	int getHP() { return HP; };
	int getBomb() { return bombs; };

	int getScore() { return score; };

	int getBulletsSize() { return bulletsSize; };

	SDL_FRect getBulletDest(int index) { return bullets[index]->getDest(); };

private:
	int width;
	int height;

	bool up, down, left, right;
	int HP;
	int bombs;
	int score;

	Bullet** bullets;
	int bulletsSize;
	//int numberOfShots; // сколько пуль осталось до перезарядки, на лучшие времена
};