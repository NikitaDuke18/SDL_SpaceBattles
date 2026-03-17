#pragma once

#include "Entity.h"

class Player : protected Entity
{
public:
	Player(SDL_Renderer* renderer);
	~Player() override;

	void update() override;
	void draw(SDL_Renderer* renderer) override;

	void animationPlay();

	bool getUp() { return up; };
	void setUp(bool up) { this->up = up; };

	bool getDown() { return down; };
	void setDown(bool down) { this->down = down; };

	bool getLeft() { return left; };
	void setLeft(bool left) { this->left = left; };

	bool getRight() { return right; };
	void setRight(bool right) { this->right = right; };
private:
	
	bool up, down, left, right;
};