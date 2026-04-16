#include "Player.h"

Player::Player(SDL_Renderer* renderer, SDL_FPoint position, int width, int height)
{
	this->width = width;
	this->height = height;

	texture = IMG_LoadTexture(renderer, "assets/entity/player/player_atlas.png");
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	src = {0, 0, 8, 16};
	scale = 4;
	dest = { position.x, position.y, src.w * scale, src.h * scale };
	speed = 4;
	HP = 3;
	bombs = 0;
	score = 0;

	bulletsSize = 40;
	bullets = new Bullet*[bulletsSize];
	for (int i = 0; i < bulletsSize; i++)
	{
		bullets[i] = nullptr;
	}
	//numberOfShots = 20;
}

Player::~Player()
{
	SDL_DestroyTexture(texture);

	for (int i = 0; i < bulletsSize; i++)
	{
		if (bullets[i] != nullptr)
		{
			delete bullets[i];
			bullets[i] = nullptr;
		}
	}
	delete[] bullets;
}

void Player::setup()
{
	dest.x = width / 2;
	dest.y = height / 2;
	HP = 3;
	bombs = 0;
	score = 0;

	for (int i = 0; i < bulletsSize; i++)
	{
		if (bullets[i] != nullptr)
		{
			delete bullets[i];
			bullets[i] = nullptr;
		}
	}

	//saveLoad->loadPlayer(this);
}

void Player::update()
{
	if (up) {
		dest.y -= speed;
	}
	if (down) {
		dest.y += speed;
	}
	if (left) {
		dest.x -= speed;
	}
	if (right) {
		dest.x += speed;
	}

	animationPlay();

	for (int i = 0; i < bulletsSize; i++)
	{
		if (bullets[i] != nullptr)
		{
			bullets[i]->update();

			if (checkBulletOut(i))
			{
				deleteBullet(i);
			}
		}
	}
}

void Player::draw(SDL_Renderer* renderer)
{
	SDL_RenderTexture(renderer, texture, &src, &dest);

	for (int i = 0; i < bulletsSize; i++)
	{
		if (bullets[i] != nullptr)
		{
			bullets[i]->draw(renderer);
		}
	}
}

void Player::animationPlay()
{
	if (left)
	{
		src.x = 0; // firstTexture
	}
	else if (right)
	{
		src.x = 8; // second Texture
	}
	else if (up || down)
	{
		src.x = 16; // third Texture
	}
}

bool Player::lostHP(int damage)
{
	HP -= damage;
	if (HP <= 0)
	{
		return true;
	}
	SDL_Log("HP: %i", HP);
	return false;
}

void Player::addScore(int score)
{
	this->score += score;
}

void Player::shoot(SDL_Renderer* renderer, int seconds)
{
	BulletType type;

	if (seconds < 1)
	{
		type = BULLET_1;
	}
	else if (seconds <= 1)
	{
		type = BULLET_2;
	}
	else
	{
		type = BULLET_3;
	}

	for (int i = 0; i < bulletsSize; i++)
	{
		if (bullets[i] == nullptr)
		{
			bullets[i] = new Bullet(renderer, { dest.x + dest.w / 2, dest.y }, type);
			SDL_Log("Create bullet");
			break;
		}
	}
}

void Player::deleteBullet(int index)
{
	if (bullets[index] != nullptr)
	{
		delete bullets[index];
		bullets[index] = nullptr;
	}
}

bool Player::checkBulletOut(int index)
{
	if (bullets[index]->getDest().y < 0 - bullets[index]->getDest().h)
	{
		return true;
	}
	return false;
}

bool Player::bulletExists(int index)
{
	if (bullets[index] != nullptr)
	{
		return true;
	}
	return false;
}
