#pragma once
#include "Bullet.h"
#include"eBullets.h"

class Boss
{
public:
	Boss(float speed, Texture *texture, int HP, Vector2u windowsize);
	~Boss();

	void Movement(RenderWindow *window, const float &dt);
	void Update(RenderWindow *window, const float &dt);
	void Draw(RenderWindow *window);

public:
	Sprite shape;
	Texture *texture;
	Vector2f size;
	Vector2f InitPos;
	Vector2u Texsize;

public:
	int bulletTimer;
	int HP;
	float shootTimer;
	float shootTimerMax;
	float moveTimer;
	float mult;
	bool enterScene;
	float speed;
	RectangleShape bossHP;

	inline bool IsInScene(RenderWindow *window)
	{
		if (this->shape.getPosition().x + this->shape.getGlobalBounds().width < window->getSize().x)
			return true;
		return false;
	}


};

